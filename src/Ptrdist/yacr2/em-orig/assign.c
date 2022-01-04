












#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "types.h"
#include "assign.h"
#include "channel.h"
#include "vcg.h"
#include "hcg.h"

unsigned long * * costMatrix;
unsigned long * tracksNoHCV;
unsigned long * tracksNotPref;
unsigned long * tracksTopNotPref;
unsigned long * tracksBotNotPref;
unsigned long cardNotPref;
unsigned long cardTopNotPref;
unsigned long cardBotNotPref;
unsigned long * tracksAssign;
unsigned long * netsAssign;
unsigned long * netsAssignCopy;








void
AllocAssign(void)
{
    unsigned long net;




    costMatrix = (long * *)malloc((channelNets+1) * sizeof(long *));
    for (net = 1; net <= channelNets; net++) {
 costMatrix[net] = (long *)malloc((channelTracks+2) * sizeof(long));
    }




    tracksNotPref = (unsigned long *)malloc((channelTracks+2) * sizeof(unsigned long));
    tracksTopNotPref = (unsigned long *)malloc((channelTracks+2) * sizeof(unsigned long));
    tracksBotNotPref = (unsigned long *)malloc((channelTracks+2) * sizeof(unsigned long));
    tracksNoHCV = (unsigned long *)malloc((channelTracks+2) * sizeof(unsigned long));
    tracksAssign = (unsigned long *)malloc((channelTracks+2) * sizeof(unsigned long));
    netsAssign = (unsigned long *)malloc((channelNets+1) * sizeof(unsigned long));
    netsAssignCopy = (unsigned long *)malloc((channelNets+1) * sizeof(unsigned long));
}

void
FreeAssign(void)
{
    unsigned long net;




    for (net = 1; net <= channelNets; net++) {
 free(costMatrix[net]);
    }
    free(costMatrix);




    free(tracksNotPref);
    free(tracksTopNotPref);
    free(tracksBotNotPref);
    free(tracksNoHCV);
    free(tracksAssign);
    free(netsAssign);
    free(netsAssignCopy);
}

void
NetsAssign(void)
{
    unsigned long net;




    for (net = 1; net <= channelNets; net++) {
 netsAssign[net] = 0;
    }




    MaxNetsAssign();

#ifdef SCOTT









#else



    LeftNetsAssign();




    RightNetsAssign();
#endif
}

void
MaxNetsAssign(void)
{
    unsigned long net;
    unsigned long netSelect;
    unsigned long netsCrossing;
    ;

#ifdef VERBOSE


#endif




    netsCrossing = 0;
    for (net = 1; net <= channelNets; net++) {
 if ((FIRST[net] <= channelDensityColumn) && (LAST[net] >= channelDensityColumn)) {
     CROSSING[net] = 1;
     netsCrossing++;
 }
 else {
     CROSSING[net] = 0;
 }
    }

    while (netsCrossing > 0) {



 Select(VCG, HCG, netsAssign, &netSelect, CROSSING);




 Assign(VCG, netsAssign, netSelect);




 CROSSING[netSelect] = 0;
 netsCrossing--;
    }
    ;
}

void
RightNetsAssign(void)
{
    unsigned long net;
    unsigned long col;
    unsigned long top;
    unsigned long bot;
    unsigned long netsCrossing;
    unsigned long netSelect;
    ;




    for (net = 1; net <= channelNets; net++) {
 CROSSING[net] = 0;
    }
    netsCrossing = 0;




    for (col = channelDensityColumn+1; col <= channelColumns; col++) {



 top = TOP[col];
 bot = BOT[col];
 if (top != bot) {
     if (top && (FIRST[top] == col)) {
  CROSSING[top] = 1;
  netsCrossing++;
     }
     if (bot && (FIRST[bot] == col)) {
  CROSSING[bot] = 1;
  netsCrossing++;
     }
 }
 else {
     if (top && (FIRST[top] == col)) {
  CROSSING[top] = 1;
  netsCrossing++;
     }
 }




 if ((LAST[top] == col) || (LAST[bot] == col)) {
     while (netsCrossing > 0) {



  Select(VCG, HCG, netsAssign, &netSelect, CROSSING);




  Assign(VCG, netsAssign, netSelect);




  CROSSING[netSelect] = 0;
  netsCrossing--;
     }
 }
    }
    ((void) sizeof ((! netsCrossing) ? 1 : 0), __extension__ ({ if (! netsCrossing) ; else __assert_fail ("! netsCrossing", "/home/matt/analyze-conversion/src/Ptrdist/yacr2/tmp-em-orig/assign.c", 247, __extension__ __PRETTY_FUNCTION__); }));
    ;
}

