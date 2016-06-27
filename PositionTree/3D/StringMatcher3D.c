#include "StringMatcher3D.h"

//----------------------------------------------------------------------------------------------------------------------

int* sizer(int Tl, int Tn, int Tm, int Pl, int Pn, int Pm, int z, int x, int y, int totalHit)
{
	int l = Tl - 2*Pl;	
	int n = Tn - 2*Pn;
	int m = Tm - 2*Pm;
	int *array = (int *)calloc(11, sizeof(int));

	if(z <= Pl){
		l += Pl - z +1;
		array[1] = z;
	}
	else
		array[1] = Pl+1;
	
	if(z+Pl-1 > Tl - Pl){
		l += z - Tl + 2*Pl -1;
		array[2] = z+Pl-1;
	}
	else
		array[2] = Tl - Pl;
//----------------------------------------------------	
	if(x <= Pn){
		n += Pn - x +1;
		array[3] = x;
	}
	else
		array[3] = Pn+1;
	
	if(x+Pn-1 > Tn-Pn){
		n += x - Tn + 2*Pn -1;
		array[4] = x+Pn-1;
	}
	else
		array[4] = Tn - Pn;
//----------------------------------------------------
	if(y <= Pm){
		m += Pm - y +1;
		array[5] = y;
	}
	else
		array[5] = Pm+1;
	
	if(y+Pm-1 > Tm-Pm){
		m += y - Tm + 2*Pm -1;
		array[6] = y+Pm-1;
	}
	else
		array[6] = Tm - Pm;
	
	array[7] = z;
	array[8] = x;
	array[9] = y;
	array[0] = l*n*m;
	array[10] = totalHit;
	//printf("%d ", n*m);
	return array;	
}	
	

void sweeper(item *v, int *check, int*valid, int *saver, int *min, int plane, int row, int Tl, int Tn, int Tm, int Pl, int Pn, int Pm, int hit)					//Search all leaves accessible under the current node
{
	int i, leaf = v->ifleaf;
	item *temp;
	int *array;
	int realPos;
	if(leaf !=0)
	{
		//printf("%d(pattern$) ", leaf);
		realPos = leaf - (plane*Tn*Tm) - (row*Tm);
		if(realPos > 0 &&  realPos%(Tn*Tm) + row*Tm <= Tn*Tm && (realPos-1)%Tm+Pm<=Tm)
		{
			valid[realPos] += hit;
			check[realPos]++;			
			if(check[realPos] == Pl*Pn)
			{
				saver[++saver[0]] = realPos;
				array = sizer(Tl, Tn, Tm, Pl, Pn, Pm, (realPos-1)/(Tn*Tm) +1, ((realPos-1)%(Tn*Tm))/Tm + 1, ((realPos-1)%(Tn*Tm))%Tm + 1, valid[realPos]);
				if(min[10] < array[10] || (min[10] == array[10] && min[0]>array[0]))
				{
					for(i=0;i<=10;i++)
						min[i] = array[i];

				}
				free(array);
			}
		}
		
		return;
	}
	for(i=0;i<=27;i++)
	{
		temp = v->T_son_list[i];
		if(temp != NULL)
			sweeper(temp, check, valid, saver, min, plane, row, Tl, Tn, Tm, Pl, Pn, Pm, hit);
	}
}
	
void stringMatcher(char *text, char *pattern, item *v, int depth, int *check, int *valid, int *saver, int *min, int plane, int row, int Tl, int Tn, int Tm, int Pl, int Pn, int Pm, int hit)//With completed position tree, compare pattern with text
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
			realPos = leaf - (plane*Tn*Tm) - (row*Tm);
			if(realPos > 0 && realPos%(Tn*Tm) + row*Tm <= Tn*Tm && (realPos-1)%Tm+Pm<=Tm)
			{
				valid[realPos] += hit;
				check[realPos]++;			
				if(check[realPos] == Pl*Pn)
				{
					saver[++saver[0]] = realPos;
					array = sizer(Tl, Tn, Tm, Pl, Pn, Pm, (realPos-1)/(Tn*Tm) +1, ((realPos-1)%(Tn*Tm))/Tm + 1, ((realPos-1)%(Tn*Tm))%Tm + 1, valid[realPos]);
					if(min[10] < array[10] || (min[10] == array[10] && min[0]>array[0]))
					{
						for(i=0;i<=10;i++)
							min[i] = array[i];
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

	else if(index == 28)					//pattern reached end
	{
		//printf("depth before sweep: %d\n", depth);
		sweeper(v, check, valid, saver, min, plane, row, Tl, Tn, Tm, Pl, Pn, Pm, hit);					//Find all possible cases when pattern reached end
	}
	else if(pattern[depth] == '?')				//if the char of the current node is '?', then go through all the  possible edges.
	{
		for(i=0;i<=26;i++)
		{
			temp = v->T_son_list[i];
			if(temp != NULL)
				stringMatcher(text, pattern, temp, depth+1, check, valid, saver, min, plane, row, Tl, Tn, Tm, Pl, Pn, Pm, hit);
		}
		/*
		endmark = v->T_son_list[27];	// [ conv('$') ]
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
		{
			//printf("OLLEH~\n");
			stringMatcher(text, pattern, temp, depth+1, check, valid, saver, min, plane, row, Tl, Tn, Tm, Pl, Pn, Pm, hit+1);
		}
		if(wildcard != NULL)
			stringMatcher(text, pattern, wildcard, depth+1, check, valid, saver, min, plane, row, Tl, Tn, Tm, Pl, Pn, Pm, hit);
		/*
		endmark = v->T_son_list[27];	// [ conv('$') ]
		if(endmark != NULL && depth != 0)
		{
			//printf("%d(text$) ", endmark->ifleaf);
			if(++check[endmark->ifleaf - (row*col)] == max)
				saver[++saver[0]] = endmark->ifleaf - (row*col);
		}*/
		
	}
}
