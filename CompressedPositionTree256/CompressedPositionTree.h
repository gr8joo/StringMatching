#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define somesize 200000
#define numLetter 256

int numVertex;
int numCase2;
int shifting;
int maxDepth;

//int conv[256];
int kbyk[somesize];

typedef struct node_st {
	char *B;
	char *substring;
	struct node_st **T_son_list;
	struct node_st **A_son_list;
	struct node_st *T_parent;
	struct node_st *A_parent;
	char T_edge;
	char A_edge;
	int T_depth;
	int A_depth;
	int ifleaf;
	int ifsub;
}item;

void setConverter();

item* newItem(item *T, item *A, char t, char a, int leaf);

int recur(FILE *out, item * temp, int depth);

void case2helper(char *x, item *u, item **dla, int depth, int i, int subsize);

void case3helper(char *x, item *u, item **dla, int i);

void case4helper(char *x, item *u, item **dla, int i);

item* CompressedPositionTree(char *x, FILE *out);
