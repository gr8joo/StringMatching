#include "StringMatcher3D.h"
	
void main()
{
	FILE *in = fopen("input.txt", "rt");

	char ***Text, ***Pattern;
	char *x, *temp;
	int Tn, Tm, Pn, Pm;
	int Tl, Pl;	//Plane
	item *root;
	item **dla;
	int l, i, j, end;

	int *check;
	int *valid;
	int *saver;
	int *min;
	//int neg=0;

	fscanf(in, "%d %d %d ", &Tl, &Tn, &Tm);
	fscanf(in, "%d %d %d ", &Pl, &Pn, &Pm);

//setting 3-dim expanded Text and 1-dim x
	Text = (char ***)calloc( Tl+2*Pl, sizeof(char**));
	x = (char *)calloc( (Tl + 2*Pl) * (Tn + 2*Pn) * (Tm + 2*Pm) +2, sizeof(char));

	for(l=0;l<Pl;l++)
	{
		Text[l] = (char **)calloc( Tn + 2*Pn, sizeof(char*));
		for(i=0; i < Tn + 2*Pn;i++)
		{
			Text[l][i] = (char *)calloc(Tm + 2*Pm +1, sizeof(char));
			for(j=0;j<Tm + 2*Pm;j++)
				Text[l][i][j] = '?';
			strcat(x, Text[l][i]);
		}
	}
	for(l=Pl;l<Tl+Pl;l++)
	{
		Text[l] = (char **)calloc( Tn + 2*Pn, sizeof(char*));
		for(i=0;i<Pn;i++)
		{
			Text[l][i] = (char *)calloc(Tm + 2*Pm +1, sizeof(char));
			for(j=0;j<Tm + 2*Pm;j++)
				Text[l][i][j] = '?';
			strcat(x, Text[l][i]);
		}
		for(i=Pn;i<Tn+Pn;i++)
		{
			temp = (char *)calloc(Tm +1, sizeof(char));
			Text[l][i] = (char *)calloc(Tm + 2*Pm +1, sizeof(char));
			fscanf(in, "%s", temp);
			for(j=0;j<Pm;j++)
				Text[l][i][j] = '?';
			strcat(Text[l][i], temp);
			for(j=Tm + Pm;j<Tm + 2*Pm;j++)
				Text[l][i][j] = '?';

			strcat(x, Text[l][i]);
			free(temp);
		}
		for(i=0;i<Pn;i++)
		{
			Text[l][Tn+Pn+i] = (char *)calloc(Tm + 2*Pm +1, sizeof(char));
			for(j=0;j<Tm + 2*Pm;j++)
				Text[l][Tn+Pn+i][j] = '?';
			strcat(x, Text[l][Tn+Pn+i]);
		}
	}
	for(l=Tl+Pl;l<Tl+2*Pl;l++)
	{
		Text[l] = (char **)calloc( Tn + 2*Pn, sizeof(char*));
		for(i=0;i<Tn+2*Pn;i++)
		{
			Text[l][i] = (char *)calloc(Tm + 2*Pm +1, sizeof(char));
			for(j=0;j<Tm + 2*Pm;j++)
				Text[l][i][j] = '?';
			strcat(x, Text[l][i]);
		}
	}
	printf("Expanded Text:\n");
	for(l=0;l<Tl+2*Pl;l++)
	{
		for(i=0;i<Tn+2*Pn;i++)
			printf("%s\n", Text[l][i]);
		printf("\n");
	}

//Setting 3-dim Pattern	
	Pattern = (char ***)calloc(Pl, sizeof(char**));
	for(l=0;l<Pl;l++)
	{
		Pattern[l] = (char **)calloc(Pn, sizeof(char*));
		for(i=0;i<Pn;i++)
		{
			Pattern[l][i] = (char *)calloc(Pm, sizeof(char));
			fscanf(in, "%s", Pattern[l][i]);
		}
	}

	printf("\nOriginal Pattern:\n");
	for(l=0;l<Pl;l++)
	{
		for(i=0;i<Pn;i++)
			printf("%s\n", Pattern[l][i]);
		printf("\n");
	}

//Setting check(# of rows at each position in Text), valid(# of valid hit at each position in Text), saver(position saver), min(optimized accumulation info)
	check = (int *)calloc( (Tl + 2*Pl) * (Tn + 2*Pn) * (Tm + 2*Pm) +1, sizeof(int));
	valid = (int *)calloc( (Tl + 2*Pl) * (Tn + 2*Pn) * (Tm + 2*Pm) +1, sizeof(int));
	saver = (int *)calloc( (Tl + 2*Pl) * (Tn + 2*Pn) * (Tm + 2*Pm) +1, sizeof(int));
	min = (int *)calloc( 11, sizeof(int));

	Tl += 2*Pl;
	Tn += 2*Pn;
	Tm += 2*Pm;
	
	min[0] = Tl*Tn*Tm+1;
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
	
//Matching
	for(l=0;l<Pl;l++)
		for(i=0;i<Pn;i++)
			stringMatcher(x, Pattern[l][i], root, 0, check, valid, saver, min, l, i, Tl, Tn, Tm, Pl, Pn, Pm, 0);		//Compare pattern with text

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
	for(l=0;l<Pl;l++)
		for(i=0;i<Pn;i++)
			for(j=0;j<Pm;j++)
			{
				if(Pattern[l][i][j] != '?')
					Text[l+min[7]-1][i+min[8]-1][j+min[9]-1] = Pattern[l][i][j];
			}
	for(l=min[1]-1;l<min[2];l++)
	{
		for(i=min[3]-1;i<min[4];i++)
		{
			for(j=min[5]-1;j<min[6];j++)
			{
				//if(Text[l][i][j] == '?')
				//	printf(" ");
				//else
					printf("%c", Text[l][i][j]);
			}
			printf("\n");
		}
		printf("\n");		
	}
	printf("Maximum hit: %d\n", min[10]);
	printf("size: %d\n", min[0]);
	printf("Beginning of plane: %d\n", min[1]);
	printf("End of plane: %d\n", min[2]);
	printf("Beginning of row: %d\n", min[3]);
	printf("End of row: %d\n", min[4]);
	printf("Beginning of column: %d\n", min[5]);
	printf("End of column: %d\n", min[6]);
	printf("Matching position(z,x,y): (%d, %d, %d)\n", min[7], min[8], min[9]);

/*	Memory Fresher
	//Text = (char **)calloc(Tn, sizeof(char*));
	//x = (char *)calloc(Tn*Tm+2, sizeof(char));
	//check = (int *)calloc(Tn*Tm+1, sizeof(int));
	for(i=0;i<Tl;i++)
		free(Text[i]);// = (char *)calloc(Tm, sizeof(char));
	free(Text);

	for(i=0;i<Pl;i++)
		free(Pattern[i]);// = (char *)calloc(Pm, sizeof(char));
	free(Pattern);
*/
/*
	for(l=0;l<Tl;l++)
	{
		for(i=0;i<Tn;i++)
		{
			for(j=0;j<Tm;j++)
				printf("%c", Text[l][i][j]);
			printf("\t");
			for(j=0;j<Tm;j++)
				printf("%d ", check[l*Tn*Tm + i*Tm + j +1]);
			printf("\t");
			for(j=0;j<Tm;j++)
				printf("%d", valid[l*Tn*Tm + i*Tm + j +1]);
			printf("\n");
		}
		printf("\n");
	}
*/
}








