#include "256Matcher1D.h"


int main()
{
	FILE *in = fopen("../../DataGenerator/input.txt","rt");
	char *x = (char*)calloc(somesize, sizeof(char));
	char *Pattern = (char*)calloc(somesize, sizeof(char));
	double time_start, time_stop, time_total;
	//Pattern = (char*)calloc(somesize, sizeof(char));
	
	
	//SuffixTree *Tree = new SuffixTree(x);

	time_start = (double)clock()/CLOCKS_PER_SEC;

	fgets(x, somesize, in);
	//if( x[ strlen(x)-1 ] == '\n' )
	//	x[ strlen(x)-1 ] = NULL;
	SuffixTree Tree(x);
	
	time_stop = (double)clock()/CLOCKS_PER_SEC;
	time_total = time_stop - time_start;

	
	//Tree.x = (char*)calloc(20, sizeof(char));
	//std::cout << "Hello World!\n" << std::endl;

	fgets(Pattern, somesize, in);
	if( Pattern[ strlen(Pattern)-1 ] == '\n' )
		Pattern[ strlen(Pattern)-1 ] = NULL;
	//printf("%s\n", Pattern);
	StringMatcher *Match = new StringMatcher(&Tree, Pattern);

	printf("The end of Construction of Suffix Tree: spent %lf sec \n", time_total);
	return 0;		
}