void
LeftNetsAssign(void)
{
    unsigned long net;
    unsigned long col;
    unsigned long top;
    unsigned long bot;
    unsigned long netsCrossing;
    unsigned long netSelect;
    ;




    for (net = 1; net <= channelNets; net++) {
 CROSSING[net] = 0;
    }
    netsCrossing = 0;




    for (col = channelDensityColumn-1; col >= 1; col--) {



 top = TOP[col];
 bot = BOT[col];
 if (top != bot) {
     if (top && (LAST[top] == col)) {
  CROSSING[top] = 1;
  netsCrossing++;
     }
     if (bot && (LAST[bot] == col)) {
  CROSSING[bot] = 1;
  netsCrossing++;
     }
 }
 else {
     if (top && (LAST[top] == col)) {
  CROSSING[top] = 1;
  netsCrossing++;
     }
 }




 if ((FIRST[top] == col) || (FIRST[bot] == col)) {
     while (netsCrossing > 0) {



  Select(VCG, HCG, netsAssign, &netSelect, CROSSING);




  Assign(VCG, netsAssign, netSelect);




  CROSSING[netSelect] = 0;
  netsCrossing--;
     }
 }
    }
    ((void) sizeof ((! netsCrossing) ? 1 : 0), __extension__ ({ if (! netsCrossing) ; else __assert_fail ("! netsCrossing", "/home/matt/analyze-conversion/src/Ptrdist/yacr2/tmp-em-orig/assign.c", 319, __extension__ __PRETTY_FUNCTION__); }));
    ;
}

void
Assign(nodeVCGType * VCG, unsigned long * assign, unsigned long select)
{
    long dist;
    unsigned long ideal;
    unsigned long track;
    unsigned long tracks;
    unsigned long trackAssign;
    unsigned long vcv;
    long vcvDist;
    unsigned long vcvAssign;
    long * costNet;
    ;

#ifdef VERBOSE

#endif













    LongestPathVCG(VCG, select);
    NoHCV(HCG, select, assign, tracksNoHCV);
    IdealTrack(channelTracks, cardTopNotPref, cardBotNotPref, &ideal);

#ifdef VERBOSE










#endif




    costNet = costMatrix[select];
    ((void) sizeof (((select >= 1) && (select <= channelNets)) ? 1 : 0), __extension__ ({ if ((select >= 1) && (select <= channelNets)) ; else __assert_fail ("(select >= 1) && (select <= channelNets)", "/home/matt/analyze-conversion/src/Ptrdist/yacr2/tmp-em-orig/assign.c", 374, __extension__ __PRETTY_FUNCTION__); }));
    tracks = 0;
    for (track = 1; track <= channelTracks; track++) {
 tracksAssign[track] = 0;
    }




    for (track = 1; track <= channelTracks; track++) {
 if (tracksNoHCV[track] && (! tracksNotPref[track])) {
     tracksAssign[track] = 1;
     tracks++;
 }
    }
#ifdef VERBOSE



#endif



    if (tracks == 0) {
 for (track = 1; track <= channelTracks; track++) {
     if (tracksNoHCV[track] && tracksTopNotPref[track] && tracksBotNotPref[track]) {
  tracksAssign[track] = 1;
  tracks++;
     }
 }
#ifdef VERBOSE



#endif
    }



    if (tracks == 0) {
 for (track = 2; track < channelTracks; track++) {
     if (tracksNoHCV[track] && tracksNotPref[track]) {
  tracksAssign[track] = 1;
  tracks++;
     }
 }
#ifdef VERBOSE



#endif
    }



    if (tracks == 0) {
 if (tracksNoHCV[1]) {
     tracksAssign[1] = 1;
     tracks++;
 }
 if (tracksNoHCV[channelTracks]) {
     tracksAssign[channelTracks] = 1;
     tracks++;
 }
#ifdef VERBOSE

#endif
    }
    ((void) sizeof ((tracks != 0) ? 1 : 0), __extension__ ({ if (tracks != 0) ; else __assert_fail ("tracks != 0", "/home/matt/analyze-conversion/src/Ptrdist/yacr2/tmp-em-orig/assign.c", 442, __extension__ __PRETTY_FUNCTION__); }));






































    trackAssign = 0;
    vcvAssign = 1000000;
    for (track = 1; track <= channelTracks; track++) {
 if (tracksAssign[track]) {
     vcv = VCV(VCG, select, track, netsAssign);
     if (vcv < vcvAssign) {
  vcvAssign = vcv;
  trackAssign = track;
  vcvDist = (long) (track - ideal);
  if (vcvDist < 0) {
      vcvDist *= -1;
  }
     }
     else if (vcv == vcvAssign) {
  ((void) sizeof ((trackAssign) ? 1 : 0), __extension__ ({ if (trackAssign) ; else __assert_fail ("trackAssign", "/home/matt/analyze-conversion/src/Ptrdist/yacr2/tmp-em-orig/assign.c", 495, __extension__ __PRETTY_FUNCTION__); }));
  dist = (long) (track - ideal);
  if (dist < 0) {
      dist *= -1;
  }
  if (dist < vcvDist) {
      vcvDist = dist;
      vcvAssign = vcv;
      trackAssign = track;
  }
     }
 }
    }
    ((void) sizeof ((trackAssign) ? 1 : 0), __extension__ ({ if (trackAssign) ; else __assert_fail ("trackAssign", "/home/matt/analyze-conversion/src/Ptrdist/yacr2/tmp-em-orig/assign.c", 508, __extension__ __PRETTY_FUNCTION__); }));
    assign[select] = trackAssign;
#ifdef VERBOSE

#endif
    ;
}

