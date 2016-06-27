#include"PositionTree.h"

int conv(char c)
{
	if(c >= 'a' && c <= 'z')
		return c - 'a' + 1;

	else if(c >= 'A' && c <= 'Z')
		return c - 'A' + 1;

	else if(c == '?')
		return 0;

	else if(c == '\0')
		return numLetter;

	else
		return numLetter-1;
}

item* newItem(item *T, item *A, char t, char a, int leaf)
{
	item *temp = (item *)malloc(sizeof(item));
	//temp -> B = (char *)calloc(, sizeof(char));
	temp -> T_son_list = (item **)calloc(numLetter, sizeof(item*));
	temp -> A_son_list = (item **)calloc(numLetter, sizeof(item*));

	temp -> T_parent = T;
	temp -> A_parent = A;

	temp -> T_edge = t;
	temp -> A_edge = a;
	
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
	
	return temp;
}

void case2helper(char *c, item *u, item **dla, int index, int depth, int i)
{
	static item *v;
	static int k;
	int l1, l2;
	if(u -> A_son_list[index] == NULL)
		case2helper(c, u -> T_parent,dla, index, depth+1, i);
	else
	{
		v = u -> A_son_list[index];
		k = v -> ifleaf;
		v -> ifleaf = 0;
		dla[k] = NULL;
		return;
	}

	l1 = conv(u->T_edge);								//C1~Cq

	v -> T_son_list[l1] = u -> A_son_list[index] = newItem(v, u, u -> T_edge, c[i-1], 0);
	//making new Vh+1 under Vh
	memcpy(v -> T_son_list[l1] -> B, v -> B, numLetter);					//Copy B

	v = v -> T_son_list[l1];							//Now goes to V from Vparent
	

	if(depth == 0)
	{
		//printf("%d %c %c\n",i, c[i + u->T_depth], c[k + u->T_depth]);
		l1 = conv( c[ i + u->T_depth] );
		dla[i]=
		v -> T_son_list[l1]=
		u -> T_son_list[l1] -> A_son_list[index]=
		newItem(v, u->T_son_list[l1], c[ i + u->T_depth], c[i-1], i);
		
		l2 = conv( c[ k + u->T_depth] );
		dla[k] = 
		v -> T_son_list[l2] = 
		u -> T_son_list[l2] -> A_son_list[index] = 
		newItem(v, u->T_son_list[l2], c[ k + u->T_depth], c[i-1], k);
		memcpy(v->T_son_list[l2]->B, v->B, numLetter);
	}
}

void case3_helper(char *c, item *u, item **dla, int index, int i)
{
	int l1, l2;
	item *v = u -> A_son_list[index];
	int k = v->ifleaf;
	v->ifleaf = 0;
	//printf("%d %d\n", index, k);
	
	l1 = conv( c[ i + u->T_depth] );
	dla[i]=
	v -> T_son_list[l1]=
	u -> T_son_list[l1] -> A_son_list[index]=
	newItem(v, u->T_son_list[l1], c[ i + u->T_depth], c[i-1], i);
		
	l2 = conv( c[ k + u->T_depth] );
	dla[k]=
	v -> T_son_list[l2]=
	u -> T_son_list[l2] -> A_son_list[index]=
	newItem(v, u->T_son_list[l2], c[ k + u->T_depth], c[i-1], k);
	memcpy(v->T_son_list[l2]->B, v->B, numLetter);
	
}

void case4_helper(char *c, item *u, item **dla, int index, int i)
{
	int l1;
	item *v = u -> A_son_list[index];
	//int k = v->ifleaf;

	l1 = conv( c[ i + u->T_depth] );
	dla[i]=
	v -> T_son_list[l1]=
	u->T_son_list[l1]->A_son_list[index]=
	newItem(v, u->T_son_list[l1], c[ i + u->T_depth], c[i-1], i);
		
}

void PositionTree(item *root, item **dla, char *x,int end)
{
	char c;
	int index;
	int i, k;
	item *temp = NULL;
	int m;

	temp = NULL;
	

	for(k=end-2; k>=0; k--)
	{
		c = x[k];
		index = conv(c);
		i = k+1;
		temp = dla[i+1];
		m=0;
		while(temp != NULL &&temp->B[index] != 1)	//find uy
		{
			temp->B[index] = 1;
			temp = temp->T_parent;
			m++;
		}
		
		if(temp == NULL)			//Case 1
		{
			root -> B[index] = 1;
			dla[i] = root -> T_son_list[index] = root->A_son_list[index] = newItem(root, root, c, c, i);
			//printf("%d: Case 1\n", i);
		}
		
		else if(temp->A_son_list[index] == 0)	//Case 2
		{
			case2helper(x, temp, dla, index, 0, i);			
			//printf("%d: Case 2\n", i);
		}

		else if(temp -> A_son_list[index] -> ifleaf != 0)	//case 3 a)
		{
			case3_helper(x, temp, dla, index, i);
			//printf("%d: Case 3_a)\n", i);
		}
		else							//case 3 b)
		{
			case4_helper(x, temp, dla, index, i);
			//printf("%d: Case 3_b)\n", i);
		}
			
		
	}
}
void recur(item * temp)		//traverse the tree from the bottom, which is leaf, to top.
{
	if(temp -> T_parent == NULL && temp -> A_parent == NULL)
		return;
	else
		recur(temp -> T_parent);
	printf("%c", temp->T_edge);
}
