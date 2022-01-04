














#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "types.h"
#include "vcg.h"
#include "assign.h"
#include "channel.h"

#pragma CHECKED_SCOPE ON
#define printf(...) _Unchecked { (printf)(__VA_ARGS__); }

_Array_ptr<nodeVCGType> VCG : count(channelNets + 1);
_Array_ptr<constraintVCGType> storageRootVCG : count((channelNets + 1) * (channelNets + 1));
_Array_ptr<constraintVCGType> storageVCG : bounds(storageRootVCG, storageRootVCG + (channelNets + 1) * (channelNets + 1));
unsigned long storageLimitVCG;
_Array_ptr<_Ptr<constraintVCGType>> removeVCG : count((channelNets + 1) * (channelNets + 1));
unsigned long removeTotalVCG;
_Array_ptr<unsigned long> SCC : count(channelNets + 1);
unsigned long totalSCC;
_Array_ptr<unsigned long> perSCC : count(channelNets + 1);







void
AllocVCG(void)
{
    VCG = malloc<nodeVCGType>((channelNets + 1) * sizeof(nodeVCGType));
    storageRootVCG = malloc<constraintVCGType>((channelNets + 1) * (channelNets + 1) * sizeof(constraintVCGType));
    storageVCG = storageRootVCG;
    storageLimitVCG = (channelNets + 1) * (channelNets + 1);
    SCC = malloc<unsigned long>((channelNets + 1) * sizeof(unsigned long));
    perSCC = malloc<unsigned long>((channelNets + 1) * sizeof(unsigned long));
    removeVCG = malloc<_Ptr<constraintVCGType>>((channelNets + 1) * (channelNets + 1) * sizeof(constraintVCGType *));
}

void
FreeVCG(void)
{
    _Unchecked { free<nodeVCGType>(VCG); }
    _Unchecked { free<constraintVCGType>(storageRootVCG); }
    storageLimitVCG = 0;
    _Unchecked { free<unsigned long>(SCC); }
    _Unchecked { free<unsigned long>(perSCC); }
    _Unchecked { free<_Ptr<constraintVCGType>>(removeVCG); }
}

void
BuildVCG(void)
{
    unsigned long col;
    unsigned long net;
    unsigned long constraint;
    unsigned long check;
    unsigned long add;




    AllocVCG();




    for (net = 1; net <= channelNets; net++) {



 constraint = 0;
 _Unchecked { VCG[net].netsAboveHook = storageVCG; }
 for (col = 1; col <= channelColumns; col++) {
     if ((TOP[col] == net) && (BOT[col] != net) && (BOT[col] != 0)) {



  add = 1;
  for (check = 0; check < constraint; check++) {
      if (VCG[net].netsAboveHook[check].bot == BOT[col]) {
   add = 0;
   break;
      }
  }




  if (add) {
   ((void) sizeof ((storageLimitVCG > 0) ? 1 : 0), __extension__ ({ if (storageLimitVCG > 0) ; else __assert_fail ("storageLimitVCG > 0", "/home/matt/analyze-conversion-1.wt/src/Ptrdist/yacr2/manual-em-tmp/vcg.c", 106, __extension__ __PRETTY_FUNCTION__); }));
   VCG[net].netsAbove = constraint;
      VCG[net].netsAboveHook[constraint].top = TOP[col];
      VCG[net].netsAboveHook[constraint].bot = BOT[col];
      VCG[net].netsAboveHook[constraint].col = col;
      VCG[net].netsAboveHook[constraint].removed = 0;
      storageVCG++;
      storageLimitVCG--;
      constraint++;
  }
     }
 }
 VCG[net].netsAbove = constraint;




 constraint = 0;
 _Unchecked { VCG[net].netsBelowHook = storageVCG; }
 for (col = 1; col <= channelColumns; col++) {
     if ((BOT[col] == net) && (TOP[col] != net) && (TOP[col] != 0)) {



  add = 1;
  for (check = 0; check < constraint; check++) {
      if (VCG[net].netsBelowHook[check].top == TOP[col]) {
   add = 0;
   break;
      }
  }




  if (add) {
   ((void) sizeof ((storageLimitVCG > 0) ? 1 : 0), __extension__ ({ if (storageLimitVCG > 0) ; else __assert_fail ("storageLimitVCG > 0", "/home/matt/analyze-conversion-1.wt/src/Ptrdist/yacr2/manual-em-tmp/vcg.c", 142, __extension__ __PRETTY_FUNCTION__); }));
   VCG[net].netsBelow = constraint;
      VCG[net].netsBelowHook[constraint].top = TOP[col];
      VCG[net].netsBelowHook[constraint].bot = BOT[col];
      VCG[net].netsBelowHook[constraint].col = col;
      VCG[net].netsBelowHook[constraint].removed = 0;
      storageVCG++;
      storageLimitVCG--;
      constraint++;
  }
     }
 }
 VCG[net].netsBelow = constraint;
    }
}

