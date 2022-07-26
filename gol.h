#ifndef __GOL__
#define __GOL__
#include <stdio.h>


struct universe {
	int rows;
	int columns;
	int **current_generation;
	int **next_generation;
};

void read_in_file(FILE *infile, struct universe *u);
void write_out_file(FILE *outfile, struct universe *u);
int is_alive(struct universe *u, int column, int row);
int will_be_alive(struct universe *u, int column, int row);
int will_be_alive_torus(struct universe *u,  int column, int row);
void evolve(struct universe *u, int (*rule)(struct universe *u, int column, int row));
void print_statistics(struct universe *u);
int count_neighbours(struct universe *u, int column, int row);
int count_neighbours_torus(struct universe *u, int column, int row);

#endif