








#define global  

#include "defs.h"
#include "code.h"


int nbody;

double sqrt(), xrand(double xl, double xh, double r), my_rand(double seed);
real pow();
extern icstruct intcoord(bodyptr p, treeptr t);
extern int BhDebug;

void computegrav(treeptr t, int nstep);
nodeptr maketree(bodyptr btab, int nbody, treeptr t, int nsteps, int proc);
void vp(bodyptr q, int nstep);

void gravstep(real rsize, nodeptr rt, bodyptr p, int nstep, real dthf);
void ptree(nodeptr n, int level);

typedef struct {
 vector cmr;
 vector cmv;
 bodyptr list;
   bodyptr tail;
} datapoints;


bodyptr testdata(void);
datapoints uniform_testdata(int proc, int nbody, int seedfactor);
void stepsystem(treeptr t, int nstep);
treeptr old_main(void);
void my_free(nodeptr n);
bodyptr  ubody_alloc(int p);


#if 0

#endif
void freetree(nodeptr n);
void freetree1(nodeptr n);
int old_subindex(icstruct ic, int l);

int dealwithargs(int argc, _Array_ptr<char *> argv);
int error(_Nt_array_ptr<char> msg);

int arg1;


int main(int argc, char **argv : itype(_Array_ptr<_Nt_array_ptr<char>>) count(argc)) {
  treeptr t = ((void *)0);


  dealwithargs(argc, argv);
  printf("nbody = %d, numnodes = %d\n", nbody, NumNodes);

  t = old_main();
  return 0;
}




treeptr old_main(void) {
  real tnow;
  real tout;
  int i, nsteps, nprocs;
  treeptr t = ((void *)0);
  bodyptr bt0 = ((void *)0);
  bodyptr p = ((void *)0);
  long t1, t2;
  vector cmr;
  vector cmv;
  bodyptr prev =((void*)0);
  int tmp=0, range=((1<<3) << 3) / NumNodes;
  int bodiesper _Checked[64];
  bodyptr ptrper _Checked[64] = {((void *)0)};

  srand(123);


  t = (_Ptr<tree>)malloc<tree>(sizeof(tree));
  ((t)->root) = ((void*)0);
  t->rmin[0] = -2.0;
  t->rmin[1] = -2.0;
  t->rmin[2] = -2.0;
  t->rsize = -2.0 * -2.0;

  ; { register int i; for (i = 0; i < 3; i++) (cmr)[i] = 0.0; };
  ; { register int i; for (i = 0; i < 3; i++) (cmv)[i] = 0.0; };


  for (i=0; i < 32; i++)
    {
    datapoints points = {};
    int processor= i/(32/NumNodes);

    points=uniform_testdata(processor, nbody/32, i+1);

    t->bodytab[i]=points.list;
    if (prev)
       ((prev)->next)=points.list;
    prev = points.tail;
    ; { register int i; for (i = 0; i < 3; i++) (cmr)[i] = (cmr)[i] + (points.cmr)[i]; };
    ; { register int i; for (i = 0; i < 3; i++) (cmv)[i] = (cmv)[i] + (points.cmv)[i]; };
    }

  printf("bodies created \n");
  ; { register int i; for (i = 0; i < 3; i++) (cmr)[i] = (cmr)[i] / ((real) nbody); };
  ; { register int i; for (i = 0; i < 3; i++) (cmv)[i] = (cmv)[i] / ((real) nbody); };

  for (tmp=0; tmp<64; tmp++) {
    bodiesper[tmp]=0;
    ptrper[tmp]=((void*)0);
    }


  for (p = t->bodytab[0]; p != ((void*)0); p = ((p)->next)) {
    icstruct xqic = {};

    ; { register int i; for (i = 0; i < 3; i++) (((p)->pos))[i] = (((p)->pos))[i] - (cmr)[i]; };
    ; { register int i; for (i = 0; i < 3; i++) (((p)->vel))[i] = (((p)->vel))[i] - (cmv)[i]; };

    xqic = intcoord(p,t);
    tmp = ((old_subindex(xqic, (1 << (8 * sizeof(int) - 2)) >> 1) << 3) +
               old_subindex(xqic, (1 << (8 * sizeof(int) - 2)) >> 2));
    tmp = tmp / range;
    bodiesper[tmp]++;
    ((p)->proc_next) = ptrper[tmp];
    ptrper[tmp] = p;
    ((p)->proc) = tmp;
  }
  for (tmp=0; tmp<NumNodes; tmp++)
    {
     printf("Bodies per %d = %d\n",tmp ,bodiesper[tmp]);
     t->bodiesperproc[tmp]=ptrper[tmp];
    }

#ifdef DEBUG







#endif
  tmp = 0;

  tnow = 0.0;
  i = 0;

  nsteps = 10;



  while ((tnow < 2.0 + 0.1*0.0125) && (i < nsteps)) {
    stepsystem(t, i);
    tnow = tnow + 0.0125;

    i++;
  }


#ifdef DEBUG







#endif



  return t;
}









