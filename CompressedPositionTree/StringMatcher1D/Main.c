#include "StringMatcher1D.h"
#include<time.h>

void main()
{
	FILE *in = fopen("input.txt","rt");
	FILE *out = fopen("out1.txt", "wt");
	item *root;
	char *x, *Pattern;// = "aaaaaaabbbbbbbaaaaaaabbbbbbbaaaaaaa";	//"baaaaaabbbaaabbb"; 	"abbabbabb";	//"datastructuresandabstractionswithjava";//"aaabbbaaacccaaabbbaaa";

	double time_start, time_stop, time_total;
	int i,occur=0;
// start counting time
	time_start = (double)clock()/CLOCKS_PER_SEC;

// Generate a Compressed Position Tree
	x = (char*)calloc(somesize, sizeof(char));
	Pattern = (char*)calloc(somesize, sizeof(char));
	fgets(x, somesize, in);
	root = CompressedPositionTree(x, out);

// Stop counting time
	//printf("Time elapsed: %f\n", ((double)clock() - start) / CLOCKS_PER_SEC);
	time_stop = (double)clock()/CLOCKS_PER_SEC;
	time_total = time_stop - time_start;
	printf("\nThe end of Construction of Compressed Position Tree: spent %lf sec \n", time_total);
/*
	for(i = end; i>=1; i--)
	{
		fprintf(out, "dla[%3d] = ", i);
		k=recur(out, dla[i], 0);
		if(k>md)
			md=k;
		fprintf(out, "\n");
		
	}
*/
	printf("Number of Vertexes: %d\n", numVertex);
	printf("Number of Vertexes Case2 Searched: %d\n", numCase2);
	printf("Number of shifting in Case4: %d\n", shifting);
	printf("Maximum Physical Depth: %d\n", maxDepth);

	fgets(Pattern, somesize, in);
	if(Pattern[strlen(Pattern)-1] == '\n')
	{
		//printf("yes\n");
		Pattern[strlen(Pattern)-1] = NULL;
	}
	//printf("%d\n", strncmp(x, Pattern, strlen(Pattern)));
	//Pattern[strlen(Pattern)-1] = NULL;
	//printf("%s\n", Pattern);

	//for(i=strlen(Pattern);i<somesize;i++)
	//	printf("%d", Pattern[i]);
	//printf("%s\n", Pattern);
	printf("Positions where pattern occurs in the text:\n");
	occur = StringMatcher(root, x, Pattern, 0);
	printf("# of occurrences = %d\n", occur);
}
