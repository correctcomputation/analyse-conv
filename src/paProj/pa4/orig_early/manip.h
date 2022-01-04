#ifndef MANIP_H
#define MANIP_H

#include "hbt.h"
#include <stdio.h>
#include <stdlib.h>

Tnode* insertKey(Tnode* root, int toInsert);
Tnode* deleteKey(Tnode* root, int keyDelete);
Tnode* balance(Tnode* root, Tnode* previous);
Tnode* clkRot(Tnode* root);
Tnode* cntClkRot(Tnode* root);
void printTreeOutput (Tnode* root, FILE* writeFile);
void printTree (Tnode* root); 
Tnode* getPred(Tnode* root);

#endif
