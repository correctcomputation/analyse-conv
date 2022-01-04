



#include "node.h"   
#include "proc.h"   
#include <stdio.h>
#include <stdlib.h>


#define printf(...)  { (printf)(__VA_ARGS__); }

#define CONST_m1 10000
#define CONST_b 31415821
#define RANGE 100

int NumNodes, NDim;

int my_random(int);

int flag=0,foo=0;

#define LocalNewNode(h,v) \
{ \
    h = (HANDLE *) calloc(1,sizeof(struct node)); \
      h->value = v; \
	h->left = NIL; \
	  h->right = NIL; \
	  };

#define NewNode(h,v,procid) LocalNewNode(h,v)

void InOrder(HANDLE * h) {
  HANDLE * l = (0);
  HANDLE * r = (0);
  if ((h != (0))) {
    l = h->left;
    r = h->right;
    InOrder(l);
    static unsigned char counter = 0;
    if (counter++ == 0)
       { (printf)("%d @ 0x%x\n",h->value, 0); };
    InOrder(r);
  }
}

int mult(int p, int q) {
  int p1, p0, q1, q0;

  p1 = p/10000; p0 = p%10000;
  q1 = q/10000; q0 = q%10000;
  return ((p0*q1+p1*q0) % 10000)*10000 +p0*q0;
}


int skiprand(int seed, int n) {
  for (; n; n--) seed=my_random(seed);
  return seed;
}

int my_random(int seed) {
  return mult(seed,31415821)+1;
}

HANDLE * RandTree(int n, int seed, int node, int level) {
  int next_val,my_name;
  future_cell_int f_left = { 0 }, f_right = {0};
  HANDLE * h = (0);
  my_name=foo++;
  if (n > 1) {
    int newnode;
    if (level<NDim)
      newnode = node + (1 << (NDim-level-1));
    else
      newnode = node;
    seed = my_random(seed);
    next_val=seed % 100;
    { h = (HANDLE *) calloc(1,sizeof(struct node)); h->value = next_val; h->left = (0); h->right = (0); };;
    f_left.value = RandTree((n/2),seed,newnode,level+1);
    f_right.value = RandTree((n/2),skiprand(seed,(n)+1),node,level+1);

    h->left = f_left.value;
    h->right = f_right.value;
  } else {
    h = 0;
  }
  return h;
}

void SwapValue(HANDLE * l, HANDLE * r) {
  int temp,temp2;

  temp = l->value;
  temp2 = r->value;
  r->value = temp;
  l->value = temp2;
}

void

SwapValLeft(HANDLE * l, HANDLE * r, HANDLE * ll, HANDLE * rl, int lval, int rval)

{
  r->value = lval;
  r->left = ll;
  l->left = rl;
  l->value = rval;
}


void

SwapValRight(HANDLE * l, HANDLE * r, HANDLE * lr, HANDLE * rr, int lval, int rval)

{
  r->value = lval;
  r->right = lr;
  l->right = rr;
  l->value = rval;

}

int

Bimerge(HANDLE * root, int spr_val, int dir)


{ int rightexchange;
  int elementexchange;
  HANDLE * pl = (0);
  HANDLE * pll = (0);
  HANDLE * plr = (0);
  HANDLE * pr = (0);
  HANDLE * prl = (0);
  HANDLE * prr = (0);
  HANDLE * rl = (0);
  HANDLE * rr = (0);
  int rv,lv;



  rv = root->value;

  pl = root->left;
  pr = root->right;
  rightexchange = ((rv > spr_val) ^ dir);
  if (rightexchange)
    {
      root->value = spr_val;
      spr_val = rv;
    }

  while ((pl != (0)))
    {

      lv = pl->value;
      pll = pl->left;
      plr = pl->right;
      rv = pr->value;
      prl = pr->left;
      prr = pr->right;
      elementexchange = ((lv > rv) ^ dir);
      if (rightexchange)
        if (elementexchange)
          {
            SwapValRight(pl,pr,plr,prr,lv,rv);
            pl = pll;
            pr = prl;
          }
        else
          { pl = plr;
            pr = prr;
          }
      else
        if (elementexchange)
          {
            SwapValLeft(pl,pr,pll,prl,lv,rv);
            pl = plr;
            pr = prr;
          }
        else
          { pl = pll;
            pr = prl;
          }
    }
  if ((root->left != (0)))
    {
      int value;
      rl = root->left;
      rr = root->right;
      value = root->value;

      root->value=Bimerge(rl,value,dir);
      spr_val=Bimerge(rr,spr_val,dir);
    }

  return spr_val;
}

int

Bisort(HANDLE * root, int spr_val, int dir)


{ HANDLE * l = (0);
  HANDLE * r = (0);
  int val;

  if ((root->left == (0)))
    {
     if (((root->value > spr_val) ^ dir))
        {
   val = spr_val;
   spr_val = root->value;
   root->value =val;
 }
    }
  else
    {
      int ndir;
      l = root->left;
      r = root->right;
      val = root->value;

      root->value=Bisort(l,val,dir);
      ndir = !dir;
      spr_val=Bisort(r,spr_val,ndir);
      spr_val=Bimerge(root,spr_val,dir);
    }

  return spr_val;
}

int main(int argc, char * * argv ) {
  HANDLE * h = (0);
  int sval;
  int n;

  n = dealwithargs(argc,argv);

   { (printf)("Bisort with %d size of dim %d\n", n, NDim); };

  h = RandTree(n,12345768,0,0);
  sval = my_random(245867) % 100;
  if (flag) {
    InOrder(h);
     { (printf)("%d\n",sval); };
  }
   { (printf)("**************************************\n"); };
   { (printf)("BEGINNING BITONIC SORT ALGORITHM HERE\n"); };
   { (printf)("**************************************\n"); };

  sval=Bisort(h,sval,0);

  if (flag) {
     { (printf)("Sorted Tree:\n"); };
    InOrder(h);
     { (printf)("%d\n",sval); };
  }

  sval=Bisort(h,sval,1);

  if (flag) {
     { (printf)("Sorted Tree:\n"); };
    InOrder(h);
     { (printf)("%d\n",sval); };
  }

  return 0;
}







