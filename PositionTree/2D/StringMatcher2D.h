#include "../PositionTree/PositionTree.h"

int* sizer(int Tn, int Tm, int Pn, int Pm, int x, int y, int totalHit);

void sweeper(item *v, int *check, int*valid, int *saver, int *min, int row, int Tn, int Tm, int Pn, int Pm, int hit);

void StringMatcher(char *text, char *pattern, item *v, int depth, int *check, int *valid, int *saver, int *min, int row, int Tn, int Tm, int Pn, int Pm, int hit);
