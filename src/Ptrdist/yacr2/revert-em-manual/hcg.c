













#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "types.h"
#include "hcg.h"
#include "channel.h"

#define printf(...)  { (printf)(__VA_ARGS__); }






nodeHCGType * HCG ;
unsigned long * storageRootHCG ;
unsigned long * storageHCG ;
unsigned long storageLimitHCG;

void
AllocHCG(void)
{
    HCG = malloc((channelNets + 1) * sizeof(nodeHCGType));
    storageRootHCG = malloc((channelNets + 1) * (channelNets + 1) * sizeof(unsigned long));
     { storageHCG = storageRootHCG; }
    storageLimitHCG = (channelNets + 1) * (channelNets + 1);
}

void
FreeHCG(void)
{
     { free(HCG); }
     { free(storageRootHCG); }
    storageLimitHCG = 0;
}

void
BuildHCG(void)
{
    unsigned long net;
    unsigned long which;
    unsigned long constraint;
    unsigned long first;
    unsigned long last;
    unsigned long check;
    unsigned long add;




    AllocHCG();




    for (net = 1; net <= channelNets; net++) {
 first = FIRST[net];
 last = LAST[net];
 constraint = 0;
 HCG[net].nets = constraint;
  { HCG[net].netsHook = storageHCG; }
 for (which = 1; which <= channelNets; which++) {
     if (((FIRST[which] < first) && (LAST[which] < first)) || ((FIRST[which] > last) && (LAST[which] > last))) {



     }
     else {






  add = 1;
  for (check = 0; check < constraint; check++) {
      if (HCG[net].netsHook[check] == which) {
   add = 0;
   break;
      }
  }
  ((void) sizeof ((add) ? 1 : 0), __extension__ ({ if (add) ; else __assert_fail ("add", "/home/matt/analyze-conversion/src/Ptrdist/yacr2/tmp-em-manual/hcg.c", 97, __extension__ __PRETTY_FUNCTION__); }));




  ((void) sizeof ((storageLimitHCG > 0) ? 1 : 0), __extension__ ({ if (storageLimitHCG > 0) ; else __assert_fail ("storageLimitHCG > 0", "/home/matt/analyze-conversion/src/Ptrdist/yacr2/tmp-em-manual/hcg.c", 102, __extension__ __PRETTY_FUNCTION__); }));
  HCG[net].nets = constraint;
  HCG[net].netsHook[constraint] = which;
  storageHCG++;
  storageLimitHCG--;
  constraint++;
     }
 }
 HCG[net].nets = constraint;
    }
}

void
DFSClearHCG(nodeHCGType * HCG )
{
    unsigned long net;

    for (net = 1; net <= channelNets; net++) {
 HCG[net].netsReached = 0;
    }
}

void
DumpHCG(nodeHCGType * HCG )
{
    unsigned long net;
    unsigned long which;

    for (net = 1; net <= channelNets; net++) {
  { (printf)("[%d]\n", net); };
 for (which = 0; which < HCG[net].nets; which++) {
      { (printf)("%d ", HCG[net].netsHook[which]); };
 }
  { (printf)("\n\n"); };
    }
}

void
NoHCV(nodeHCGType * HCG , unsigned long select, unsigned long * netsAssign , unsigned long * tracksNoHCV )
{
    unsigned long track;
    unsigned long net;
    unsigned long which;
    unsigned long ok;

    for (track = 1; track <= channelTracks; track++) {




 ok = 1;
 for (net = 1; net <= channelNets; net++) {
     if (netsAssign[net] == track) {



  for (which = 0; which < HCG[select].nets; which++) {
      if (HCG[select].netsHook[which] == net) {



   ok = 0;
   break;
      }
  }




  if (! ok) {
      break;
  }
     }
 }




 tracksNoHCV[track] = ok;
    }
}
