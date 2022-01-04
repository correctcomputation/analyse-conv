



































#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <sys/time.h>

#include "Fheap.h"
#include "graph.h"

#pragma CHECKED_SCOPE ON

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
main(int argc, _Array_ptr<_Nt_array_ptr<const char>> argv : count(argc) )
{
  int nVertex;
  int nEdge;
  _Ptr<Vertices> graph = 0;

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
    _Unchecked { (printf)("Generating a connected graph ... "); };
  }

  graph = GenGraph(nVertex, nEdge);

  if(debug)
  {
    _Unchecked { (printf)("done\nFinding the mininmum spanning tree ... "); };
  }

  graph = MST(graph);

  if(debug)
  {
    _Unchecked { (printf)("done\nThe graph:\n"); };
    PrintGraph(graph);
    _Unchecked { (printf)("The minimum spanning tree:\n"); };
    PrintMST(graph);
  }

  if(debug)
  {
    _Unchecked { (printf)("Time spent in finding the mininum spanning tree:\n"); };
  }
#ifdef PLUS_STATS


#endif 
  exit(0);
  return 0;
}

_Ptr<Vertices> MST(_Ptr<Vertices> graph)
{
  _Ptr<HeapP> heap = 0;
  _Ptr<Vertices> vertex = 0;
  _Ptr<Edges> edge = 0;
  ;

  InitFHeap();








  vertex = graph;
  ((*(vertex)).key) = 0;
  heap = MakeHeap();
  (void)Insert(&heap, vertex);

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
  _Ptr<Vertices> vertex = 0;

  ((void) sizeof ((graph != ((void *) 0)) ? 1 : 0), __extension__ ({ if (graph != ((void *) 0)) ; else __assert_fail ("graph != NULL_VERTEX", "/home/matt/analyze-conversion-1.wt/src/Ptrdist/ft/manual-em-tmp/ft.c", 183, __extension__ __PRETTY_FUNCTION__); }));

  vertex = ((*(graph)).next);

  while(vertex != graph)
  {
    _Unchecked { (printf)("vertex %d to %d\n", ((*(vertex)).id), ((*(((*(((*(vertex)).chosenEdge))).source))).id)); };
    vertex = ((*(vertex)).next);
  }

}

