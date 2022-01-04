









#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>













#define BUF_LEN 1024    
#define G_SZ    1024    

#define fprintf(...)  { (fprintf)(__VA_ARGS__); }


#define TRY(exp, accpt_tst, fn, fail_fmt, arg1, arg2, arg3, fail_action) { \
              exp; \
              if (!(accpt_tst)) { \
                  fprintf(stderr, "(%s:%s():%d): ", __FILE__, fn, __LINE__); \
                  fprintf(stderr, fail_fmt, arg1, arg2, arg3); \
                  fprintf(stderr, "\n"); \
                  fail_action; \
                  } \
                  }





typedef struct _Net {
    struct _Net * next;
    unsigned long net;
} Net;
typedef Net * NetPtr;

extern NetPtr modules  [1024];
extern unsigned long numModules;


typedef struct _Module {
    struct _Module * next;
    unsigned long module;
} Module;
typedef Module * ModulePtr;

extern ModulePtr nets  [1024];
extern unsigned long numNets;

typedef struct _ModuleRec {
    struct _ModuleRec * next;
    unsigned long module;
} ModuleRec;
typedef ModuleRec * ModuleRecPtr;

typedef struct _ModuleList {
    ModuleRecPtr head;
    ModuleRecPtr tail;
} ModuleList;
typedef ModuleList * ModuleListPtr;

extern ModuleList groupA, groupB;
extern ModuleList swapToA, swapToB;
extern float GP  [1024];

typedef enum { GroupA, GroupB, SwappedToA, SwappedToB } Groups;

extern Groups moduleToGroup  [1024];
extern float D  [1024];
extern float cost  [1024];

void ReadNetList(char * fname);
void NetsToModules(void);
void ComputeNetCosts(void);
void InitLists(void);
void ComputeDs(ModuleListPtr group, Groups myGroup, Groups mySwap);
float CAiBj(ModuleRecPtr mrA, ModuleRecPtr mrB);
void SwapNode(ModuleRecPtr maxPrev, ModuleRecPtr max, ModuleListPtr group, ModuleListPtr swapTo);
void UpdateDs(ModuleRecPtr max, Groups group);
float FindMaxGpAndSwap(void);
void SwapSubsetAndReset(unsigned long iMax);
void PrintResults(int verbose);
int main(int argc, char * * argv );

