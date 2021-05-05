/* For copyright information, see olden_v1.0/COPYRIGHT */

/* ========== PROCEDURE TYPES/NUMS ================== */



#pragma CHECKED_SCOPE ON

_Ptr<HANDLE> RandTree(int, int, int, int);

void SwapValue(_Ptr<HANDLE> l, _Ptr<HANDLE> r);
void SwapValLeft(_Ptr<HANDLE> l, _Ptr<HANDLE> r, _Ptr<HANDLE> ll, _Ptr<HANDLE> rl, int lval, int rval);
void SwapValRight(_Ptr<HANDLE> l, _Ptr<HANDLE> r, _Ptr<HANDLE> lr, _Ptr<HANDLE> rr, int lval, int rval);
int Bimerge(_Ptr<HANDLE> root, int spr_val, int dir);
int Bisort(_Ptr<HANDLE> root, int spr_val, int dir);
int dealwithargs(int argc, _Array_ptr<_Nt_array_ptr<char>> argv : count(argc));

#pragma CHECKED_SCOPE OFF