#define MFRAC  0.999		


bodyptr testdata(void)
{
    real rsc, vsc, r, v, x, y;
    vector cmr;
    vector cmv;
    bodyptr head = ((void *)0);
    bodyptr p = ((void *)0);
    bodyptr prev = ((void *)0);
    register int i;
    double temp, t1;
    double seed = 123.0;
    register int k;
    double rsq, rsc1;
    real rad;

    if (!(0)) {printf("Assertion Failure #%d", (99)); abort();};
    rsc = 3 * 3.14159265358979323846 / 16;
    vsc = sqrt(1.0 / rsc);
    ; { register int i; for (i = 0; i < 3; i++) (cmr)[i] = 0.0; };
    ; { register int i; for (i = 0; i < 3; i++) (cmv)[i] = 0.0; };
    head = (_Ptr<struct bnode>) ubody_alloc(0);
    prev = head;

    for (i = 0; i < nbody; i++) {
        p = ubody_alloc(0);

        if (p == ((void*)0))
   error("testdata: not enough memory\n");
        ((prev)->next) = p;
        prev = p;
 ((p)->type) = 01;
 ((p)->mass) = 1.0 / nbody;
 seed = my_rand(seed);
 t1 = xrand(0.0, 0.999, seed);
 temp = pow(t1,
    -2.0/3.0) - 1;
 r = 1 / sqrt(temp);


 rad = rsc * r;
 do {
   for (k = 0; k < 3; k++) {
     seed = my_rand(seed);
     ((p)->pos)[k] = xrand(-1.0, 1.0, seed);
   }
   ; { register int i; (rsq) = 0.0; for (i = 0; i < 3; i++) (rsq) += (((p)->pos))[i] * (((p)->pos))[i]; };
 } while (rsq > 1.0);
 rsc1 = rad / sqrt(rsq);
 ; { register int i; for (i = 0; i < 3; i++) (((p)->pos))[i] = (((p)->pos))[i] * (rsc1); };

 ; { register int i; for (i = 0; i < 3; i++) (cmr)[i] = (cmr)[i] + (((p)->pos))[i]; };
 do {
   seed = my_rand(seed);
   x = xrand(0.0, 1.0, seed);
   seed = my_rand(seed);
   y = xrand(0.0, 0.1, seed);
 } while (y > x*x * pow(1 - x*x, 3.5));
 v = sqrt(2.0) * x / pow(1 + r*r, 0.25);


 rad = vsc*v;

 do {
   for (k = 0; k < 3; k++) {
     seed = my_rand(seed);
     ((p)->vel)[k] = xrand(-1.0, 1.0, seed);
   }
   ; { register int i; (rsq) = 0.0; for (i = 0; i < 3; i++) (rsq) += (((p)->vel))[i] * (((p)->vel))[i]; };
 } while (rsq > 1.0);
 rsc1 = rad / sqrt(rsq);
 ; { register int i; for (i = 0; i < 3; i++) (((p)->vel))[i] = (((p)->vel))[i] * (rsc1); };
 ; { register int i; for (i = 0; i < 3; i++) (cmv)[i] = (cmv)[i] + (((p)->vel))[i]; };
    }



    ((prev)->next) = ((void*)0);
    head = ((head)->next);

    ; { register int i; for (i = 0; i < 3; i++) (cmr)[i] = (cmr)[i] / ((real) nbody); };
    ; { register int i; for (i = 0; i < 3; i++) (cmv)[i] = (cmv)[i] / ((real) nbody); };
    for (p = head; p != ((void*)0); p = ((p)->next)) {
 ; { register int i; for (i = 0; i < 3; i++) (((p)->pos))[i] = (((p)->pos))[i] - (cmr)[i]; };
 ; { register int i; for (i = 0; i < 3; i++) (((p)->vel))[i] = (((p)->vel))[i] - (cmv)[i]; };
    }
   return head;
}




extern int EventCount;

