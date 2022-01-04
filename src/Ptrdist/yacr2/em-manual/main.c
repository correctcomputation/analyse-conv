







#define MAIN_CODE








#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "option.h"
#include "channel.h"
#include "vcg.h"
#include "hcg.h"
#include "assign.h"
#include "maze.h"


#pragma CHECKED_SCOPE ON
#define printf(...) _Unchecked { (printf)(__VA_ARGS__); }






int
main(int argc, _Array_ptr<_Nt_array_ptr<char>> argv : count(argc))
{
    unsigned long done;
    unsigned long fail;
    unsigned long net;
    unsigned long insert;
    int netsLeft;
int TIMELOOP;
for (TIMELOOP = 0; TIMELOOP < 20; ++TIMELOOP) {

    Option(argc, argv);

    BuildChannel();
    BuildVCG();
    AcyclicVCG();
    BuildHCG();

    do {



 AllocAssign();
 NetsAssign();
 InitAllocMaps();




 channelTracksCopy = channelTracks;
 for (net = 1; net <= channelNets; net++) {
     netsAssignCopy[net] = netsAssign[net];
 }




 fail = 0;
 do {
     done = 1;
     if ((netsLeft = DrawNets()) != 0) {
  _Unchecked { (printf)("Assignment could not route %d columns, trying maze1...\n", netsLeft); };

  if ((netsLeft = Maze1()) != 0) {
      _Unchecked { (printf)("Maze1 could not route %d columns, trying maze2...\n", netsLeft); };

      if ((netsLeft = Maze2()) != 0) {
   _Unchecked { (printf)("Maze2 could not route %d columns, trying maze3...\n", netsLeft); };

   if ((netsLeft = Maze3()) != 0) {
       _Unchecked { (printf)("Maze3 could not route %d columns, adding a track...\n", netsLeft); };


       if (! fail) {
    channelTracks++;
       }
       fail++;




       for (net = 1; net <= channelNets; net++) {
    netsAssign[net] = netsAssignCopy[net];
       }




       done = 0;
   }
      }
  }
     }





     if ((! done) && fail) {
#ifdef VERBOSE

#endif
  for (insert = 1; insert <= channelNets; insert++) {
      if (netsAssign[insert] >= fail) {
   netsAssign[insert]++;
      }
  }
     }
 } while ((! done) && (fail <= channelTracksCopy + 1));





 if (! done) {
     FreeAllocMaps();
     FreeAssign();
     ((void) sizeof ((channelTracks == channelTracksCopy + 1) ? 1 : 0), __extension__ ({ if (channelTracks == channelTracksCopy + 1) ; else __assert_fail ("channelTracks == channelTracksCopy + 1", "/home/matt/analyze-conversion-1.wt/src/Ptrdist/yacr2/manual-em-tmp/main.c", 134, __extension__ __PRETTY_FUNCTION__); }));
 }
    } while (! done);

    _Unchecked { (printf)("\n"); };
    PrintChannel();
#ifdef PLUS_STATS


#endif 
}
    exit(0);
}
