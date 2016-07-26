#include "256Matcher1D.h"
StringMatcher::StringMatcher(SuffixTree *Tree, char *Pattern)
{
	this -> Tree = Tree;
	this -> Pattern = Pattern;
	this -> pEnd = strlen(Pattern)-1;
	this -> occurrence = 0;
	printf("\nPositions where Pattern appears in Text:\n");
	findPattern(this->Tree -> root, 0);
	printf("\nTotal #of occurrences of Pattern in Text: %d\n", occurrence);
}

void StringMatcher::sweeper(Vertex *v)
{
	//printf("Sweeper?\n");
	if( v == NULL)
		return;
	else if( v -> position != -1)
	{
		occurrence++;
		printf("\t%d\n", v->position);
		return;
	}
	else
	{
		for(int i=0;i<numLetter;i++)
			if( v->sonList[i] != NULL)
				sweeper(v->sonList[i]);
	}
}

void StringMatcher::findPattern(Vertex *v, int index)
{
	int i;
	int end;
	int range;

	//printf("Hello??\n");
	if(v -> end == -2)
		end = *(v -> gEnd);
	else
		end = v->end;

	// Current vertex is a leaf
	if( v -> position != -1 )
	{
		//printf("Leaf\n");
		if(end < pEnd)
			return;
			
		for(i=v->start; i<=end; i++)
		{
			if(Tree->x[i] != Pattern[index])
			{
				//printf("index: %d\n", index);
				return;
			}
			index++;
			if(Pattern[index] == NULL)
				break;
		}
		occurrence++;
		printf("\t%d\n", v->position);
	}

	// Current vertex is an interior vertex
	else
	{
		//printf("interior\n");
		if(end - v->start < pEnd - index)
		{
			//printf("here\n");
			range = end;
		}
		else
		{
			//printf("there\n");
			range = v->start + pEnd - index;
		}
		//printf("%d %d\n", v->start, range);
		for(i=v->start; i<=range; i++)
		{
			if(Tree->x[i] != Pattern[index])
				return;
			index++;
		}
		//printf("index: %d\n", index);
		//printf("pEnd: %d\n", pEnd);
		if(index <= pEnd)
		{
			if( v->sonList[ Pattern[index] ] != NULL )
				findPattern( v->sonList[ Pattern[index] ], index );
			else
				return;
		}
		else
			sweeper(v);
	}
}


