#include "CompressedPositionTree.h"
/*
void setConverter()
{
	int i;
	for(i=0;i<10;i++)
		conv['0' + i] = i;
	for(i=0;i<26;i++)
		conv['a' + i] = conv['A' + i] = i + 10;
	conv[' '] = 36;
	conv[','] = 37;		conv['.'] = 38;
	conv[39]  = 39;		conv[34]  = 40;		// ' & "
	conv['-'] = 41;
	conv['!'] = 42;
	
	conv['('] = 43;		conv[')'] = 44;		conv['['] = 45;		conv[']'] = 46;		conv['<'] = 47;		conv['>'] = 48;
	
	conv[':'] = 49;		conv[';'] = 50;
	conv['$'] = numLetter-1;
}
*/
item* newItem(item *T, item *A, char t, char a, int leaf)
{
	item *temp = (item *)malloc(sizeof(item));
	temp -> B = (char *)calloc(numLetter, sizeof(char));
	temp -> T_son_list = (item **)calloc(numLetter, sizeof(item*));		temp -> A_son_list = (item **)calloc(numLetter, sizeof(item*));
	temp -> T_parent = T;							temp -> A_parent = A;
	temp -> T_edge = t;							temp -> A_edge = a;
		
	if(temp -> T_parent == NULL && temp -> A_parent == NULL)
	{
		temp -> T_depth = 0;
		temp -> A_depth = 0;
	}
	else
	{
		temp -> T_depth = temp->T_parent->T_depth + 1;
		temp -> A_depth = temp->A_parent->A_depth + 1;
	}
	
	temp -> ifleaf = leaf;

	temp -> substring = NULL;
	temp -> ifsub = 0;

	numVertex++;

	return temp;
}

int recur(FILE *out, item * temp, int depth)
{
	int d;
	if(temp -> T_parent == NULL)	// || temp -> A_parent == NULL
	{
		//printf("%d ", depth);
		return 0;
	}
	else
		d = recur(out, temp -> T_parent, depth+1)+1;
	
	fprintf(out, "%c", temp->T_edge);
	if( temp -> ifsub != 0)
		fprintf(out, "%s", temp ->substring);

	return d;

}

void case2helper(char *x, item *u, item **dla, int depth, int i, int subsize)
{
	static item *v = NULL;
	static int k;
	static int z=0;
	int l1, l2, index = x[i-1];

//We must be able to find a leaf!
	if(u -> A_son_list[index] == NULL ||						//From Case 2
		u -> A_son_list[index] -> T_depth < u -> T_depth +1 - u->ifsub){	//From Case 3&4 

		numCase2++;
		v = u -> A_son_list[index];
		case2helper(x, u -> T_parent,dla, depth+1, i, subsize + 1+u->ifsub);
	}
	
	else
	{
		if(v != NULL && v != u -> A_son_list[index])
		{
			if(v == u -> A_son_list[index] -> T_parent)
				printf("Yes: previous case:%d\n", kbyk[i+1]);
			else
				printf("No\n");
		}
		//	printf("depth of v:%d\t v1:%d\n", v -> T_depth, u->A_son_list[index]->T_depth);
		//	printf("v changed in case2: %d %d\n", v-> T_depth, v->A_parent->T_depth);
		v = u -> A_son_list[index];
		k = v -> ifleaf;
		dla[k] = NULL;
		v -> ifleaf = 0;

		if(u -> ifsub != 0)
		{
			v -> substring = (char*)calloc(subsize+ u->ifsub + 1, sizeof(char));
			strcpy(v -> substring, u -> substring);
			v -> ifsub += u -> ifsub;
			v -> T_depth += u -> ifsub;
		}
		else
			v -> substring = (char*)calloc(subsize+ 1, sizeof(char));

		return;
	}

	l1 = u->T_edge;									//C1~Cq

//Original
/*
	//v -> T_son_list[l1] = u -> A_son_list[index] = newItem(v, u, u -> T_edge, c[i-1], 0);
	//making new Vh+1 under Vh
	//memcpy(v -> T_son_list[l1] -> B, v -> B, numLetter);					//Copy B

	//v = v -> T_son_list[l1];							//Now goes to V from Vparent
*/

//Compressed

	u -> A_son_list[index] = v;
	v -> substring[ v->ifsub ] = u->T_edge;
	v -> ifsub++;
	v -> T_depth++;
	if(u -> ifsub != 0)
	{
		v -> ifsub += u -> ifsub;
		v -> T_depth += u -> ifsub;
		strcat(v -> substring, u -> substring);		
	}

	if(depth == 0)
	{
		v -> A_parent = u;
				
		l1 = x[ i + u->T_depth];
		dla[i]=	v -> T_son_list[l1]=
			u -> T_son_list[l1] -> A_son_list[index]=
				newItem(v, u->T_son_list[l1], x[ i + u->T_depth], x[i-1], i);

		l2 = x[ k + u->T_depth];
		dla[k]=	v -> T_son_list[l2] =
			u -> T_son_list[l2] -> A_son_list[index] =
				newItem(v, u->T_son_list[l2], x[ k + u->T_depth], x[i-1], k);
		memcpy(v->T_son_list[l2]->B, v->B, numLetter);
		v = NULL;
	}
}