void DFSClearVCG(_Array_ptr<nodeVCGType> VCG : count(channelNets + 1))
{
    unsigned long net;

    for (net = 1; net <= channelNets; net++) {
 VCG[net].netsAboveLabel = 0;
 VCG[net].netsAboveReached = 0;
 VCG[net].netsBelowLabel = 0;
 VCG[net].netsBelowReached = 0;
    }
}

void DumpVCG(_Array_ptr<nodeVCGType> VCG : count(channelNets + 1))
{
    unsigned long net;
    unsigned long which;

    for (net = 1; net <= channelNets; net++) {
 _Unchecked { (printf)("[%d]\n", net); };
 _Unchecked { (printf)("above: "); };
 for (which = 0; which < VCG[net].netsAbove; which++) {
     if (! VCG[net].netsAboveHook[which].removed) {
  ((void) sizeof ((VCG[net].netsAboveHook[which].top == net) ? 1 : 0), __extension__ ({ if (VCG[net].netsAboveHook[which].top == net) ; else __assert_fail ("VCG[net].netsAboveHook[which].top == net", "/home/matt/analyze-conversion-1.wt/src/Ptrdist/yacr2/manual-em-tmp/vcg.c", 180, __extension__ __PRETTY_FUNCTION__); }));
  _Unchecked { (printf)("%d ", VCG[net].netsAboveHook[which].bot); };
     }
 }

 _Unchecked { (printf)("\n"); };
    _Unchecked { (printf)("below: "); };
 for (which = 0; which < VCG[net].netsBelow; which++) {
     if (! VCG[net].netsBelowHook[which].removed) {
  ((void) sizeof ((VCG[net].netsBelowHook[which].bot == net) ? 1 : 0), __extension__ ({ if (VCG[net].netsBelowHook[which].bot == net) ; else __assert_fail ("VCG[net].netsBelowHook[which].bot == net", "/home/matt/analyze-conversion-1.wt/src/Ptrdist/yacr2/manual-em-tmp/vcg.c", 189, __extension__ __PRETTY_FUNCTION__); }));
  _Unchecked { (printf)("%d ", VCG[net].netsBelowHook[which].top); };
     }
 }
 _Unchecked { (printf)("\n\n"); };
    }
}

void DFSAboveVCG(_Array_ptr<nodeVCGType> VCG : count(channelNets + 1), unsigned long net)
{
    unsigned long s;
    unsigned long above;

    VCG[net].netsAboveReached = 1;
    for (s = 0; s < VCG[net].netsAbove; s++) {
 if (! VCG[net].netsAboveHook[s].removed) {
     ((void) sizeof ((VCG[net].netsAboveHook[s].top == net) ? 1 : 0), __extension__ ({ if (VCG[net].netsAboveHook[s].top == net) ; else __assert_fail ("VCG[net].netsAboveHook[s].top == net", "/home/matt/analyze-conversion-1.wt/src/Ptrdist/yacr2/manual-em-tmp/vcg.c", 205, __extension__ __PRETTY_FUNCTION__); }));
     above = VCG[net].netsAboveHook[s].bot;
     if (! VCG[above].netsAboveReached) {
  DFSAboveVCG(VCG, above);
     }
 }
    }
}

