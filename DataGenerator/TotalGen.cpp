#include <stdio.h>
#include <stdlib.h>
#define max_size 200000
int main()
{
	int i, r, temp, total_len=0, repeat, len;
	double d;
	char x[max_size] = {NULL};
	FILE *out = fopen("input.txt","wt");

	printf("This is a input data generator for testing CompressedPositionTree256 and SuffixTree.\n");
	printf("This program will make a (slightly less than) 200,000-length string.\n");
	printf("I, the set of regular letter, is composed of 94 letters including ' '\n");
	printf("$(%d) is a non-regular letter, excluded in I\n", '$');
	printf("\nDesired # of repeatitions (non-negative): ");
	scanf("%d", &repeat);

	len = (max_size-2) / (repeat+1);

// Text
	
	for(i=0;i<len;i++)
	{
		d = 32.0 + rand()%95;
		temp = d;
		if(temp == '$')
		{
			i--;
			continue;
		}
		x[i] = temp;
		fprintf(out, "%c", temp);
	}

	for(r=0; r<repeat; r++)
		for(i=0;i<len;i++)
			fprintf(out, "%c", x[i]);

	printf("Total Length: %d\n", (repeat+1)*len);

// Pattern
	fprintf(out, "\n");
	for(i=0;i<len;i++)
			fprintf(out, "%c", x[i]);
	

	

	return 0;
}
