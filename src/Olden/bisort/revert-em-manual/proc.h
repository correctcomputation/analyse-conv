






HANDLE * RandTree(int, int, int, int);

void SwapValue(HANDLE * l, HANDLE * r);
void SwapValLeft(HANDLE * l, HANDLE * r, HANDLE * ll, HANDLE * rl, int lval, int rval);
void SwapValRight(HANDLE * l, HANDLE * r, HANDLE * lr, HANDLE * rr, int lval, int rval);
int Bimerge(HANDLE * root, int spr_val, int dir);
int Bisort(HANDLE * root, int spr_val, int dir);
int dealwithargs(int argc, char * * argv );

