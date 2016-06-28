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
int StringMatcher(item *Vertex, char *Pattern, int index)
{
	int result = 0, i=0, len;
	int total=0;
	int l;
	static int z = 0;
	char x, y;
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

	if(Vertex -> ifleaf != 0)
	{
		//printf("One\n");
		if(Pattern[index] == NULL)
			printf("\t%d\n", Vertex->ifleaf);
		return 1;
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
				x = Vertex -> substring[i];
				y = Pattern[index + i];
				if( x >= 'A' && x <= 'Z')
					x = x - 'A' + 'a';
				if( y >= 'A' && y <= 'Z')
					y = y - 'A' + 'a';
				if(x != y)
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
					total += StringMatcher(temp, Pattern, index + len + 1);
			}
		
		}
		else
		{
			//printf("Three\n");
			l = conv[Pattern[index]];
			temp = Vertex -> T_son_list[l];
			
			if(temp != NULL)
				total+=StringMatcher(temp, Pattern, index + 1);
		}

	}
	return total;
}

