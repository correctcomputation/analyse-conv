






#include <string.h>








#include <stdio.h>
#include <stdlib.h>
#include "channel.h"

#define printf(...)  { (printf)(__VA_ARGS__); }







void
Option(int argc, char * * argv )
{



    if (argc != 2) {
  { (printf)("\nUsage: yacr2 <filename>\n\n"); };
 exit(1);
    }




     { channelFile = argv[1]; }
}
