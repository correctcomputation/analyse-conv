


#include <stdlib.h>
#include "hash.h"

#define printf(...)  { (printf)(__VA_ARGS__); }
#define assert(num,a) if (!(a)) {printf("Assertion failure:%d in hash\n",num); exit(-1);}





















#define localfree(sz)


Hash MakeHash(int size, int(*map)(unsigned int))
{
  Hash retval = ((void*)0);
  int i;

  retval = malloc(sizeof(struct hash));
  retval->array = malloc(size*sizeof(HashEntry));
  retval->size = size;
  for (i=0; i<size; i++)
    retval->array[i] = ((void*)0);
  retval->mapfunc = map;
  return retval;
}

int HashLookup(unsigned int key, Hash hash)
{
  int j;
  HashEntry ent = ((void*)0);

  j = (hash->mapfunc)(key);
  if (!(j>=0)) { { (printf)("Assertion failure:%d in hash\n",1); }; exit(-1);};
  if (!(j<hash->size)) { { (printf)("Assertion failure:%d in hash\n",2); }; exit(-1);};
  for (ent = hash->array[j];
       ent &&
           ent->key!=key;
       ent=ent->next);
  if (ent) return ent->entry;
  return ((void*)0);
}

void HashInsert(int entry,unsigned int key,Hash hash)
{
  HashEntry ent = ((void*)0);
  int j;

  if (!(!HashLookup(key,hash))) { { (printf)("Assertion failure:%d in hash\n",3); }; exit(-1);};

  j = (hash->mapfunc)(key);
  ent = malloc(sizeof(*ent));
  ent->next = hash->array[j];
  hash->array[j]=ent;
  ent->key = key;
  ent->entry = entry;
}

void HashDelete(unsigned key, Hash hash) {
  HashEntry tmp = ((void*)0);
  int j = (hash->mapfunc)(key);
  int size = hash->size;
  ;
  HashEntry * ent = 0;
   { ent = &hash->array[j]; }

  while (*ent && (*ent)->key != key) {
    ent = &(*ent)->next;
  }

  if (!(*ent)) { { (printf)("Assertion failure:%d in hash\n",4); }; exit(-1);};

  tmp = *ent;
  *ent = (*ent)->next;
  free(tmp);
}





