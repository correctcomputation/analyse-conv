








#ifndef EM3D
#define EM3D



void dealwithargs(int argc, char * * argv );
void printstats(void);
void srand48(long);
long lrand48(void);

#include <stdio.h>
#include <stdlib.h>

#define chatting(...)  { printf(__VA_ARGS__); }




extern int n_nodes;
extern int d_nodes;
extern int local_p;
#define PROCS 1

#define assert(a) if (!a) { puts("Assertion failure"); exit(-1); }

typedef struct node_t {
  double * value;
  struct node_t * next;
  struct node_t * * to_nodes ;
  double * * from_values ;
  double * coeffs ;
  int from_count;
  int from_length;
  int degree;
} node_t;

typedef struct graph_t {
  node_t * e_nodes [1];
  node_t * h_nodes [1];
} graph_t;

typedef struct table_arr_t {
  node_t * * table ;
  int size;
} table_arr_t;

typedef struct table_t {
  table_arr_t e_table [1];
  table_arr_t h_table [1];
} table_t;


void compute_nodes(node_t * nodelist);
double gen_uniform_double(void);

#endif
