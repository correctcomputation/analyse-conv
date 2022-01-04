








#ifndef EM3D
#define EM3D

void dealwithargs(int argc, char *argv[]);
void printstats(void);
void srand48(long);
long lrand48(void);

#include <stdio.h>
#include <stdlib.h>

#define chatting printf

extern char * min_ptr;
extern char * max_ptr;

extern int n_nodes;
extern int d_nodes;
extern int local_p;
#define PROCS 1

#define assert(a) if (!a) {printf("Assertion failure\n"); exit(-1);}

typedef struct node_t {
  double *value;
  struct node_t *next;
  struct node_t **to_nodes;
  double **from_values;
  double *coeffs;
  int from_count;
  int from_length;
} node_t;

typedef struct graph_t {
  node_t *e_nodes[1];
  node_t *h_nodes[1];
} graph_t;

typedef struct table_t {
  node_t **e_table[1];
  node_t **h_table[1];
} table_t;


void compute_nodes(node_t *nodelist);
double gen_uniform_double(void);

#endif