void DFSBelowVCG(_Array_ptr<nodeVCGType> VCG : count(channelNets + 1), unsigned long net)
{
    unsigned long s;
    unsigned long below;

    VCG[net].netsBelowReached = 1;
    for (s = 0; s < VCG[net].netsBelow; s++) {
 if (! VCG[net].netsBelowHook[s].removed) {
     ((void) sizeof ((VCG[net].netsBelowHook[s].bot == net) ? 1 : 0), __extension__ ({ if (VCG[net].netsBelowHook[s].bot == net) ; else __assert_fail ("VCG[net].netsBelowHook[s].bot == net", "/home/matt/analyze-conversion-1.wt/src/Ptrdist/yacr2/manual-em-tmp/vcg.c", 222, __extension__ __PRETTY_FUNCTION__); }));
     below = VCG[net].netsBelowHook[s].top;
     if (! VCG[below].netsBelowReached) {
  DFSBelowVCG(VCG, below);
     }
 }
    }
}

void SCCofVCG(_Array_ptr<nodeVCGType> VCG : count(channelNets + 1), _Array_ptr<unsigned long> SCC : count(channelNets + 1), _Array_ptr<unsigned long> perSCC : count(countSCC + 1), unsigned long countSCC)
{
    unsigned long net;
    unsigned long scc;
    unsigned long per;
    unsigned long label;
    unsigned long which;
    unsigned long choose;
    unsigned long large;
    unsigned long done;
    ;




    label = 0;
    for (net = 1; net <= channelNets; net++){
 if (! VCG[net].netsAboveReached) {
     SCC_DFSAboveVCG(VCG, net, &label);
 }
    }




    which = 0;
    do {
 done = 1;




 choose = 0;
 large = 0;
 for (net = 1; net <= channelNets; net++) {
     if (! VCG[net].netsBelowReached) {
  ((void) sizeof ((VCG[net].netsAboveLabel > 0) ? 1 : 0), __extension__ ({ if (VCG[net].netsAboveLabel > 0) ; else __assert_fail ("VCG[net].netsAboveLabel > 0", "/home/matt/analyze-conversion-1.wt/src/Ptrdist/yacr2/manual-em-tmp/vcg.c", 267, __extension__ __PRETTY_FUNCTION__); }));
  if (VCG[net].netsAboveLabel > large) {
      choose = net;
      large = VCG[net].netsAboveLabel;
      done = 0;
  }
     }
 }




 if (! done) {
     which++;
     SCC_DFSBelowVCG(VCG, choose, which);
 }
    } while (! done);




    totalSCC = 0;
    for (net = 1; net <= channelNets; net++) {
 SCC[net] = VCG[net].netsBelowLabel;
 if (SCC[net] > totalSCC) {
     totalSCC = SCC[net];
 }
    }
    ((void) sizeof ((totalSCC > 0) ? 1 : 0), __extension__ ({ if (totalSCC > 0) ; else __assert_fail ("totalSCC > 0", "/home/matt/analyze-conversion-1.wt/src/Ptrdist/yacr2/manual-em-tmp/vcg.c", 295, __extension__ __PRETTY_FUNCTION__); }));
    for (scc = 1; scc <= totalSCC; scc++) {
 per = 0;
 for (net = 1; net <= channelNets; net++) {
     if (SCC[net] == scc) {
  per++;
     }
 }
 perSCC[scc] = per;
    }
    ;
}

void SCC_DFSAboveVCG(_Array_ptr<nodeVCGType> VCG : count(channelNets + 1), unsigned long net, _Ptr<unsigned long> label)
{
    unsigned long s;
    unsigned long above;

    VCG[net].netsAboveReached = 1;
    for (s = 0; s < VCG[net].netsAbove; s++) {
 if (! VCG[net].netsAboveHook[s].removed) {
     ((void) sizeof ((VCG[net].netsAboveHook[s].top == net) ? 1 : 0), __extension__ ({ if (VCG[net].netsAboveHook[s].top == net) ; else __assert_fail ("VCG[net].netsAboveHook[s].top == net", "/home/matt/analyze-conversion-1.wt/src/Ptrdist/yacr2/manual-em-tmp/vcg.c", 316, __extension__ __PRETTY_FUNCTION__); }));
     above = VCG[net].netsAboveHook[s].bot;
     if (! VCG[above].netsAboveReached) {
  SCC_DFSAboveVCG(VCG, above, label);
     }
 }
    }
    (*label)++;
    VCG[net].netsAboveLabel = *label;
}

