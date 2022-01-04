
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "channel.h"
#include "assign.h"

#define printf(...)  { (printf)(__VA_ARGS__); }
#define fprintf(...)  { (fprintf)(__VA_ARGS__); }

#define min(a,b)	((a<b) ? a : b)
#define max(a,b)	((a<b) ? b : a)





#define FROM_LEFT	0x01
#define FROM_RIGHT	0x02
#define FROM_TOP	0x04
#define FROM_BOT	0x08


#define ACCESS_MAP(a, x, y)	a[(y)*channelColumns + (x)]

static char * horzPlane ;


#define HORZ(x,y)	ACCESS_MAP(horzPlane, x, y)

static char * vertPlane ;


#define VERT(x,y)	ACCESS_MAP(vertPlane, x, y)

static char * viaPlane ;


#define VIA(x,y)	ACCESS_MAP(viaPlane, x, y)

static char * mazeRoute ;






void
InitAllocMaps(void)
{

    horzPlane = malloc<char>((channelColumns+1)*(channelTracks+3));
    vertPlane = malloc<char>((channelColumns+1)*(channelTracks+3));
    viaPlane = malloc<char>((channelColumns+1)*(channelTracks+3));
    mazeRoute = malloc<char>((channelColumns+1));



    if (horzPlane==((void*)0) || vertPlane==((void*)0) ||
 viaPlane==((void*)0) || mazeRoute==((void*)0)) {
  { (fprintf)(stderr, "unable to allocate plane allocation maps\n"); };
 exit(1);
    }

}

void
FreeAllocMaps(void)
{
     { free<char>(horzPlane); }
     { free<char>(vertPlane); }
     { free<char>(viaPlane); }
     { free<char>(mazeRoute); }
}










void
DrawSegment(_Array_ptr<char> plane, unsigned long x1, unsigned long y1, unsigned long x2, unsigned long y2)
{
    unsigned long x, y;


    ((void) sizeof (((x1 == x2) || (y1 == y2)) ? 1 : 0), __extension__ ({ if ((x1 == x2) || (y1 == y2)) ; else __assert_fail ("(x1 == x2) || (y1 == y2)", "/home/matt/analyze-conversion/src/Ptrdist/yacr2/tmp-em-manual/maze.c", 94, __extension__ __PRETTY_FUNCTION__); }));


    ((void) sizeof (((x1 != x2) || (y1 != y2)) ? 1 : 0), __extension__ ({ if ((x1 != x2) || (y1 != y2)) ; else __assert_fail ("(x1 != x2) || (y1 != y2)", "/home/matt/analyze-conversion/src/Ptrdist/yacr2/tmp-em-manual/maze.c", 97, __extension__ __PRETTY_FUNCTION__); }));

    if (x1 == x2) {


 plane[(((y1<y2) ? y1 : y2))*channelColumns + (x1)] |= 0x08;


 for (y=((y1<y2) ? y1 : y2)+1; y<((y1<y2) ? y2 : y1); y++) {

     plane[(y)*channelColumns + (x1)] |= 0x04|0x08;
 }



 plane[(((y1<y2) ? y2 : y1))*channelColumns + (x1)] |= 0x04;

    }
    else {


 plane[(y1)*channelColumns + (((x1<x2) ? x1 : x2))] |= 0x02;


 for (x=((x1<x2) ? x1 : x2)+1; x<((x1<x2) ? x2 : x1); x++) {

     plane[(y1)*channelColumns + (x)] = 0x01|0x02;
 }



 plane[(y1)*channelColumns + (((x1<x2) ? x2 : x1))] |= 0x01;
    }
}





void
DrawVia(unsigned long x, unsigned long y)
{

    viaPlane[(y)*channelColumns + (x)] = 1;
}





int
HasVia(unsigned long x, unsigned long y)
{
    return(viaPlane[(y)*channelColumns + (x)]);
}








