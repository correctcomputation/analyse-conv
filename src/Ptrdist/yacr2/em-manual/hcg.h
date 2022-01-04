












#include "types.h"


#ifndef HCG_H
#define HCG_H

#pragma CHECKED_SCOPE ON













typedef struct _nodeHCGType {
    _Array_ptr<unsigned long> netsHook : count(nets + 1);
    unsigned long nets;
    unsigned long netsReached;
} nodeHCGType;








extern unsigned long channelNets;
extern unsigned long channelTracks;

extern _Array_ptr<nodeHCGType> HCG : count(channelNets + 1);
extern _Array_ptr<unsigned long> storageRootHCG : count(channelNets + 1);
extern _Array_ptr<unsigned long> storageHCG : bounds(storageRootHCG, storageRootHCG + channelNets + 1);
extern unsigned long storageLimitHCG;







void
AllocHCG(void);

void
FreeHCG(void);

void
BuildHCG(void);

void
DFSClearHCG(_Array_ptr<nodeHCGType> : count(channelNets + 1));

void
DumpHCG(_Array_ptr<nodeHCGType> : count(channelNets + 1));

void
NoHCV(_Array_ptr<nodeHCGType> : count(channelNets + 1), unsigned long, _Array_ptr<unsigned long> : count(channelNets + 1), _Array_ptr<unsigned long> : count(channelTracks + 2));

#pragma CHECKED_SCOPE OFF
#endif	
