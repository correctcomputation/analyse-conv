













typedef struct demand {
  double P;
  double Q;
} Demand;

#include <math.h>

#pragma CHECKED_SCOPE ON

#ifdef SMALL_PROBLEM_SIZE   
#define NUM_FEEDERS 8
#define LATERALS_PER_FEEDER 16
#define BRANCHES_PER_LATERAL 5
#define LEAVES_PER_BRANCH 10
#else
#if 0  
#define NUM_FEEDERS 10
#define LATERALS_PER_FEEDER 20
#define BRANCHES_PER_LATERAL 5
#define LEAVES_PER_BRANCH 10
#else  
#define NUM_FEEDERS 11
#define LATERALS_PER_FEEDER 21
#define BRANCHES_PER_LATERAL 6
#define LEAVES_PER_BRANCH 12
#endif
#endif

#define F_EPSILON 0.000001
#define G_EPSILON 0.000001
#define H_EPSILON 0.000001
#define ROOT_EPSILON 0.00001

struct root {
  Demand D;
  double theta_R;
  double theta_I;
  Demand last;
  double last_theta_R;
  double last_theta_I;
  _Ptr<struct lateral> feeders _Checked[11];
};

typedef _Ptr<struct root> Root;

struct lateral {
  Demand D;
  double alpha;
  double beta;
  double R;
  double X;
  _Ptr<struct lateral> next_lateral;
  _Ptr<struct branch> branch;
};

typedef _Ptr<struct lateral> Lateral;

struct branch {
  Demand D;
  double alpha;
  double beta;
  double R;
  double X;
  _Ptr<struct branch> next_branch;
  _Ptr<struct leaf> leaves _Checked[12];
};

typedef _Ptr<struct branch> Branch;

struct leaf {
  Demand D;
  double pi_R;
  double pi_I;
};

typedef _Ptr<struct leaf> Leaf;


Root build_tree(void);
Lateral build_lateral(int i, int num);
Branch build_branch(int i, int j, int num);
Leaf build_leaf(void);

void Compute_Tree(Root r);
Demand Compute_Lateral(Lateral l, double theta_R, double theta_I, double pi_R, double pi_I);
Demand Compute_Branch(Branch b, double theta_R, double theta_I, double pi_R, double pi_I);
Demand Compute_Leaf(Leaf l, double pi_R, double pi_I);

#pragma CHECKED_SCOPE OFF