void SCC_DFSBelowVCG(_Array_ptr<nodeVCGType> VCG : count(channelNets + 1), unsigned long net, unsigned long label)
{
    unsigned long s;
    unsigned long below;

    VCG[net].netsBelowReached = 1;
    for (s = 0; s < VCG[net].netsBelow; s++) {
 if (! VCG[net].netsBelowHook[s].removed) {
     ((void) sizeof ((VCG[net].netsBelowHook[s].bot == net) ? 1 : 0), __extension__ ({ if (VCG[net].netsBelowHook[s].bot == net) ; else __assert_fail ("VCG[net].netsBelowHook[s].bot == net", "/home/matt/analyze-conversion-1.wt/src/Ptrdist/yacr2/manual-em-tmp/vcg.c", 335, __extension__ __PRETTY_FUNCTION__); }));
     below = VCG[net].netsBelowHook[s].top;
     if (! VCG[below].netsBelowReached) {
  SCC_DFSBelowVCG(VCG, below, label);
     }
 }
    }
    VCG[net].netsBelowLabel = label;
}

void DumpSCC(_Array_ptr<unsigned long> SCC : count(channelNets + 1), _Array_ptr<unsigned long> perSCC : count(totalSCC + 1))
{
    unsigned long net;
    unsigned long scc;

    for (scc = 1; scc <= totalSCC; scc++) {
 _Unchecked { (printf)("[%d]\t", scc); };
 for (net = 1; net <= channelNets; net++) {
     if (SCC[net] == scc) {
  _Unchecked { (printf)("%d ", net); };
     }
 }
 _Unchecked { (printf)("<%d>", perSCC[scc]); };
 _Unchecked { (printf)("\n"); };
    }
    _Unchecked { (printf)("\n"); };
}

void
AcyclicVCG(void)
{
    unsigned long done;
    unsigned long scc;
    unsigned long net;
    unsigned long top;
    unsigned long bot;
    unsigned long rep;
    unsigned long which;
    unsigned long total;
    unsigned long cycle;
    unsigned long acyclic;

    for (net = 1; net <= channelNets; net++) {
 for (which = 0; which < VCG[net].netsAbove; which++) {
     VCG[net].netsAboveHook[which].removed = 0;
 }
 for (which = 0; which < VCG[net].netsBelow; which++) {
     VCG[net].netsBelowHook[which].removed = 0;
 }
    }

    acyclic = 1;
    removeTotalVCG = 0;
    do {
 done = 1;




 DFSClearVCG(VCG);
 SCCofVCG(VCG, SCC, perSCC, channelNets);
 for (scc = 1; scc <= totalSCC; scc++) {
     if (perSCC[scc] > 1) {
  acyclic = 0;
  done = 0;
  break;
     }
 }





 if (! done) {
     RemoveConstraintVCG(VCG, SCC, perSCC, removeVCG);
 }
    } while (! done);






    total = removeTotalVCG;
    for (rep = 0; rep < removeTotalVCG; rep++) {




 top = (*removeVCG[rep]).top;
 bot = (*removeVCG[rep]).bot;




 for (which = 0; which < VCG[top].netsAbove; which++) {
     if (VCG[top].netsAboveHook[which].bot == bot) {
  VCG[top].netsAboveHook[which].removed = 0;
  break;
     }
 }




 for (which = 0; which < VCG[bot].netsBelow; which++) {
     if (VCG[bot].netsBelowHook[which].top == top) {
  VCG[bot].netsBelowHook[which].removed = 0;
  break;
     }
 }




 cycle = 0;
 DFSClearVCG(VCG);
 SCCofVCG(VCG, SCC, perSCC, channelNets);
 for (scc = 1; scc <= totalSCC; scc++) {
     if (perSCC[scc] > 1) {
  cycle = 1;
  break;
     }
 }
 if (cycle) {




     for (which = 0; which < VCG[top].netsAbove; which++) {
  if (VCG[top].netsAboveHook[which].bot == bot) {
      VCG[top].netsAboveHook[which].removed = 1;
      break;
  }
     }
     for (which = 0; which < VCG[bot].netsBelow; which++) {
  if (VCG[bot].netsBelowHook[which].top == top) {
      VCG[bot].netsBelowHook[which].removed = 1;
      break;
  }
     }
 }
 else {




     total--;
 }
    }

    if (acyclic) {
 _Unchecked { (printf)("\n*** Input is acyclic! ***\n"); };
    }
    else {
 _Unchecked { (printf)("\n*** Input is cyclic! ***\n"); };
 _Unchecked { (printf)("*** VC's removed (%d) ***\n", total); };
    }
}

