#include "shell_list.h"

List* addNode(List* list, long val)
{
    //make new node
    Node* newNode = NULL;
    newNode = malloc(sizeof(*newNode));
    newNode -> value = val;
    newNode -> next = NULL;
    // printf("newNode -> value = %ld\n", newNode -> value);

    //checks if head is null
    if(list -> head == NULL)
    {
        //if it is then the end of the list is the head
        list -> head = newNode;
        list -> tail = newNode;
        return list;
    }
    else
    {
        //if it isn't p will then find the end of the list and add there
        (list -> tail) -> next = newNode;
        list -> tail = newNode;
        return list;
    }

}

Node* destroyList(Node* head)
{
    Node* p = NULL;
    p = head;
    
    Node * next = NULL;

    while(p != NULL)
    {
        next = p -> next;
        free(p);
        p = next;
    }

    head = NULL;
    return head;
}


Node *List_Load_From_File(char *filename)
{
    //opening file
    FILE *fh = fopen(filename, "rb");
    if(fh == NULL)
    {
        fprintf(stderr, "%s", "file didn't load properly\n");
        return NULL;
    }

    List *list = malloc(sizeof(*list)); //initializing the head of the list
    list -> head = NULL;
    list -> tail = NULL;

    long tmp = 0; //tmp for reading into
    int read = 0;

    while(!feof(fh))
    {
        read += fread(&tmp, sizeof(long), 1, fh); //read a value into tmp
        if(!feof(fh)) //check if EOF has been reached
            list = addNode(list, tmp); //add value to list
    }

    if(read == 0)
    {
        fprintf(stderr,"%s","read failed");
        destroyList(list -> head);
        free(list);
        return NULL;
    }

    fclose(fh); //close the file

    Node* head = list -> head;

    free(list);

    return head; //return the new head of the list
}

int List_Save_To_File(char* filename, Node* list)
{
    FILE *fh = NULL;
    fh = fopen(filename, "w");


    if(fh == NULL)
    {
        fprintf(stderr,"%s", "fopen in save failed");
        return 0;
    }
    

    Node *p = list;
    int written = 0;

    while(p != NULL)
    {
        written += fwrite(&(p -> value), sizeof(long), 1, fh);
        p = p -> next;
    }

    fclose(fh);

    destroyList(list);

    return written;
}

Node *List_Shellsort(Node *head, long *n_comp)
{
    if(head == NULL)
        return NULL;

    //counting the size of the list
    Node* p = head;
    long size = 1;

    while(p -> next != NULL)
    {
        p = p -> next;
        size++;
    }


    long h = 0; //sequence value

    //getting max sequence value
    do
    {

        h = 3 * h + 1;

    } while (h < size);
    h = (h - 1) / 3;

    //shell sort --------------------------------------------------
    
    //variable declarations ---------------------------------------
    long j;
    long i;
    Node* arrIminH = NULL;
    Node* tmp = NULL;
    //variable declarations ---------------------------------------

    while(h > 0)
    {
        for(j = h; j < size; j++)
        {
            tmp = getNodeAtIndex(head, j);
            i = j;
            arrIminH = getNodeAtIndex(head, (i - h));
            while(i >= h && arrIminH -> value > tmp -> value)
            {
                (*n_comp)++; 

                head = swapNodes(head, i - h, i);

                i = i - h;
                
                arrIminH = getNodeAtIndex(head, (i - h));
            }
            (*n_comp)++;
        }

        h = (h - 1) / 3;
    }
    //shell sort --------------------------------------------------

    return head;
}


Node* getNodeAtIndex(Node* head, long index)
{
    Node* node = head;
    int i;

    for(i = 0; i < index; i++)
    {   
        node = node -> next;
    }
    return node;
}


Node* swapNodes(Node* list, int pos1, int pos2)
{

    if(pos1 == pos2)
        return list;
    

    if ((pos1 < 0) || (pos2 < 0))
    {
        fprintf(stderr, "\tinvalid position args in swapNodes\n");
        return list;
    }

    Node* node1 = NULL;
    Node* node2 = NULL;
    Node* prev1 = NULL;
    Node* prev2 = NULL;

    Node* tmp = list;

    int i = 0;

    while(tmp != NULL && (node1 == NULL || node2 == NULL))
    {   
        if(i == pos1 - 1)
            prev1 = tmp;
        if(i == pos2 - 1)
            prev2 = tmp;
        if(i == pos1)
            node1 = tmp;
        if(i == pos2)
            node2 = tmp;
        tmp = tmp -> next;
        i++;
    }

    if(node1 != NULL && node2 != NULL)
    {   
        if(prev1 != NULL)
            prev1 -> next = node2;
        
        if(prev2 != NULL)
            prev2 -> next = node1;

        tmp = node1 -> next;
        node1 -> next = node2 -> next;
        node2 -> next = tmp;

        if(prev1 == NULL)
        {
            list = node2;
        }
        else if(prev2 == NULL)
        {
            list = node1;
        }
    }

    return list;

}

void printList(Node* head)
{
    Node* p = head;
    while(p != NULL)
    {
        fprintf(stderr, "%ld\n", p -> value);
        p = p -> next;
    }

    if(p == NULL)
        fprintf(stderr, "null reached\n");

    return;
}
