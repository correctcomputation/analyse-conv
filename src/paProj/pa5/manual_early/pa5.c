#include "sorting.h"
#include <stdio_checked.h>
#include <stdlib_checked.h>
#include <string_checked.h>
#include <time_checked.h>

void printArray(_Array_ptr<long> array : count(size), int size);


int main(int argc, _Nt_array_ptr<char> argv [])
{

    if(argc != 4)
    {
				_Unchecked {
        	fprintf(stderr, "incorrect inputs\n");
        }
				return EXIT_FAILURE;
    }
    
    if(!(strcmp(argv[1], "-q")))
    {
        size_t size = 0;
				size = getArraySize(argv[2]);
        _Array_ptr<long> array : count(size) = Array_Load_From_File(argv[2], size);
        clock_t start = clock();
        Quick_Sort(array, size);
        clock_t end = clock(); 
        double time = (double)(end - start) / CLOCKS_PER_SEC;
        _Unchecked {
					fprintf(stderr, "%lf\n", time);
				}
        int written = Array_Save_To_File(argv[3], array, size);
        if(written != size){
            fprintf(stderr, "something went wrong saving\n");
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

void printArray(_Array_ptr<long> array : count(size), int size)
{
    int i;
    for(i = 0; i < size; i++)
			_Unchecked{
        fprintf(stderr, "%ld\n", array[i]);
    	}
		_Unchecked {
			fprintf(stderr, "\n");
    }
		return;
}
