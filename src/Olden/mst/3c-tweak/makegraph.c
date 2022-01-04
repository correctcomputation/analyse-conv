

#include "mst.h"




#define CONST_m1 10000
#define CONST_b 31415821
#define RANGE 2048
static int HashRange;

static int mult(int p, int q)
{
   int p1, p0, q1, q0;

   p1=p/10000; p0=p%10000;
   q1=q/10000; q0=q%10000;
   return (((p0*q1+p1*q0) % 10000)*10000 +p0*q0);
}

static int random2(int seed)
{
  int tmp;
  tmp = (mult(seed,31415821)+1);
  return tmp;
}

static int compute_dist(int i,int j, int numvert)
{
  int less, gt;
  if (i<j) {less = i; gt = j;} else {less = j; gt = i;}
  return (random2(less*numvert+gt) % 2048)+1;
}

static int hashfunc(unsigned int key)
{
  return ((key>>3) % HashRange);
}

static void AddEdges(int count1, Graph retval, int numproc, int perproc, int numvert, int j)
{
  Vertex tmp;
  Vertex helper _Checked[1] = {((void *)0)};
  int i;

  for (i=0; i<numproc; i++) {
    helper[i] = retval->vlist[i];
  }

  for (tmp = retval->vlist[j]; tmp; tmp=tmp->next)
    {
      for (i=0; i<numproc*perproc; i++)
        {
          int pn,offset,dist;
          Vertex dest;
          Hash hash;

          if (i!=count1)
            {
              dist = compute_dist(i,count1,numvert);
              pn = i/perproc;
              offset = i % perproc;
              dest = ((helper[pn])+offset);
              hash = tmp->edgehash;
              HashInsert((void *) dist,(unsigned int) dest,hash);

            }
        }
      count1++;
    }
}

Graph MakeGraph(int numvert, int numproc)
{
  int perproc = numvert/numproc;
  int i,j;
  int count1;
  Vertex v;
  Vertex tmp;
  Vertex block;
  Graph retval;
  retval = (Graph)malloc<struct graph_st>(sizeof(*retval));
  for (i=0; i<1; i++)
    {
      retval->vlist[i]=((void*)0);
    }
  printf("Make phase 2\n");
  for (j=numproc-1; j>=0; j--)
    {
      block = (Vertex) malloc<struct vert_st>(perproc*(sizeof(*tmp)));
      v = ((void*)0);
      for (i=0; i<perproc; i++)
        {
          tmp = block+(perproc-i-1);
          HashRange = numvert/4;
          tmp->mindist = 9999999;
          tmp->edgehash = MakeHash(numvert/4,hashfunc);
          tmp->next = v;
          v=tmp;
        }
      retval->vlist[j] = v;
    }

  printf("Make phase 3\n");
  for (j=numproc-1; j>=0; j--)
    {
      count1 = j*perproc;
      AddEdges(count1, retval, numproc, perproc, numvert, j);
    }
  printf("Make phase 4\n");

  printf("Make returning\n");
  return retval;
}






