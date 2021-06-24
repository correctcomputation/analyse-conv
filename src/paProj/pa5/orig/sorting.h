#ifndef __PA05__
#define __PA05__

void Quick_Sort(long *Array, int Size);

void Merge_Sort(long *Array, int Size);

long *Array_Load_From_File(char *filename, int *size);
int Array_Save_To_File(char *filename, long *array, int size);

void medianQuick(long* array, int start, int end);
int Partition(long* array, int start, int end);
void swap(long* a, long* b);
void compSwap(long* a, long* b);
void insertionSort(long* array, int start, int end);

#endif
