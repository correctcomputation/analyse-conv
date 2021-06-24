#ifndef __PA4H__
#define __PA4H__

#include <stdio_checked.h>
#include <stdlib_checked.h>
#include <string_checked.h>

int evaluate(_Nt_array_ptr<char> filename, _Ptr<Tnode> root);
void getBalance(_Ptr<Tnode> root, _Ptr<int> balanceScore);
void getBalanceNS(_Ptr<Tnode> root);
void updateBals(_Ptr<Tnode> root);
int getHeight(_Ptr<Tnode> root);
void bstEval(_Ptr<Tnode> root, _Ptr<int> bstScore);

#endif
