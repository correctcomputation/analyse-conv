













#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "channel.h"

unsigned long * TOP;
unsigned long * BOT;
unsigned long * FIRST;
unsigned long * LAST;
unsigned long * DENSITY;
unsigned long * CROSSING;
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
    FILE *channelFP;
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
    FILE *channelFP;
    unsigned long line;
    unsigned long col;
    unsigned long bot;
    unsigned long top;
    long stat;




    TOP = (unsigned long *)malloc((channelColumns+1) * sizeof(unsigned long));




    BOT = (unsigned long *)malloc((channelColumns+1) * sizeof(unsigned long));




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




    FIRST = (unsigned long *)malloc((channelNets+1) * sizeof(unsigned long));
    LAST = (unsigned long *)malloc((channelNets+1) * sizeof(unsigned long));
    DENSITY = (unsigned long *)malloc((channelColumns+1) * sizeof(unsigned long));
    CROSSING = (unsigned long *)malloc((channelNets+1) * sizeof(unsigned long));




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









