#include "hbt.h"
#include <stdio_checked.h>
#include <stdlib_checked.h>
void destroyTree(_Ptr<Tnode> root);
_Ptr<Tnode> buildFromFile(_Ptr<FILE> fh, _Ptr<int> formatScore);
int buildFromOps(_Ptr<FILE> fh, _Ptr<Tnode> root, _Nt_array_ptr<char> outputFile);