int
SegmentFree(_Array_ptr<char> plane, unsigned long x1, unsigned long y1, unsigned long x2, unsigned long y2)
{
    unsigned long x, y;
    unsigned long index;


    ((void) sizeof (((x1 == x2) || (y1 == y2)) ? 1 : 0), __extension__ ({ if ((x1 == x2) || (y1 == y2)) ; else __assert_fail ("(x1 == x2) || (y1 == y2)", "/home/matt/analyze-conversion/src/Ptrdist/yacr2/tmp-em-manual/maze.c", 167, __extension__ __PRETTY_FUNCTION__); }));

    if (x1 == x2) {
 index = ((y1<y2) ? y1 : y2)*channelColumns + x1;
 for (y=((y1<y2) ? y1 : y2); y<=((y1<y2) ? y2 : y1); y++, index += channelColumns) {
     if (plane[index])
  return 0;
 }
    }
    else {
 index = y1*channelColumns + ((x1<x2) ? x1 : x2);
 for (x=((x1<x2) ? x1 : x2); x<=((x1<x2) ? x2 : x1); x++, index++) {
     if (plane[index])
  return 0;
 }
    }
    return 1;
}






void
PrintChannel(void)
{
    unsigned long x, y;


     { (printf)("           "); };
    for (x=1; x<=channelColumns; x++)
  { (printf)(" %d ", TOP[x]/100); };
     { (printf)("\n"); };


     { (printf)("           "); };
    for (x=1; x<=channelColumns; x++)
  { (printf)(" %d ", (TOP[x] - (TOP[x]/100)*100)/10); };
     { (printf)("\n"); };


     { (printf)("           "); };
    for (x=1; x<=channelColumns; x++)
  { (printf)(" %d ", TOP[x] % 10); };
     { (printf)("\n"); };

     { (printf)("           "); };
    for (x=1; x<=channelColumns; x++)
  { (printf)("%%%c%%", vertPlane[(0)*channelColumns + (x)] ? '|' : /**/ ' '); };
     { (printf)("\n"); };

    for (y=1; y<=channelTracks; y++) {

  { (printf)("           "); };
 for (x=1; x<=channelColumns; x++) {
     if (vertPlane[(y)*channelColumns + (x)]&0x04)
   { (printf)(" | "); }
     else
   { (printf)("   "); }
 }
  { (printf)("\n"); };

  { (printf)("Track %3d: ", y); };
 for (x=1; x<=channelColumns; x++) {
     if ((horzPlane[(y)*channelColumns + (x)]&0x01) && (vertPlane[(y)*channelColumns + (x)]&0x01))
   { (printf)("="); }
     else if (horzPlane[(y)*channelColumns + (x)]&0x01)
   { (printf)("-"); }
     else if (vertPlane[(y)*channelColumns + (x)]&0x01)
   { (printf)("^"); }
     else
   { (printf)(" "); }

     if (viaPlane[(y)*channelColumns + (x)])
   { (printf)("X"); }
     else if (horzPlane[(y)*channelColumns + (x)] && vertPlane[(y)*channelColumns + (x)])
   { (printf)("+"); }
     else if (horzPlane[(y)*channelColumns + (x)])
   { (printf)("-"); }
     else if (vertPlane[(y)*channelColumns + (x)])
   { (printf)("|"); }
     else
   { (printf)(" "); }


     if ((horzPlane[(y)*channelColumns + (x)]&0x02) && (vertPlane[(y)*channelColumns + (x)]&0x02))
   { (printf)("="); }
     else if (horzPlane[(y)*channelColumns + (x)]&0x02)
   { (printf)("-"); }
     else if (vertPlane[(y)*channelColumns + (x)]&0x02)
   { (printf)("^"); }
     else
   { (printf)(" "); }
 }
  { (printf)("\n"); };

  { (printf)("           "); };
 for (x=1; x<=channelColumns; x++) {
     if (vertPlane[(y)*channelColumns + (x)]&0x08)
   { (printf)(" | "); }
     else
   { (printf)("   "); }
 }
  { (printf)("\n"); };
    }

     { (printf)("           "); };
    for (x=1; x<=channelColumns; x++)
  { (printf)("%%%c%%", vertPlane[(channelTracks+1)*channelColumns + (x)] ? '|' : /**/ ' '); };
     { (printf)("\n"); };


     { (printf)("           "); };
    for (x=1; x<=channelColumns; x++)
  { (printf)(" %d ", BOT[x]/100); };
     { (printf)("\n"); };


     { (printf)("           "); };
    for (x=1; x<=channelColumns; x++)
  { (printf)(" %d ", (BOT[x] - (BOT[x]/100)*100)/10); };
     { (printf)("\n"); };


     { (printf)("           "); };
    for (x=1; x<=channelColumns; x++)
  { (printf)(" %d ", BOT[x] % 10); };
     { (printf)("\n"); };

}









