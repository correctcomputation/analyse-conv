





































#ifndef _fstruct_h
#define _fstruct_h


#define ITEM(P)		((*(P)).item)
#define PARENT(P)	((*(P)).parent)
#define CHILD(P)	((*(P)).child)
#define FORWARD(P)	((*(P)).forward)
#define BACKWARD(P)	((*(P)).backward)
#define RANK(P)		((*(P)).rank)
#define MARKED(P)	((*(P)).marked)

#define ORPHAN(P)	(PARENT(P) == NULL_HEAP)
#define ONLY_CHILD(P)	((P) == FORWARD(P))
#define PARENT_OF(P, C)	(CHILD(P) == (C))

#define TRUE		1
#define FALSE		0
#define MAX_RANK	10000


#endif
