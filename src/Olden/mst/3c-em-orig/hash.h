

#include "stdio.h"

typedef struct hash_entry {
  unsigned int key;
  void *entry;
  struct hash_entry *next;
} *HashEntry;

struct hash {
  HashEntry *array;
  _Ptr<int (unsigned int)> mapfunc;
  int size;
};
typedef _Array_ptr<struct hash> Hash;

Hash MakeHash(int size, _Ptr<int (unsigned int)> map);
void *HashLookup(unsigned int key, Hash hash);
void HashInsert(void *entry, unsigned int key, Hash hash);
void HashDelete(unsigned int key, Hash hash);
