#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include "parser.h"
#include "graphparse.h"

void parser(int const argc, char *const *argv) {
    int opt;
    char *filename =NULL;
    if (argc<=1) exit (1);
    while ((opt =getopt(argc, argv, "hr:m:sp:"))!=-1){
        switch (opt) {
            case 'h':{
            printf("Usage : ./ pagerank [ OPTIONS ] ... [ FILENAME ]\n");
            printf("Perform pagerank computations for a given file in the DOT format\n\n");
            printf("  -h    Print a brief overview of the available command line parameters\n");
            printf("  -r N  Simulatcleare N steps of the random surfer and output the result\n");
            printf("  -m N  Simulate N steps of the Markov chain and output the result\n");
            printf("  -s    Compute and print the statistics of the graph as defined \n");
            printf("          in section 3.4\n");
            printf("  -p P  Set the parameter p to P%%. (Default : P = 10)\n");}
            exit(0); 

            case 'r':filename = argv[optind]; exit (0);
            case 'm':filename = argv[optind]; exit (0);

            case 's':if (optind<argc){
                filename = argv[optind];
            graph_t *graph= parse_graph (filename);
            print_stats(graph);
            free_graph (graph);
            exit (0);}
            else{ printf ("No file name provided\n");
                    exit (1);
            }

            case 'p':filename = argv[optind];
                exit(0);

           
            default : printf("error\n"); exit (1);
        } 
    }
}
