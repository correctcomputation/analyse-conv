









#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "KS.h"

#pragma CHECKED_SCOPE ON


float
CAiBj(ModuleRecPtr mrA, ModuleRecPtr mrB)
{
    NetPtr netNode = 0;
    ModulePtr modNode = 0;
    float gain = 0.0;
    float netCost;
    unsigned long module = (*mrB).module;



    for (netNode = modules[(*mrA).module];
  netNode != ((void*)0);
  netNode = (*netNode).next) {
 netCost = cost[(*netNode).net];
 for (modNode = nets[(*netNode).net];
      modNode != ((void*)0);
      modNode = (*modNode).next) {
     if ((*modNode).module == module) {
  gain = gain + netCost;
     }
 }
    }
    return gain;
}


void
SwapNode(ModuleRecPtr maxPrev, ModuleRecPtr max, ModuleListPtr group, ModuleListPtr swapTo)
{
    if (maxPrev == ((void*)0)) {
 if ((*group).head == (*group).tail) {
     (*group).head = ((void*)0);
     (*group).tail = ((void*)0);
     (*max).next = ((void*)0);
 }
 else {
     (*group).head = (*max).next;
     (*max).next = ((void*)0);
 }
    }
    else {
 if ((*group).tail == max)
     (*group).tail = maxPrev;
 (*maxPrev).next = (*max).next;
 (*max).next = ((void*)0);
    }


    if ((*swapTo).tail == ((void*)0)) {
#if 0

#endif
 (*swapTo).tail = max;
 (*swapTo).head = max;
    }
    else {
 (*(*swapTo).tail).next = max;
 (*swapTo).tail = max;
    }
    (*max).next = ((void*)0);
}


void
UpdateDs(ModuleRecPtr max, Groups group)
{
    NetPtr net = 0;
    ModulePtr mod = 0;


    for (net = modules[(*max).module]; net != ((void*)0); net = (*net).next) {


 for (mod = nets[(*net).net]; mod != ((void*)0); mod = (*mod).next) {

     if (moduleToGroup[(*mod).module] < SwappedToA) {
  if (moduleToGroup[(*mod).module] == group)
      D[(*mod).module] = D[(*mod).module] + cost[(*net).net];
  else
      D[(*mod).module] = D[(*mod).module] - cost[(*net).net];
     }
 }
    }
}


