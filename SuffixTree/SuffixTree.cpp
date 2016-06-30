#include "SuffixTree.h"


//const char SuffixTree::nonRegularLetter = '$';

//SuffixTree::SuffixTree(){}

SuffixTree::SuffixTree(char *y)//:example(1,2)
{
// Text(x) Setting
	
	x = (char*)calloc(strlen(y)+1, sizeof(char));
	memcpy(x,y,strlen(y));

	//  Replacing '\n' to '$'
	x[strlen(x)-1] = Dollar;
	
	std::cout << strlen(x) << std::endl;
	//std::cout << x << std::endl;
	
	howManyL = 0;
	buildTree();
	setPosition(root, 0, strlen(x));
	printf("# of Leaves: %d\n", howManyL);
}

void SuffixTree::buildTree()
{
	int i;

	root = new Vertex(1, 0);
	root -> position = -1;

//Active Point Setting	
	actV = root;
	actL = 0;
	actE = -1;

	GlobalEnd = -1;

	leftSuffix = 0;
	for(i=0;i<strlen(x);i++)
	{
		//printf("Evolve %d: ", i);
		evolveTree(i);
		//printf("\n\tactL: %d\tactE: %d\n\tleft Suffix: %d\t global end:%d\n\n", actL, actE, leftSuffix, GlobalEnd);
		//printf("\n");
	}
	//printf("%d\n", leftSuffix);
	

	
}
void SuffixTree::evolveTree(int i)
{
	Vertex *lastInternalV = NULL;
	
	GlobalEnd++;

	leftSuffix++;
	while( leftSuffix > 0)
	{
		
	// If active length is equal to zero, always start from root
		if(actL == 0)
		{
			//printf("Z");
			if(pickV(i) != NULL)
			{
				//printf("-a ");
				actE = pickV(i)->start;
				actL++;
				break;
			}
		
			else
			{
				//printf("-b ");
				root -> sonList[ x[i] ] = new Vertex(i, &GlobalEnd);
				leftSuffix--;
			}
		}

		else
		{
			char c = nextLetter(i);

			if(c == NULL)
			{
				//printf("E");
				Vertex *V = pickV();
				V->sonList[ x[i] ] = new Vertex(i, &GlobalEnd);
				if( lastInternalV != NULL ){
					//printf(".5");
					lastInternalV -> SuffixLink = V;
				}

				lastInternalV = V;
				if( actV != root )
				{
					//printf("-a ");
					actV = actV -> SuffixLink;
				}
				else
				{
					//printf("-b ");
					actE++;
					actL--;
				}
				leftSuffix--;
			}
			else if(c == x[i])
			{
				//printf("1");
				if( lastInternalV != NULL )
				{
					//printf(".5");
					lastInternalV -> SuffixLink = pickV();
				}
				cursor(i);
				//printf(" ");
				break;
			}
			else
			{
				//printf("2");
				Vertex *V = pickV();
				int prevStart = V->start;
				V->start = V->start + actL;

				Vertex *newInternalV = new Vertex(prevStart, prevStart + actL-1);
				
				Vertex *newLeafV = new Vertex(i, &GlobalEnd);			//this.end			

				newInternalV -> sonList[ x[ newInternalV->start + actL] ] = V;
				newInternalV -> sonList[ x[i] ] = newLeafV;
				newInternalV -> position = -1;
				actV -> sonList[ x[ newInternalV->start ] ] = newInternalV;

				if( lastInternalV != NULL)
				{
					//printf(".5");
					lastInternalV -> SuffixLink = newInternalV;
				}
				lastInternalV = newInternalV;
				newInternalV -> SuffixLink = root;

				if( actV != root )
				{
					actV = actV -> SuffixLink;
					//printf("-a ");
				}
				else
				{
					//printf("-b ");
					actE++;
					actL--;
				}
				leftSuffix--;
			}
		}
	}
}

void SuffixTree::cursor(int i)
{
	Vertex *V = pickV();

	if( diff(V) < actL )
	{
		actV = V;
		actL = actL - diff(V);
		actE = V->sonList[ x[i] ]->start;
	}
	else
		actL++;
}

char SuffixTree::nextLetter(int i)
{
	Vertex *V = pickV();
	/*
	printf("diff(V) = %d", diff(V));
	if(V->end == -2)
		printf("(Global) ");
	else
		printf("(local) ");
	*/	
	if( diff(V) >= actL )
		return x[ actV->sonList[ x[actE] ]->start + actL ];


	if( diff(V)+1 == actL ){
		if( V->sonList[ x[i] ] != NULL)
			return x[i];
	}
	else
	{
		//printf("(recur) ");
		actV = V;
		actL = actL - diff(V) -1;
		actE = actE + diff(V) +1;
		return nextLetter(i);
	}
	
	return NULL;
}
		
int SuffixTree::diff(Vertex *V)
{
	int result;
	if( V->end == -2)
		result = *(V->gEnd) - V->start;
	else
		result = V->end - V->start;
	//printf("%d\n", result);
	return result;
}

Vertex* SuffixTree::pickV()
{
	return actV -> sonList[ x[actE] ];
}
Vertex* SuffixTree::pickV(int i)
{
	return actV -> sonList[ x[i] ];
}
void SuffixTree::setPosition(Vertex *V, int edgeLen, int Len)
{
	if( V == NULL )
		return;

	edgeLen += diff(V) + 1;
	if(V -> position != -1)
	{
		howManyL++;
		V->position = Len - edgeLen;
		//printf("%d\n", V->position);
		return;
	}
	for(int i=0;i<numLetter;i++)
	{
		if(V -> sonList[i] != NULL)
		{
			//printf("%c ", i);
			setPosition(V -> sonList[i], edgeLen, Len);
		}
	}
}
int main()
{
	FILE *in = fopen("input.txt","rt");
	char *x = (char*)calloc(somesize, sizeof(char));
	//Pattern = (char*)calloc(somesize, sizeof(char));
	
	fgets(x, somesize, in);
	//SuffixTree *Tree = new SuffixTree(x);
	SuffixTree Tree(x);
	
	//Tree.x = (char*)calloc(20, sizeof(char));
	//std::cout << "Hello World!\n" << std::endl;
	return 0;		
}
