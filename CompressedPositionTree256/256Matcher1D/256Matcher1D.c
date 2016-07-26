#include "256Matcher1D.h"

int Sweeper(item *Vertex)
{
	int i, total = 0;
	item *temp;
	if(Vertex -> ifleaf != 0)
	{
		printf("\t%d\n", Vertex->ifleaf);
		return 1;
	}
			
	for(i=0;i<numLetter;i++)
	{
		temp = Vertex -> T_son_list[i];
		if(temp != NULL)
			total += Sweeper(temp);
	}
	return total;
}
int StringMatcher(item *Vertex, char *x, char *Pattern, int index)
{
	int result = 0, i=0, len, range=0;
	int total=0;
	int l;
	static int z = 0;
	char a, b;
	item *temp;
	//printf("%d\n", index);
	if(Vertex -> ifsub != 0)
	{
		len = strlen(Vertex -> substring);
		if(len != Vertex -> ifsub)
		{
			// If this if statement is executed, there are some problem with memory allocation in Vertex.
			printf("difference: %d\n", Vertex -> ifsub - len);
			return 0;
		}
	}

	if(Vertex -> ifleaf != 0)
	{
		//printf("One\n");
		//printf("index: %d\n", index);
		//printf("%d\n", Vertex -> ifleaf);
		if(Pattern[index] == NULL)
		{
			printf("\t%d\n", Vertex->ifleaf);
			return 1;
		}
		else
		{
			if( strlen(x) - Vertex -> ifleaf - index + 1 < strlen(Pattern) - index)
			{
				//printf("here\n");
				return 0;
			}
			for( i=Vertex->ifleaf+index-1;i<strlen(x);i++)
			{
				if(x[i] != Pattern[index])
				{
					//printf("here2\n");
					//printf("%d\n", index);
					return 0;
				}
				index++;
				if(Pattern[index] == NULL)
					break;
			}
			printf("\t%d\n", Vertex->ifleaf);
			return 1;
		}
	}
	else if(Pattern[index] == NULL)
	{
		printf("Sweeper\n");
		total += Sweeper(Vertex);
	}
	
	else
	{
		if(Vertex -> ifsub != 0)
		{
			//if( strlen(&Pattern[index]) < len )
			//	len = strlen(&Pattern[index]);
					
			for(i=0;i<len;i++)
			{	
				a = Vertex -> substring[i];
				b = Pattern[index ];
				//if( x >= 'A' && x <= 'Z')
				//	x = x - 'A' + 'a';
				//if( y >= 'A' && y <= 'Z')
				//	y = y - 'A' + 'a';
				if( b == NULL)
					break;
				else if(a != b)
					return 0;
				else
					index++;
				
			}

			if( Pattern[index] == NULL)
			{
				//printf("Sweeper\n");
				total += Sweeper(Vertex);
			}
			
			else
			{
				//printf("Two\n");
				l = Pattern[index];
				temp = Vertex -> T_son_list[l];
				if(temp != NULL)
					total += StringMatcher(temp, x, Pattern, index+1);
			}
		
		}
		else
		{
			//printf("Three\n");
			l = Pattern[index];
			temp = Vertex -> T_son_list[l];
			
			if(temp != NULL)
				total+=StringMatcher(temp, x, Pattern, index + 1);
		}

	}
	return total;
}

