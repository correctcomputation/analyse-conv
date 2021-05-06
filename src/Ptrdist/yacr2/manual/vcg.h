
/*
 *
 * vcg.h
 *
 */


/*
 *
 * Includes.
 *
 */

#include "types.h"


#ifndef VCG_H
#define VCG_H

#pragma CHECKED_SCOPE ON
/*
 *
 * Defines.
 *
 */

#define	EMPTY			0
#define	EMPTY_HALF_EMPTY	2
#define	EMPTY_FULL		3
#define	HALF_EMPTY		4
#define	HALF_EMPTY_FULL		5
#define	FULL			6


/*
 *
 * Types.
 *
 */

typedef struct _constraintVCGType {
    ulong	top;
    ulong	bot;
    ulong	col;
    ulong	removed;
} constraintVCGType;

typedef struct _nodeVCGType {
    _Array_ptr<constraintVCGType>	netsAboveHook : count(netsAbove + 1);
    ulong			netsAbove;
    ulong			netsAboveLabel;
    ulong			netsAboveReached;
    _Array_ptr<constraintVCGType>	netsBelowHook : count(netsBelow + 1);
    ulong			netsBelow;
    ulong			netsBelowLabel;
    ulong			netsBelowReached;
} nodeVCGType;


/*
 *
 * Globals.
 *
 */

extern ulong channelNets;

extern _Array_ptr<nodeVCGType>			VCG : count(channelNets + 1);
extern _Array_ptr<constraintVCGType>			storageRootVCG : count((channelNets + 1) * (channelNets + 1));
extern _Array_ptr<constraintVCGType>			storageVCG : bounds(storageRootVCG, storageRootVCG + (channelNets + 1) * (channelNets + 1));
extern ulong					storageLimitVCG;
extern _Array_ptr<_Ptr<constraintVCGType>>		removeVCG : count((channelNets + 1) * (channelNets + 1));
extern ulong					removeTotalVCG;
extern _Array_ptr<ulong>				SCC : count(channelNets + 1);
extern ulong					totalSCC;
extern _Array_ptr<ulong>				perSCC : count(channelNets + 1);


/*
 *
 * Prototypes.
 *
 */

void
AllocVCG(void);

void
FreeVCG(void);

void
BuildVCG(void);

void DFSClearVCG(_Array_ptr<nodeVCGType> : count(channelNets + 1));

void DumpVCG(_Array_ptr<nodeVCGType> : count(channelNets + 1));

void DFSAboveVCG(_Array_ptr<nodeVCGType> : count(channelNets + 1),	    ulong);

void DFSBelowVCG(_Array_ptr<nodeVCGType> : count(channelNets + 1),	    ulong);

void SCCofVCG(_Array_ptr<nodeVCGType> : count(channelNets + 1),		 _Array_ptr<ulong> : count(channelNets + 1),		 _Array_ptr<ulong> : count(countSCC + 1),		 ulong countSCC);

void SCC_DFSAboveVCG(_Array_ptr<nodeVCGType> : count(channelNets + 1),				ulong,				_Ptr<ulong>);

void SCC_DFSBelowVCG(_Array_ptr<nodeVCGType> : count(channelNets + 1),		ulong,		ulong);

void DumpSCC(_Array_ptr<ulong> : count(channelNets + 1),	    _Array_ptr<ulong> : count(totalSCC + 1));

void
AcyclicVCG(void);

void RemoveConstraintVCG(_Array_ptr<nodeVCGType> : count(channelNets + 1),					_Array_ptr<ulong> : count(channelNets + 1),					_Array_ptr<ulong> : count(channelNets + 1),					_Array_ptr<_Ptr<constraintVCGType>> : count((channelNets + 1) * (channelNets + 1)));

ulong ExistPathAboveVCG(_Array_ptr<nodeVCGType> : count(channelNets + 1),				  ulong above,				  ulong below);

void LongestPathVCG(_Array_ptr<nodeVCGType> : count(channelNets + 1),	       ulong);

ulong DFSAboveLongestPathVCG(_Array_ptr<nodeVCGType> : count(channelNets + 1),		       ulong);

ulong DFSBelowLongestPathVCG(_Array_ptr<nodeVCGType> : count(channelNets + 1),		       ulong);

ulong VCV(_Array_ptr<nodeVCGType> : count(channelNets + 1),    ulong,    ulong,    _Array_ptr<ulong> : count(channelNets + 1));


#pragma CHECKED_SCOPE OFF
#endif	/* VCG_H */
