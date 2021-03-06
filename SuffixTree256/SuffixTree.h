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

	void cursor(int i);

	char nextLetter(int i);
	
	Vertex* pickV();
	
	Vertex* pickV(int i);

	int diff(Vertex *v);
	
	void setPosition(Vertex *V, int edgeLen, int Len); 

	int howManyL;
};
