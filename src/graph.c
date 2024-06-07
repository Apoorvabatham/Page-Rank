#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"

graph_t *init_graph (const char *name){
    graph_t *graph = calloc (1, sizeof (graph_t));
    if (!graph){
        fprintf (stderr, "memory exhausted for allocating graph\n");
        exit(1);
    }
    graph->vertices = NULL;
    graph->count = 0;
    graph-> name = calloc (strlen(name)+1, sizeof (char));
    strcpy(graph->name, name);
    return graph;
}

void free_graph (graph_t *graph){
    if (!graph) return;
    while(graph->count--){
        vertice_t *vertice= graph-> vertices [graph->count];
        if (vertice-> num_edges)
            free (vertice-> out_edges);
        free (vertice->name);
        free (vertice);
    }
    free (graph->name);
    free(graph-> vertices);
    free (graph);
}

vertice_t *get_vertice (graph_t *graph, const char *name){
    for(int tmp= 0; tmp< graph->count; tmp++){
        if (strcmp(graph->vertices[tmp]->name, name)== 0){
            return graph->vertices[tmp];
        }
    }
    vertice_t *vertice = calloc (1, sizeof(vertice_t));
    if (!vertice) return NULL;
    vertice->out_edges= NULL;
    vertice->num_edges = 0;
    vertice->in_edges= 0;
    vertice-> something= 0;
    vertice ->name = calloc(strlen(name) +1, sizeof(char));
    strcpy(vertice->name, name);
    vertice_t **temp = realloc(graph->vertices, (graph->count + 1) * sizeof(vertice_t *));
    if (!temp) {
    free(vertice->name);
    free(vertice);
    return NULL;
}
graph->vertices = temp;
    graph->vertices[graph->count++]=vertice;
    return vertice;
}

void add_edge (vertice_t *source, vertice_t *target){
    vertice_t **temp = realloc(source->out_edges, (source->num_edges + 1) * sizeof(vertice_t *));
    if (!temp) {
    return;}
    source->out_edges = temp;
    source->out_edges[source->num_edges++]= target;
    target->in_edges++;
}