













#include "types.h"


#ifndef VCG_H
#define VCG_H

#pragma CHECKED_SCOPE ON






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
    _Array_ptr<constraintVCGType> netsAboveHook : count(netsAbove + 1);
    unsigned long netsAbove;
    unsigned long netsAboveLabel;
    unsigned long netsAboveReached;
    _Array_ptr<constraintVCGType> netsBelowHook : count(netsBelow + 1);
    unsigned long netsBelow;
    unsigned long netsBelowLabel;
    unsigned long netsBelowReached;
} nodeVCGType;








extern unsigned long channelNets;

extern _Array_ptr<nodeVCGType> VCG : count(channelNets + 1);
extern _Array_ptr<constraintVCGType> storageRootVCG : count((channelNets + 1) * (channelNets + 1));
extern _Array_ptr<constraintVCGType> storageVCG : bounds(storageRootVCG, storageRootVCG + (channelNets + 1) * (channelNets + 1));
extern unsigned long storageLimitVCG;
extern _Array_ptr<_Ptr<constraintVCGType>> removeVCG : count((channelNets + 1) * (channelNets + 1));
extern unsigned long removeTotalVCG;
extern _Array_ptr<unsigned long> SCC : count(channelNets + 1);
extern unsigned long totalSCC;
extern _Array_ptr<unsigned long> perSCC : count(channelNets + 1);








void
AllocVCG(void);

void
FreeVCG(void);

void
BuildVCG(void);

void DFSClearVCG(_Array_ptr<nodeVCGType> : count(channelNets + 1));

void DumpVCG(_Array_ptr<nodeVCGType> : count(channelNets + 1));

void DFSAboveVCG(_Array_ptr<nodeVCGType> : count(channelNets + 1), unsigned long);

void DFSBelowVCG(_Array_ptr<nodeVCGType> : count(channelNets + 1), unsigned long);

void SCCofVCG(_Array_ptr<nodeVCGType> : count(channelNets + 1), _Array_ptr<unsigned long> : count(channelNets + 1), _Array_ptr<unsigned long> : count(countSCC + 1), unsigned long countSCC);

void SCC_DFSAboveVCG(_Array_ptr<nodeVCGType> : count(channelNets + 1), unsigned long, _Ptr<unsigned long>);

void SCC_DFSBelowVCG(_Array_ptr<nodeVCGType> : count(channelNets + 1), unsigned long, unsigned long);

void DumpSCC(_Array_ptr<unsigned long> : count(channelNets + 1), _Array_ptr<unsigned long> : count(totalSCC + 1));

void
AcyclicVCG(void);

void RemoveConstraintVCG(_Array_ptr<nodeVCGType> : count(channelNets + 1), _Array_ptr<unsigned long> : count(channelNets + 1), _Array_ptr<unsigned long> : count(channelNets + 1), _Array_ptr<_Ptr<constraintVCGType>> : count((channelNets + 1) * (channelNets + 1)));

unsigned long ExistPathAboveVCG(_Array_ptr<nodeVCGType> : count(channelNets + 1), unsigned long above, unsigned long below);

void LongestPathVCG(_Array_ptr<nodeVCGType> : count(channelNets + 1), unsigned long);

unsigned long DFSAboveLongestPathVCG(_Array_ptr<nodeVCGType> : count(channelNets + 1), unsigned long);

unsigned long DFSBelowLongestPathVCG(_Array_ptr<nodeVCGType> : count(channelNets + 1), unsigned long);

unsigned long VCV(_Array_ptr<nodeVCGType> : count(channelNets + 1), unsigned long, unsigned long, _Array_ptr<unsigned long> : count(channelNets + 1));


#pragma CHECKED_SCOPE OFF
#endif	
