#include "shell_array.h"
#include "shell_list.h"

int main(int argc, char *argv[])
{
  if(argc < 3)
  {
    fprintf(stderr,"arguments missing");
    return 0;
  }

  if(!strcmp(argv[1],"-a"))
  {
		size_t size = getSize(argv[2]);

		long* array = Array_Load_From_File(argv[2], size);

    long n_comp = 0;

    clock_t begin = clock();
    Array_Shellsort(array, size, &n_comp);
    clock_t end = clock();
    double timeSpend = (double)(end - begin) / CLOCKS_PER_SEC;
    fprintf(stderr ,"list sorted in: %fs\n", timeSpend);
    int writ = 0;

    writ = Array_Save_To_File(argv[3], array, size);

    if(writ != size)
    {
      fprintf(stderr, "written != size of array");
      return 0;
    }

    fprintf(stdout, "%ld\n", n_comp);
  }

  if(!strcmp(argv[1], "-l"))
  {
		Node* head = NULL;
    clock_t begin = clock();
    head = List_Load_From_File(argv[2]);
    clock_t end = clock();
    double timeSpend = (double)(end - begin) / CLOCKS_PER_SEC;
    fprintf(stderr, "list loaded in: %fs\n", timeSpend);
    long n_comp = 0;

    int size = 0;
    Node* p = NULL;

    p = head;

    while(p != NULL)
    {
      p = p -> next;
      size++;
    }
    fprintf(stderr, "sorting...\n");
    begin = clock();
    head = List_Shellsort(head, &n_comp);
    end = clock();
    timeSpend = (double)(end - begin) / CLOCKS_PER_SEC;
    fprintf(stderr, "sorted in: %fs\n", timeSpend);

    int writ;

    fprintf(stderr, "saving\n");
    writ = List_Save_To_File(argv[3], head);
    fprintf(stderr, "saved\n");

    if(writ != size)
    {
      fprintf(stderr,"writ != size");
      exit(EXIT_FAILURE);
      return 0;
    }

    fprintf(stdout, "%ld\n", n_comp);
  }

  return 0;
}
