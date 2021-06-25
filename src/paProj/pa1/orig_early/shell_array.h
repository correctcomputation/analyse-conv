#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

size_t getSize(char* filename);

long *Array_Load_From_File(char *filename, size_t size);

int Array_Save_To_File(char *filename, long *array, size_t size);

void Array_Shellsort(long *array, size_t size, long *n_comp);



