#ifndef MANIP_H
#define MANIP_H

#include "hbt.h"
#include <stdio_checked.h>
#include <stdlib_checked.h>

_Ptr<Tnode> insertKey(_Ptr<Tnode> root, int toInsert);
_Ptr<Tnode> deleteKey(_Ptr<Tnode> root, int keyDelete);
_Ptr<Tnode> balance(_Ptr<Tnode> root, _Ptr<Tnode> previous);
_Ptr<Tnode> clkRot(_Ptr<Tnode> root);
_Ptr<Tnode> cntClkRot(_Ptr<Tnode> root);
void printTreeOutput (_Ptr<Tnode> root, _Ptr<FILE> writeFile);
void printTree (_Ptr<Tnode> root); 
_Ptr<Tnode> getPred(_Ptr<Tnode> root);

#endif
