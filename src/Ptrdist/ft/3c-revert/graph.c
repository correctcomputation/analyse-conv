





























#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


#define TRUE 1
#define FALSE 0

#ifdef __MINGW32__
#define random() rand()
#endif

#define GET_WEIGHT	(random() + 1) % MAX_WEIGHT




static int generatedEdges;




_Ptr<Vertices>  GenTree(int vertex);
_Ptr<Vertices> AddEdges(_Ptr<Vertices> graph, int nVertex, int nEdge);
_Ptr<Vertices> PickVertex(_Ptr<Vertices> graph, int whichVertex);
void Connect(_Ptr<Vertices> vertex1, _Ptr<Vertices> vertex2);
int Duplicate(_Ptr<Vertices> vertex1, _Ptr<Vertices> vertex2);
_Ptr<Vertices>  NewVertex(void);
_Ptr<Edges>  NewEdge(void);
void PrintNeighbors(_Ptr<Vertices> vertex);




static id = 1;








_Ptr<Vertices> 
GenGraph(int nVertex, int nEdge)
{
  _Ptr<Vertices> graph = 0;

  ((void) sizeof ((nEdge + 1 >= nVertex) ? 1 : 0), __extension__ ({ if (nEdge + 1 >= nVertex) ; else __assert_fail ("nEdge + 1 >= nVertex", "/home/matt/analyze-conversion-1.wt/src/Ptrdist/ft/manual-em-tmp/graph.c", 81, __extension__ __PRETTY_FUNCTION__); }));
  ((void) sizeof ((nEdge <= nVertex * (nVertex - 1) / 2) ? 1 : 0), __extension__ ({ if (nEdge <= nVertex * (nVertex - 1) / 2) ; else __assert_fail ("nEdge <= nVertex * (nVertex - 1) / 2", "/home/matt/analyze-conversion-1.wt/src/Ptrdist/ft/manual-em-tmp/graph.c", 82, __extension__ __PRETTY_FUNCTION__); }));

  generatedEdges = 0;

  graph = GenTree(nVertex);
  graph = AddEdges(graph, nVertex, nEdge - nVertex + 1);
  return(graph);
}

_Ptr<Vertices> 
GenTree(int nVertex)
{
  int i;
  int weight;
  _Ptr<Vertices> vertex = 0;
  _Ptr<Vertices> graph = 0;
  _Ptr<Edges> edge = 0;

  graph = NewVertex();
  ((*(graph)).next) = graph;

  for(i = 1; i < nVertex; i++)
  {
    vertex = NewVertex();
    edge = NewEdge();




    ((*(vertex)).edges) = edge;





    ((*(edge)).vertex) = PickVertex(graph, random() % i);
    weight = (random() + 1) % 100;
    ((*(edge)).weight) = weight;
    ((*(edge)).source) = vertex;




    ((*(vertex)).next) = ((*(graph)).next);
    ((*(graph)).next) = vertex;




    edge = NewEdge();
    ((*(edge)).weight) = weight;
    ((*(edge)).source) = ((*(((*(vertex)).edges))).vertex);
    ((*(edge)).vertex) = vertex;
    ((*(edge)).next) = ((*(((*(((*(vertex)).edges))).vertex))).edges);
    ((*(((*(((*(vertex)).edges))).vertex))).edges) = edge;
   }

  return(graph);
}

_Ptr<Vertices> AddEdges(_Ptr<Vertices> graph, int nVertex, int nEdge)
{
  int i;
  _Ptr<Vertices> vertex1 = 0;
  _Ptr<Vertices> vertex2 = 0;

  ((void) sizeof ((graph != ((void *) 0)) ? 1 : 0), __extension__ ({ if (graph != ((void *) 0)) ; else __assert_fail ("graph != NULL_VERTEX", "/home/matt/analyze-conversion-1.wt/src/Ptrdist/ft/manual-em-tmp/graph.c", 148, __extension__ __PRETTY_FUNCTION__); }));
  ((void) sizeof ((nEdge >= 0) ? 1 : 0), __extension__ ({ if (nEdge >= 0) ; else __assert_fail ("nEdge >= 0", "/home/matt/analyze-conversion-1.wt/src/Ptrdist/ft/manual-em-tmp/graph.c", 149, __extension__ __PRETTY_FUNCTION__); }));

  for(i = 0; i < nEdge; i++)
  {
    do
    {
      vertex1 = PickVertex(graph, random() % nVertex);
      vertex2 = PickVertex(((*(vertex1)).next), (random() % nVertex) - 1);
      ((void) sizeof ((vertex1 != vertex2) ? 1 : 0), __extension__ ({ if (vertex1 != vertex2) ; else __assert_fail ("vertex1 != vertex2", "/home/matt/analyze-conversion-1.wt/src/Ptrdist/ft/manual-em-tmp/graph.c", 157, __extension__ __PRETTY_FUNCTION__); }));
    }
    while(Duplicate(vertex1, vertex2));

    Connect(vertex1, vertex2);
  }

  return(graph);
}