void case3helper(char *x, item *u, item **dla, int i)
{
	int l1, l2, depth_diff, index = x[i-1];
	item *v = u -> A_son_list[index];
	int k = v->ifleaf;
	char *sub = NULL;

	dla[k] = NULL;
	v->ifleaf = 0;

	depth_diff = u -> T_depth + 1 - v -> T_depth;
	
	if( depth_diff > 0)	//Then, u -> ifsub > 0
	{
		v -> substring = (char*)calloc(depth_diff + 1, sizeof(char));		// size was u -> ifsub + 1;
		strncat(v -> substring, &(u -> substring[u->ifsub - depth_diff]), depth_diff);
		v -> T_depth += depth_diff;
		v -> ifsub += depth_diff;
	}

	l1 = x[ i + u->T_depth];
	dla[i]=	v -> T_son_list[l1]=
		u -> T_son_list[l1] -> A_son_list[index]=
			newItem(v, u->T_son_list[l1], x[ i + u->T_depth], x[i-1], i);
		
	l2 = x[ k + u->T_depth];
	dla[k]=	v -> T_son_list[l2]=
		u -> T_son_list[l2] -> A_son_list[index]=
			newItem(v, u->T_son_list[l2], x[ k + u->T_depth], x[i-1], k);
	memcpy(v->T_son_list[l2]->B, v->B, numLetter);
	
}

