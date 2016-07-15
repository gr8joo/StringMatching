#include "StringMatcher1D.h"

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
	int result = 0, i=0, len;
	int total=0;
	int l;
	static int z = 0;
	char a, b;
	item *temp;

		
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

	// If Vertex is a leaf
	if(Vertex -> ifleaf != 0)
	{
		//printf("One\n");
		if(Pattern[index] == NULL)
		{
			printf("\t%d\n", Vertex->ifleaf);
			return 1;
		}
		else
		{
			if( strlen(x) - Vertex->ifleaf < strlen(Pattern) - index)
				return 0;
			for( i=Vertex->ifleaf;i<strlen(x);i++)
			{
				a = x[i];
				b = Pattern[index];
				if( a >= 'A' && a <= 'Z')
					a = a - 'A' + 'a';
				if( b >= 'A' && b <= 'Z')
					b = b - 'A' + 'a';
				if(a != b)
					return 0;
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
		//printf("Sweeper\n");
		total += Sweeper(Vertex);
	}
	
	else
	{
		if(Vertex -> ifsub != 0)
		{
			if( strlen(&Pattern[index]) < len )
				len = strlen(&Pattern[index]);
					
			for(i=0;i<len;i++)
			{	
				a = Vertex -> substring[i];
				b = Pattern[index + i];
				if( a >= 'A' && a <= 'Z')
					a = a - 'A' + 'a';
				if( b >= 'A' && b <= 'Z')
					b = b - 'A' + 'a';
				if(a != b)
					return 0;
			}

			if( Pattern[index+len] == NULL)
			{
				//printf("Sweeper\n");
				total += Sweeper(Vertex);
			}
			
			else
			{
				//printf("Two\n");
				l = conv[Pattern[index+len]];
				temp = Vertex -> T_son_list[l];
				if(temp != NULL)
					total += StringMatcher(temp, x, Pattern, index + len + 1);
			}
		
		}
		else
		{
			//printf("Three\n");
			l = conv[Pattern[index]];
			temp = Vertex -> T_son_list[l];
			
			if(temp != NULL)
				total+=StringMatcher(temp, x, Pattern, index + 1);
		}

	}
	return total;
}