float
FindMaxGpAndSwap(void)
{
  ModuleRecPtr mrA = 0;
  ModuleRecPtr mrPrevA = 0;
  ModuleRecPtr mrB = 0;
  ModuleRecPtr mrPrevB = 0;
  ModuleRecPtr maxA = 0;
  ModuleRecPtr maxPrevA = 0;
  ModuleRecPtr maxB = 0;
  ModuleRecPtr maxPrevB = 0;
    float gp, gpMax;

    gpMax = -9999999;
    maxA = maxPrevA = maxB = maxPrevB = ((void*)0);
    for (mrA = groupA.head, mrPrevA = ((void*)0);
  mrA != ((void*)0);
  mrPrevA = mrA, mrA = (*mrA).next) {

 for (mrB = groupB.head, mrPrevB = ((void*)0);
      mrB != ((void*)0);
      mrPrevB = mrB, mrB = (*mrB).next) {

#ifdef KS_MODE

#else 
     gp = D[(*mrA).module] + D[(*mrB).module] - 2*CAiBj(mrA, mrB);
#endif 
     if (gp > gpMax) {
  gpMax = gp;
  maxA = mrA; maxPrevA = mrPrevA;
  maxB = mrB; maxPrevB = mrPrevB;
     }
 }
    }


    ((void) sizeof ((maxA != ((void*)0)) ? 1 : 0), __extension__ ({ if (maxA != ((void*)0)) ; else __assert_fail ("maxA != NULL", "/home/matt/analyze-conversion-1.wt/src/Ptrdist/ks/manual-em-tmp/KS-2.c", 145, __extension__ __PRETTY_FUNCTION__); }));
    _Unchecked { SwapNode(maxPrevA, maxA, &(groupA), &(swapToB)); }
    ((void) sizeof ((maxB != ((void*)0)) ? 1 : 0), __extension__ ({ if (maxB != ((void*)0)) ; else __assert_fail ("maxB != NULL", "/home/matt/analyze-conversion-1.wt/src/Ptrdist/ks/manual-em-tmp/KS-2.c", 147, __extension__ __PRETTY_FUNCTION__); }));
    _Unchecked { SwapNode(maxPrevB, maxB, &(groupB), &(swapToA)); }



    ((void) sizeof ((moduleToGroup[(*maxA).module] == GroupA) ? 1 : 0), __extension__ ({ if (moduleToGroup[(*maxA).module] == GroupA) ; else __assert_fail ("moduleToGroup[(*maxA).module] == GroupA", "/home/matt/analyze-conversion-1.wt/src/Ptrdist/ks/manual-em-tmp/KS-2.c", 152, __extension__ __PRETTY_FUNCTION__); }));
    moduleToGroup[(*maxA).module] = SwappedToB;

    ((void) sizeof ((moduleToGroup[(*maxB).module] == GroupB) ? 1 : 0), __extension__ ({ if (moduleToGroup[(*maxB).module] == GroupB) ; else __assert_fail ("moduleToGroup[(*maxB).module] == GroupB", "/home/matt/analyze-conversion-1.wt/src/Ptrdist/ks/manual-em-tmp/KS-2.c", 155, __extension__ __PRETTY_FUNCTION__); }));
    moduleToGroup[(*maxB).module] = SwappedToA;

#ifndef KS_MODE

    UpdateDs(maxA, GroupA);
    UpdateDs(maxB, GroupB);
#endif 

    return gpMax;
}


float
FindGMax(_Ptr<unsigned long> iMax)
{
    int i;
    float gMax;

    gMax = -9999999;
    *iMax = 0xffffffff;
    for (i=0; i<numModules/2; i++) {
 if (GP[i] > gMax) {
     gMax = GP[i];
     *iMax = i;
 }
    }
    return gMax;
}


void
SwapSubsetAndReset(unsigned long iMax)
{
    unsigned long i;
    ModuleRecPtr mrPrevA = 0;
    ModuleRecPtr mrA = 0;
    ModuleRecPtr mrPrevB = 0;
    ModuleRecPtr mrB = 0;


    for (mrPrevA = ((void*)0), mrA = swapToA.head,
  mrPrevB = ((void*)0), mrB = swapToB.head, i=0;
  i <= iMax;
  mrPrevA = mrA, mrA = (*mrA).next,
  mrPrevB = mrB, mrB = (*mrB).next,
  i++);


    ((void) sizeof ((mrPrevA != ((void*)0) && mrPrevB != ((void*)0)) ? 1 : 0), __extension__ ({ if (mrPrevA != ((void*)0) && mrPrevB != ((void*)0)) ; else __assert_fail ("mrPrevA != NULL && mrPrevB != NULL", "/home/matt/analyze-conversion-1.wt/src/Ptrdist/ks/manual-em-tmp/KS-2.c", 204, __extension__ __PRETTY_FUNCTION__); }));

    if (mrA == ((void*)0)) {

 groupA = swapToA;
 groupB = swapToB;
    }
    else {

 (*mrPrevA).next = mrB;
 groupA.head = swapToA.head;
 groupA.tail = swapToB.tail;

 (*mrPrevB).next = mrA;
 groupB.head = swapToB.head;
 groupB.tail = swapToA.tail;
    }


    for (mrA = groupA.head; mrA != ((void*)0); mrA = (*mrA).next)
 moduleToGroup[(*mrA).module] = GroupA;
    for (mrB = groupB.head; mrB != ((void*)0); mrB = (*mrB).next)
 moduleToGroup[(*mrB).module] = GroupB;


    swapToA.head = swapToA.tail = ((void*)0);
    swapToB.head = swapToB.tail = ((void*)0);
}


