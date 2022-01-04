













#include "types.h"


#ifndef CHANNEL_H
#define CHANNEL_H






















extern _Array_ptr<unsigned long> TOP : count(channelColumns);
extern _Array_ptr<unsigned long> BOT : count(channelColumns);
extern _Array_ptr<unsigned long> FIRST;
extern _Array_ptr<unsigned long> LAST;
extern _Array_ptr<unsigned long> DENSITY;
extern _Array_ptr<unsigned long> CROSSING;
extern unsigned long channelNets;
extern unsigned long channelColumns;
extern unsigned long channelTracks;
extern unsigned long channelTracksCopy;
extern unsigned long channelDensity;
extern unsigned long channelDensityColumn;
extern char * channelFile;







void
BuildChannel(void);

void
DimensionChannel(void);

void
DescribeChannel(void);

void
DensityChannel(void);

#endif	
