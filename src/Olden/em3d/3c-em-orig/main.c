

#include "em3d.h"
#include "make_graph.h"

extern int NumNodes;

int DebugFlag;

void print_graph(_Ptr<graph_t> graph, int id)
{
  _Ptr<node_t> cur_node = ((void *)0);
  cur_node=graph->e_nodes[id];

  for(; cur_node; cur_node=cur_node->next)
    {
      printf("E: value %f, from_count %d\n", *cur_node->value,
        cur_node->from_count);
    }
  cur_node=graph->h_nodes[id];
  for(; cur_node; cur_node=cur_node->next)
    {
      printf("H: value %f, from_count %d\n", *cur_node->value,
        cur_node->from_count);
    }
}

extern int nonlocals;

int main(int argc, _Array_ptr<_Nt_array_ptr<char>> argv : count(argc))
{
  int i;
  _Ptr<graph_t> graph = ((void *)0);

  dealwithargs(argc,argv);

  printf("Hello world--Doing em3d with args %d %d %d %d\n",
           n_nodes,d_nodes,local_p,NumNodes);
  graph=initialize_graph();
  if (DebugFlag)
    for(i=0; i<NumNodes;i++)
      print_graph(graph,i);


  compute_nodes(graph->e_nodes[0]);
  compute_nodes(graph->h_nodes[0]);

  printf("nonlocals = %d\n",nonlocals);

  printstats();
  return 0;
}
