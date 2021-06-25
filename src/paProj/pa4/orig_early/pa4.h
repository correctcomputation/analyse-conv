#ifndef __PA4H__
#define __PA4H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int evaluate(char* filename, Tnode* root);
void getBalance(Tnode* root, int* balanceScore);
void getBalanceNS(Tnode* root);
void updateBals(Tnode* root);
int getHeight(Tnode* root);
void bstEval(Tnode* root, int* bstScore);

#endif
