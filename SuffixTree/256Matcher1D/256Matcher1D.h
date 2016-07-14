#include "../SuffixTree.h"

class StringMatcher
{
public:
	SuffixTree *Tree;
	char *Pattern;
	int pEnd;
	int occurrence;
	
	StringMatcher(SuffixTree *Tree, char *Pattern);
	void sweeper(Vertex *v);
	void findPattern(Vertex *v, int index);
};

