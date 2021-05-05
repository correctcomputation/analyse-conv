/* For copyright information, see olden_v1.0/COPYRIGHT */


#include <stdio.h>

struct hash_entry {
  unsigned int key;
  void *entry;
  _Ptr<struct hash_entry> next;
};

#pragma CHECKED_SCOPE ON

typedef _Ptr<struct hash_entry> HashEntry;

struct hash {
  _Array_ptr<HashEntry> array : count(size);
  _Ptr<int(unsigned int)> mapfunc;
  int size;
};

typedef _Ptr<struct hash> Hash;

Hash MakeHash(int size, _Ptr<int(unsigned int)> map);
_Unchecked void *HashLookup(unsigned int key, Hash hash);
_Unchecked void HashInsert(void *entry, unsigned int key, Hash hash);
void HashDelete(unsigned int key, Hash hash);

#pragma CHECKED_SCOPE OFF
