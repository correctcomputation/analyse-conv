













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
    _Array_ptr<constraintVCGType> netsAboveHook ;
    unsigned long netsAbove;
    unsigned long netsAboveLabel;
    unsigned long netsAboveReached;
    _Array_ptr<constraintVCGType> netsBelowHook ;
    unsigned long netsBelow;
    unsigned long netsBelowLabel;
    unsigned long netsBelowReached;
} nodeVCGType;








extern unsigned long channelNets;

extern _Array_ptr<nodeVCGType> VCG : count(channelNets) ;
extern _Array_ptr<constraintVCGType> storageRootVCG ;
extern _Array_ptr<constraintVCGType> storageVCG ;
extern unsigned long storageLimitVCG;
extern _Array_ptr<_Ptr<constraintVCGType>> removeVCG : count(removeTotalVCG) ;
extern unsigned long removeTotalVCG;
extern _Array_ptr<unsigned long> SCC : count(channelNets) ;
extern unsigned long totalSCC;
extern _Array_ptr<unsigned long> perSCC : count(channelNets) ;








void
AllocVCG(void);

void
FreeVCG(void);

void
BuildVCG(void);

void DFSClearVCG(_Array_ptr<nodeVCGType> VCG : count(channelNets));

void DumpVCG(_Array_ptr<nodeVCGType> VCG);

void DFSAboveVCG(_Array_ptr<nodeVCGType> VCG : count(channelNets), unsigned long net);

void DFSBelowVCG(_Array_ptr<nodeVCGType> VCG : count(net + 1), unsigned long net);

void SCCofVCG(_Array_ptr<nodeVCGType> VCG : count(countSCC), _Array_ptr<unsigned long> SCC : count(countSCC), _Array_ptr<unsigned long> perSCC : count(countSCC), unsigned long countSCC);

void SCC_DFSAboveVCG(_Array_ptr<nodeVCGType> VCG : count(net + 1), unsigned long net, _Ptr<unsigned long> label);

void SCC_DFSBelowVCG(_Array_ptr<nodeVCGType> VCG : count(net + 1), unsigned long net, unsigned long label);

void DumpSCC(_Array_ptr<unsigned long> SCC, _Array_ptr<unsigned long> perSCC);

void
AcyclicVCG(void);

void RemoveConstraintVCG(_Array_ptr<nodeVCGType> VCG : count(channelNets), _Array_ptr<unsigned long> SCC : count(channelNets), _Array_ptr<unsigned long> perSCC : count(channelNets), _Array_ptr<_Ptr<constraintVCGType>> removeVCG : count(removeTotalVCG));

unsigned long ExistPathAboveVCG(_Array_ptr<nodeVCGType> VCG : count(channelNets), unsigned long above, unsigned long below);

void LongestPathVCG(_Array_ptr<nodeVCGType> VCG : count(channelNets), unsigned long net);

unsigned long DFSAboveLongestPathVCG(_Array_ptr<nodeVCGType> VCG : count(channelNets), unsigned long net);

unsigned long DFSBelowLongestPathVCG(_Array_ptr<nodeVCGType> VCG : count(channelNets), unsigned long net);

unsigned long VCV(_Array_ptr<nodeVCGType> VCG : count(channelNets), unsigned long check, unsigned long track, _Array_ptr<unsigned long> assign);


#endif	
