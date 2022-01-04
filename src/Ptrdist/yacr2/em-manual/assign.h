












#include "types.h"
#include "vcg.h"
#include "hcg.h"

#ifndef ASSIGN_H
#define ASSIGN_H

#pragma CHECKED_SCOPE ON






#define	LOW		1
#define	MEDIUM		100
#define	HIGH		10000
#define	INFINITY	1000000








struct costMatrixRow {
    _Array_ptr<long> row : count(len);
    unsigned long len;
};








extern unsigned long channelNets;
extern unsigned long channelTracks;

extern _Array_ptr<struct costMatrixRow> costMatrix : count(channelNets + 1);
extern _Array_ptr<unsigned long> tracksNoHCV : count(channelTracks+2);
extern _Array_ptr<unsigned long> tracksNotPref : count(channelTracks+2);
extern _Array_ptr<unsigned long> tracksTopNotPref : count(channelTracks+2);
extern _Array_ptr<unsigned long> tracksBotNotPref : count(channelTracks+2);
extern unsigned long cardNotPref;
extern unsigned long cardTopNotPref;
extern unsigned long cardBotNotPref;
extern _Array_ptr<unsigned long> tracksAssign : count(channelTracks+2);
extern _Array_ptr<unsigned long> netsAssign : count(channelNets + 1);
extern _Array_ptr<unsigned long> netsAssignCopy : count(channelNets + 1);








void
AllocAssign(void);

void
FreeAssign(void);

void
NetsAssign(void);

void
MaxNetsAssign(void);

void
RightNetsAssign(void);

void
LeftNetsAssign(void);

void
Assign(_Array_ptr<nodeVCGType> : count(channelNets + 1), _Array_ptr<unsigned long> : count(channelNets + 1), unsigned long);

void
Select(_Array_ptr<nodeVCGType> : count(channelNets + 1), _Array_ptr<nodeHCGType> : count(channelNets + 1), _Array_ptr<unsigned long> : count(channelNets + 1), _Ptr<unsigned long>, _Array_ptr<unsigned long> : count(channelNets + 1));

void
BuildCostMatrix(_Array_ptr<nodeVCGType> : count(channelNets + 1), _Array_ptr<nodeHCGType> : count(channelNets + 1), _Array_ptr<unsigned long> : count(channelNets + 1), _Array_ptr<unsigned long> : count(channelNets + 1));

void
IdealTrack(unsigned long, unsigned long, unsigned long, _Ptr<unsigned long>);

#pragma CHECKED_SCOPE OFF
#endif	

