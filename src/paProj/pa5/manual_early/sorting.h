#ifndef __PA05__
#define __PA05__

#include <stdio_checked.h>
#include <stdlib_checked.h>

void Quick_Sort(_Array_ptr<long> Array : count(Size), size_t Size);

void Merge_Sort(_Array_ptr<long> Array : count(Size), size_t Size);

size_t getArraySize(_Nt_array_ptr<char> filename);

_Array_ptr<long> Array_Load_From_File(_Nt_array_ptr<char> filename, size_t size) : count(size);

int Array_Save_To_File(_Nt_array_ptr<char> filename, _Array_ptr<long> array : count(size), size_t size);

void medianQuick(_Array_ptr<long> array : count(size), int start, int end, size_t size);
int Partition(_Array_ptr<long> array : count(size), int start, int end, size_t size);
void swap(_Ptr<long> a, _Ptr<long> b);
void compSwap(_Ptr<long> a, _Ptr<long> b);
void insertionSort(_Array_ptr<long> array : count(size), int start, int end, size_t size);


#endif