struct _netstats {
    unsigned long total;
    unsigned long edgesCut;
    unsigned long netsCut;
};
struct _netstats netStats _Checked [256];
long maxStat;


void
PrintResults(int verbose)
{
    ModuleRecPtr mr = 0;
    NetPtr nn = 0;
    ModulePtr mn = 0;
    unsigned long cuts;
    Groups grp;
    int i, netSz;

    _Unchecked { (fprintf)(stdout, "----------------------------------------------\n"); };

    maxStat = -1;
    for (i=0; i<256; i++)
 netStats[i].total = netStats[i].edgesCut = netStats[i].netsCut = 0;


    if (verbose) {
 _Unchecked { (fprintf)(stdout, "Group A:  \n"); };
 for (mr = groupA.head; mr != ((void*)0); mr = (*mr).next)
     _Unchecked { (fprintf)(stdout, "%3lu ", (*mr).module+1); };
 _Unchecked { (fprintf)(stdout, "\n"); };

 _Unchecked { (fprintf)(stdout, "Group B:  \n"); };
 for (mr = groupB.head; mr != ((void*)0); mr = (*mr).next)
     _Unchecked { (fprintf)(stdout, "%3lu ", (*mr).module+1); };
 _Unchecked { (fprintf)(stdout, "\n"); };
    }


    cuts = 0;
    for (mr = groupA.head; mr != ((void*)0); mr = (*mr).next) {

 ((void) sizeof ((moduleToGroup[(*mr).module] == GroupA) ? 1 : 0), __extension__ ({ if (moduleToGroup[(*mr).module] == GroupA) ; else __assert_fail ("moduleToGroup[(*mr).module] == GroupA", "/home/matt/analyze-conversion-1.wt/src/Ptrdist/ks/manual-em-tmp/KS-2.c", 276, __extension__ __PRETTY_FUNCTION__); }));


 for (nn = modules[(*mr).module]; nn != ((void*)0); nn = (*nn).next) {

     netSz = 0;
     for (mn = nets[(*nn).net]; mn != ((void*)0); mn = (*mn).next)
  netSz++;
     ((void) sizeof ((netSz >= 2) ? 1 : 0), __extension__ ({ if (netSz >= 2) ; else __assert_fail ("netSz >= 2", "/home/matt/analyze-conversion-1.wt/src/Ptrdist/ks/manual-em-tmp/KS-2.c", 284, __extension__ __PRETTY_FUNCTION__); }));


     for (mn = nets[(*nn).net]; mn != ((void*)0); mn = (*mn).next) {


  if (moduleToGroup[(*mr).module] != moduleToGroup[(*mn).module]) {
      if (verbose)
   _Unchecked { (fprintf)(stdout, "Conn %3lu - %3lu cut.\n", (*mr).module+1, (*mn).module+1); };

      netStats[netSz].edgesCut++;
      cuts++;
  }
     }
 }
    }
    _Unchecked { (fprintf)(stdout, "Total edge cuts = %lu\n", cuts); };


    cuts = 0;
    for (i=0; i<numNets; i++) {

 netSz = 0;
 for (mn = nets[i]; mn != ((void*)0); mn = (*mn).next)
     netSz++;
 ((void) sizeof ((netSz >= 2) ? 1 : 0), __extension__ ({ if (netSz >= 2) ; else __assert_fail ("netSz >= 2", "/home/matt/analyze-conversion-1.wt/src/Ptrdist/ks/manual-em-tmp/KS-2.c", 309, __extension__ __PRETTY_FUNCTION__); }));
 netStats[netSz].total++;
 if (netSz > maxStat)
     maxStat = netSz;

 for (grp=moduleToGroup[(*(nets[i])).module],mn = (*(nets[i])).next;
      mn != ((void*)0);
      mn = (*mn).next) {


     if (grp != moduleToGroup[(*mn).module]) {
  if (verbose)
      _Unchecked { (fprintf)(stdout, "Net %3lu cut.\n", i+1); };
  cuts++;
  netStats[netSz].netsCut++;
  break;
     }
 }
    }
    _Unchecked { (fprintf)(stdout, "Total net cuts  = %lu\n", cuts); };

    for (i=2; i<=maxStat; i++)
 _Unchecked { (fprintf)(stdout, "sz:%5lu     total:%5lu     edgesCut:%5lu     netsCuts:%5lu\n", i, netStats[i].total, netStats[i].edgesCut, netStats[i].netsCut); };



}

