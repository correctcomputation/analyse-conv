#ifndef __HBT_TREE__
#define __HBT_TREE__

typedef struct _Tnode {
   int key;
   char balance;   
   _Ptr<struct _Tnode> left;
   _Ptr<struct _Tnode> right;
} Tnode;

#endif