int
DrawNets(void)
{
    unsigned long i;
    int numLeft = 0;


     { memset(horzPlane, '\0',
   (int)((channelColumns+1)*(channelTracks+2))); }
     { memset(vertPlane, '\0',
   (int)((channelColumns+1)*(channelTracks+2))); }
     { memset(viaPlane, '\0',
   (int)((channelColumns+1)*(channelTracks+2))); }
     { memset(mazeRoute, '\0',
   (int)(channelColumns+1)); }


    for (i=1; i<=channelNets; i++) {
 if (FIRST[i] != LAST[i])
      { DrawSegment(_Assume_bounds_cast<_Array_ptr<char>>(horzPlane, bounds(unknown)),
   FIRST[i], netsAssign[i],
   LAST[i], netsAssign[i]); }
#ifdef VERBOSE


#endif
    }


    for (i=1; i<=channelColumns; i++) {
 if ((BOT[i] == 0) && (TOP[i] == 0)) {

 }
 else if ((BOT[i] == 0) && (TOP[i] != 0)) {

      { DrawSegment(_Assume_bounds_cast<_Array_ptr<char>>(vertPlane, bounds(unknown)),
   i, 0,
   i, netsAssign[TOP[i]]); }
     DrawVia(i, netsAssign[TOP[i]]);
 }
 else if ((TOP[i] == 0) && (BOT[i] != 0)) {

      { DrawSegment(_Assume_bounds_cast<_Array_ptr<char>>(vertPlane, bounds(unknown)),
   i, netsAssign[BOT[i]],
   i, channelTracks+1); }
     DrawVia(i, netsAssign[BOT[i]]);
 }

 else if ((TOP[i] == BOT[i]) && (FIRST[TOP[i]] == LAST[TOP[i]])) {

     ((void) sizeof (((FIRST[TOP[i]] == i) && (LAST[TOP[i]] == i)) ? 1 : 0), __extension__ ({ if ((FIRST[TOP[i]] == i) && (LAST[TOP[i]] == i)) ; else __assert_fail ("(FIRST[TOP[i]] == i) && (LAST[TOP[i]] == i)", "/home/matt/analyze-conversion/src/Ptrdist/yacr2/tmp-em-manual/maze.c", 357, __extension__ __PRETTY_FUNCTION__); }));
      { DrawSegment(_Assume_bounds_cast<_Array_ptr<char>>(vertPlane, bounds(unknown)),
   i, 0,
   i, channelTracks+1); }
 }
 else if (TOP[i] == BOT[i]) {

      { DrawSegment(_Assume_bounds_cast<_Array_ptr<char>>(vertPlane, bounds(unknown)),
   i, 0,
   i, channelTracks+1); }
     DrawVia(i, netsAssign[BOT[i]]);
 }

 else if (netsAssign[TOP[i]] < netsAssign[BOT[i]]) {

      { DrawSegment(_Assume_bounds_cast<_Array_ptr<char>>(vertPlane, bounds(unknown)),
   i, 0,
   i, netsAssign[TOP[i]]); }
     DrawVia(i, netsAssign[TOP[i]]);
      { DrawSegment(_Assume_bounds_cast<_Array_ptr<char>>(vertPlane, bounds(unknown)),
   i, netsAssign[BOT[i]],
   i, channelTracks+1); }
     DrawVia(i, netsAssign[BOT[i]]);
 }

 else {
     ((void) sizeof ((netsAssign[TOP[i]] > netsAssign[BOT[i]]) ? 1 : 0), __extension__ ({ if (netsAssign[TOP[i]] > netsAssign[BOT[i]]) ; else __assert_fail ("netsAssign[TOP[i]] > netsAssign[BOT[i]]", "/home/matt/analyze-conversion/src/Ptrdist/yacr2/tmp-em-manual/maze.c", 383, __extension__ __PRETTY_FUNCTION__); }));
     mazeRoute[i] = 1;
     numLeft++;
 }
#ifdef VERBOSE






#endif
    }
    return numLeft;
}