void RemoveConstraintVCG(_Array_ptr<nodeVCGType> VCG : count(channelNets + 1), _Array_ptr<unsigned long> SCC : count(channelNets + 1), _Array_ptr<unsigned long> perSCC : count(channelNets + 1), _Array_ptr<_Ptr<constraintVCGType>> removeVCG : count((channelNets + 1) * (channelNets + 1)))
{
    unsigned long scc;
    unsigned long net;
    unsigned long which;
    unsigned long best;
    unsigned long weight;
    unsigned long top;
    unsigned long bot;
    unsigned long col;
    _Ptr<constraintVCGType> remove = ((void*)0);

    for (scc = 1; scc <= totalSCC; scc++) {



 if (perSCC[scc] > 1) {



     remove = ((void*)0);
     best = 6 + 1;
     for (net = 1; net <= channelNets; net++) {



  if (SCC[net] == scc) {




      for (which = 0; which < VCG[net].netsAbove; which++) {
   bot = VCG[net].netsAboveHook[which].bot;
   if ((SCC[bot] == scc) && (! VCG[net].netsAboveHook[which].removed)) {


















       col = VCG[net].netsAboveHook[which].col;
       weight = 0;
       if (col == 1) {
    weight += 3;
    if (TOP[col+1] && BOT[col+1]) {
        weight += 3;
    }
    else if (! (TOP[col+1] || BOT[col+1])) {
    }
    else {
        weight += 2;
    }
       }
       else if (col == channelColumns) {
    weight += 3;
    if (TOP[col-1] && BOT[col-1]) {
        weight += 3;
    }
    else if (! (TOP[col-1] || BOT[col-1])) {
    }
    else {
        weight += 2;
    }
       }
       else {
    if (TOP[col-1] && BOT[col-1]) {
        weight += 3;
    }
    else if (! (TOP[col-1] || BOT[col-1])) {
    }
    else {
        weight += 2;
    }
    if (TOP[col+1] && BOT[col+1]) {
        weight += 3;
    }
    else if (! (TOP[col+1] || BOT[col+1])) {
    }
    else {
        weight += 2;
    }
       }




       if (weight < best) {
    best = weight;
    _Unchecked { remove = &VCG[net].netsAboveHook[which]; }
       }
   }
      }
  }
     }




     ((void) sizeof ((remove != ((void*)0)) ? 1 : 0), __extension__ ({ if (remove != ((void*)0)) ; else __assert_fail ("remove != NULL", "/home/matt/analyze-conversion-1.wt/src/Ptrdist/yacr2/manual-em-tmp/vcg.c", 605, __extension__ __PRETTY_FUNCTION__); }));
     fflush(stdout);
     ((void) sizeof ((removeTotalVCG < ((channelNets + 1) * (channelNets + 1))) ? 1 : 0), __extension__ ({ if (removeTotalVCG < ((channelNets + 1) * (channelNets + 1))) ; else __assert_fail ("removeTotalVCG < ((channelNets + 1) * (channelNets + 1))", "/home/matt/analyze-conversion-1.wt/src/Ptrdist/yacr2/manual-em-tmp/vcg.c", 607, __extension__ __PRETTY_FUNCTION__); }));
     removeVCG[removeTotalVCG] = remove;
     removeTotalVCG++;
     top = (*remove).top;
     bot = (*remove).bot;




     (*remove).removed = 1;




     for (which = 0; which < VCG[bot].netsBelow; which++) {
  if (VCG[bot].netsBelowHook[which].top == top) {
      VCG[bot].netsBelowHook[which].removed = 1;
      break;
  }
     }
 }
    }
}

unsigned long ExistPathAboveVCG(_Array_ptr<nodeVCGType> VCG : count(channelNets + 1), unsigned long above, unsigned long below)
{
    DFSClearVCG(VCG);
    DFSAboveVCG(VCG, above);
    return(VCG[below].netsAboveReached);
}

