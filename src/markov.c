#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "markov.h"
#include "graph.h"

void calculate_Tprob (graph_t *graph, double p, double **tp){

    for (int i=0; i<graph->count; i++){
        vertice_t *current_v = graph->vertices[i];

        if (current_v->num_edges>0){

                for(int y; y<graph->count;y++){
                    tp[i][y]= p/ graph->count;
                }
            for(int j=0; j<current_v->num_edges; j++){
                vertice_t *target_v= current_v->out_edges[j];
                int tv_num;
                    for(int k=0; k<graph->count; k++){
                        if(target_v==graph->vertices[k]){
                            tv_num= k;
                        }
                    }
                 tp[i][tv_num] += (1-p)/current_v->num_edges; 
            }

        }else{
         for(int x= 0; x<graph->count;x++){
            tp[i][x] += (double)1.0/graph->count;
         }   
        }  
    }
}

void simulate_markov (graph_t *graph, int no_steps, double p) {

    if(graph== NULL || graph->count==0) return;
     double **tp = calloc(graph->count,sizeof(double *));
    if (tp == NULL) {
        fprintf(stderr, "Memory allocation failed for tp.\n");
        exit(1);
    }
    for (int i = 0; i < graph->count; i++) {
        tp[i] = calloc(graph->count, sizeof(double));
        if (tp[i] == NULL) {
            fprintf(stderr, "Memory allocation failed for rows of tp.\n");
            exit(1);
        }
    }

    double *current_vector = calloc(graph->count, sizeof(double));

    double *next_vector = calloc(graph->count, sizeof(double));

    if (current_vector == NULL || next_vector == NULL) {
        fprintf(stderr, "Memory allocation failed for vectors.\n");
        exit(1);
    }
    for (int i = 0; i < graph->count; i++) {
        current_vector[i] = (double)1.0 /graph->count;
    }
    
    calculate_Tprob (graph, p, tp);

    for(int a=0;a< no_steps; a++){
        for(int i= 0; i<graph->count; i++){
            next_vector[i]= 0.0;
            for (int j= 0; j<graph->count; j++){
                next_vector[i] += current_vector[j] *tp [j][i];
            }
        }
        
        for (int k= 0; k< graph->count; k++){
            current_vector[k]= next_vector[k];
        }
    }

    for (int i = 0; i< graph->count; i++){
        printf("%s %.10f\n", graph->vertices[i]->name, current_vector[i]);
    }
    for(int a=0; a<graph->count; a++){
        free(tp[a]);
    }
    free(tp);   
    free (current_vector);
    free (next_vector);
}