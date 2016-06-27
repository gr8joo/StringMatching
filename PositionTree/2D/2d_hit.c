#include "StringMatcher2D.h"

void main()
{
	FILE *in = fopen("input.txt", "rt");

	char **Text, **Pattern;
	char *x, *temp;
	int Tn, Tm, Pn, Pm;

	item *root;
	item **dla;
	int i, j, end;

	int *check;
	int *valid;
	int *saver;
	int *min;
	//int neg=0;

	fscanf(in, "%d %d ", &Tn, &Tm);
	fscanf(in, "%d %d ", &Pn, &Pm);

//setting 2-dim Text and 1-dim x
	Text = (char **)calloc( Tn+2*Pn, sizeof(char*));
	x = (char *)calloc( (Tn + 2*Pn) * (Tm + 2*Pm) +2, sizeof(char));

	for(i=0;i<Pn;i++)
	{
		Text[i] = (char *)calloc(Tm + 2*Pm +1, sizeof(char));
		for(j=0;j<Tm + 2*Pm;j++)
			Text[i][j] = '?';
		strcat(x, Text[i]);
	}
	for(i=Pn;i<Tn+Pn;i++)
	{
		temp = (char *)calloc(Tm +1, sizeof(char));
		Text[i] = (char *)calloc(Tm + 2*Pm +1, sizeof(char));
		fscanf(in, "%s", temp);
		for(j=0;j<Pm;j++)
			Text[i][j] = '?';
		strcat(Text[i], temp);
		for(j=Tm + Pm;j<Tm + 2*Pm;j++)
			Text[i][j] = '?';

		strcat(x, Text[i]);
		free(temp);
		
	}
	for(i=0;i<Pn;i++)
	{
		Text[Tn+Pn+i] = (char *)calloc(Tm + 2*Pm +1, sizeof(char));
		for(j=0;j<Tm + 2*Pm;j++)
			Text[Tn+Pn+i][j] = '?';
		strcat(x, Text[Tn+Pn+i]);
	}
	printf("Expanded Text:\n");
	for(i=0;i<Tn+2*Pn;i++)
		printf("%s\n", Text[i]);

//Setting 2-dim Pattern	
	Pattern = (char **)calloc(Pn, sizeof(char*));
	for(i=0;i<Pn;i++)
	{
		Pattern[i] = (char *)calloc(Pm, sizeof(char));
		fscanf(in, "%s", Pattern[i]);
	}

	printf("\nOriginal Pattern:\n");
	for(i=0;i<Pn;i++)
		printf("%s\n", Pattern[i]);

//Setting check(# of rows at each position in Text), valid(# of valid hit at each position in Text), saver(position saver), min(optimized accumulation info)
	check = (int *)calloc( (Tn + 2*Pn) * (Tm + 2*Pm) +1, sizeof(int));
	valid = (int *)calloc( (Tn + 2*Pn) * (Tm + 2*Pm) +1, sizeof(int));
	saver = (int *)calloc( (Tn + 2*Pn) * (Tm + 2*Pm) +1, sizeof(int));
	min = (int *)calloc( 8, sizeof(int));

	Tn += 2*Pn;
	Tm += 2*Pm;
	
	min[0] = Tn*Tm+1;
//	printf("min[0] = %d\n", min[0]);
//String Setting
	strcat(x, "$");
	end = strlen(x);
	
//Direct Leaf Access Setting
	dla = (item **)calloc(end, sizeof(item*));

//Root and Tn+1 An+1 Setting
	root = newItem(NULL, NULL, '\0', '\0', 0);
	root->B[conv('$')] = 1;

	dla[end] = root->T_son_list[conv('$')] = root->A_son_list[conv('$')]
		= newItem(root, root, '$', '$', end);

	PositionTree(root, dla, x, end);
	

	for(i=0;i<Pn;i++)
		StringMatcher(x, Pattern[i], root, 0, check, valid, saver, min, i, Tn, Tm, Pn, Pm, 0);			//Compare pattern with text
/*Saver saves all possilbe occurence of pattern in text but what we need is only the best option in terms of size. So, do not need to sort them			
	for(i=1;i<=saver[0];i++)
		for(j=i+1;j<=saver[0];j++)
			if(saver[i]>saver[j])
			{		
				end=saver[i];
				saver[i] = saver[j];
				saver[j] = end;
			}



	for(i=1;i<=saver[0];i++)
//		printf("%d\n", saver[i]);
		printf("%d %d\n", (saver[i]-1)/Tm+1, (saver[i]-1)%Tm+1);
*/
	printf("\nAccumulated Text: (following position numbers are in terms of expanded Text!)\n");
	for(i=0;i<Pn;i++)
		for(j=0;j<Pm;j++)
		{
			if(Pattern[i][j] != '?')
				Text[i+min[5]-1][j+min[6]-1] = Pattern[i][j];
		}
	for(i=min[1]-1;i<min[2];i++)
	{
		for(j=min[3]-1;j<min[4];j++)
		{
			if(Text[i][j] == '?')
				printf(" ");
			else
				printf("%c", Text[i][j]);
		}
		printf("\n");
	}
	printf("Maximum hit: %d\n", min[7]);
	printf("size: %d\n", min[0]);
	printf("Begining of row: %d\n", min[1]);
	printf("End of row: %d\n", min[2]);
	printf("Begining of column: %d\n", min[3]);
	printf("End of column: %d\n", min[4]);
	printf("Px: %d\n", min[5]);
	printf("Py: %d\n", min[6]);

//	Memory Fresher
	//Text = (char **)calloc(Tn, sizeof(char*));
	//x = (char *)calloc(Tn*Tm+2, sizeof(char));
	//check = (int *)calloc(Tn*Tm+1, sizeof(int));
	for(i=0;i<Tn;i++)
		free(Text[i]);// = (char *)calloc(Tm, sizeof(char));
	free(Text);

	for(i=0;i<Pn;i++)
		free(Pattern[i]);// = (char *)calloc(Pm, sizeof(char));
	free(Pattern);



}







