#include <stdio.h>
#include <stdlib.h>
#include "randomsurfer.h"
#include "utils.h"
#include "graph.h"

    struct Visited {
    int times;
    };

void simulate_rs (graph_t *graph, int no_steps, double p) {
    rand_init();
    if (p==0.1){p=p*100;}

    int start_s = randu(graph->count);

    struct Visited visited[graph->count];

    for(int i=0; i<graph->count; i++){
        visited[i].times=0;
    }

    int current_s = start_s;

    for(int i = 0; i<no_steps; i++){
        if( randu(100)< p){
            current_s= randu(graph->count);
        }else{
            if (graph->vertices[current_s]->num_edges==0) {
                current_s= randu(graph->count);
            }else {
            int edge_index = randu( graph-> vertices[current_s]-> num_edges);
           vertice_t *next_vertice = graph->vertices[current_s]->out_edges[edge_index];

           for(int j=0; j<graph->count; j++){
                if (graph->vertices[j]== next_vertice){
                    current_s= j;
                }
           }
            }
        }
        visited[current_s].times++;
    }
    for(int i=0; i<graph->count; i++){
    printf("%s ",graph->vertices[i]->name);
    printf("%.10f\n",(double)(((double)visited[i].times)/((double)no_steps)));
    }

}

