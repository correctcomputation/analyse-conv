#include "shell_list.h"

#pragma CHECKED_SCOPE on

_Ptr<List> addNode(_Ptr<List> list, long val)
{
	_Ptr<Node> newNode = malloc<Node>(sizeof(*newNode));
	newNode -> value = val;
	newNode -> next = NULL;

	if(list -> head == NULL)
	{
		list -> head = newNode;
		list -> tail = newNode;
		return list;
	}
	(list -> tail) -> next = newNode;
	list -> tail = newNode;
	return list;
}

_Ptr<Node> destroyList(_Ptr<Node> head)
{
	_Ptr<Node> p = head;

	_Ptr<Node> next = NULL;

	while(p != NULL)
	{
		next = p -> next;
		free<Node>(p);
		p = next;
	}

	head = NULL;
	return head;
}

_Ptr<Node> List_Load_From_File(_Nt_array_ptr<char> filename)
{
	_Ptr<FILE> fh = fopen(filename, "rb");
	if(fh == NULL)
	{
		_Unchecked{
			fprintf(stderr, "%s", "file didn't load properly\n");
		}
		return NULL;
	}

	_Ptr<List> list = malloc<List>(sizeof(*list));
	list -> head = NULL;
	list -> tail = NULL;

	long tmp = 0;
	int read = 0;

	while(!feof(fh))
	{
		read += fread(&tmp, sizeof(long), 1, fh);
		if(!feof(fh))
			list = addNode(list, tmp);
	}

	if(read == 0)
	{
		_Unchecked{
			fprintf(stderr, "%s", "read failed");
		}
		destroyList(list -> head);
		free<List>(list);
		return NULL;
	}

	fclose(fh);

	_Ptr<Node> head = list -> head;

	free<List>(list);


	return head;
}

size_t List_Save_To_File(_Nt_array_ptr<char> filename, _Ptr<Node> list)
{
	_Ptr<FILE> fh = fopen(filename, "w");

	if(fh == NULL)
	{
		_Unchecked{
			fprintf(stderr, "%s", "fopen in save failed");
		}	
		return 0;
	}

	_Ptr<Node> p = list;
	size_t written = 0;

	while(p != NULL)
	{
		written += fwrite(&(p -> value), sizeof(long), 1, fh);
		_Unchecked {
			fprintf(stderr, "%ld\n", p -> value);
		}
		p = p -> next;
	}

	fclose(fh);

	destroyList(list);

	return written;
}

_Ptr<Node> List_Shellsort(_Ptr<Node> head, _Ptr<long> n_comp)
{
	if(head == NULL)
		return NULL;

	//count size of list
	_Ptr<Node> p = head;
	size_t size = 1;

	while(p -> next != NULL)
	{
		p = p -> next;
		size++;
	}

	long h = 0;

	do
	{
		h = 3 * h + 1;
	} while (h < size);
	h = (h - 1) / 3;

	//shell sort ------------------------------------------

	//variable declarations -------------------------------
	long j;
	long i;
	long tmp;
	//variable declarations -------------------------------

	while(h > 0)
	{
		for(j = h; j < size; j++)
		{
			tmp = getNodeAtIndex(head, j) -> value;
			i = j;
			while(i >= h && getNodeAtIndex(head, i - h) -> value > tmp)
			{
				(*n_comp)++;

				head = swapNodes(head, i-h, i);

				i = i - h;
			}
			(*n_comp)++;
		}
		h = (h - 1) / 3;
	}

	return head;

}

_Ptr<Node> getNodeAtIndex(_Ptr<Node> head, long index)
{
	_Ptr<Node> node = head;
	int i;

	for(i = 0; i < index; i++)
	{
		node = node -> next;
	}
	return node;
}

_Ptr<Node> swapNodes(_Ptr<Node> head, int pos1, int pos2)
{
	if(pos1 == pos2)
		return head;

	if((pos1 < 0) || (pos2 < 0))
	{
		_Unchecked{
			fprintf(stderr, "ERROR: Invalid position args in swapNodes\n");
		}
		return head;
	}

	//get pointers to all involved nodes
	_Ptr<Node> node1 = getNodeAtIndex(head, pos1);
	_Ptr<Node> node2 = getNodeAtIndex(head, pos2);
	_Ptr<Node> node1Prev = pos1 <= 0 ? NULL : getNodeAtIndex(head, pos1 - 1);
	_Ptr<Node> node2Prev = getNodeAtIndex(head, pos2 - 1);
	_Ptr<Node> tmp = NULL;

	if(node1Prev == NULL)
	{
		head = node2;
		
		tmp = node2 -> next;

		//special case if node2 is node1's next
		node2 -> next = node1 -> next != node2 ? node1 -> next : node1;
		
		node1 -> next = tmp;

		//special case if node2Prev is node1
		node2Prev -> next = node2Prev == node1 ? tmp : node1;
		
		return head;
	}

	node1Prev -> next = node2;

	tmp = node2 -> next;

	//special case if node2 is node1's next
	node2 -> next = node1 -> next != node2 ? node1 -> next : node1;

	node1 -> next = tmp;

	//special case if node2Prev is node1
	node2Prev -> next = node2Prev == node1 ? tmp : node1;

	return head;
}

void printList(_Ptr<Node> head)
{
	_Ptr<Node> p = head;
	while(p != NULL)
	{
		_Unchecked{
			fprintf(stderr, "%ld\n", p -> value);
		}
		p = p -> next;
	}

	if(p == NULL)
		_Unchecked{
			fprintf(stderr, "null reached\n");
		}
	
	return;
}
