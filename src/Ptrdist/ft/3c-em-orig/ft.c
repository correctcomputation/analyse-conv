



































#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <sys/time.h>

#include "Fheap.h"
#include "graph.h"

#define MINUS_INFINITY		INT_MIN
#define PLUS_INFINITY		INT_MAX

#define DEFAULT_N_VERTEX	10
#define DEFAULT_N_EDGE		9

#ifdef __MINGW32__
#define srandom(x) srand(x)
#endif




void PrintMST(_Ptr<Vertices> graph);
_Ptr<Vertices> MST(_Ptr<Vertices> graph);




int debug = 1;

int
main(int argc, _Array_ptr<_Nt_array_ptr<char>> argv : count(argc))
{
  int nVertex;
  int nEdge;
  _Ptr<Vertices> graph = ((void *)0);

  nVertex = 10;
  nEdge = 9;

  if(argc > 1)
  {
    nVertex = atoi(argv[1]);
    if(argc > 2)
    {
      nEdge = atoi(argv[2]);
      if(argc > 3)
      {
        srandom(atoi(argv[3]));
      }
    }
  }

  if(debug)
  {
    printf("Generating a connected graph ... ");
  }

  graph = GenGraph(nVertex, nEdge);

  if(debug)
  {
    printf("done\nFinding the mininmum spanning tree ... ");
  }

  graph = MST(graph);

  if(debug)
  {
    printf("done\nThe graph:\n");
    PrintGraph(graph);
    printf("The minimum spanning tree:\n");
    PrintMST(graph);
  }

  if(debug)
  {
    printf("Time spent in finding the mininum spanning tree:\n");
  }
#ifdef PLUS_STATS


#endif 
  exit(0);
  return 0;
}

_Ptr<Vertices> MST(_Ptr<Vertices> graph)
{
  _Ptr<HeapP> heap = ((void *)0);
  _Ptr<Vertices> vertex = ((void *)0);
  _Ptr<Edges> edge = ((void *)0);
  ;

  InitFHeap();








  vertex = graph;
  ((*(vertex)).key) = 0;
  heap = MakeHeap();
  (void)Insert(&heap, (_Ptr<Item>)vertex);

  vertex = ((*(vertex)).next);
  while(vertex != graph)
  {
    ((*(vertex)).key) = 2147483647;
    vertex = ((*(vertex)).next);
  }
  while(vertex != graph);

  vertex = FindMin(heap);
  while(vertex != ((void *) 0))
  {
    heap = DeleteMin(heap);
    ((*(vertex)).key) = (-2147483647 -1);
    edge = ((*(vertex)).edges);
    while(edge != ((void *) 0))
    {
      if(((*(edge)).weight) < ((*(((*(edge)).vertex))).key))
      {
        ((*(((*(edge)).vertex))).key) = ((*(edge)).weight);
        ((*(((*(edge)).vertex))).chosenEdge) = edge;
        (void)Insert(&heap, ((*(edge)).vertex));
      }
      edge = ((*(edge)).next);
    }
    vertex = FindMin(heap);
  }
  ;
  return(graph);
}

void
PrintMST(_Ptr<Vertices> graph)
{
  _Ptr<Vertices> vertex = ((void *)0);

  ((void) sizeof ((graph != ((void *) 0)) ? 1 : 0), __extension__ ({ if (graph != ((void *) 0)) ; else __assert_fail ("graph != NULL_VERTEX", "/home/matt/analyze-conversion/src/Ptrdist/ft/tmp-em-orig/ft.c", 181, __extension__ __PRETTY_FUNCTION__); }));

  vertex = ((*(graph)).next);

  while(vertex != graph)
  {
    printf("vertex %d to %d\n", ((*(vertex)).id), ((*(((*(((*(vertex)).chosenEdge))).source))).id));
    vertex = ((*(vertex)).next);
  }

}