static void
CleanNet(unsigned long net)
{
    unsigned long i;
    unsigned long firstVia, lastVia;
    unsigned long effFIRST, effLAST;
    unsigned long track;


    for (i=FIRST[net]; i<=LAST[net]; i++) {
 if (((TOP[i] == net) || (BOT[i] == net)) && (mazeRoute[i]))
     return;
    }

    track = netsAssign[net];


    effFIRST = FIRST[net];
    while (horzPlane[(track)*channelColumns + (effFIRST)]&0x01)
 effFIRST--;

    effLAST = LAST[net];
    while (horzPlane[(track)*channelColumns + (effLAST)]&0x02)
 effLAST++;


    firstVia = 9999999;
    lastVia = 0;
    for (i=effFIRST; i<=effLAST; i++) {
 if (HasVia(i, track)) {
     if (i < firstVia)
  firstVia = i;
     if (i > lastVia)
  lastVia = i;
 }
    }
    if (effFIRST < firstVia) {

 for (i=effFIRST; i<firstVia; i++) {
     horzPlane[(track)*channelColumns + (i)] = 0;
 }

 horzPlane[(track)*channelColumns + (firstVia)] &= ~0x01;
    }
    if (lastVia < effLAST) {

 horzPlane[(track)*channelColumns + (lastVia)] &= ~0x02;

 for (i=lastVia+1; i<= effLAST; i++) {
     horzPlane[(track)*channelColumns + (i)] = 0;
 }
    }
}





static int
HasVCV(unsigned long i)
{
    return ((TOP[i] != 0) &&
     (BOT[i] != 0) &&
     (TOP[i] != BOT[i]) &&
     (netsAssign[TOP[i]] > netsAssign[BOT[i]]));
}







static int
Maze1Mech(unsigned long i,
   unsigned long s1,
   unsigned long s2,
   unsigned long b1,
   unsigned long b2,
   int bXdelta, int bYdelta)
 {
    if (SegmentFree(_Assume_bounds_cast<_Array_ptr<char>>(vertPlane, bounds(unknown)),
      i, s1,
      i, s2) &&
 SegmentFree(_Assume_bounds_cast<_Array_ptr<char>>(vertPlane, bounds(unknown)),
      i, b1,
      i, s2+bYdelta) &&
 SegmentFree(_Assume_bounds_cast<_Array_ptr<char>>(vertPlane, bounds(unknown)),
      i, s2+bYdelta,
      i+bXdelta, s2+bYdelta) &&
 SegmentFree(_Assume_bounds_cast<_Array_ptr<char>>(vertPlane, bounds(unknown)),
      i+bXdelta, s2+bYdelta,
      i+bXdelta, b2) &&
 !HasVCV(i+bXdelta)) {

 DrawSegment(_Assume_bounds_cast<_Array_ptr<char>>(vertPlane, bounds(unknown)),
      i, s1,
      i, s2);
 DrawVia(i, s2);
 DrawSegment(_Assume_bounds_cast<_Array_ptr<char>>(vertPlane, bounds(unknown)),
      i, b1,
      i, s2+bYdelta);
 DrawSegment(_Assume_bounds_cast<_Array_ptr<char>>(vertPlane, bounds(unknown)),
      i, s2+bYdelta,
      i+bXdelta, s2+bYdelta);
 DrawSegment(_Assume_bounds_cast<_Array_ptr<char>>(vertPlane, bounds(unknown)),
      i+bXdelta, s2+bYdelta,
      i+bXdelta, b2);
 DrawVia(i+bXdelta, b2);
 DrawSegment(_Assume_bounds_cast<_Array_ptr<char>>(horzPlane, bounds(unknown)),
      i+bXdelta, b2,
      i, b2);
 return 1;
    }
    return 0;
}


