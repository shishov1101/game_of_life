#include "gol.h"
#include <stdlib.h>

void read_in_file(FILE *infile, struct universe *u) {
    int row = 0;
    int column = 0;
    if(infile != NULL) {
        char buff;
        while ((buff = fgetc(infile)) != EOF) {
            if(buff == '\n') {
                column = 0;
                row++;
            }
            column++;
        }
        row++;
        rewind(infile);
        u->rows = row;
        u->columns = column;
        u->current_generation = (int **)malloc(u->rows*sizeof(int *));
        u->next_generation = (int **)malloc(u->rows*sizeof(int *));
        for(int i = 0; i < u->rows; i++) {
            u->current_generation[i] = (int *)malloc(u->columns*sizeof(int));
            u->next_generation[i] = (int *)malloc(u->columns*sizeof(int));
        }
        int i = 0;
        int j = 0;
        while ((buff = fgetc(infile)) != EOF) {
            if(buff == '\n') {
                j = 0;
                i++;
                continue;
            }
            if(buff == '*') u->current_generation[i][j] = 1;
            else if(buff == '.') u->current_generation[i][j] = 0;
            j++;
        }
    }
    else {
        char elem =' ';
        printf("Write number of columns:");
        scanf("%d", &column);
        printf("Write number of rows:");
        scanf("%d", &row);
        u->rows = row;
        u->columns = column;
        u->current_generation = (int **)malloc(u->rows*sizeof(int *));
        u->next_generation = (int **)malloc(u->rows*sizeof(int *));
        for(int i = 0; i < u->rows; i++) {
            u->current_generation[i] = (int *)malloc(u->columns*sizeof(int));
            u->next_generation[i] = (int *)malloc(u->columns*sizeof(int));
        }
        for(int i = 0; i < u->rows; i++) {
            for(int j = 0; j < u->columns; j++){
                printf("Write element row = %d, column = %d:\n", i, j);
                scanf("%s", &elem);
                if(elem == '*') u->current_generation[i][j] = 1;
                else u->current_generation[i][j] = 0;
            }
        }
        for(int i = 0; i < u->rows; i++) {
            for (int j = 0; j < u->columns; j++) {
                printf("%d", u->current_generation[i][j]);
            }
            printf("\n");
        }
    }
}

void write_out_file(FILE *outfile, struct universe *u) {
    char zvezda = '*';
    char tochka = '.';
    if (outfile != NULL) {
        for(int i = 0; i < u->rows; i++) {
            for(int j = 0; j < u->columns; j++){
                if(u->current_generation[i][j] == 1) fprintf(outfile,"%c", zvezda);
                else fprintf(outfile, "%c", tochka);
            }
            fprintf(outfile,"\n");
        }
    }
    else {
        for(int i = 0; i < u->rows; i++) {
            for(int j = 0; j < u->columns; j++){
                if(u->next_generation[i][j] == 1) printf("%c", zvezda);
                else printf("%c", tochka);
            }
            printf("\n");
        }
    }
}

int is_alive(struct universe *u, int column, int row) {
    return u->current_generation[row][column] == 1 ? 1 : 0;
}

int will_be_alive(struct universe *u, int column, int row) {
    int neighbours = 0;
    if (is_alive(u, column, row)) {
        neighbours = count_neighbours(u, column, row);
        if(neighbours == 2 || neighbours == 3) return 1;
    }
    else {
        neighbours = count_neighbours(u, column, row);
        if(neighbours == 3) return 1;
    }
    return 0;
}

int will_be_alive_torus(struct universe *u,  int column, int row) {
    int neighbours = 0;
    if (is_alive(u, column, row)) {
        neighbours = count_neighbours_torus(u, column, row);
        if(neighbours == 2 || neighbours == 3) return 1;
    }
    else {
        neighbours = count_neighbours_torus(u, column, row);
        if(neighbours == 3) return 1;
    }
    return 0;
}

