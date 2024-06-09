#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "randomsurfer.h"
#include "utils.h"
#include "graph.h"

    struct Visited {
    char name[256];
    float times;
    };

void simulate_rs (graph_t *graph, int no_steps, double p) {
    rand_init();

    int start_s = randu(graph->count);

    struct Visited visited[graph->count];

    for(int i=0; i<graph->count; i++){
        strncpy(visited[i].name ,graph->vertices[i]->name, sizeof(visited[i].name) - 1);
        visited[i].name[sizeof(visited[i].name)-1]= '\0';
        visited[i].times=0;
    }

    int current_s = start_s;

    for(int i = 0; i<no_steps; i++){
        if( randu(100)< p*100){
            current_s= randu(graph->count);
        }else{
            if (graph->vertices[current_s]->num_edges> 0) {
            int edge_index = randu( graph-> vertices[current_s]-> num_edges);
           vertice_t *next_vertice = graph->vertices[current_s]->out_edges[edge_index];

           for(int j=0; j<graph->count; j++){
                if (graph->vertices[j]== next_vertice){
                    current_s= j;
                    break;
                }
           }
            }else {
                current_s= randu(graph->count);
            }
        }
        visited[current_s].times++;
    }
    for(int i=0; i<graph->count; i++){
    printf("%s  ",visited[i].name);
    printf("%f\n",(float)(visited[i].times)/no_steps);
    }

}