int
Maze1(void)
{
    int numLeft = 0;
    unsigned long p, s;
    unsigned long i;

    for (i=1; i<=channelColumns; i++) {
 if (mazeRoute[i]) {

     s = netsAssign[TOP[i]];
     p = netsAssign[BOT[i]];
     ((void) sizeof ((s > p) ? 1 : 0), __extension__ ({ if (s > p) ; else __assert_fail ("s > p", "/home/matt/analyze-conversion/src/Ptrdist/yacr2/tmp-em-manual/maze.c", 536, __extension__ __PRETTY_FUNCTION__); }));

#ifdef TODD
     if ((i > 1) && (p > 1) &&
  Maze1Mech(i,
     channelTracks+1, p,
     0, s,
     -1, -1)) {
  mazeRoute[i] = 0;
  CleanNet(TOP[i]);
  CleanNet(BOT[i]);
     }
     else if ((i < channelColumns) && (p > 1) &&
       Maze1Mech(i,
          channelTracks+1, p,
          0, s,
          1, -1)) {
  mazeRoute[i] = 0;
  CleanNet(TOP[i]);
  CleanNet(BOT[i]);
     }
#else


















#endif
#ifdef TODD
     else if ((i > 1) && (s < channelTracks) &&
       Maze1Mech(i,
          0, s,
          channelTracks+1, p,
          -1, 1)) {
  mazeRoute[i] = 0;
  CleanNet(TOP[i]);
  CleanNet(BOT[i]);
     }
     else if ((i < channelColumns) && (s < channelTracks) &&
       Maze1Mech(i,
          0, s,
          channelTracks+1, p,
          1, 1)) {
  mazeRoute[i] = 0;
  CleanNet(TOP[i]);
  CleanNet(BOT[i]);
     }
#else


















#endif
     else {

  numLeft++;
     }
#ifdef VERBOSE







#endif
 }
    }
    return numLeft;
}












int
ExtendOK(unsigned long net, _Array_ptr<char> plane : count(_x1), unsigned long _x1, unsigned long _y1, unsigned long _x2, unsigned long _y2)
{
    unsigned long x1, y1, x2, y2;


    x1 = ((_x1<_x2) ? _x1 : _x2);
    y1 = ((_y1<_y2) ? _y1 : _y2);
    x2 = ((_x1<_x2) ? _x2 : _x1);
    y2 = ((_y1<_y2) ? _y2 : _y1);

    ((void) sizeof (((y1 == y2) && (netsAssign[net] == y1)) ? 1 : 0), __extension__ ({ if ((y1 == y2) && (netsAssign[net] == y1)) ; else __assert_fail ("(y1 == y2) && (netsAssign[net] == y1)", "/home/matt/analyze-conversion/src/Ptrdist/yacr2/tmp-em-manual/maze.c", 656, __extension__ __PRETTY_FUNCTION__); }));

    if ((x1 >= FIRST[net]) && (x2 <= LAST[net]))
 return 1;
    if ((x1 < FIRST[net]) && (x2 > LAST[net])) {

  { return (SegmentFree(plane,
       x1, y1,
       FIRST[net]-1, y1) &&
  SegmentFree(plane,
       LAST[net]+1, y1,
       x2, y1)); }
    }
    else if (x1 < FIRST[net]) {

  { return SegmentFree(plane,
      x1, y1,
      FIRST[net]-1, y1); }
    }
    else if (x2 > LAST[net]) {

  { return SegmentFree(plane,
      LAST[net]+1, y1,
      x2, y1); }
    }

    abort();
    return 0;
}


static int
Maze2Mech(unsigned long bentNet,
   unsigned long i,
   unsigned long s1,
   unsigned long s2,
   unsigned long b1,
   unsigned long b2,
   unsigned long xStart,
   unsigned long xEnd,
   int bXdelta,
   unsigned long yStart,
          unsigned long yEnd,
          int bYdelta)
{
    unsigned long row, col;
    int colFree;

    xEnd += bXdelta;
    yEnd += bYdelta;

    for (row = yStart; row != yEnd; row += bYdelta) {
 colFree = 1;
 for (col = xStart;
      colFree && (col != xEnd);
      col += bXdelta)  {
     if ((colFree = SegmentFree(_Assume_bounds_cast<_Array_ptr<char>>(horzPlane, bounds(unknown)),
       i, row,
       col, row)) &&
  SegmentFree(_Assume_bounds_cast<_Array_ptr<char>>(vertPlane, bounds(unknown)),
       i, s1,
       i, s2) &&
  SegmentFree(_Assume_bounds_cast<_Array_ptr<char>>(vertPlane, bounds(unknown)),
       i, b1,
       i, row) &&
  SegmentFree(_Assume_bounds_cast<_Array_ptr<char>>(vertPlane, bounds(unknown)),
       col, row,
       col, b2-1) &&
  !HasVCV(col) &&
  ExtendOK(bentNet, _Assume_bounds_cast<_Array_ptr<char>>(horzPlane, bounds(unknown)),
    col, b2,
    i, b2)) {

  DrawSegment(_Assume_bounds_cast<_Array_ptr<char>>(vertPlane, bounds(unknown)),
       i, s1,
       i, s2);
  DrawVia(i, s2);

  DrawSegment(_Assume_bounds_cast<_Array_ptr<char>>(vertPlane, bounds(unknown)),
       i, b1,
       i, row);
  DrawVia(i, row);
  DrawSegment(_Assume_bounds_cast<_Array_ptr<char>>(horzPlane, bounds(unknown)),
       i, row,
       col, row);
  DrawVia(col, row);
  DrawSegment(_Assume_bounds_cast<_Array_ptr<char>>(vertPlane, bounds(unknown)),
       col, row,
       col, b2);
  DrawVia(col, b2);
  DrawSegment(_Assume_bounds_cast<_Array_ptr<char>>(horzPlane, bounds(unknown)),
       col, b2,
       i, b2);
  return 1;
     }
 }
    }
    return 0;
}


