#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define numLetter 256
#define somesize 200000
// #define nonRegularLetter '$';
class Vertex{

public:
	
	//Vertex **sonList = (Vertex **)
	int start;
	int end;
	int *gEnd;

	int position;

	Vertex *SuffixLink;
	//Vertex();
	Vertex(int a, int b);
	Vertex(int a, int *b);
	
	Vertex **sonList;

};
