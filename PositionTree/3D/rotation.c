#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define l 3
#define m 3
#define n 3

char*** X_rotation(char ***c, int x, int y, int z)
{
	int i, j, k;
	char ***r;
	printf("%d %d %d\n", x, y, z);
	r=(char ***)calloc(x, sizeof(char**));
	printf("???");
	for(i=0;i<x;i++)
	{
		r[i] = (char **)calloc(z, sizeof(char *));
		for(j=0;i<z;j++)
			r[i][j] = (char *)calloc(y, sizeof(char));
	}

	for(i=0;i<x;i++)
		for(j=0;j<y;j++)
			for(k=0;k<z;k++)
				r[i][z-k-1][j] = c[i][j][k];
	return r;
}
char*** Y_rotation(char ***c, int x, int y, int z)
{
	int i, j, k;
	char ***r = (char ***)calloc(z, sizeof(char **));
	for(i=0;i<x;i++)
	{
		r[i] = (char **)calloc(y, sizeof(char *));
		for(j=0;i<z;j++)
			r[i][j] = (char *)calloc(x, sizeof(char));
	}

	for(i=0;i<x;i++)
		for(j=0;j<y;j++)
			for(k=0;k<z;k++)
				r[k][j][x-i-1] = c[i][j][k];
	return r;
}
char*** Z_rotation(char ***c, int x, int y, int z)
{
	int i, j, k;
	char ***r = (char ***)calloc(y, sizeof(char **));
	for(i=0;i<x;i++)
	{
		r[i] = (char **)calloc(x, sizeof(char *));
		for(j=0;i<z;j++)
			r[i][j] = (char *)calloc(z, sizeof(char));
	}

	for(i=0;i<x;i++)
		for(j=0;j<y;j++)
			for(k=0;k<z;k++)
				r[y-j-1][i][k] = c[i][j][k];
	return r;
}

void main()
{
	char ***origin, ***a, ***b, ***c;
	int i, j, k;
	int ch='a'-1;


	origin = (char ***)calloc(l,sizeof(char**));
	for(i=0;i<l;i++)
	{
		origin[i] = (char **)calloc(m,sizeof(char*));
		for(j=0;j<m;j++)
			origin[i][j] = (char *)calloc(n, sizeof(char));
	}
	for(i=0;i<l;i++)
		for(j=0;j<m;j++)
			for(k=0;k<n;k++)
				origin[i][j][k] = ++ch;
	origin[l-1][m-1][n-1] = '?';
	
	a = X_rotation(origin,l,m,n);
	//b = Y_rotation(origin,l,m,n);
	//c = Z_rotation(origin,l,m,n);
//printf("origin / a / b/ c\n");
	for(i=0;i<l;i++){
		for(j=0;j<m;j++){
			printf("%s\n", origin[i][j]);
			printf("%s ", a[i][j]);
			//printf("%s ", b[i][j]);
			//printf("%s", c[i][j]);
		}
		printf("\n");
	}
}