int
Maze2(void)
{
    int numLeft = 0;
    unsigned long p, s;
    unsigned long i;

    for (i=1; i<=channelColumns; i++) {
 if (mazeRoute[i]) {

     s = netsAssign[TOP[i]];
     p = netsAssign[BOT[i]];
     ((void) sizeof ((s > p) ? 1 : 0), __extension__ ({ if (s > p) ; else __assert_fail ("s > p", "/home/matt/analyze-conversion/src/Ptrdist/yacr2/tmp-em-manual/maze.c", 769, __extension__ __PRETTY_FUNCTION__); }));

#ifdef TODD
     if ((i > 1) && (p > 1) &&
  Maze2Mech(TOP[i], i,
     channelTracks+1, p,
     0, s,
     i-1, 1, -1,
     1, p-1, 1)) {
  mazeRoute[i] = 0;
  CleanNet(TOP[i]);
  CleanNet(BOT[i]);
     }
     else if ((i < channelColumns) && (p > 1) &&
       Maze2Mech(TOP[i], i,
          channelTracks+1, p,
          0, s,
          i+1, channelColumns, 1,
          1, p-1, 1)) {
  mazeRoute[i] = 0;
  CleanNet(TOP[i]);
  CleanNet(BOT[i]);
     }
#else




















#endif 
#ifdef TODD
     else if ((i > 1) && (s < channelTracks) &&
       Maze2Mech(BOT[i], i,
          0, s,
          channelTracks+1, p,
          i-1, 1, -1,
          s+1, channelTracks, 1)) {
  mazeRoute[i] = 0;
  CleanNet(TOP[i]);
  CleanNet(BOT[i]);
     }
     else if ((i < channelColumns) && (s < channelTracks) &&
       Maze2Mech(BOT[i], i,
          0, s,
          channelTracks+1, p,
          i+1, channelColumns, 1,
          s+1, channelTracks, 1)) {
  mazeRoute[i] = 0;
  CleanNet(TOP[i]);
  CleanNet(BOT[i]);
     }
#else




















#endif
     else {

  numLeft++;
     }
#ifdef VERBOSE







#endif
 }
    }
    return numLeft;
}


void
FindFreeHorzSeg(unsigned long startCol, unsigned long row, _Ptr<unsigned long> rowStart, _Ptr<unsigned long> rowEnd)
{
    unsigned long i;

    for (i=startCol; i >= 1; i--) {
 if (horzPlane[(row)*channelColumns + (i)])
     break;
    }
    *rowStart = i+1;

    for (i=startCol; i <= channelColumns; i++) {
 if (horzPlane[(row)*channelColumns + (i)])
     break;
    }
    *rowEnd = i-1;
}

