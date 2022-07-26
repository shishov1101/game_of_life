#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gol.h"


int main(int argc, char **argv) {
    FILE* file_intput;
    FILE* file_output;
    struct universe u;
    char str_input[200] = "";
    char str_output[200] = "";
    int generations = 5;
    int stats = 0;
    int command = 0;
    for (int i = 0; i < argc; i++) {
        if(argc == 1) {
            file_intput = NULL;
            file_output = NULL;
            break;
        }
        if (!strcmp(argv[i], "-i")) {
            if(i + 1 < argc) {
                strcpy(str_input, argv[i + 1]);
                file_intput = fopen(str_input,"r");
            }
            else {
                fprintf(stderr,"Error! You did not write argument");
                return -3;
            }
        }
        else if (!strcmp(argv[i], "-o")) {
            if(i + 1 < argc) {
                strcpy(str_output, argv[i + 1]);
                file_output = fopen(str_output,"w");
            }
            else {
                fprintf(stderr,"Error! You did not write argument");
                return -3;
            }
        }
        else if (!strcmp(argv[i], "-g")) {
            if(i + 1 < argc) generations = atoi(argv[i + 1]);
            else {
                fprintf(stderr,"Error! You did not write argument");
                return -3;
            }
        }
        else if (!strcmp(argv[i], "-s")) stats = 1;
    }
    printf("Choose the rule, for torus press 1, for default press 2\n");
    scanf("%d", &command);
    read_in_file(file_intput, &u);
    for(int i = 0; i < generations; ++i) {
        if(command == 1) evolve(&u, will_be_alive_torus);
        else evolve(&u, will_be_alive);
        if(stats) print_statistics(&u);
    }
    write_out_file(file_output, &u);
    return 0;
}
