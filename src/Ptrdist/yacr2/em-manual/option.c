






#include <string.h>








#include <stdio.h>
#include <stdlib.h>
#include "channel.h"

#pragma CHECKED_SCOPE ON
#define printf(...) _Unchecked { (printf)(__VA_ARGS__); }







void
Option(int argc, _Array_ptr<_Nt_array_ptr<char>> argv : count(argc))
{



    if (argc != 2) {
 _Unchecked { (printf)("\nUsage: yacr2 <filename>\n\n"); };
 exit(1);
    }




    _Unchecked { channelFile = argv[1]; }
}