static int
Maze3Mech(unsigned long topNet,
   unsigned long botNet,
   unsigned long i,
   unsigned long s1,
   unsigned long s2,
   unsigned long b1,
   unsigned long b2)
{
    unsigned long topRow, topCol, botRow, botCol;
    unsigned long topStart, topEnd, botStart, botEnd;
    ;

    for (topRow = b2+1; topRow < s2-1; topRow++) {
 FindFreeHorzSeg(i, topRow, &topStart, &topEnd);
 if (topEnd <= topStart)
     continue;
 for (botRow = topRow+1; botRow < s2; botRow++) {
     FindFreeHorzSeg(i, botRow, &botStart, &botEnd);
     if (botEnd <= botStart)
  continue;
     for (topCol = topStart; topCol <= topEnd; topCol++) {
  for (botCol = botStart; botCol <= botEnd; botCol++)  {
      if ((topCol != i) && (botCol != i) &&
   (topRow != botRow) && (topCol != botCol) &&
   SegmentFree(_Assume_bounds_cast<_Array_ptr<char>>(vertPlane, bounds(unknown)),
        i, s1,
        i, topRow) &&
   SegmentFree(_Assume_bounds_cast<_Array_ptr<char>>(horzPlane, bounds(unknown)),
        i, topRow,
        topCol, topRow) &&
   SegmentFree(_Assume_bounds_cast<_Array_ptr<char>>(vertPlane, bounds(unknown)),
        topCol, topRow,
        topCol, s2+1) &&
   !HasVCV(topCol) &&
   ExtendOK(topNet, _Assume_bounds_cast<_Array_ptr<char>>(horzPlane, bounds(unknown)),
     topCol, s2,
     i, s2) &&
   SegmentFree(_Assume_bounds_cast<_Array_ptr<char>>(vertPlane, bounds(unknown)),
        i, b1,
        i, botRow) &&
   SegmentFree(_Assume_bounds_cast<_Array_ptr<char>>(horzPlane, bounds(unknown)),
        i, botRow,
        botCol, botRow) &&
   SegmentFree(_Assume_bounds_cast<_Array_ptr<char>>(vertPlane, bounds(unknown)),
        botCol, botRow,
        botCol, b2-1) &&
   !HasVCV(botCol) &&
   ExtendOK(botNet, _Assume_bounds_cast<_Array_ptr<char>>(horzPlane, bounds(unknown)),
     botCol, b2,
     i, b2)) {

   DrawSegment(_Assume_bounds_cast<_Array_ptr<char>>(vertPlane, bounds(unknown)),
        i, s1,
        i, topRow);
   DrawVia(i, topRow);
   DrawSegment(_Assume_bounds_cast<_Array_ptr<char>>(horzPlane, bounds(unknown)),
        i, topRow,
        topCol, topRow);
   DrawVia(topCol, topRow);
   DrawSegment(_Assume_bounds_cast<_Array_ptr<char>>(vertPlane, bounds(unknown)),
        topCol, topRow,
        topCol, s2);
   DrawVia(topCol, s2);
   DrawSegment(_Assume_bounds_cast<_Array_ptr<char>>(horzPlane, bounds(unknown)),
        topCol, s2,
        i, s2);

   DrawSegment(_Assume_bounds_cast<_Array_ptr<char>>(vertPlane, bounds(unknown)),
        i, b1,
        i, botRow);
   DrawVia(i, botRow);
   DrawSegment(_Assume_bounds_cast<_Array_ptr<char>>(horzPlane, bounds(unknown)),
        i, botRow,
        botCol, botRow);
   DrawVia(botCol, botRow);
   DrawSegment(_Assume_bounds_cast<_Array_ptr<char>>(vertPlane, bounds(unknown)),
        botCol, botRow,
        botCol, b2);
   DrawVia(botCol, b2);
   DrawSegment(_Assume_bounds_cast<_Array_ptr<char>>(horzPlane, bounds(unknown)),
        botCol, b2,
        i, b2);
       ;
   return 1;
      }
  }
     }
 }
    }
    ;
    return 0;
}


int Maze3(void)
{
    int numLeft = 0;
    unsigned long p, s;
    unsigned long i;

    for (i=1; i<=channelColumns; i++) {
 if (mazeRoute[i]) {

     s = netsAssign[TOP[i]];
     p = netsAssign[BOT[i]];
     ((void) sizeof ((s > p) ? 1 : 0), __extension__ ({ if (s > p) ; else __assert_fail ("s > p", "/home/matt/analyze-conversion/src/Ptrdist/yacr2/tmp-em-manual/maze.c", 1000, __extension__ __PRETTY_FUNCTION__); }));

     if (Maze3Mech(TOP[i], BOT[i], i,
      0, s,
      channelTracks+1, p)) {
  mazeRoute[i] = 0;
  CleanNet(TOP[i]);
  CleanNet(BOT[i]);
     }
     else {

  numLeft++;
     }
#ifdef VERBOSE







#endif
 }
    }
    return numLeft;
}
