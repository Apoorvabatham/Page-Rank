
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graphparse.h"
#include "graph.h"

graph_t *parse_graph (const char *filename){
    FILE *file = fopen (filename, "r");
    if (!file){
        fprintf(stderr, "wrong file name!!!!!\n");
        exit(1);
    }
    char s_name [257];
    char t_name [257];

    int c= fscanf (file, "digraph %s {\n", &s_name[0]);
    if (c!=1){
        fprintf(stderr,"Error while parsing graph definition.\n");
        fclose (file);
        exit (1);
    }
    if (strlen(s_name) >= 256) {
    fprintf(stderr, "Graph name is too longgggg\n");
    fclose(file);
    exit(0);
}
    
    graph_t *graph =init_graph (s_name);
    if (!graph){
        fprintf(stderr, "Error while initializing the graph");
        fclose(file);
        exit(1);
    }
    
    while (1){
    memset(s_name, 0, 256);
    memset(s_name, 0, 256);
        c= fscanf(file, "%s -> %[^;];\n", &s_name[0], &t_name[0]);
        if (c== EOF){
            fprintf (stderr, "Error in file while reading\n");
            fclose(file);
            exit(1);
        }
        if (s_name[0] == '}') break;
        vertice_t *s_vertice = get_vertice (graph, s_name);
         if (!s_vertice) {
            fprintf(stderr, "Error getting vertice.\n");
            fclose(file);
            exit(1);
        }
        vertice_t *t_vertice = get_vertice (graph, t_name);
        if (!t_vertice) {
            fprintf(stderr, "Error getting vertice.\n");
            fclose(file);
            exit(1);
        }
        add_edge ( s_vertice, t_vertice);
    }

    fclose (file);
    return graph;
}

void print_stats(graph_t* graph){
    printf("%s:\n",graph->name);

    if (graph->count==0){
         printf("- num nodes: 0\n");
          printf("- num edges: 0\n");
           printf("- indegree: 0-0\n");
            printf("- outdegree: 0-0\n");
    }else{

    printf("- num nodes: %d\n", graph->count);

    unsigned num_edge= 0;
    for(unsigned i=0 ;i<graph->count ;i++){
        num_edge+= graph->vertices[i]->num_edges;
    }
    printf("- num edges: %d\n", num_edge);

    int mini= graph->vertices[0]->in_edges;
    int maxi= graph->vertices[0]->in_edges;
    for(unsigned i= 1; i< graph->count; i++){
        if (graph->vertices[i]->in_edges< mini)
            mini= graph->vertices[i]->in_edges;
    
        if (graph->vertices[i]->in_edges> maxi)
            maxi= graph->vertices[i]->in_edges ;
    } 
    printf("- indegree: %d-%d\n", mini, maxi);

    int mino= graph->vertices[0]->num_edges;
    int maxo= graph->vertices[0]->num_edges;
     for(unsigned i=1; i< graph->count; i++){
        if (graph->vertices[i]->num_edges< mino)
            mino= graph->vertices[i]->num_edges;
    
        if (graph->vertices[i]->num_edges> maxo)
            maxo= graph->vertices[i]->num_edges ;
    } 
    printf("- outdegree: %d-%d\n", mino, maxo);
    }
}