


#include <stdio.h>


struct hash_entry {
  unsigned int key;
  int entry;
  struct hash_entry * next;
};

typedef struct hash_entry * HashEntry;

struct hash {
  HashEntry * array ;
  int(*mapfunc)(unsigned int);
  int size;
};

typedef struct hash * Hash;

Hash MakeHash(int size, int(*map)(unsigned int));
int HashLookup(unsigned int key, Hash hash);
void HashInsert(int entry, unsigned int key, Hash hash);
void HashDelete(unsigned int key, Hash hash);