_Ptr<Vertices> PickVertex(_Ptr<Vertices> graph, int whichVertex)
{
  int i;

  for(i = 0; i < whichVertex; i++)
  {
    graph = ((*(graph)).next);
  }

  return(graph);
}

void
Connect(_Ptr<Vertices> vertex1, _Ptr<Vertices> vertex2)
{
  int weight;
  _Ptr<Edges> edge = 0;

  weight = (random() + 1) % 100;

  edge = NewEdge();
  ((*(edge)).weight) = weight;
  ((*(edge)).source) = vertex1;
  ((*(edge)).vertex) = vertex2;
  ((*(edge)).next) = ((*(vertex1)).edges);
  ((*(vertex1)).edges) = edge;

  edge = NewEdge();
  ((*(edge)).weight) = weight;
  ((*(edge)).source) = vertex2;
  ((*(edge)).vertex) = vertex1;
  ((*(edge)).next) = ((*(vertex2)).edges);
  ((*(vertex2)).edges) = edge;
}

int
Duplicate(_Ptr<Vertices> vertex1, _Ptr<Vertices> vertex2)
{
  _Ptr<Edges> edge = 0;

  edge = ((*(vertex1)).edges);

  while(edge != ((void *) 0))
  {
    if(((*(edge)).vertex) == vertex2)
    {
      return(1);
    }

    edge = ((*(edge)).next);
  }

  return(0);
}

_Ptr<Vertices> 
NewVertex(void)
{
  _Ptr<Vertices> vertex = 0;

  vertex = calloc<Vertices>(1, sizeof(Vertices));

  if(vertex == ((void*)0))
  {
     { (fprintf)(stderr, "Could not malloc\n"); };
    exit(1);
  }

  ((*(vertex)).id) = id++;
  ((*(vertex)).edges) = ((void*)0);
  ((*(vertex)).next) = ((void*)0);

  return(vertex);
}

_Ptr<Edges> 
NewEdge(void)
{
  _Ptr<Edges> edge = 0;

  edge = calloc<Edges>(1, sizeof(Edges));

  if(edge == ((void*)0))
  {
     { (fprintf)(stderr, "Could not malloc\n"); };
    exit(1);
  }

  ((*(edge)).weight) = 0;
  ((*(edge)).vertex) = ((void*)0);
  ((*(edge)).next) = ((void*)0);

  return(edge);
}

void
PrintGraph(_Ptr<Vertices> graph)
{
  _Ptr<Vertices> vertex = 0;

  ((void) sizeof ((graph != ((void*)0)) ? 1 : 0), __extension__ ({ if (graph != ((void*)0)) ; else __assert_fail ("graph != NULL", "/home/matt/analyze-conversion-1.wt/src/Ptrdist/ft/manual-em-tmp/graph.c", 267, __extension__ __PRETTY_FUNCTION__); }));

  vertex = graph;
  do
  {
     { (printf)("Vertex %d is connected to:", ((*(vertex)).id)); };
    PrintNeighbors(vertex);
     { (printf)("\n"); };
    vertex = ((*(vertex)).next);
  }
  while(vertex != graph);
}

void
PrintNeighbors(_Ptr<Vertices> vertex)
{
  _Ptr<Edges> edge = 0;

  edge = ((*(vertex)).edges);
  while(edge != ((void*)0))
  {
     { (printf)(" %d(%d)[%d]", ((*(((*(edge)).vertex))).id), ((*(edge)).weight), ((*(((*(edge)).source))).id)); };
    edge = ((*(edge)).next);
  }
}

