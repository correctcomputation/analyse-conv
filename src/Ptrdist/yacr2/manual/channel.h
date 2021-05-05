
/*
 *
 * channel.h
 *
 */


/*
 *
 * Includes.
 *
 */

#include "types.h"


#ifndef CHANNEL_H
#define CHANNEL_H


#pragma CHECKED_SCOPE ON
/*
 *
 * Defines.
 *
 */


/*
 *
 * Types.
 *
 */


/*
 *
 * Globals.
 *
 */

extern ulong		channelNets;
extern ulong		channelColumns;
extern _Array_ptr<ulong>		TOP : count(channelColumns + 1);
extern _Array_ptr<ulong>		BOT : count(channelColumns + 1);
extern _Array_ptr<ulong>		FIRST : count(channelNets + 1);
extern _Array_ptr<ulong>		LAST : count(channelNets + 1);
extern _Array_ptr<ulong>		DENSITY : count(channelColumns + 1);
extern _Array_ptr<ulong>		CROSSING : count(channelNets + 1);
extern ulong		channelTracks;
extern ulong		channelTracksCopy;
extern ulong		channelDensity;
extern ulong		channelDensityColumn;
extern _Nt_array_ptr<char>		channelFile;


/*
 *
 * Prototypes.
 *
 */

void
BuildChannel(void);

void
DimensionChannel(void);

void
DescribeChannel(void);

void
DensityChannel(void);

#pragma CHECKED_SCOPE OFF
#endif	/* CHANNEL_H */
