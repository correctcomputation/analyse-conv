







#ifdef TORONTO
#include <stdio.h>
#define chatting printf
#define PLAIN
#define LOCAL(xxx) xxx
#define local
#define MLOCAL(xxx);
#define NOTEST();
#define RETEST();

#define PID(xxx) 0
int NumNodes;
#endif


#include "stdinc.h"

#define THREEDIM
#include "vectmath.h"

#define MAX_NUM_NODES 64
extern double fabs();



























typedef struct node{
    short type;
    real mass;
    vector pos;
    int proc;
    int new_proc;
#ifdef JUMP

#endif
} node, *nodeptr;


#define Type(x) (((nodeptr) (x))->type)
#define Mass(x) (((nodeptr) (x))->mass)
#define Pos(x)  (((nodeptr) (x))->pos)
#define Proc(x) (((nodeptr) (x))->proc)
#define New_Proc(x) (((nodeptr) (x))->new_proc)

#define Type(x) ((x)->type)
#define Mass(x) ((x)->mass)
#define Pos(x)  ((x)->pos)
#define Proc(x) ((x)->proc)
#define New_Proc(x) ((x)->new_proc)





#define BODY 01                 

typedef struct bnode *bodyptr;

typedef struct bnode {
    short type;
    real mass;
    vector pos;
    int proc;
    int new_proc;
#ifdef JUMP

#endif
    vector vel;
    vector acc;
    vector new_acc;
    real phi;
    bodyptr next;
    bodyptr proc_next;
} body;


#define Vel(x)  (((bodyptr) (x))->vel)
#define Acc(x)  (((bodyptr) (x))->acc)
#define New_Acc(x)  (((bodyptr) (x))->new_acc)
#define Phi(x)  (((bodyptr) (x))->phi)
#define Next(x) (((bodyptr) (x))->next)
#define Proc_Next(x) (((bodyptr) (x))->proc_next)

#define Vel(x)  ((x)->vel)
#define Acc(x)  ((x)->acc)
#define New_Acc(x)  ((x)->new_acc)
#define Phi(x)  ((x)->phi)
#define Next(x) ((x)->next)
#define Proc_Next(x) ((x)->proc_next)





#define CELL 02                 

#define NSUB (1 << NDIM)        

typedef struct cnode *cellptr;

typedef struct cnode {
    short type;
    real mass;
    vector pos;
    int proc;
    int new_proc;
#ifdef JUMP

#endif
    nodeptr subp _Checked[(1 << 3)];
    cellptr next;

} cell;



#define Subp(x) (((cellptr) (x))->subp)
#define FL_Next(x) (((cellptr) (x))->next)

#define Subp(x) ((x)->subp)
#define FL_Next(x) ((x)->next)

typedef struct {
  real rmin _Checked[3];
  real rsize;
  nodeptr root;
  bodyptr bodytab _Checked[64];
  bodyptr bodiesperproc _Checked[64];
} tree;
typedef _Ptr<tree> treeptr;

#define Root(t) ((t)->root)
#define Rmin(t) ((t)->rmin)
#define Rsize(t) ((t)->rsize)
#define Bodytab(t) ((t)->bodytab[0])





typedef struct {
  real tnow;
  real tout;
  int nsteps;
} timerecord, *timeptr;

#define Tnow(t) ((t)->tnow)
#define Tout(t) ((t)->tout)
#define Nsteps(t) ((t)->nsteps)

typedef struct {
  int xp _Checked[3];
  bool inb;
} icstruct;

typedef struct {
  double v _Checked[3];
} vecstruct;






       nodeptr root;





       vector rmin;

       real xxxrsize;

#define IMAX_SHIFT (8 * sizeof(int) - 2)
#define IMAX  (1 << (8 * sizeof(int) - 2))    








#define eps 0.05 		
#define tol 1.00 		
#define NSTEPS  10
#define fcells 0.75		




typedef struct {
  real mtot;
  real etot _Checked[3];
  matrix keten;
  matrix peten;
  vector cmphase _Checked[2];
  vector amvec;
} ostruct;



#define assert(b,n) if (!(b)) {chatting("Assertion Failure #%d", (n)); abort();}


#define TASKLIMIT 256
extern int nbody;

#ifndef TORONTO
#include "future-cell.h"
#define exit __ShutDown
#endif





