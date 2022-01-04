






#include <string.h>








#include <stdio.h>
#include <stdlib.h>
#include "channel.h"








void
Option(int argc, _Array_ptr<_Nt_array_ptr<char>> argv : count(argc))
{



    if (argc != 2) {
 printf("\nUsage: yacr2 <filename>\n\n");
 exit(1);
    }




    channelFile = argv[1];
}
