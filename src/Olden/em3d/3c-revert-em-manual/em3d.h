








#ifndef EM3D
#define EM3D



void dealwithargs(int argc, _Array_ptr<_Nt_array_ptr<char>> argv : count(argc));
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
  _Ptr<double> value;
  _Ptr<struct node_t> next;
  _Array_ptr<_Ptr<struct node_t>> to_nodes : count(degree) ;
  _Array_ptr<_Ptr<double>> from_values : count(20) ;
  _Array_ptr<double> coeffs : count(20) ;
  int from_count;
  int from_length;
  int degree;
} node_t;

typedef struct graph_t {
  _Ptr<node_t> e_nodes _Checked[1];
  _Ptr<node_t> h_nodes _Checked[1];
} graph_t;

typedef struct table_arr_t {
  _Array_ptr<_Ptr<node_t>> table : count(0 + 1) ;
  int size;
} table_arr_t;

typedef struct table_t {
  table_arr_t e_table _Checked[1];
  table_arr_t h_table _Checked[1];
} table_t;


void compute_nodes(_Ptr<node_t> nodelist);
double gen_uniform_double(void);

#endif
