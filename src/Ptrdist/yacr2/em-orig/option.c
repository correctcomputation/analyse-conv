






#include <string.h>








#include <stdio.h>
#include <stdlib.h>
#include "channel.h"








void
Option(int argc, char *argv[])
{



    if (argc != 2) {
 printf("\nUsage: yacr2 <filename>\n\n");
 exit(1);
    }




    channelFile = argv[1];
}
