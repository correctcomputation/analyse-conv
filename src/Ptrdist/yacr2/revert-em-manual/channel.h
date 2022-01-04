













#include "types.h"


#ifndef CHANNEL_H
#define CHANNEL_H






















extern unsigned long channelNets;
extern unsigned long channelColumns;
extern unsigned long * TOP ;
extern unsigned long * BOT ;
extern unsigned long * FIRST ;
extern unsigned long * LAST ;
extern unsigned long * DENSITY ;
extern unsigned long * CROSSING ;
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