void case4helper(char *x, item *u, item **dla, int i)
{
	int l1, l2, depth_diff, index = x[i-1];
	item *v = u -> A_son_list[index];
	item *temp, *temp2;
	char *cat;
	
	l1 = x[ i + u->T_depth];
	if(u -> T_son_list[l1] == NULL)
	{
		printf("u' does not exist\n");
		printf("%d %c\n", u->T_depth, x[ i + u->T_depth]);
		exit(0);
	}
	depth_diff = u->T_depth+1 - v->T_depth;
	// v -> T_depth = ~~~ + v -> ifsub

	if(depth_diff < 0)		//Assumption: v -> ifsub != 0 && v -> ifsub >= depth_diff
	{
		
		temp =	u -> A_son_list[index] =
			v -> T_parent -> T_son_list[ v -> T_edge ] =
				newItem(v -> T_parent, u, v -> T_edge, x[i-1], 0);

		if( v-> ifsub + depth_diff > 0)
		{
			temp -> ifsub = v -> ifsub + depth_diff;
			temp -> substring = (char*)calloc(temp -> ifsub +1, sizeof(char));
			strncpy(temp -> substring, v -> substring, temp -> ifsub);
		}

		l2 = v -> substring[ v-> ifsub + depth_diff];

// copying v->A_son_list to temp->A_son_list might be dangerous because of depth difference between them.
		temp -> T_son_list[ l2 ] =
		u -> T_son_list[l2] -> A_son_list[index] =  v;
		memcpy(temp -> B, v -> B, numLetter);
		memcpy(temp -> A_son_list, v -> A_son_list, numLetter*sizeof(item*));


//B????
		temp -> T_depth = v -> T_parent -> T_depth + temp -> ifsub + 1;
		v -> T_parent = temp;
		v -> T_edge = v -> substring[v -> ifsub + depth_diff];
		v -> A_parent = u -> T_son_list[ l2 ];
		v -> A_edge = x[i-1];

		if(depth_diff < -1)
		{
			cat = (char*)calloc( (-1)*depth_diff, sizeof(char));
			strncpy( cat, &(v -> substring[ v-> ifsub + depth_diff +1]), (-1)*depth_diff-1);
			free(v -> substring);
			v -> substring = cat;
			v -> ifsub = (-1)*depth_diff-1;
		}
		else
		{
			v -> ifsub =0;
			free( v-> substring);
		}

//Shifting
		//printf("In Case4: ");
		temp2 = u -> T_parent;
		
		while(temp2 != NULL && temp2 -> A_son_list[index] == v)
		{
			//printf("Shift ");
			shifting++;
			temp2 -> A_son_list[index] = temp;
			temp2 = temp2->T_parent;
		}
		//printf("\n");
		
		v = temp;

	} 
	
	dla[i]=	v -> T_son_list[l1] =
		u->T_son_list[l1]->A_son_list[index] =
			newItem(v, u->T_son_list[l1], x[ i + u->T_depth], x[i-1], i);

}

item* CompressedPositionTree(char *x, FILE *out)
{
	item *root, *temp;
	item **dla;
	char c;
	int end, index;
	int i, j, k;

	if(x[strlen(x)-1] == '\n')
		x[strlen(x)-1] = NULL;
	strcat(x, "$");
	end = strlen(x);
	printf("Length of the input: %d\n", end);		//printf("%s\n", x);
	
/* Converter setting for B
	for(i=0;i<256;i++)
		conv[i] = numLetter-1;
	setConverter();
*/

// Direct Leaf Access Setting
	dla = (item **)calloc(end, sizeof(item*));

// Root and Tn+1 An+1 Setting
	root = newItem(NULL, NULL, '\0', '\0', 0);
	root->B['$'] = 1;

	dla[end] =	root->T_son_list['$'] =
			root->A_son_list['$'] =
				newItem(root, root, '$', '$', end);
	
	temp = NULL;
	
	for(k=end-2; k>=0; k--)
	{
		c = x[k];			//c = ai
		//index = conv[c];		index of ai
		i = k+1;
		temp = dla[i+1];		// leaf i+1
		//printf("%d_", i);
		
		while(temp != NULL && temp->B[c] != 1)	//Finding Uy
		{
			temp -> B[c] = 1;
			temp = temp->T_parent;
		}
		

		if(temp == NULL)			//Case 1
		{
			kbyk[i] = 1;
			root -> B[c] = 1;
			dla[i] = root -> T_son_list[c] = root->A_son_list[c] = newItem(root, root, c, c, i);
		}
		
		//Case 2
		else if(temp->A_son_list[c] == NULL ||
			temp -> A_son_list[c] -> T_depth < temp -> T_depth + 1 - temp -> ifsub)			{
			kbyk[i] = 2;
			case2helper(x, temp, dla, 0, i, 0);
		}			

		else if(temp -> A_son_list[c] -> ifleaf != 0)	//case 3
		{
			kbyk[i] = 3;		
			case3helper(x, temp, dla, i);
		}
		
		else							//case 4
		{
			kbyk[i] = 4;
			case4helper(x, temp, dla, i);
		}
	}
/*	Printing All substring identfiers in the text(input)
	for comparing the result with Original Position Tree
	for(i = end; i>=1; i--)
	{
		fprintf(out, "dla[%3d] = ", i);
		k=recur(out, dla[i], 0);
		if(k>maxDepth)
			maxDepth=k;
		fprintf(out, "\n");
		
	}
*/
	return root;
}



