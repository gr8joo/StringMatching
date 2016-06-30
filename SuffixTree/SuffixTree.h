#include "Vertex.h"

class SuffixTree{

public:	
	Vertex *root;
	
// Active Point matterials: Vertex/ Length/ Edge
	Vertex *actV;
	int actL;
	int actE;
	
	int leftSuffix;					//Vertex example;
	
	int GlobalEnd;
	
	char *x;

// const static char nonRegularLetter = '$';
	const static char Dollar = '$';

//	SuffixTree();
	
	SuffixTree(char *y);
	
	void buildTree();

	void evolveTree(int i);

	void cursor(int index);

	char nextLetter(int i);
	
	Vertex* pickV();
	
	Vertex* pickV(int index);

	int diff(Vertex *v);
	
	void setIndex(Vertex *V, int edgeLen, int Len); 

	int howManyL;
};
