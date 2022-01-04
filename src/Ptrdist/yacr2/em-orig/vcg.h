













#include "types.h"


#ifndef VCG_H
#define VCG_H







#define	EMPTY			0
#define	EMPTY_HALF_EMPTY	2
#define	EMPTY_FULL		3
#define	HALF_EMPTY		4
#define	HALF_EMPTY_FULL		5
#define	FULL			6








typedef struct _constraintVCGType {
    unsigned long top;
    unsigned long bot;
    unsigned long col;
    unsigned long removed;
} constraintVCGType;

typedef struct _nodeVCGType {
    constraintVCGType * netsAboveHook;
    unsigned long netsAbove;
    unsigned long netsAboveLabel;
    unsigned long netsAboveReached;
    constraintVCGType * netsBelowHook;
    unsigned long netsBelow;
    unsigned long netsBelowLabel;
    unsigned long netsBelowReached;
} nodeVCGType;








extern nodeVCGType * VCG;
extern constraintVCGType * storageRootVCG;
extern constraintVCGType * storageVCG;
extern unsigned long storageLimitVCG;
extern constraintVCGType * * removeVCG;
extern unsigned long removeTotalVCG;
extern unsigned long * SCC;
extern unsigned long totalSCC;
extern unsigned long * perSCC;








void
AllocVCG(void);

void
FreeVCG(void);

void
BuildVCG(void);

void
DFSClearVCG(nodeVCGType *);

void
DumpVCG(nodeVCGType *);

void
DFSAboveVCG(nodeVCGType *, unsigned long);

void DFSBelowVCG(nodeVCGType *, unsigned long);

void SCCofVCG(nodeVCGType *, unsigned long *, unsigned long *);

void SCC_DFSAboveVCG(nodeVCGType *, unsigned long, unsigned long *);

void SCC_DFSBelowVCG(nodeVCGType *, unsigned long, unsigned long);

void DumpSCC(unsigned long *, unsigned long *);

void AcyclicVCG(void);

void RemoveConstraintVCG(nodeVCGType *, unsigned long *, unsigned long *, constraintVCGType * *);

unsigned long ExistPathAboveVCG(nodeVCGType *, unsigned long, unsigned long);

void LongestPathVCG(nodeVCGType *, unsigned long);

unsigned long DFSAboveLongestPathVCG(nodeVCGType *, unsigned long);

unsigned long DFSBelowLongestPathVCG(nodeVCGType *, unsigned long);

unsigned long VCV(nodeVCGType *, unsigned long, unsigned long, unsigned long *);

#endif	
