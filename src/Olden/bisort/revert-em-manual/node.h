






struct node {
  int value;
  struct node * left;
  struct node * right;
};

typedef struct node HANDLE;

typedef struct future_cell_int{
  HANDLE * value;
} future_cell_int;

#define NIL (0)