void stepsystem(treeptr t, int nstep) {
  bodyptr bt = ((void *)0);
  bodyptr bt0 = ((void *)0);
  bodyptr q = ((void *)0);
  int i;
  nodeptr root = ((void *)0);

  int barge,cflctdiff,misstemp,diff;



  if (((t)->root) != ((void*)0)) {
    freetree1(((t)->root));
    ((t)->root) = ((void*)0);
  }



  root = maketree(bt, nbody, t, nstep, 0);


  ((t)->root)=root;

  computegrav(t, nstep);


  vp(t->bodiesperproc[0],nstep);
}


void freetree1(nodeptr n)
{
  unsigned long t1, t2;
  int foo;

  freetree(n);
}


void freetree(nodeptr n)
{
  register nodeptr r = ((void *)0);
  register int i;


  if ((n == ((void*)0)) || (((n)->type) == 01))
    return;


  for (i=(1 << 3)-1; i >= 0; i--) {
    r = (((cellptr) n)->subp)[i];
    if (r != ((void*)0)) {
      freetree(r);
    }
  }

  my_free(n);
  ;;
}


nodeptr cp_free_list = ((void*)0);
bodyptr bp_free_list = ((void*)0);



void my_free(nodeptr n)
{
  if (((n)->type) == 01) {
    (((bodyptr) n)->next) = bp_free_list;
    bp_free_list = (_Ptr<struct bnode>) n;
  }
  else {
    (((cellptr) n)->next) = (_Ptr<struct cnode>) cp_free_list;
    cp_free_list = n;
  }
}


bodyptr  ubody_alloc(int p)
{ register bodyptr tmp = ((void *)0);

  tmp = (_Ptr<struct bnode>)malloc<struct bnode>(sizeof(body));

  ((tmp)->type) = 01;
  ((tmp)->proc) = p;
  ((tmp)->proc_next) = ((void*)0);
  ((tmp)->new_proc) = p;
  return tmp;

}


cellptr  cell_alloc(int p)
{ register cellptr tmp = ((void *)0);
  register int i;

  if (cp_free_list != ((void*)0)) {
    tmp = (_Ptr<struct cnode>) cp_free_list;
    cp_free_list = (_Ptr<node>) (((cellptr) cp_free_list)->next);
  }
  else
    {
      tmp = (_Ptr<struct cnode>)malloc<struct cnode>(sizeof(cell));
    }
  ((tmp)->type) = 02;
  ((tmp)->proc) = p;
  for (i=0; i < (1 << 3); i++)
    ((tmp)->subp)[i] = ((void*)0);

  return tmp;
}


#define MFRAC  0.999		
#define DENSITY 0.5

datapoints uniform_testdata(int proc, int nbodyx, int seedfactor)
{
  datapoints retval = {};
  real rsc, vsc, r, v, x, y;
  bodyptr head = ((void *)0);
  bodyptr p = ((void *)0);
  bodyptr prev = ((void *)0);
  register int i;
  double temp, t1;
  double seed = 123.0 * (double) seedfactor;
  register int k;
  double rsq, rsc1;
  real rad;
  real coeff;


  rsc = 3 * 3.14159265358979323846 / 16;
  vsc = sqrt(1.0 / rsc);
  ; { register int i; for (i = 0; i < 3; i++) (retval.cmr)[i] = 0.0; };
  ; { register int i; for (i = 0; i < 3; i++) (retval.cmv)[i] = 0.0; };
  head = (_Ptr<struct bnode>) ubody_alloc(proc);
  prev = head;

  for (i = 0; i < nbodyx; i++) {
    p = ubody_alloc(proc);

    if (p == ((void*)0))
      error("testdata: not enough memory\n");
    ((prev)->next) = p;
    prev = p;
    ((p)->type) = 01;
    ((p)->mass) = 1.0 / nbodyx;
    seed = my_rand(seed);
    t1 = xrand(0.0, 0.999, seed);
    temp = pow(t1,
    -2.0/3.0) - 1;
    r = 1 / sqrt(temp);

    coeff = 4.0;
    for (k=0; k < 3; k++) {
      seed = my_rand(seed);
      r = xrand(0.0, 0.999, seed);
      ((p)->pos)[k] = coeff*r;
    }

    ; { register int i; for (i = 0; i < 3; i++) (retval.cmr)[i] = (retval.cmr)[i] + (((p)->pos))[i]; };
    do {
      seed = my_rand(seed);
      x = xrand(0.0, 1.0, seed);
      seed = my_rand(seed);
      y = xrand(0.0, 0.1, seed);
    } while (y > x*x * pow(1 - x*x, 3.5));
    v = sqrt(2.0) * x / pow(1 + r*r, 0.25);


    rad = vsc*v;

    do {
      for (k = 0; k < 3; k++) {
 seed = my_rand(seed);
 ((p)->vel)[k] = xrand(-1.0, 1.0, seed);
      }
      ; { register int i; (rsq) = 0.0; for (i = 0; i < 3; i++) (rsq) += (((p)->vel))[i] * (((p)->vel))[i]; };
    } while (rsq > 1.0);
    rsc1 = rad / sqrt(rsq);
    ; { register int i; for (i = 0; i < 3; i++) (((p)->vel))[i] = (((p)->vel))[i] * (rsc1); };
    ; { register int i; for (i = 0; i < 3; i++) (retval.cmv)[i] = (retval.cmv)[i] + (((p)->vel))[i]; };
  }


  ((prev)->next) = ((void*)0);
  retval.list = ((head)->next);
  retval.tail = prev;

  ;;

  return retval;
}








