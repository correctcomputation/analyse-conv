#include <stdio_checked.h>
#include <string_checked.h>
#include <stdlib_checked.h>
#include <time_checked.h>


size_t getSize(_Nt_array_ptr<char> filename);

_Array_ptr<long> Array_Load_From_File(_Nt_array_ptr<char> filename, size_t size) : count(size);

int Array_Save_To_File(_Nt_array_ptr<char> filename, _Array_ptr<long> array : count(size), size_t size);

void Array_Shellsort(_Array_ptr<long> array : count(size), size_t size, _Ptr<long> n_comp);


