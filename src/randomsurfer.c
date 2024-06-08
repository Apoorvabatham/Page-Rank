#include <math.h>
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
        strcpy(visited[i].name ,graph->vertices[i]->name);
        visited[i].times=0;
    }

    int current_s = start_s;
    char nem [256];

    for(int i = 0; i<no_steps; i++){
        if( randu(100)< p){
            current_s= randu(graph->count);
        }else{
            int edge_index = randu( graph-> vertices[current_s]-> num_edges);
            strcpy( nem, graph->vertices[current_s]->out_edges[edge_index]->name);
            for(int j=0; j<graph->count;j++){
            if (!strcmp(nem, graph->vertices[j]->name)){
                current_s=j;
            }
        }
        }
        for(int j=0; j<graph->count;j++){
            if (!strcmp(nem, visited[j].name))
            visited[j].times++;
        }
    }
    for(int i=0; i<graph->count; i++){
    printf("%s  ",visited[i].name);
    if(visited[i].times==0){
        printf("0.0\n");

    }else{
    printf("%f\n",(float)(visited[i].times)/graph->count);}
    }

}

