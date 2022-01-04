

#include "tsp.h"
#ifdef FUTURES
#include "future-cell.h"
#endif
#define NULL 0

static Tree conquer(Tree t);
static Tree merge(Tree a, Tree b, Tree t, int nproc);
static Tree makelist(Tree t);
static void reverse(Tree t);
static double distance(Tree a, Tree b);
extern double sqrt(double a);


static double distance(Tree a, Tree b) {
  double ax,ay,bx,by;

  ax = a->x; ay = a->y;
  bx = b->x; by = b->y;
  return (sqrt((ax-bx)*(ax-bx)+(ay-by)*(ay-by)));
}



static Tree makelist(Tree t) {
  Tree left = ((void *)0);
  Tree right = ((void *)0);
  Tree tleft = ((void *)0);
  Tree tright = ((void *)0);
  Tree retval = t;

  if (!t) return 0;

  left = makelist(t->left);
  right = makelist(t->right);

  if (right) { retval = right; tright = t->right; tright->next = t; }
  if (left) { retval=left; tleft=t->left; tleft->next = (right) ? right : t; }
  t->next = 0;

  return retval;
}


static void reverse(Tree t) {
  Tree prev = ((void *)0);
  Tree back = ((void *)0);
  Tree next = ((void *)0);
  Tree tmp = ((void *)0);

  if (!t) return;


  prev = t->prev;
  prev->next = 0;
  t->prev = 0;
  back = t;
  tmp = t;
  for (t=t->next; t; back=t,t=next) {
    next = t->next;
    t->next = back;
    back->prev = t;
    }
  tmp->next = prev;
  prev->prev = tmp;



}


static Tree conquer(Tree t) {
  Tree cycle = ((void *)0);
  Tree tmp = ((void *)0);
  Tree min = ((void *)0);
  Tree prev = ((void *)0);
  Tree next = ((void *)0);
  Tree donext = ((void *)0);
  double mindist,test;
  double mintonext, mintoprev, ttonext, ttoprev;

  if (!t) return 0;
  t=makelist(t);



  cycle = t;
  t = t->next;
  cycle->next = cycle;
  cycle->prev = cycle;

  for (; t; t=donext) {
    donext = t->next;
    min = cycle;
    mindist = distance(t,cycle);
    for (tmp=cycle->next; tmp!=cycle; tmp=tmp->next) {
      test = distance(tmp,t);
      if (test < mindist) {
        mindist = test;
        min = tmp;
        }
      }
    next = min->next;
    prev = min->prev;
    mintonext = distance(min,next);
    mintoprev = distance(min,prev);
    ttonext = distance(t,next);
    ttoprev = distance(t,prev);
    if ((ttoprev - mintoprev) < (ttonext - mintonext)) {

      prev->next = t;
      t->next = min;
      t->prev = prev;
      min->prev = t;
      }
    else {
      next->prev = t;
      t->next = next;
      min->next = t;
      t->prev = min;
      }
    }


  return cycle;
}


static Tree merge(Tree a, Tree b, Tree t, int nproc) {
  Tree min = ((void *)0);
  Tree next = ((void *)0);
  Tree prev = ((void *)0);
  Tree tmp = ((void *)0);
  double mindist,test,mintonext,mintoprev,ttonext,ttoprev;
  Tree n1 = ((void *)0);
  Tree p1 = ((void *)0);
  Tree n2 = ((void *)0);
  Tree p2 = ((void *)0);
  double tton1,ttop1,tton2,ttop2;
  double n1ton2,n1top2,p1ton2,p1top2;
  int choice;


  min = a;
  mindist = distance(t,a);
  tmp = a;
  for (a=a->next; a!=tmp; a=a->next) {
    test = distance(a,t);
    if (test < mindist) {
      mindist = test;
      min = a;
      }
    }
  next = min->next;
  prev = min->prev;
  mintonext = distance(min,next);
  mintoprev = distance(min,prev);
  ttonext = distance(t,next);
  ttoprev = distance(t,prev);
  if ((ttoprev - mintoprev) < (ttonext - mintonext)) {

    p1 = prev;
    n1 = min;
    tton1 = mindist;
    ttop1 = ttoprev;
    }
  else {
    p1 = min;
    n1 = next;
    ttop1 = mindist;
    tton1 = ttonext;
    }


  min = b;
  mindist = distance(t,b);
  tmp = b;
  for (b=b->next; b!=tmp; b=b->next) {
    test = distance(b,t);
    if (test < mindist) {
      mindist = test;
      min = b;
      }
    }
  next = min->next;
  prev = min->prev;
  mintonext = distance(min,next);
  mintoprev = distance(min,prev);
  ttonext = distance(t,next);
  ttoprev = distance(t,prev);
  if ((ttoprev - mintoprev) < (ttonext - mintonext)) {

    p2 = prev;
    n2 = min;
    tton2 = mindist;
    ttop2 = ttoprev;
    }
  else {
    p2 = min;
    n2 = next;
    ttop2 = mindist;
    tton2 = ttonext;
    }






  n1ton2 = distance(n1,n2);
  n1top2 = distance(n1,p2);
  p1ton2 = distance(p1,n2);
  p1top2 = distance(p1,p2);

  mindist = ttop1+ttop2+n1ton2;
  choice = 1;

  test = ttop1+tton2+n1top2;
  if (test<mindist) {
    choice = 2;
    mindist = test;
    }

  test = tton1+ttop2+p1ton2;
  if (test<mindist) {
    choice = 3;
    mindist = test;
    }

  test = tton1+tton2+p1top2;
  if (test<mindist) choice = 4;


  switch (choice) {
    case 1:


      reverse(n2);
      p1->next = t;
      t->prev = p1;
      t->next = p2;
      p2->prev = t;
      n2->next = n1;
      n1->prev = n2;
      break;
    case 2:

      p1->next = t;
      t->prev = p1;
      t->next = n2;
      n2->prev = t;
      p2->next = n1;
      n1->prev = p2;
      break;
    case 3:

      p2->next = t;
      t->prev = p2;
      t->next = n1;
      n1->prev = t;
      p1->next = n2;
      n2->prev = p1;
      break;
    case 4:


      reverse(n1);
      n1->next = t;
      t->prev = n1;
      t->next = n2;
      n2->prev = t;
      p2->next = p1;
      p1->prev = p2;
      break;
    }
  return t;
}


Tree tsp(Tree t, int sz, int nproc) {
  Tree left = ((void *)0);
  Tree right = ((void *)0);
  Tree leftval = ((void *)0);
#ifdef FUTURES

#endif
  Tree rightval = ((void *)0);
  int nproc_2 = nproc/2;

  if (t->sz <= sz) return conquer(t);

  left = t->left; right = t->right;
#ifndef FUTURES
  leftval = tsp(left,sz,nproc_2);
#else

#endif
  rightval = tsp(right,sz,nproc_2);
#ifdef FUTURES



#else
  return merge(leftval,rightval,t,nproc);
#endif
}