int
main(int argc, _Array_ptr<_Nt_array_ptr<char>> argv : count(argc))
{
    unsigned long p, iMax;
    float gMax, lastGMax;
    ModuleRecPtr mr = 0;
    ;


    if (argc != 2) {
 _Unchecked { (fprintf)(stderr, "Usage: KL <input_file>\n"); };
        ;
 exit(1);
    }


 ReadNetList(argv[1]);
      NetsToModules();
      ComputeNetCosts();

    ((void) sizeof (((numModules % 2) == 0) ? 1 : 0), __extension__ ({ if ((numModules % 2) == 0) ; else __assert_fail ("(numModules % 2) == 0", "/home/matt/analyze-conversion-1.wt/src/Ptrdist/ks/manual-em-tmp/KS-2.c", 357, __extension__ __PRETTY_FUNCTION__); }));


    InitLists();
    lastGMax = 0;


    do {

#ifndef KS_MODE

 _Unchecked { ComputeDs(&(groupA), GroupA, SwappedToA); }
 _Unchecked { ComputeDs(&(groupB), GroupB, SwappedToB); }
#endif 


 for (p = 0; p<numModules/2; p++) {

#ifdef KS_MODE



#endif 


     GP[p] = FindMaxGpAndSwap();

 }

 ((void) sizeof ((groupA.head == ((void*)0) && groupA.tail == ((void*)0)) ? 1 : 0), __extension__ ({ if (groupA.head == ((void*)0) && groupA.tail == ((void*)0)) ; else __assert_fail ("groupA.head == NULL && groupA.tail == NULL", "/home/matt/analyze-conversion-1.wt/src/Ptrdist/ks/manual-em-tmp/KS-2.c", 386, __extension__ __PRETTY_FUNCTION__); }));
 ((void) sizeof ((groupB.head == ((void*)0) && groupB.tail == ((void*)0)) ? 1 : 0), __extension__ ({ if (groupB.head == ((void*)0) && groupB.tail == ((void*)0)) ; else __assert_fail ("groupB.head == NULL && groupB.tail == NULL", "/home/matt/analyze-conversion-1.wt/src/Ptrdist/ks/manual-em-tmp/KS-2.c", 387, __extension__ __PRETTY_FUNCTION__); }));

 gMax = FindGMax(&iMax);


 if (lastGMax == gMax)
     _Unchecked { (fprintf)(stdout, "No progress: gMax = %f\n", gMax); };
 lastGMax = gMax;
 _Unchecked { (fprintf)(stdout, "gMax = %f, iMax = %lu\n", gMax, iMax); };

 if (gMax > 0.0)
     SwapSubsetAndReset(iMax);
 PrintResults(0);
    } while (gMax > 0.0);


    groupA = swapToB;
    for (mr = groupA.head; mr != ((void*)0); mr = (*mr).next)
 moduleToGroup[(*mr).module] = GroupA;
    groupB = swapToA;
    for (mr = groupB.head; mr != ((void*)0); mr = (*mr).next)
 moduleToGroup[(*mr).module] = GroupB;

    ;


    PrintResults(1);
#ifdef PLUS_STATS


#endif 
    exit(0);
    return 0;
}
