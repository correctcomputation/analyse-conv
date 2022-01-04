#include "hbt.h"
#include <stdio.h>
#include <stdlib.h>
void destroyTree(Tnode* root);
Tnode* buildFromFile(FILE* fh, int* formatScore);
int buildFromOps(FILE* fh, Tnode* root, char* outputFile);