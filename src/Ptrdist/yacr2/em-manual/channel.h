













#include "types.h"


#ifndef CHANNEL_H
#define CHANNEL_H


#pragma CHECKED_SCOPE ON




















extern unsigned long channelNets;
extern unsigned long channelColumns;
extern _Array_ptr<unsigned long> TOP : count(channelColumns + 1);
extern _Array_ptr<unsigned long> BOT : count(channelColumns + 1);
extern _Array_ptr<unsigned long> FIRST : count(channelNets + 1);
extern _Array_ptr<unsigned long> LAST : count(channelNets + 1);
extern _Array_ptr<unsigned long> DENSITY : count(channelColumns + 1);
extern _Array_ptr<unsigned long> CROSSING : count(channelNets + 1);
extern unsigned long channelTracks;
extern unsigned long channelTracksCopy;
extern unsigned long channelDensity;
extern unsigned long channelDensityColumn;
extern _Nt_array_ptr<char> channelFile;








void
BuildChannel(void);

void
DimensionChannel(void);

void
DescribeChannel(void);

void
DensityChannel(void);

#pragma CHECKED_SCOPE OFF
#endif	
