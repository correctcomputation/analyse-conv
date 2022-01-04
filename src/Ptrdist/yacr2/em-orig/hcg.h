












#include "types.h"


#ifndef HCG_H
#define HCG_H














typedef struct _nodeHCGType {
    unsigned long * netsHook;
    unsigned long nets;
    unsigned long netsReached;
} nodeHCGType;








extern nodeHCGType * HCG;
extern unsigned long * storageRootHCG;
extern unsigned long * storageHCG;
extern unsigned long storageLimitHCG;








void
AllocHCG(void);

void
FreeHCG(void);

void
BuildHCG(void);

void
DFSClearHCG(nodeHCGType *);

void
DumpHCG(nodeHCGType *);

void
NoHCV(nodeHCGType *, unsigned long, unsigned long *, unsigned long *);

#endif	
