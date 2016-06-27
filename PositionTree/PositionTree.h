#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define numLetter 28

typedef struct Vertex {
	char B[numLetter];

	struct Vertex **T_son_list;
	struct Vertex **A_son_list;

	struct Vertex *T_parent;
	struct Vertex *A_parent;
	
	char T_edge;
	char A_edge;

	int T_depth;
	int A_depth;

	int ifleaf;
}item;

int conv(char c);

item* newItem(item *T, item *A, char t, char a, int leaf);

void case2helper(char *c, item *u, item **dla, int index, int depth, int i);

void case3_helper(char *c, item *u, item **dla, int index, int i);

void case4_helper(char *c, item *u, item **dla, int index, int i);

void PositionTree(item *root, item **dla, char *x,int end);
