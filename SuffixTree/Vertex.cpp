#include "Vertex.h"

Vertex::Vertex(){}

Vertex::Vertex(int a, int b)
{
	start = a;
	end = b;
	gEnd = NULL;
	
	sonList = new Vertex *[numLetter];

	index=0;
}

Vertex::Vertex(int a, int *b)
{
	start = a;
	end = -2;
	gEnd = b;

	sonList = new Vertex *[numLetter];

	index=0;
}

