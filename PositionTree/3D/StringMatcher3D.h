#include "../PositionTree.h"

int* sizer(int Tl, int Tn, int Tm, int Pl, int Pn, int Pm, int z, int x, int y, int totalHit);

//Search all leaves accessible under the current node
void sweeper(item *v, int *check, int*valid, int *saver, int *min, int plane, int row, int Tl, int Tn, int Tm, int Pl, int Pn, int Pm, int hit);

//With completed position tree, compare pattern with text
void stringMatcher(char *text, char *pattern, item *v, int depth, int *check, int *valid, int *saver, int *min, int plane, int row, int Tl, int Tn, int Tm, int Pl, int Pn, int Pm, int hit);


