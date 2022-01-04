












#include "types.h"


#ifndef HCG_H
#define HCG_H














typedef struct _nodeHCGType {
    _Array_ptr<unsigned long> netsHook : count(nets);
    unsigned long nets;
    unsigned long netsReached;
} nodeHCGType;








extern _Array_ptr<nodeHCGType> HCG;
extern _Array_ptr<unsigned long> storageRootHCG;
extern _Array_ptr<unsigned long> storageHCG;
extern unsigned long storageLimitHCG;








void
AllocHCG(void);

void
FreeHCG(void);

void
BuildHCG(void);

void
DFSClearHCG(_Array_ptr<nodeHCGType> HCG);

void
DumpHCG(_Array_ptr<nodeHCGType> HCG);

void
NoHCV(_Array_ptr<nodeHCGType> HCG, unsigned long select, _Array_ptr<unsigned long> netsAssign, _Array_ptr<unsigned long> tracksNoHCV);

#endif	