void evolve(struct universe *u, int (*rule)(struct universe *u, int column, int row)) {
    if(rule == will_be_alive) {
        for(int i = 0; i < u->rows; i++) {
            for(int j = 0; j < u->columns; j++){
                if(will_be_alive(u, j, i)) u->next_generation[i][j] = 1;
                else u->next_generation[i][j] = 0;
            }
        }
    }
    else if(rule == will_be_alive_torus) {
        for(int i = 0; i < u->rows; i++) {
            for(int j = 0; j < u->columns; j++){
                if(will_be_alive_torus(u, j, i)) u->next_generation[i][j] = 1;
                else u->next_generation[i][j] = 0;
            }
        }
    }
    for(int i = 0; i < u->rows; i++) {
        for(int j = 0; j < u->columns; j++){
            u->current_generation[i][j] = u->next_generation[i][j];
        }
    }
}

void print_statistics(struct universe *u) {
    int count_alive = 0;
    static float sum_of_stats = 0.0f;
    static int count_iterations = 0;
    for(int i = 0; i < u->rows; i++) {
        for(int j = 0; j < u->columns; j++){
            if(u->current_generation[i][j] == 1) count_alive += 1;
        }
    }
    count_iterations += 1;
    printf("```\n");
    printf("   %.3f%% of cells currently alive\n", 100 * (float)count_alive / (float)(u->columns * u->rows));
    sum_of_stats += (float)count_alive / (float)(u->columns * u->rows);
    printf("   %.3f%% of cells alive on average\n", 100 * sum_of_stats / count_iterations);
    printf("```\n");
}

int count_neighbours(struct universe *u, int column, int row) {
    int neighbours = 0;
    if (column > 0 && row > 0 && column < u->columns - 1 && row < u->rows - 1) {
        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                if(j == 0 && i == 0) continue;
                if(is_alive(u, column + i, row+ j)) neighbours++;
            }
        }
    }
    else if(column == 0 && row == 0) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                if(j == 0 && i == 0) continue;
                if(is_alive(u, column + i, row+ j)) neighbours++;
            }
        }
    }
    else if(column == u->columns - 1 && row == u->rows - 1) {
        for (int i = -1; i < 1; i++) {
            for (int j = -1; j < 1; j++) {
                if(j == 0 && i == 0) continue;
                if(is_alive(u, column + i, row+ j)) neighbours++;
            }
        }
    }
    else if(column == 0 && row == u->rows - 1) {
        for (int i = 0; i < 2; i++) {
            for (int j = -1; j < 1; j++) {
                if(j == 0 && i == 0) continue;
                if(is_alive(u, column + i, row+ j)) neighbours++;
            }
        }
    }
    else if(column == u->columns - 1 && row == 0) {
        for (int i = -1; i < 1; i++) {
            for (int j = 0; j < 2; j++) {
                if(j == 0 && i == 0) continue;
                if(is_alive(u, column + i, row+ j)) neighbours++;
            }
        }
    }
    else if(column == 0) {
        for (int i = 0; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                if(j == 0 && i == 0) continue;
                if(is_alive(u, column + i, row+ j)) neighbours++;
            }
        }
    }
    else if(row == 0) {
        for (int i = -1; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                if(j == 0 && i == 0) continue;
                if(is_alive(u, column + i, row+ j)) neighbours++;
            }
        }
    }
    else if(column == u->columns - 1) {
        for (int i = -1; i < 1; i++) {
            for (int j = -1; j < 2; j++) {
                if(j == 0 && i == 0) continue;
                if(is_alive(u, column + i, row+ j)) neighbours++;
            }
        }
    }
    else if(row == u->rows - 1) {
        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 1; j++) {
                if(j == 0 && i == 0) continue;
                if(is_alive(u, column + i, row+ j)) neighbours++;
            }
        }
    }
    return neighbours;
}

int count_neighbours_torus(struct universe *u, int column, int row) {
    int neighbours = 0;
    int current_column = 0;
    int current_row = 0;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if(j == 0 && i == 0) continue;
            current_column = column + i;
            current_row = row + j;
            if(current_column > u->columns - 1) current_column = 0;
            else if(current_column < 0) current_column = u->columns - 1;
            if(current_row > u->rows - 1) current_row = 0;
            else if(current_row < 0) current_row = u->rows - 1;
            if(is_alive(u, current_column, current_row)) neighbours++;
        }
    }
    return neighbours;
}