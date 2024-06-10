#ifndef GRAPH_H
#define GRAPH_H

typedef struct vertice {
    struct vertice **out_edges;
    unsigned *num_out_neighbor;
    unsigned in_edges;
    unsigned num_edges;
    char* name;
} vertice_t;

typedef struct graph {
    vertice_t **vertices;
    unsigned count;
    char* name;
} graph_t;

graph_t *init_graph (const char *);

void free_graph (graph_t *);

vertice_t *get_vertice (graph_t *, const char *);

void add_edge (vertice_t *, vertice_t*);

#endif