#if 0
#define global extern

#include "defs.h"
#include "code.h"
#include "mem-ref.h"
#endif



typedef struct {
  bodyptr pskip;
  vector pos0;
  real phi0;
  vector acc0;
} hgstruct, *hgsptr;

hgstruct gravsub(nodeptr p, hgstruct hg);
hgstruct walksub(nodeptr p, real dsq, real tolsq, hgstruct hg, int level);
bool subdivp(nodeptr p, real dsq, real tolsq, hgstruct hg);
double sqrt(double arg);
void grav(real rsize, nodeptr rt, bodyptr q, int nstep, real dthf);
void vp(bodyptr q, int nstep);
void hackgrav(bodyptr p, real rsize, nodeptr rt);

void computegrav(treeptr t, int nstep)
{ register int i;
   real rsize;
   real dthf;
   nodeptr root = ((void *)0);
   bodyptr blist = ((void *)0);


   rsize = ((t)->rsize);

   dthf = 0.5 * 0.0125;

   for (i=NumNodes-1; i>=0; i--) {
     root = ((t)->root);
     blist = t->bodiesperproc[i];
     grav(rsize,root,blist,nstep,dthf);
   }
}


void grav(real rsize, nodeptr rt, bodyptr bodies, int nstep, real dthf)
{
  register bodyptr p = ((void *)0);
  register bodyptr q = ((void *)0);
  int i=0;



  if (bodies!= ((void*)0)) {
    bodyptr foo = bodies;
  }
  q = bodies;

  ;;

  while (q!=((void*)0)) {
    gravstep(rsize, rt, q, nstep, dthf);
    q=((q)->proc_next);
    i++;
  }

  ;;

}

