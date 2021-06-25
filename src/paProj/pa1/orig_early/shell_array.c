#include "shell_array.h"
#include <stdio.h>
#include <stdlib.h>

size_t getSize(char* filename)
{
	FILE* fh = fopen(filename, "r");

	fseek(fh, 0, SEEK_END);
	int size = ftell(fh) / sizeof(long);
	rewind(fh);

	fclose(fh);

	return size;
}

long *Array_Load_From_File(char *filename, size_t size)
{
  
  //open file
  FILE *fh = fopen(filename, "r");
  if (fh == NULL)
  {
    fprintf(stderr, "failed to open file properly\n");
    return NULL;
  }

  //get size of file in bytes
  fseek(fh, 0, SEEK_END);
  size = ftell(fh) / sizeof(long);
  rewind(fh);

  //allocate array space
  long* arr = NULL;
  arr = malloc(sizeof(long) * (size));

  //read the file
  int ver;
  ver = fread(arr, sizeof(long), (size), fh);

  if(ver != size)
  {
    fclose(fh);
    free(arr);
    exit(EXIT_FAILURE);
    return NULL;
  }

  //close file and return
  fclose(fh);
  return arr;
}

int Array_Save_To_File(char *filename, long *array, size_t size) 
{
  //open file
  FILE * fh = NULL;

  fh = fopen(filename, "wb");

  //check if file opened successfully
  if (size == 0)
  {
    fclose(fh);
    free(array); 
    return 0;
  }

  //number of written items
  int numWrit;

  //write to file
  numWrit = fwrite(array, sizeof(long), size, fh);

  //close file
  fclose(fh);

  //free array
  free(array);

  //return number of written values
  return numWrit;
}

void Array_Shellsort(long *array, size_t size, long *n_comp)
{
  //sequence value
  long h = 0;

  //indexing values
  long i = 0;
  long j = 0;

  //temp variables
  long tmp = 0;


  //getting max sequence value
  do
  {

    h = 3 * h + 1;

  } while (h < size);
  h = (h - 1) / 3;
  

  //shell sort --------------------------------------------------
  while (h > 0)
  {
    for (j = h; j < size; j++)
    {
      tmp = array[j];
      i = j;
      while (i >= h && array[i-h] > tmp)
      {
        (*n_comp)++; //increment number of comparisons
        //swap the first node and the second
        array[i] = array[i-h];
        i = i - h; //shift i back to the first node in the list
        array[i] = tmp;
      }
      (*n_comp)++;
    }
    //decrement sequence
    h = (h - 1) / 3;
  }
  //shell sort --------------------------------------------------

  return;
}
