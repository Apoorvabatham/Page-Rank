#ifndef MARKOV_H
#define MARKOV_H
#include "graph.h"

void calculate_Tprob(graph_t *graph, double p, double **tp);

void simulate_markov (graph_t* graph, int no_steps, double p);

#endif