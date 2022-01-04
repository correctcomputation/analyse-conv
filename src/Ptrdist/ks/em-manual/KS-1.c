









#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "KS.h"

#pragma CHECKED_SCOPE ON

NetPtr modules _Checked[1024] = {((void *)0)};
unsigned long numModules;

ModulePtr nets _Checked [1024] = {((void *)0)};
unsigned long numNets;

ModuleList groupA, groupB;
ModuleList swapToA, swapToB;
float GP _Checked [1024];

Groups moduleToGroup _Checked [1024];
float D _Checked [1024];
float cost _Checked [1024];



void
ReadNetList(_Nt_array_ptr<char> fname)
{
    _Ptr<FILE> inFile = 0;
    char line _Nt_checked[1024 + 1] = { 0 };
    unsigned long net, dest;
    ModulePtr node = 0;
    ModulePtr prev = 0;
    ModulePtr head = 0;

    { inFile = fopen(fname, "r"); if (!(inFile != ((void*)0))) { _Unchecked { (fprintf)(stderr, "(%s:%s():%d): ", "/home/matt/analyze-conversion/src/Ptrdist/ks/tmp-em-manual/KS-1.c", "ReadData", 49); }; _Unchecked { (fprintf)(stderr, "unable to open input file [%s]", fname, 0, 0); }; _Unchecked { (fprintf)(stderr, "\n"); }; exit(1); } };




    _Unchecked { { fgets(line, 1024, inFile); if (!(sscanf((const char*)line, "%lu %lu", &numNets, &numModules) == 2)) { _Unchecked { (fprintf)(stderr, "(%s:%s():%d): ", "/home/matt/analyze-conversion/src/Ptrdist/ks/tmp-em-manual/KS-1.c", "ReadData", 54); }; _Unchecked { (fprintf)(stderr, "unable to parse header in file [%s]", fname, 0, 0); }; _Unchecked { (fprintf)(stderr, "\n"); }; exit(1); } }; }




    for (net = 0; net < numNets; net++) {
 fgets(line, 1024, inFile);


 dest = atol(strtok(line, " \t\n"))-1;


 { head = prev = calloc<Module>(1, sizeof(Module)); if (!(prev != ((void*)0))) { _Unchecked { (fprintf)(stderr, "(%s:%s():%d): ", "/home/matt/analyze-conversion/src/Ptrdist/ks/tmp-em-manual/KS-1.c", "ReadData", 66); }; _Unchecked { (fprintf)(stderr, "unable to allocate a module list node", 0, 0, 0); }; _Unchecked { (fprintf)(stderr, "\n"); }; exit(1); } };



 (*prev).module = atol(strtok(((void*)0), " \t\n"))-1;
 (*prev).next = ((void*)0);
    _Nt_array_ptr<char> tok = ((void*)0);
 while ((tok = strtok(((void*)0), " \t\n")) != ((void*)0)) {
     { node = calloc<Module>(1, sizeof(Module)); if (!(node != ((void*)0))) { _Unchecked { (fprintf)(stderr, "(%s:%s():%d): ", "/home/matt/analyze-conversion/src/Ptrdist/ks/tmp-em-manual/KS-1.c", "ReadData", 74); }; _Unchecked { (fprintf)(stderr, "unable to allocate a module list node", 0, 0, 0); }; _Unchecked { (fprintf)(stderr, "\n"); }; exit(1); } };



     (*node).module = atol(tok)-1;
     (*node).next = ((void*)0);
     (*prev).next = node;
     prev = node;
 }
 nets[dest] = head;
    }
}


void
NetsToModules(void)
{
    unsigned long net, mod;
    ModulePtr modNode = 0;
    NetPtr netNode = 0;

    for (mod = 0; mod<numModules; mod++)
 modules[mod] = ((void*)0);

    for (net=0; net<numNets; net++) {
 for (modNode = nets[net]; modNode != ((void*)0); modNode = (*modNode).next) {
     { netNode = calloc<Net>(1, sizeof(Net)); if (!(netNode != ((void*)0))) { _Unchecked { (fprintf)(stderr, "(%s:%s():%d): ", "/home/matt/analyze-conversion/src/Ptrdist/ks/tmp-em-manual/KS-1.c", "NetsToModules", 100); }; _Unchecked { (fprintf)(stderr, "unable to allocate net list node", 0, 0, 0); }; _Unchecked { (fprintf)(stderr, "\n"); }; exit(1); } };



     (*netNode).net = net;
     (*netNode).next = modules[(*modNode).module];
     modules[(*modNode).module] = netNode;
 }
    }
}



