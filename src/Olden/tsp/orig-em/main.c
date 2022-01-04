

#include "tsp.h"
#include <stdio.h>
#define conquer_thresold 150  
extern int flag;

void print_tree(Tree t)
{
  Tree left;
  Tree right;

  double x,y;

  if (!t) return;
  x = t->x; y = t->y;
  printf("x=%f,y=%f\n",x,y);
  left = t->left; right=t->right;
  print_tree(left);
  print_tree(right);
}

void print_list(Tree t)
{
  Tree tmp;
  double x,y;

  if (!t) return;
  x = t->x; y = t->y;
  printf("%f %f\n",x,y);
  for (tmp=t->next; tmp!=t; tmp=tmp->next)
    {
    x = tmp->x; y = tmp->y;
    printf("%f %f\n",x,y);
    }
}

int main(int argc,char *argv[])
{
  Tree t;
  int num;

  num=dealwithargs(argc,argv);

  printf("Building tree of size %d\n",num);
  t=build_tree(num,0,0,NumNodes,0.0,1.0,0.0,1.0);
  if (!flag) printf("Past build\n");
  if (flag) printf("newgraph\n");
  if (flag) printf("newcurve pts\n");

  printf("Call tsp(t, %d, %d)\n", 150, NumNodes);
  tsp(t,150, NumNodes);

  if (flag) print_list(t);
  if (flag) printf("linetype solid\n");

  return 0;
}
