#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "markov.h"
#include "graph.h"

void calculate_Tprob (graph_t *graph, double p, double **tp){

    for (int i=0; i<graph->count; i++){
        vertice_t *current_v = graph->vertices[i];
        int total_out = current_v->num_edges;
              double sum= 0.0;
        if (p == 1.0) {
            for (int j = 0; j < graph->count; j++) {
                if (total_out != 0) {
                    if (current_v->num_out_neighbor[j] > 0)
                        tp[i][j] = 1.0;
                    else
                        tp[i][j] = 0.0;
                } else {
                    tp[i][j] = 1.0 / (double)graph->count;
                }
            }
        } else {        
        for(int j= 0; j< graph->count; j++){
            if (total_out!=0){
                tp [i] [j] = (p/ (double)graph->count) +(1.0-p)*((double)current_v->num_out_neighbor[j]/(double)total_out);
            }else{
                tp [i][j]= p/(double)graph->count;
            }
            sum += tp [i][j];
        }
        if (sum != 1.0) {
            for (int j = 0; j < graph->count; j++) {
                tp[i][j] /= sum;}
            }
        }
    }
}

void simulate_markov (graph_t *graph, int no_steps, double p) {

    if(graph== NULL || graph->count==0) return;

    if (p==100){
         for (int i = 0; i< graph->count; i++){
        printf("%s %.10f\n", graph->vertices[i]->name, (1.0/(double)graph->count));
    }

        exit(0);
    }

    for(int i =0; i< graph->count; i++){
        graph->vertices[i]->num_out_neighbor= calloc(graph->count, sizeof(unsigned));
         if (graph->vertices[i]->num_out_neighbor == NULL) {
            fprintf(stderr, "Memory allocation failed for num_out_neighbor.\n");
            exit(1);
        }
        for(int j=0; j< graph->vertices[i]->num_edges; j++){
            for (int k= 0; k< graph->count; k++){
                if(strcmp(graph->vertices[i]->out_edges[j]->name, graph->vertices[k]->name )==0){
                    graph->vertices[i]->num_out_neighbor[k]++;
                }
            }
        }
    }

     double **tp = calloc(graph->count, sizeof(double *));
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
        current_vector[i] = 1.0 / (double)graph->count;
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

    for (int i=0; i<graph->count; i++){
        free (graph->vertices[i]->num_out_neighbor);
        free (tp[i]);
    }
    free(tp);
    free (current_vector);
    free (next_vector);
}
