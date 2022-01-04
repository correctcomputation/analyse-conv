








#ifndef THREEDIM
#  ifndef TWODIM
#    ifndef NDIM
#      define THREEDIM
#    endif
#  endif
#endif

#ifdef TWODIM
#  define NDIM 2
#endif

#ifdef THREEDIM
#  define NDIM 3
#endif

typedef real vector [3];
typedef real matrix [3][3];
#ifdef TORONTO
extern double sqrt(double x);
#endif




#define CLRV(v);						\
{									\
    register int i;							\
    for (i = 0; i < NDIM; i++)					\
        (v)[i] = 0.0;							\
}

#define UNITV(v,j);					\
{									\
    register int i;							\
    for (i = 0; i < NDIM; i++)					\
        (v)[i] = (i == (j) ? 1.0 : 0.0);				\
}

#define SETV(v,u);					\
{ 									\
    register int i; 							\
    for (i = 0; i < NDIM; i++) 					\
        (v)[i] = (u)[i]; 						\
}


#define ADDV(v,u,w);					\
{									\
    register int i;							\
    for (i = 0; i < NDIM; i++)					\
        (v)[i] = (u)[i] + (w)[i];					\
}

#define SUBV(v,u,w);					\
{									\
    register int i;							\
    for (i = 0; i < NDIM; i++)					\
        (v)[i] = (u)[i] - (w)[i];					\
}

#define MULVS(v,u,s);				\
{									\
    register int i;							\
    for (i = 0; i < NDIM; i++)					\
        (v)[i] = (u)[i] * (s);					\
}


#define DIVVS(v,u,s);				\
{									\
    register int i;							\
    for (i = 0; i < NDIM; i++)					\
        (v)[i] = (u)[i] / (s);					\
}


#define DOTVP(s,v,u);				\
{									\
    register int i;							\
    (s) = 0.0;								\
    for (i = 0; i < NDIM; i++)					\
        (s) += (v)[i] * (u)[i];					\
}


#define ABSV(s,v);			\
{									\
    double tmp;                                                \
    register int i;							\
    tmp = 0.0;								\
    for (i = 0; i < NDIM; i++)					\
        tmp += (v)[i] * (v)[i];					\
    (s) = sqrt(tmp);                                                   \
}

#define DISTV(s,u,v);		        	\
{									\
    double tmp;                                                \
    register int i;							\
    tmp = 0.0;								\
    for (i = 0; i < NDIM; i++)					\
        tmp += ((u)[i]-(v)[i]) * ((u)[i]-(v)[i]);		        \
    (s) = sqrt(tmp);                                                   \
}

#ifdef TWODIM

#define CROSSVP(s,v,u);				\
{									\
    (s) = (v)[0]*(u)[1] - (v)[1]*(u)[0];				\
}

#endif

#ifdef THREEDIM

#define CROSSVP(v,u,w);				\
{									\
    (v)[0] = (u)[1]*(w)[2] - (u)[2]*(w)[1];				\
    (v)[1] = (u)[2]*(w)[0] - (u)[0]*(w)[2];				\
    (v)[2] = (u)[0]*(w)[1] - (u)[1]*(w)[0];				\
}

#endif

#define INCADDV(v,u);                      \
{									\
    register int i;                                                    \
    for (i = 0; i < NDIM; i++)                                       \
        (v)[i] += (u)[i];                                             \
}

#define INCSUBV(v,u);                 \
{									\
    register int i;                                                    \
    for (i = 0; i < NDIM; i++)                                       \
        (v)[i] -= (u)[i];                                             \
}

#define INCMULVS(v,s);		\
{									\
    register int i;                                                    \
    for (i = 0; i < NDIM; i++)                                       \
        (v)[i] *= (s);                                                 \
}

#define INCDIVVS(v,s);		\
{									\
    register int i;                                                    \
    for (i = 0; i < NDIM; i++)                                       \
        (v)[i] /= (s);                                                 \
}





#define CLRM(p);						\
{									\
    register int i, j;						\
    for (i = 0; i < NDIM; i++)					\
        for (j = 0; j < NDIM; j++)					\
	    (p)[i][j] = 0.0;						\
}

#define SETMI(p);				\
{									\
    register int i, j;						\
    for (i = 0; i < NDIM; i++)					\
        for (j = 0; j < NDIM; j++)					\
	    (p)[i][j] = (i == j ? 1.0 : 0.0);			\
}

#define SETM(p,q);					\
{									\
    register int i, j;						\
    for (i = 0; i < NDIM; i++)					\
        for (j = 0; j < NDIM; j++)					\
	    (p)[i][j] = (q)[i][j];					\
}

#define TRANM(p,q);					\
{									\
    register int i, j;						\
    for (i = 0; i < NDIM; i++)					\
        for (j = 0; j < NDIM; j++)					\
	    (p)[i][j] = (q)[j][i];					\
}

#define ADDM(p,q,r);					\
{									\
    register int i, j;						\
    for (i = 0; i < NDIM; i++)					\
        for (j = 0; j < NDIM; j++)					\
	    (p)[i][j] = (q)[i][j] + (r)[i][j];			\
}

#define SUBM(p,q,r);					\
{									\
    register int i, j;						\
    for (i = 0; i < NDIM; i++)					\
        for (j = 0; j < NDIM; j++)					\
	    (p)[i][j] = (q)[i][j] - (r)[i][j];			\
}

#define MULM(p,q,r);					\
{									\
    register int i, j, k;						\
    for (i = 0; i < NDIM; i++)					\
	for (j = 0; j < NDIM; j++) {					\
	    (p)[i][j] = 0.0;						\
            for (k = 0; k < NDIM; k++)				\
		(p)[i][j] += (q)[i][k] * (r)[k][j];		\
        }								\
}

#define MULMS(p,q,s);				\
{									\
    register int i, j;						\
    for (i = 0; i < NDIM; i++)				        \
        for (j = 0; j < NDIM; j++)					\
	    (p)[i][j] = (q)[i][j] * (s);				\
}

#define DIVMS(p,q,s);				\
{									\
    register int i, j;						\
    for (i = 0; i < NDIM; i++)					\
        for (j = 0; j < NDIM; j++)					\
	    (p)[i][j] = (q)[i][j] / (s);				\
}

#define MULMV(v,p,u);				\
{									\
    register int i, j;						\
    for (i = 0; i < NDIM; i++) {					\
	(v)[i] = 0.0;							\
	for (j = 0; j < NDIM; j++)					\
	    (v)[i] += (p)[i][j] * (u)[j];				\
    }									\
}

#define OUTVP(p,v,u);				\
{									\
    register int i, j;						\
    for (i = 0; i < NDIM; i++)					\
        for (j = 0; j < NDIM; j++)					\
	    (p)[i][j] = (v)[i] * (u)[j];				\
}

#define TRACEM(s,p);					\
{									\
    register int i;							\
    (s) = 0.0;								\
    for (i = 0.0; i < NDIM; i++)					\
	(s) += (p)[i][i];						\
}





#define SETVS(v,s);				\
{									\
    register int i;							\
    for (i = 0; i < NDIM; i++)					\
        (v)[i] = (s);							\
}

#define ADDVS(v,u,s);				\
{									\
    register int i;							\
    for (i = 0; i < NDIM; i++)					\
        (v)[i] = (u)[i] + (s);					\
}

#define SETMS(p,s);				\
{									\
    register int i, j;						\
    for (i = 0; i < NDIM; i++)					\
        for (j = 0; j < NDIM; j++)					\
	    (p)[i][j] = (s);						\
}