void
ComputeNetCosts(void)
{
#ifdef WEIGHTED


#endif 
    unsigned long i;

    for (i=0; i<numNets; i++) {
#ifndef WEIGHTED
 cost[i] = 1.0;
#else





#endif 
    }
}


void
InitLists(void)
{
    unsigned long p;
    ModuleRecPtr mr = 0;

    groupA.head = groupA.tail = ((void*)0);
    groupB.head = groupB.tail = ((void*)0);


    for (p = 0; p<numModules/2; p++) {


 { mr = calloc<ModuleRec>(1, sizeof(ModuleRec)); if (!(mr != ((void*)0))) { _Unchecked { (fprintf)(stderr, "(%s:%s():%d): ", "/home/matt/analyze-conversion/src/Ptrdist/ks/tmp-em-manual/KS-1.c", "main", 149); }; _Unchecked { (fprintf)(stderr, "unable to allocate ModuleRec", 0, 0, 0); }; _Unchecked { (fprintf)(stderr, "\n"); }; exit(1); } };



 (*mr).module = p;
 if (groupA.head == ((void*)0)) {

     groupA.head = groupA.tail = mr;
     (*mr).next = ((void*)0);
 }
 else {

     (*mr).next = ((void*)0);
     (*groupA.tail).next = mr;
     groupA.tail = mr;
 }
 moduleToGroup[p] = GroupA;


 { mr = calloc<ModuleRec>(1, sizeof(ModuleRec));; if (!(mr != ((void*)0))) { _Unchecked { (fprintf)(stderr, "(%s:%s():%d): ", "/home/matt/analyze-conversion/src/Ptrdist/ks/tmp-em-manual/KS-1.c", "main", 168); }; _Unchecked { (fprintf)(stderr, "unable to allocate ModuleRec", 0, 0, 0); }; _Unchecked { (fprintf)(stderr, "\n"); }; exit(1); } };



 (*mr).module = (numModules/2) + p;
 if (groupB.head == ((void*)0)) {

     groupB.head = groupB.tail = mr;
     (*mr).next = ((void*)0);
 }
 else {

     (*mr).next = ((void*)0);
     (*groupB.tail).next = mr;
     groupB.tail = mr;
 }
 moduleToGroup[(numModules/2) + p] = GroupB;
    }


    swapToA.head = swapToA.tail = ((void*)0);
    swapToB.head = swapToB.tail = ((void*)0);
}



void
ComputeDs(ModuleListPtr group, Groups myGroup, Groups mySwap)
{
#ifdef KS_MODE










































#else 

    float I, E;

    NetPtr netNode = 0;
    ModulePtr modNode = 0;
    ModuleRecPtr groupNode = 0;


    for (groupNode = (*group).head;
  groupNode != ((void*)0);
  groupNode = (*groupNode).next) {

 ((void) sizeof ((moduleToGroup[(*groupNode).module] == myGroup) ? 1 : 0), __extension__ ({ if (moduleToGroup[(*groupNode).module] == myGroup) ; else __assert_fail ("moduleToGroup[(*groupNode).module] == myGroup", "/home/matt/analyze-conversion/src/Ptrdist/ks/tmp-em-manual/KS-1.c", 250, __extension__ __PRETTY_FUNCTION__); }));


 I = E = 0.0;


 for (netNode = modules[(*groupNode).module];
      netNode != ((void*)0);
      netNode = (*netNode).next) {


     for (modNode = nets[(*netNode).net];
   modNode != ((void*)0);
   modNode = (*modNode).next) {


  if (((*modNode).module != (*groupNode).module) &&
      (moduleToGroup[(*modNode).module] < SwappedToA)) {
      if (moduleToGroup[(*modNode).module] == myGroup)
   I = I + cost[(*netNode).net];
      else
   E = E + cost[(*netNode).net];
  }
     }
 }
 D[(*groupNode).module] = E - I;
    }

#endif 

}