void vp(bodyptr q, int nstep)
{
  real dthf;
  vector acc1;
  vector dacc;
  vector dvel;
  vector vel1;
  vector dpos;

  dthf = 0.5 * 0.0125;


  if (q!= ((void*)0)) {
    bodyptr foo = q;
  }

  ;;

  for (; q != ((void*)0); q = ((q)->proc_next)) {
    ; { register int i; for (i = 0; i < 3; i++) (acc1)[i] = (((q)->new_acc))[i]; };
    if (nstep > 0) {
      ; { register int i; for (i = 0; i < 3; i++) (dacc)[i] = (acc1)[i] - (((q)->acc))[i]; };
      ; { register int i; for (i = 0; i < 3; i++) (dvel)[i] = (dacc)[i] * (dthf); };

      ; { register int i; for (i = 0; i < 3; i++) (dvel)[i] = (((q)->vel))[i] + (dvel)[i]; };
      ; { register int i; for (i = 0; i < 3; i++) (((q)->vel))[i] = (dvel)[i]; };
    }
    { real p0,p1,p2;
    p0=((q)->pos)[0];
    p1=((q)->pos)[1];
    p2=((q)->pos)[2];
    if (!(!__builtin_isnan (p0))) {printf("Assertion Failure #%d", (99)); abort();};
    if (!(!__builtin_isnan (p1))) {printf("Assertion Failure #%d", (98)); abort();};
    if (!(!__builtin_isnan (p2))) {printf("Assertion Failure #%d", (97)); abort();};
    if (!(fabs(p0)<10.0)) {printf("Assertion Failure #%d", (96)); abort();};
    if (!(fabs(p1)<10.0)) {printf("Assertion Failure #%d", (95)); abort();};
    if (!(fabs(p2)<10.0)) {printf("Assertion Failure #%d", (94)); abort();};
#ifdef DEBUG

#endif
    }
    ; { register int i; for (i = 0; i < 3; i++) (((q)->acc))[i] = (acc1)[i]; };
    { real p0,p1,p2;
    p0=((q)->acc)[0];
    p1=((q)->acc)[1];
    p2=((q)->acc)[2];
    if (!(!__builtin_isnan (p0))) {printf("Assertion Failure #%d", (89)); abort();};
    if (!(!__builtin_isnan (p1))) {printf("Assertion Failure #%d", (88)); abort();};
    if (!(!__builtin_isnan (p2))) {printf("Assertion Failure #%d", (87)); abort();};
    if (!(fabs(p0)<10000.0)) {printf("Assertion Failure #%d", (86)); abort();};
    if (!(fabs(p1)<10000.0)) {printf("Assertion Failure #%d", (85)); abort();};
    if (!(fabs(p2)<10000.0)) {printf("Assertion Failure #%d", (84)); abort();};

    }

    ; { register int i; for (i = 0; i < 3; i++) (dvel)[i] = (((q)->acc))[i] * (dthf); };
    { real p0,p1,p2;
    p0=((q)->vel)[0];
    p1=((q)->vel)[1];
    p2=((q)->vel)[2];
    if (!(!__builtin_isnan (p0))) {printf("Assertion Failure #%d", (79)); abort();};
    if (!(!__builtin_isnan (p1))) {printf("Assertion Failure #%d", (78)); abort();};
    if (!(!__builtin_isnan (p2))) {printf("Assertion Failure #%d", (77)); abort();};
    if (!(fabs(p0)<10000.0)) {printf("Assertion Failure #%d", (76)); abort();};
    if (!(fabs(p1)<10000.0)) {printf("Assertion Failure #%d", (75)); abort();};
    if (!(fabs(p2)<10000.0)) {printf("Assertion Failure #%d", (74)); abort();};

    }
    ; { register int i; for (i = 0; i < 3; i++) (vel1)[i] = (((q)->vel))[i] + (dvel)[i]; };
    ; { register int i; for (i = 0; i < 3; i++) (dpos)[i] = (vel1)[i] * (0.0125); };
    ; { register int i; for (i = 0; i < 3; i++) (dpos)[i] = (((q)->pos))[i] + (dpos)[i]; };
    ; { register int i; for (i = 0; i < 3; i++) (((q)->pos))[i] = (dpos)[i]; };
    ; { register int i; for (i = 0; i < 3; i++) (((q)->vel))[i] = (vel1)[i] + (dvel)[i]; };
    { real p0,p1,p2;
    p0=((q)->pos)[0];
    p1=((q)->pos)[1];
    p2=((q)->pos)[2];
    if (!(!__builtin_isnan (p0))) {printf("Assertion Failure #%d", (69)); abort();};
    if (!(!__builtin_isnan (p1))) {printf("Assertion Failure #%d", (68)); abort();};
    if (!(!__builtin_isnan (p2))) {printf("Assertion Failure #%d", (67)); abort();};
    if (!(fabs(p0)<10000.0)) {printf("Assertion Failure #%d", (66)); abort();};
    if (!(fabs(p1)<10000.0)) {printf("Assertion Failure #%d", (65)); abort();};
    if (!(fabs(p2)<10000.0)) {printf("Assertion Failure #%d", (64)); abort();};

    }
  }

  ;;
}




void gravstep(real rsize, nodeptr rt, bodyptr p, int nstep, real dthf)
{

  hackgrav(p, rsize, rt);
}






void hackgrav(bodyptr p, real rsize, nodeptr rt)
{
  hgstruct hg = {};
  real szsq;

  ;;
  hg.pskip = p;
  ; { register int i; for (i = 0; i < 3; i++) (hg.pos0)[i] = (((p)->pos))[i]; };
  hg.phi0 = 0.0;
  ; { register int i; for (i = 0; i < 3; i++) (hg.acc0)[i] = 0.0; };
  szsq = rsize * rsize;
  hg = walksub(rt, szsq, 1.00*1.00, hg, 0);
  ((p)->phi) = hg.phi0;

  ; { register int i; for (i = 0; i < 3; i++) (((p)->new_acc))[i] = (hg.acc0)[i]; };
  ;;
}





