












#include "types.h"
#include "vcg.h"
#include "hcg.h"

#ifndef ASSIGN_H
#define ASSIGN_H








#define	LOW		1
#define	MEDIUM		100
#define	HIGH		10000
#define	INFINITY	1000000















extern unsigned long * * costMatrix;
extern unsigned long * tracksNoHCV;
extern unsigned long * tracksNotPref;
extern unsigned long * tracksTopNotPref;
extern unsigned long * tracksBotNotPref;
extern unsigned long cardNotPref;
extern unsigned long cardTopNotPref;
extern unsigned long cardBotNotPref;
extern unsigned long * tracksAssign;
extern unsigned long * netsAssign;
extern unsigned long * netsAssignCopy;








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
Assign(nodeVCGType *, unsigned long *, unsigned long);

void
Select(nodeVCGType *, nodeHCGType *, unsigned long *, unsigned long *, unsigned long *);

void
BuildCostMatrix(nodeVCGType *, nodeHCGType *, unsigned long *, unsigned long *);

void
IdealTrack(unsigned long tracks, unsigned long top, unsigned long bot, unsigned long * ideal);


#endif	