void
Select(nodeVCGType * VCG, nodeHCGType * HCG, unsigned long * netsAssign, unsigned long * netSelect, unsigned long * CROSSING)
{
    unsigned long net;
    unsigned long track;
    unsigned long select;
    long * costNet;
    long cost;
    long largest;




    BuildCostMatrix(VCG, HCG, netsAssign, CROSSING);





    largest = -1;
    select = 0;
    for (net = 1; net <= channelNets; net++) {
 if (CROSSING[net]) {
     cost = 0;
     costNet = costMatrix[net];
     for (track = 1; track <= channelTracks; track++) {
  cost += costNet[track];
     }
     if (cost > largest) {
  largest = cost;
  select = net;
     }
 }
    }
    ((void) sizeof ((select) ? 1 : 0), __extension__ ({ if (select) ; else __assert_fail ("select", "/home/matt/analyze-conversion/src/Ptrdist/yacr2/tmp-em-orig/assign.c", 550, __extension__ __PRETTY_FUNCTION__); }));




    *netSelect = select;
}

void
BuildCostMatrix(nodeVCGType * VCG, nodeHCGType * HCG, unsigned long * netsAssign, unsigned long * CROSSING)
{
    unsigned long net;
    unsigned long track;
    unsigned long ideal;
    long dist;
    long mult;
    long * costNet;
    ;




    for (net = 1; net <= channelNets; net++) {
 costNet = costMatrix[net];
 for (track = 1; track <= channelTracks; track++) {
     costNet[track] = 0;
 }
    }

    for (net = 1; net <= channelNets; net++) {
 if (CROSSING[net]) {




     costNet = costMatrix[net];




     LongestPathVCG(VCG, net);
     NoHCV(HCG, net, netsAssign, tracksNoHCV);
     IdealTrack(channelTracks, cardTopNotPref, cardBotNotPref, &ideal);




     for (track = 1; track <= channelTracks; track++) {
  if (tracksNoHCV[track]) {
      if (cardNotPref != channelTracks) {
   if (tracksNotPref[track]) {
       costNet[track] = 10000;
   }
   else {
       costNet[track] = 100 * cardNotPref;
   }
      }
      else {
   if ((track > (channelTracks - cardBotNotPref)) && (track <= cardTopNotPref)) {
       mult = cardNotPref - (cardTopNotPref + cardBotNotPref - channelTracks);
       ((void) sizeof ((mult >= 0) ? 1 : 0), __extension__ ({ if (mult >= 0) ; else __assert_fail ("mult >= 0", "/home/matt/analyze-conversion/src/Ptrdist/yacr2/tmp-em-orig/assign.c", 610, __extension__ __PRETTY_FUNCTION__); }));
       costNet[track] = 100 * mult;
   }
   else {
       costNet[track] = 10000;
   }
      }

      if (costNet[track] < 1000000) {
   dist = (long) (ideal - track);
   if (dist < 0) {
       dist *= -1;
   }
   costNet[track] += 1 * dist;
      }
  }
  else {
      costNet[track] = 1000000;
  }
     }
 }
    }
    ;
}

void
IdealTrack(unsigned long tracks, unsigned long top, unsigned long bot, unsigned long * ideal)
{
    unsigned long num;
    unsigned long den;

    num = (top * (tracks - bot)) + (bot * (top + 1));
    den = top + bot;

    if (den != 0) {
 *ideal = (unsigned long) ((unsigned long) num / (unsigned long) den);
    }
    else {
 *ideal = 1;
    }
}

