#include "sorting.h"

#define M 9

#pragma CHECKED_SCOPE on

size_t getArraySize(_Nt_array_ptr<char> filename)
{
	int size = 0;
	_Ptr<FILE> fh = fopen(filename, "r");

	if (fh == NULL)
	{
		_Unchecked {
			fprintf(stderr, "failed to open file properly\n");
		}
		size = 0;
		return size;
	}

	fseek(fh, 0, SEEK_END);
	size = ftell(fh) / sizeof(long);
	fclose(fh);
	return size;
}


_Array_ptr<long> Array_Load_From_File(_Nt_array_ptr<char> filename, size_t size) : count(size)
{


    //open file
    _Ptr<FILE> fh = fopen(filename, "r");
		
    //allocate array space
    _Array_ptr<long> arr : count(size) = calloc<long>(size, sizeof(long));

    //read the file
    int ver;
    ver = fread(arr, sizeof(long), (size), fh);

    if(ver != size)
    {
        fclose(fh);
        free<long>(arr);
        exit(EXIT_FAILURE);
        return NULL;
    }

    //close file and return
    fclose(fh);
    return arr;
}


int Array_Save_To_File(_Nt_array_ptr<char> filename, _Array_ptr<long> array : count(size), size_t size) 
{
  //open file
  _Ptr<FILE> fh = NULL;

  fh = fopen(filename, "wb");

  //check if file opened successfully
  if (size == 0)
  {
    fclose(fh);
    free<long>(array); 
    return 0;
  }

  //number of written items
  int numWrit;


  //write to file
  numWrit = fwrite(array, sizeof(long), size, fh);

  //close file
  fclose(fh);

  //free array
  free<long>(array);

  //return number of written values
  return numWrit;
}

void Quick_Sort(_Array_ptr<long> Array : count(Size), size_t Size)
{
    medianQuick(Array, 0, Size - 1, Size);
		insertionSort(Array, 0, Size - 1, Size);
    return;
}

void insertionSort(_Array_ptr<long> array : count(size), int start, int end, size_t size)
{

    int i;
    for( i = start + 1; i <= end; i++)
		{
        compSwap(&array[start], &array[i]);
		}
		for(i = start + 2; i <= end; i++)
    {
        int j = i;
        long v = array [i];
        while(v < array[j - 1])
        {
            array[j] = array[j-1];
            j--;
        }
        array[j] = v;
    }
}

void medianQuick(_Array_ptr<long> array : count(size), int start, int end, size_t size)
{   
    if(end - start <= M)
		{
        return;
    }

		int i;
    swap(&array[(start + end) / 2], &array[end-1]);

    compSwap(&array[start], &array[end - 1]);
    compSwap(&array[start], &array[end]);
    compSwap(&array[end - 1], &array[end]);

    i = Partition(array, start, end, size);
    medianQuick(array, start, i - 1, size);
    medianQuick(array, i + 1, end, size);

}

void compSwap(_Ptr<long> a, _Ptr<long> b)
{
    if(*a > *b)
        swap(a, b);
    return;
}

//returns the median index after sorting the partitions
int Partition(_Array_ptr<long> array : count(size), int start, int end, size_t size)
{
    int i = start;
    int j = end - 1;
    long v = array[end];

    for(;;)
    {
        while(array[i] < v)
            i++;
        while(array[j] > v)
        {
            j--;
            if(j == 1)
                break;
        }
        if (i >= j) 
            break;
        else
            swap(&array[i], &array[j]);
    }
    swap(&array[i], &array[end]);
    return i;
}

void swap(_Ptr<long> a, _Ptr<long> b)
{
    long tmp = (*a);
    (*a) = (*b);
    (*b) = tmp;
}