hgstruct gravsub(nodeptr p, hgstruct hg)
{
  real drabs, phii, mor3;
  vector ai;
  vector quaddr;
  real dr5inv, phiquad, drquaddr;
  vector dr;
  real drsq;


  ; { register int i; for (i = 0; i < 3; i++) (dr)[i] = (((p)->pos))[i] - (hg.pos0)[i]; };
  ; { register int i; (drsq) = 0.0; for (i = 0; i < 3; i++) (drsq) += (dr)[i] * (dr)[i]; };

  drsq += 0.05*0.05;
  drabs = sqrt((double) drsq);
  phii = ((p)->mass) / drabs;
  hg.phi0 -= phii;
  mor3 = phii / drsq;
  ; { register int i; for (i = 0; i < 3; i++) (ai)[i] = (dr)[i] * (mor3); };
  ; { register int i; for (i = 0; i < 3; i++) (hg.acc0)[i] = (hg.acc0)[i] + (ai)[i]; };

  if(((p)->type) == 02) {
#ifdef QUADPOLE				










#endif
  }

  return hg;
}




















 bool subdivp(nodeptr p, real dsq, real tolsq, hgstruct hg)
{
  register nodeptr local_p = ((void *)0);
  vector dr;
  vector pos;
  real drsq;

  local_p = (_Ptr<node>)p;
  if (((local_p)->type) == 01)
    return (0);

  ; { register int i; for (i = 0; i < 3; i++) (dr)[i] = (((local_p)->pos))[i] - (hg.pos0)[i]; };
  ; { register int i; (drsq) = 0.0; for (i = 0; i < 3; i++) (drsq) += (dr)[i] * (dr)[i]; };


  return (tolsq * drsq < dsq);
}







double ceil();



#if 0

#endif
bodyptr  ubody_alloc(int p);
cellptr  cell_alloc(int p);

typedef struct {
  nodeptr tp;
  int num;
} dtstruct;

typedef struct {
  nodeptr tp;
  int num;
  int proc;
} dt1struct;


nodeptr loadtree(bodyptr p, icstruct xpic, nodeptr t, int l, treeptr tr);
void expandbox(bodyptr p, treeptr t, int nsteps, int proc);
icstruct intcoord1(double rp0, double rp1, double rp2, treeptr t);
icstruct intcoord(bodyptr p, treeptr t);
int ic_test(bodyptr p, treeptr t);
int subindex(bodyptr p, treeptr t, int l);
real hackcofm(nodeptr q);


int dis2_number(nodeptr n, int prev_bodies, int tnperproc);
void dis_number (nodeptr n);





nodeptr maketree(bodyptr btab, int nb, treeptr t, int nsteps, int proc)
{
  register bodyptr q = ((void *)0);
  int tmp;
  nodeptr node1 = ((void *)0);
  icstruct xqic = {};
  int holder;

  ((t)->root) = ((void*)0);
  nbody = nb;


 for (tmp=NumNodes-1; tmp>=0; tmp--) {
  btab = t->bodiesperproc[tmp];


  for (q = btab; q != ((void*)0); q=((q)->proc_next)) {
    if (((q)->mass) != 0.0) {
      expandbox(q, t, nsteps, proc);
      xqic = intcoord(q,t);
      node1=((t)->root);
      node1 = loadtree(q, xqic, node1, (1 << (8 * sizeof(int) - 2)) >> 1, t);
      ((t)->root) = node1;

    }
  }
 }




  hackcofm(((t)->root));



  return ((t)->root);
}










void expandbox(bodyptr p, treeptr t, int nsteps, int proc)
{
    icstruct ic = {};
    int k;
    vector rmid;
    cellptr newt = ((void *)0);
    tree tmp = {};
    real rsize;
    int inbox;

    inbox = ic_test(p, t);
    while (!inbox) {
      rsize = ((t)->rsize);

      if (!(rsize<1000.0)) {printf("Assertion Failure #%d", (999)); abort();};
      ; { register int i; for (i = 0; i < 3; i++) (rmid)[i] = (((t)->rmin))[i] + (0.5 * rsize); };












      for (k=0; k < 3; k++)
        if (((p)->pos)[k] < rmid[k])
           {
             real rmin;
             rmin = ((t)->rmin)[k];
           ((t)->rmin)[k] = rmin - rsize;
           }

      ((t)->rsize) = 2.0 * rsize;


      rsize = ((t)->rsize);

      if (((t)->root) != ((void*)0)) {
    register int i;
    newt = cell_alloc(0);

    ic = intcoord1(rmid[0], rmid[1], rmid[2], t);

    if (!(ic.inb)) {printf("Assertion Failure #%d", (1)); abort();};
    k = old_subindex(ic, (1 << (8 * sizeof(int) - 2)) >> 1);
    ((newt)->subp)[k] = ((t)->root);
    ((t)->root) = (_Ptr<node>) newt;
    inbox = ic_test(p, t);
      }
    }
}









