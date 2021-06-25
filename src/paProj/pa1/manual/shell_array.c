//shell_array.c contains the functions for loading, sorting, and saving the array

#include "shell_array.h"

#pragma CHECKED_SCOPE on

size_t getSize(_Nt_array_ptr<char> filename)
{
  _Ptr<FILE> fh = fopen(filename, "r");

	fseek(fh, 0, SEEK_END);
	int size = ftell(fh) / sizeof(long);
	rewind(fh);

	fclose(fh);

	return size;
}


//This is unchecked because reading of file causes the bounds of the array to be undetermined
_Array_ptr<long> Array_Load_From_File(_Nt_array_ptr<char> filename,  size_t size) : count(size)
{

	_Ptr<FILE> fh = fopen(filename, "r");


	if (fh == NULL)
	{
		_Unchecked {
	  	fprintf(stderr, "failed to open file properly\n");
		}
		return NULL;
	}

	//allocate array space
	_Array_ptr<long> arr : count(size) = calloc<long>(size, sizeof(long));

	//read file
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

int Array_Save_To_File(_Nt_array_ptr<char> filename, _Array_ptr<long> array : count(size), size_t size) _Checked
{

	//open file
	_Ptr<FILE> fh = NULL;

	fh = fopen(filename, "wb");

	//check if opened successfully and if there is an array to write
	if (fh == NULL || size == 0)
	{
		fclose(fh);
		return 0;
	}

	//number of written items
	int numWrit;

	//write to file
	numWrit = fwrite(array, sizeof(long), size, fh);
  
  //check number written to see if successful
	if (numWrit != size)
	{
	  fclose(fh);
		free<long>(array);
    return 0;
	}

	//close file
	fclose(fh);
	return numWrit;
}

void Array_Shellsort(_Array_ptr<long> array : count(size), size_t size, _Ptr<long> n_comp)
{
	//sequence value
	long h = 0;

	//indexing values
	long i = 0;
	long j = 0;

	//temp variables
	long tmp = 0;

	//getting max sequence vlaue
	do
	{
		h = 3 * h + 1;
	} while (h < size);
	h = (h - 1) / 3;

	//shell sort --------------------------------------------------------
	while ( h > 0 )
	{
		for (j = h; j < size; j++)
		{
			tmp = array[j];
			i = j;
			while(i >= h && array[i-h] > tmp)
			{
				(*n_comp)++; //increment number of comparisons
				array[i] = array[i-h];
				i = i - h; //shift i back to the first node in the list
				array[i] = tmp;
			}
			(*n_comp)++;
		}
		//decrement sequence
		h = (h - 1) / 3;
	}
	//shell sort end-----------------------------------------------------

	return;

}

