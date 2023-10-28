#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct element {
	char object[6];
	int x;
	int y;
} element;

int main(int argc, char **argv) {
	
	char object[6];
	int x, y;
	int gen_food_fox;
	int gen_rep_rabbit, gen_rep_fox;
	int n_gen, r, c, n;
	 
	FILE *fp = fopen("../instances/test.txt", "r");
	if (fp == NULL) {
		printf("Failed opening file\n");
		exit(EXIT_FAILURE);
	}
	
	fscanf(fp, "%d %d %d %d %d %d %d\n", &gen_rep_rabbit, &gen_rep_fox, &gen_food_fox, &n_gen, &r, &c, &n);
	element *elements = (element *) malloc (n * sizeof(element));
	for (int i = 0; i < n; i++) {
		fscanf(fp, "%s %d %d\n", object, &x, &y);
		strcpy(elements[i].object, object);
		elements[i].x = x;
		elements[i].y = y;
	}
	fclose(fp);
	
	printf("%d %d %d %d %d %d %d\n", gen_rep_rabbit, gen_rep_fox, gen_food_fox, n_gen, r, c, n);
	for (int i = 0; i < n; i++) 
		printf("%s %d %d\n", elements[i].object, elements[i].x, elements[i].y);
		
	int **env = calloc(r, sizeof(int *));
	for (int i = 0; i < r; i++)
		env[i] = calloc (c, sizeof(int));
		
	for (int i = 0; i < n; i++)
		if (!strcmp("RAPOSA", elements[i].object))
			env[elements[i].x][elements[i].y] = 3;
		else if (!strcmp("COELHO", elements[i].object))
			env[elements[i].x][elements[i].y] = 2;
		else 
			env[elements[i].x][elements[i].y] = 1;
			
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < r; j++)
			printf("%d\t", env[i][j]);
		printf("\n");
	}
	return 0;
}