void LongestPathVCG(_Array_ptr<nodeVCGType> VCG : count(channelNets + 1), unsigned long net)
{
    unsigned long track;
    unsigned long bot;
    unsigned long top;
    unsigned long not;






    DFSClearVCG(VCG);
    cardBotNotPref = DFSAboveLongestPathVCG(VCG, net) - 1;
    bot = cardBotNotPref;
    for (track = channelTracks; track >= 1; track--) {
 if (bot > 0) {
     tracksBotNotPref[track] = 1;
     bot--;
 }
 else {
     tracksBotNotPref[track] = 0;
 }
    }






    DFSClearVCG(VCG);
    cardTopNotPref = DFSBelowLongestPathVCG(VCG, net) - 1;
    top = cardTopNotPref;
    for (track = 1; track <= channelTracks; track++) {
 if (top > 0) {
     tracksTopNotPref[track] = 1;
     top--;
 }
 else {
     tracksTopNotPref[track] = 0;
 }
    }







    not = 0;
    for (track = 1; track <= channelTracks; track++) {
 if (tracksTopNotPref[track] || tracksBotNotPref[track]) {
     tracksNotPref[track] = 1;
     not++;
 }
 else {
     tracksNotPref[track] = 0;
 }
    }
    cardNotPref = not;
}

unsigned long DFSAboveLongestPathVCG(_Array_ptr<nodeVCGType> VCG : count(channelNets + 1), unsigned long net)
{
    unsigned long s;
    unsigned long above;
    unsigned long path;
    unsigned long longest;

    longest = 0;
    VCG[net].netsAboveReached = 1;
    for (s = 0; s < VCG[net].netsAbove; s++) {
 if (! VCG[net].netsAboveHook[s].removed) {
     ((void) sizeof ((VCG[net].netsAboveHook[s].top == net) ? 1 : 0), __extension__ ({ if (VCG[net].netsAboveHook[s].top == net) ; else __assert_fail ("VCG[net].netsAboveHook[s].top == net", "/home/matt/analyze-conversion-1.wt/src/Ptrdist/yacr2/manual-em-tmp/vcg.c", 711, __extension__ __PRETTY_FUNCTION__); }));
     above = VCG[net].netsAboveHook[s].bot;
     if (! VCG[above].netsAboveReached) {
  path = DFSAboveLongestPathVCG(VCG, above);
  if (path > longest) {
      longest = path;
  }
     }
 }
    }
    return(longest+1);
}

unsigned long DFSBelowLongestPathVCG(_Array_ptr<nodeVCGType> VCG : count(channelNets + 1), unsigned long net)
{
    unsigned long s;
    unsigned long below;
    unsigned long path;
    unsigned long longest;

    longest = 0;
    VCG[net].netsBelowReached = 1;
    for (s = 0; s < VCG[net].netsBelow; s++) {
 if (! VCG[net].netsBelowHook[s].removed) {
     ((void) sizeof ((VCG[net].netsBelowHook[s].bot == net) ? 1 : 0), __extension__ ({ if (VCG[net].netsBelowHook[s].bot == net) ; else __assert_fail ("VCG[net].netsBelowHook[s].bot == net", "/home/matt/analyze-conversion-1.wt/src/Ptrdist/yacr2/manual-em-tmp/vcg.c", 735, __extension__ __PRETTY_FUNCTION__); }));
     below = VCG[net].netsBelowHook[s].top;
     if (! VCG[below].netsBelowReached) {
  path = DFSBelowLongestPathVCG(VCG, below);
  if (path > longest) {
      longest = path;
  }
     }
 }
    }
    return(longest+1);
}

unsigned long VCV(_Array_ptr<nodeVCGType> VCG : count(channelNets + 1), unsigned long check, unsigned long track, _Array_ptr<unsigned long> assign : count(channelNets + 1))
{
    unsigned long net;
    unsigned long vcv;

    vcv = 0;
    for (net = 1; net <= channelNets; net++) {
 if (assign[net]) {
     if (assign[net] < track) {



  if (ExistPathAboveVCG(VCG, net, check)) {
      vcv++;
  }
     }
     else if (assign[net] > track) {



  if (ExistPathAboveVCG(VCG, check, net)) {
      vcv++;
  }
     }
     else {



  if (ExistPathAboveVCG(VCG, net, check) || ExistPathAboveVCG(VCG, check, net)) {
      vcv++;
  }
     }
 }
    }
    return(vcv);
}
