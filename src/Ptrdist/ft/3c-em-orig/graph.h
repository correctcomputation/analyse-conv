





























#ifndef _graph_h
#define _graph_h

struct _Vertices;

typedef struct _Edges
{
  int weight;

  _Ptr<struct _Vertices> source;
  _Ptr<struct _Vertices> vertex;
  _Ptr<struct _Edges> next;
} Edges;

typedef struct _Vertices
{
  int id;
  _Ptr<Edges> edges;
  _Ptr<struct _Vertices> next;




  int key;
  _Ptr<Edges> chosenEdge;
} Vertices;

#define NULL_EDGE	((void *) 0)
#define NULL_VERTEX	((void *) 0)

#define MAX_WEIGHT	100

#define ID(V)		((*(V)).id)
#define EDGES(V)	((*(V)).edges)
#define NEXT_VERTEX(V)	((*(V)).next)

#define WEIGHT(E)	((*(E)).weight)
#define SOURCE(E)	((*(E)).source)
#define VERTEX(E)	((*(E)).vertex)
#define NEXT_EDGE(E)	((*(E)).next)

#define KEY(V)		((*(V)).key)
#define CHOSEN_EDGE(V)	((*(V)).chosenEdge)

_Ptr<Vertices>  GenGraph(int nVertex, int nEdge);
void PrintGraph(_Ptr<Vertices> graph);

#endif
