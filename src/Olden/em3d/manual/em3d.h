/* For copyright information, see olden_v1.0/COPYRIGHT */

/* em3d.h - Header file for the electromagnetic problem in 3 dimensions
 *
 * By:  Martin C. Carlisle
 * Date: Feb. 23, 1994
 *
 */

#ifndef EM3D
#define EM3D



void dealwithargs(int argc, _Array_ptr<_Nt_array_ptr<char>> argv : count(argc));
void printstats(void);
void srand48(long);
long lrand48(void);

#include <stdio.h>
#include <stdlib.h>

#pragma CHECKED_SCOPE ON
#define chatting(...) _Unchecked { printf(__VA_ARGS__); }

// extern char * min__Ptr;
// extern char * max__Ptr;

extern int n_nodes; /* number of nodes (E and H) */
extern int d_nodes; /* degree of nodes */
extern int local_p; /* percentage of local edges */
#define PROCS 1

#define assert(a) if (!a) { puts("Assertion failure"); exit(-1); }

typedef struct node_t {
  _Ptr<double> value;
  _Ptr<struct node_t> next;
  _Array_ptr<_Ptr<struct node_t>> to_nodes : count(degree); /* array of nodes pointed to */
  _Array_ptr<_Ptr<double>> from_values : count(from_count); /* array of _Ptrs to vals where data comes from */
  _Array_ptr<double> coeffs : count(from_count); /* array of coeffs on edges */
  int from_count;
  int from_length;
  int degree;
} node_t;

typedef struct graph_t {
  _Ptr<node_t> e_nodes _Checked[PROCS];
  _Ptr<node_t> h_nodes _Checked[PROCS];
} graph_t;

typedef struct table_arr_t {
  _Array_ptr<_Ptr<node_t>> table : count(size);
  int size;
} table_arr_t;

typedef struct table_t {
  table_arr_t e_table _Checked[PROCS];
  table_arr_t h_table _Checked[PROCS];
} table_t;

/* Perform 1 step for a nodelist */
void compute_nodes(_Ptr<node_t> nodelist);
double gen_uniform_double(void);

#pragma CHECKED_SCOPE OFF
#endif
