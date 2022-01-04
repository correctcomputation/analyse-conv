













#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "channel.h"

_Array_ptr<unsigned long> TOP : count(channelColumns) = ((void *)0);
_Array_ptr<unsigned long> BOT : count(channelColumns) = ((void *)0);
_Array_ptr<unsigned long> FIRST = ((void *)0);
_Array_ptr<unsigned long> LAST = ((void *)0);
_Array_ptr<unsigned long> DENSITY = ((void *)0);
_Array_ptr<unsigned long> CROSSING = ((void *)0);
unsigned long channelNets;
unsigned long channelColumns;
unsigned long channelTracks;
unsigned long channelTracksCopy;
unsigned long channelDensity;
unsigned long channelDensityColumn;
char * channelFile;








void
BuildChannel(void)
{




    DimensionChannel();





    DescribeChannel();






    DensityChannel();
}

void
DimensionChannel(void)
{
    _Ptr<FILE> channelFP = ((void *)0);
    unsigned long line;
    unsigned long dim;
    unsigned long net;
    unsigned long col;
    unsigned long bot;
    unsigned long top;
    long stat;




    channelFP = fopen(channelFile, "r");
    if (channelFP == ((void*)0)) {



 printf("Error:\n");
 printf("\tChannel file cannot be opened.\n");
 exit(1);
    }









    line = 0;
    dim = 0;
    net = 0;
    do {
 line++;
 unsigned int c1, b1, t1;
 stat = fscanf(channelFP, "%u%u%u", &c1, &b1, &t1);
 col = c1; bot = b1; top = t1;
 if (stat != (-1)) {
     if (stat == 3) {



  if (col > dim) {
      dim = col;
  }




  if (bot > net) {
      net = bot;
  }
  if (top > net) {
      net = top;
  }
     }
     else {



  printf("Error:\n");
  printf("\tChannel file description invalid at line %d.\n", line);
  printf("\tIncorrect number of specifiers.\n");
  exit(1);
     }
 }
    } while (stat != (-1));




    if (fclose(channelFP) == (-1)) {



 printf("Error:\n");
 printf("\tChannel file cannot be closed.\n");
 exit(1);
    }




    if (dim == 0) {



 printf("Error:\n");
 printf("\tChannel description invalid.\n");
 printf("\tChannel has null dimension.\n");
 exit(1);
    }




    channelColumns = dim;
    channelNets = net;
}

void
DescribeChannel(void)
{
    _Ptr<FILE> channelFP = ((void *)0);
    unsigned long line;
    unsigned long col;
    unsigned long bot;
    unsigned long top;
    long stat;




    TOP = (_Array_ptr<unsigned long>)malloc<unsigned long>((channelColumns+1) * sizeof(unsigned long));




    BOT = (_Array_ptr<unsigned long>)malloc<unsigned long>((channelColumns+1) * sizeof(unsigned long));




    for (col = 0; col <= channelColumns; col++) {
 TOP[col] = 0;
 BOT[col] = 0;
    }




    channelFP = fopen(channelFile, "r");
    if (channelFP == ((void*)0)) {



 printf("Error:\n");
 printf("\tChannel file cannot be opened.\n");
 exit(1);
    }









    line = 0;
    do {
 line++;
 unsigned int c1, b1, t1;
 stat = fscanf(channelFP, "%u%u%u", &c1, &b1, &t1);
 col = c1; bot = b1; top = t1;
 if (stat != (-1)) {
     if (stat == 3) {



  if (col > channelColumns) {



      printf("Error:\n");
      printf("\tChannel file description invalid at line %d.\n", line);
      printf("\tColumn number out of range.\n");
      exit(1);
  }
  else {



      BOT[col] = bot;
      TOP[col] = top;
  }
     }
     else {



  printf("Error:\n");
  printf("\tChannel file description invalid at line %d.\n", line);
  printf("\tIncorrect number of specifiers.\n");
  exit(1);
     }
 }
    } while (stat != (-1));




    if (fclose(channelFP) == (-1)) {



 printf("Error:\n");
 printf("\tChannel file cannot be closed.\n");
 exit(1);
    }
}

void
DensityChannel(void)
{
    unsigned long init;
    unsigned long which;
    unsigned long col;
    unsigned long bound;
    unsigned long boundColumn;




    FIRST = (_Array_ptr<unsigned long>)malloc<unsigned long>((channelNets+1) * sizeof(unsigned long));
    LAST = (_Array_ptr<unsigned long>)malloc<unsigned long>((channelNets+1) * sizeof(unsigned long));
    DENSITY = (_Array_ptr<unsigned long>)malloc<unsigned long>((channelColumns+1) * sizeof(unsigned long));
    CROSSING = (_Array_ptr<unsigned long>)malloc<unsigned long>((channelNets+1) * sizeof(unsigned long));




    for (init = 0; init <= channelNets; init++) {
 FIRST[init] = 0;
 LAST[init] = 0;
 CROSSING[init] = 0;
    }
    for (init = 0; init <= channelColumns; init++) {
 DENSITY[init] = 0;
    }




    for (which = 1; which <= channelNets; which++) {




 for (col = 1; col <= channelColumns; col++) {
     if ((BOT[col] == which) || (TOP[col] == which)) {
  FIRST[which] = col;
  break;
     }
 }





 for (col = channelColumns; col >= 1; col--) {
     if ((BOT[col] == which) || (TOP[col] == which)) {
  LAST[which] = col;
  break;
     }
 }





 for (col = FIRST[which]; col <= LAST[which]; col++) {
     DENSITY[col]++;
 }
    }




#ifdef SCOTT







#else
    bound = 0;
    for (col = channelColumns; col >= 1; col--) {
 if (DENSITY[col] > bound) {
     bound = DENSITY[col];
     boundColumn = col;
 }
    }
#endif




    channelTracks = bound;
    channelDensity = bound;
    channelDensityColumn = boundColumn;
}









