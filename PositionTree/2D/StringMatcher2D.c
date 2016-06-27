#include "StringMatcher2D.h"

int* sizer(int Tn, int Tm, int Pn, int Pm, int x, int y, int totalHit)
{
	int n = Tn - 2*Pn;
	int m = Tm - 2*Pm;
	int *array = (int *)calloc(8, sizeof(int));

	if(x <= Pn){
		n += Pn - x +1;
		array[1] = x;
	}
	else
		array[1] = Pn+1;
	
	if(x+Pn-1 > Tn-Pn){
		n += x - Tn + 2*Pn -1;
		array[2] = x+Pn-1;
	}
	else
		array[2] = Tn - Pn;
//----------------------------------------------------
	if(y <= Pm){
		m += Pm - y +1;
		array[3] = y;
	}
	else
		array[3] = Pm+1;
	
	if(y+Pm-1 > Tm-Pm){
		m += y - Tm + 2*Pm -1;
		array[4] = y+Pm-1;
	}
	else
		array[4] = Tm - Pm;
	
	array[5] = x;
	array[6] = y;
	array[0]=n*m;
	array[7] = totalHit;
	//printf("%d ", n*m);
	return array;	
}	
	

void sweeper(item *v, int *check, int*valid, int *saver, int *min, int row, int Tn, int Tm, int Pn, int Pm, int hit)					//Search all leaves accessible under the current node
{
	int i, leaf = v->ifleaf;
	item *temp;
	int *array;
	int realPos;
	if(leaf !=0)
	{
		//printf("%d(pattern$) ", leaf);
		realPos = leaf- (row*Tm);
		if(realPos > 0 && (realPos-1)%Tm+Pm<=Tm)
		{
			valid[realPos] += hit;
			check[realPos]++;			
			if(check[realPos] == Pn)
			{
				saver[++saver[0]] = leaf - (row*Tm);
				array = sizer(Tn, Tm, Pn, Pm, (realPos-1)/Tm + 1, (realPos-1)%Tm + 1, valid[realPos]);
				if(min[7] < array[7] || (min[7] == array[7] && min[0]>array[0]))
				{
					min[0] = array[0];
					min[1] = array[1];
					min[2] = array[2];
					min[3] = array[3];
					min[4] = array[4];
					min[5] = array[5];
					min[6] = array[6];
					min[7] = array[7];
				}
				free(array);
			}
		}
		
		return;
	}
	for(i=0;i<=numLetter-1;i++)
	{
		temp = v->T_son_list[i];
		if(temp != NULL)
			sweeper(temp, check, valid, saver, min, row, Tn, Tm, Pn, Pm, hit);
	}
}
	
void StringMatcher(char *text, char *pattern, item *v, int depth, int *check, int *valid, int *saver, int *min, int row, int Tn, int Tm, int Pn, int Pm, int hit)//With completed position tree, compare pattern with text
{
	int index = conv(pattern[depth]);
	int leaf = v->ifleaf;	
	item *temp;
	item *wildcard;
	item *endmark;
	int i, end, realPos;
	char c, d;
	int *array;

	//printf("%d", len);

	if(leaf != 0)						//at the position identifier
	{
		end = strlen(text) - (leaf + depth);
		if(end > strlen(pattern) - depth)
			end = strlen(pattern) - depth;
		//printf("%d %d %d \n", strlen(text) - (leaf + depth), strlen(pattern) - depth, end);
		for(i=0;i<end;i++)
		{
			c = text[leaf+depth+i-1];
			d = pattern[depth+i];
			//printf("%c %c // ", c, d);
			if(c != '?' && d != '?' && c != d)
				return;
			else if(c != '?' && c == d)
				hit++;
		}
		
		
		c = text[leaf+depth+i-1];
		d = pattern[depth+i];
		if(d == '\0'){					//if the pattern is within the text
			//printf("(pattern$) ");			//pattern expired earlier than text (or at the same time)
			//printf("%d", leaf);
			realPos = leaf - (row*Tm);
			if(realPos > 0 && (realPos-1)%Tm+Pm<=Tm)
			{
				valid[realPos] += hit;
				check[realPos]++;			
				if(check[realPos] == Pn)
				{
					saver[++saver[0]] = leaf - (row*Tm);
					array = sizer(Tn, Tm, Pn, Pm, (realPos-1)/Tm + 1, (realPos-1)%Tm + 1, valid[realPos]);
					if(min[7] < array[7] || (min[7] == array[7] && min[0]>array[0]))
					{
						min[0] = array[0];
						min[1] = array[1];
						min[2] = array[2];
						min[3] = array[3];
						min[4] = array[4];
						min[5] = array[5];
						min[6] = array[6];
						min[7] = array[7];
					}
					free(array);
				}
			}
		}
		else{						//else if the text expired earlier than pattern
			//printf("(text$) ");
		}
		return;
	}

	else if(index == numLetter)					//pattern reached end
	{
		//printf("depth before sweep: %d\n", depth);
		sweeper(v, check, valid, saver, min, row, Tn, Tm, Pn, Pm, hit);					//Find all possible cases when pattern reached end
	}
	else if(pattern[depth] == '?')				// if the char of the current node is '?', 
	{
		for(i=0;i<=numLetter-2;i++)			// then go through all the edges labeled with regular letter.
		{
			temp = v->T_son_list[i];
			if(temp != NULL)
				StringMatcher(text, pattern, temp, depth+1, check, valid, saver, min, row, Tn, Tm, Pn, Pm, hit);
		}
		/*
		endmark = v->T_son_list[numLetter-1];	// [ conv('$') ]
		if(endmark != NULL && depth != 0){
			//printf("%d(text$) ", endmark->ifleaf);
			if(++check[endmark->ifleaf - (row*col)] == max)
				saver[++saver[0]] = endmark->ifleaf - (row*col);
		}*/		
	}
		
	else							//regular case
	{
		temp = v->T_son_list[index];
		wildcard = v->T_son_list[0];	// [ conv('?') ]

		if(temp != NULL)
			StringMatcher(text, pattern, temp, depth+1, check, valid, saver, min, row, Tn, Tm, Pn, Pm, hit+1);
		if(wildcard != NULL)
			StringMatcher(text, pattern, wildcard, depth+1, check, valid, saver, min, row, Tn, Tm, Pn, Pm, hit);
		/*
		endmark = v->T_son_list[numLetter-1];	// [ conv('$') ]
		if(endmark != NULL && depth != 0)
		{
			//printf("%d(text$) ", endmark->ifleaf);
			if(++check[endmark->ifleaf - (row*col)] == max)
				saver[++saver[0]] = endmark->ifleaf - (row*col);
		}*/
		
	}
}