nodeptr loadtree(bodyptr p, icstruct xpic, nodeptr t, int l, treeptr tr)
{
  int si;
  cellptr c = ((void *)0);
  nodeptr rt = ((void *)0);

  if (t == ((void*)0))
     {
      return ((_Ptr<node>) p);
     }
  else {
    if (!(l != 0)) {printf("Assertion Failure #%d", (2)); abort();};
    if (((t)->type) == 01) {
      int i,j;
      icstruct pic = {};
      icstruct tic = {};



      i = 0;
      c = (_Ptr<struct cnode>) cell_alloc(i);
      si = subindex((_Ptr<struct bnode>) t, tr, l);

      ((c)->subp)[si] = (_Ptr<node>) t;
      t = (_Ptr<node>) c;
    }

    si = old_subindex(xpic, l);
    rt = (((cellptr) t)->subp)[si];
    (((cellptr) t)->subp)[si] = loadtree(p, xpic, rt, l >> 1, tr);
  }
  return (t);
}







icstruct intcoord1(double rp0, double rp1, double rp2, treeptr t)
{
    double xsc, floor();

    icstruct ic = {};






    ic.inb = 1;

    xsc = (rp0 - t->rmin[0]) / t->rsize;
    if (0.0 <= xsc && xsc < 1.0)
      ic.xp[0] = floor((1 << (8 * sizeof(int) - 2)) * xsc);
    else {

      ic.inb = 0;
      }

    xsc = (rp1 - t->rmin[1]) / t->rsize;
    if (0.0 <= xsc && xsc < 1.0)
      ic.xp[1] = floor((1 << (8 * sizeof(int) - 2)) * xsc);
    else {

      ic.inb = 0;
      }


    xsc = (rp2 - t->rmin[2]) / t->rsize;
    if (0.0 <= xsc && xsc < 1.0)
      ic.xp[2] = floor((1 << (8 * sizeof(int) - 2)) * xsc);
    else {

      ic.inb = 0;
      }


    return (ic);
}







icstruct intcoord(bodyptr p, treeptr t)
{
    register double xsc;
    double floor();
    icstruct ic = {};
    register real rsize;
    vector pos;


    ic.inb = 1;
    rsize = t->rsize;

    pos[0] = ((p)->pos)[0];
    pos[1] = ((p)->pos)[1];
    pos[2] = ((p)->pos)[2];



    xsc = (pos[0] - t->rmin[0]) / rsize;
    if (0.0 <= xsc && xsc < 1.0)
      ic.xp[0] = floor((1 << (8 * sizeof(int) - 2)) * xsc);
    else {
      ic.inb = 0;
      ic.xp[0] = 0;
    }


    xsc = (pos[1] - t->rmin[1]) / rsize;
    if (0.0 <= xsc && xsc < 1.0)
      ic.xp[1] = floor((1 << (8 * sizeof(int) - 2)) * xsc);
    else {
      ic.inb = 0;
      ic.xp[1] = 0;
    }


    xsc = (pos[2] - t->rmin[2]) / rsize;
    if (0.0 <= xsc && xsc < 1.0)
      ic.xp[2] = floor((1 << (8 * sizeof(int) - 2)) * xsc);
    else {
      ic.inb = 0;
      ic.xp[2] = 0;
    }



    return (ic);
}


int ic_test(bodyptr p, treeptr t)
{
    double xsc, rsize, floor();
    int result;
    vector pos;

    result = 1;

    pos[0] = ((p)->pos)[0];
    pos[1] = ((p)->pos)[1];
    pos[2] = ((p)->pos)[2];
    rsize = t->rsize;

    xsc = (pos[0] - t->rmin[0]) / rsize;
    if (!(0.0 <= xsc && xsc < 1.0))
      result = 0;


    xsc = (pos[1] - t->rmin[1]) / rsize;
    if (!(0.0 <= xsc && xsc < 1.0))
      result = 0;


    xsc = (pos[2] - t->rmin[2]) / rsize;
    if (!(0.0 <= xsc && xsc < 1.0))
      result = 0;











    return (result);
}








int subindex(bodyptr p, treeptr t, int l)
{
    register int i, k;
    register real rsize;
    double xsc, floor();
    int xp _Checked[3];
    vector pos;

    pos[0] = ((p)->pos)[0];
    pos[1] = ((p)->pos)[1];
    pos[2] = ((p)->pos)[2];

    rsize = t->rsize;

    xsc = (pos[0] - t->rmin[0]) / rsize;
    if (!((0.0 <= xsc) && (xsc < 1.0))) {printf("Assertion Failure #%d", (5)); abort();};
    xp[0] = floor((1 << (8 * sizeof(int) - 2)) * xsc);

    xsc = (pos[1] - t->rmin[1]) / rsize;
    if (!((0.0 <= xsc) && (xsc < 1.0))) {printf("Assertion Failure #%d", (6)); abort();};
    xp[1] = floor((1 << (8 * sizeof(int) - 2)) * xsc);

    xsc = (pos[2] - t->rmin[2]) / rsize;
    if (!((0.0 <= xsc) && (xsc < 1.0))) {printf("Assertion Failure #%d", (7)); abort();};
    xp[2] = floor((1 << (8 * sizeof(int) - 2)) * xsc);


    i = 0;
    for (k = 0; k < 3; k++)
        if (xp[k] & l)
            i += (1 << 3) >> (k + 1);

    return (i);
}



int old_subindex(icstruct ic, int l)
{
    register int i, k;

    i = 0;
    for (k = 0; k < 3; k++)
        if (ic.xp[k] & l)
            i += (1 << 3) >> (k + 1);
    return (i);
}






real hackcofm(nodeptr q)
{
    register int i;
    register nodeptr r = ((void *)0);
    vector tmpv;
    vector tmp_pos;
    register real mq, mr;


    if (((q)->type) == 02) {
      mq = 0.0;
      ; { register int i; for (i = 0; i < 3; i++) (tmp_pos)[i] = 0.0; };
      for (i=0; i < (1 << 3); i++) {
      r = (((cellptr) q)->subp)[i];
      if (r != ((void*)0)) {
        mr = hackcofm(r);
        mq = mr + mq;
        ; { register int i; for (i = 0; i < 3; i++) (tmpv)[i] = (((r)->pos))[i] * (mr); };
        ; { register int i; for (i = 0; i < 3; i++) (tmp_pos)[i] = (tmp_pos)[i] + (tmpv)[i]; };
      }
      }

      ((q)->mass) = mq;
      ;;
      ((q)->pos)[0] = tmp_pos[0];
      ((q)->pos)[1] = tmp_pos[1];
      ((q)->pos)[2] = tmp_pos[2];
      ; { register int i; for (i = 0; i < 3; i++) (((q)->pos))[i] = (((q)->pos))[i] / (((q)->mass)); };
      ;;


      return mq;
    }


    mq = ((q)->mass);



    return mq;
  }




void printtree(nodeptr n)
{ ptree(n, 0);
}

void ptree(nodeptr n, int level)
{
  nodeptr r = ((void *)0);


  if (n != ((void*)0)) {
    if (((n)->type) == 01) {
      printf("%2d BODY@%x %f, %f, %f\n", level, n, ((n)->pos)[0], ((n)->pos)[1], ((n)->pos)[2]);
    }
    else {
      int i;

      printf("%2d CELL@%x %f, %f, %f\n", level, n,((n)->pos)[0], ((n)->pos)[1], ((n)->pos)[2]);
      for (i = 0; i < (1 << 3); i++) {
 r = (((cellptr) n)->subp)[i];
 ptree(r, level+1);
      }
    }
  }
  else
    printf("%2d NULL TREE\n", level);
}



typedef struct {
  int bits;
  int split;
  cellptr new;
  nodeptr non_local _Checked[(1 << 3)];
} dt3_struct;


void dis_number (nodeptr n)
{
  int tnperproc = (int) ceil ( (double) nbody/NumNodes);

  dis2_number(n, -1, tnperproc);
}

int dis2_number(nodeptr n, int prev_bodies, int tnperproc)
{

  if (n == ((void*)0))
    return prev_bodies;

  else if (((n)->type) == 01) {
    ((n)->new_proc) = (prev_bodies+1)/tnperproc;
    return prev_bodies + 1;
  }

  else {
    register int i;
    register nodeptr r = ((void *)0);


    for (i=0; i < (1 << 3); i++) {
      r = (((cellptr) n)->subp)[i];
      prev_bodies = dis2_number(r, prev_bodies, tnperproc);
    }

    ;;
    return prev_bodies;
  }
}

