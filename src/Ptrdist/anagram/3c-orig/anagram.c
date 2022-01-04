

































































































































#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <setjmp.h>
#include <strings.h>
#include <unistd.h>












typedef unsigned long Quad;
#define MASK_BITS (sizeof(Quad)*8)                    

#define MAX_QUADS 2                     

#define MAXWORDS 26000                  
#define MAXCAND  5000                   
#define MAXSOL   51                     

#define ALPHABET 26                     
#define ch2i(ch) ((ch)-'a')             
#define i2ch(ch) ((ch)+'a')             














#   define huge
#   define far
#   define StringFormat    "%15s%c"
#   define bigmalloc       malloc
#   define smallmalloc     malloc
#   define smallmallocfail (char *)0
#   define HaltProcessing() 0           
#   define Cdecl




#ifdef DEBUG
#define Debug(x) x
#else
#define Debug(x)
#endif

#ifdef STAT
#define Stat(x) x
#else
#define Stat(x)
#endif


typedef struct {
    Quad aqMask[2];
    _Nt_array_ptr<char> pchWord;
    unsigned cchLength;
} Word;
typedef _Ptr<Word> PWord;
typedef _Array_ptr<_Ptr<Word>> PPWord;

PWord apwCand _Checked[5000] = {((void *)0)};
unsigned cpwCand;






typedef struct {
    unsigned uFrequency;
    unsigned uShift;
    unsigned uBits;
    unsigned iq;
} Letter;
typedef _Ptr<Letter> PLetter;

Letter alPhrase[26];
#define lPhrase(ch) alPhrase[ch2i(ch)]  

int cchPhraseLength;

Quad aqMainMask[2];
Quad aqMainSign[2];

int cchMinLength = 3;





unsigned auGlobalFrequency _Checked[26];
char achByFrequency[26];

char * pchDictionary;

#define Zero(t) memset(t, 0, sizeof(t)) 


void Fatal(_Nt_array_ptr<char> pchMsg, unsigned u) {
    fprintf(stderr, pchMsg, u);
    exit(1);
}













void ReadDict(_Nt_array_ptr<char> pchFile) {
    _Ptr<FILE> fp = ((void *)0);
    char * pch;
    char * pchBase;
    unsigned long ulLen;
    unsigned cWords = 0;
    unsigned cLetters;
    int ch;
    struct stat statBuf;

    if (stat(pchFile, &statBuf)) Fatal("Cannot stat dictionary\n", 0);

    ulLen = statBuf.st_size + 2 * (unsigned long)26000;
    pchBase = pchDictionary = (char *)malloc<char>(ulLen);

    if(pchDictionary == ((void*)0))
 Fatal("Unable to allocate memory for dictionary\n", 0);

    if ((fp = fopen(pchFile, "r")) == ((void*)0))
 Fatal("Cannot open dictionary\n", 0);

    while (!feof(fp)) {
        pch = pchBase+2;
        cLetters = 0;
        while ((ch = fgetc(fp)) != '\n' && ch != (-1)) {
            if (((*__ctype_b_loc ())[(int) ((ch))] & (unsigned short int) _ISalpha)) cLetters++;
            *pch++ = ch;
        }
        *pch++ = '\0';
        *pchBase = pch - pchBase;
        pchBase[1] = cLetters;
        pchBase = pch;
        cWords++;
    }
    fclose(fp);

    *pchBase++ = 0;

    fprintf(stderr, "main dictionary has %u entries\n", cWords);
    if (cWords >= 26000)
 Fatal("Dictionary too large; increase MAXWORDS\n", 0);
    fprintf(stderr, "%lu bytes wasted\n", ulLen - (pchBase - pchDictionary));
}

void BuildMask(_Array_ptr<char> pchPhrase) {
    int i;
    int ch;
    unsigned iq;
    int cbtUsed;
    int cbtNeed;
    Quad qNeed;

    bzero(alPhrase, sizeof(Letter)*26);
    bzero(aqMainMask, sizeof(Quad)*2);
    bzero(aqMainSign, sizeof(Quad)*2);







    cchPhraseLength = 0;
    while ((ch = *pchPhrase++) != '\0') {
        if (((*__ctype_b_loc ())[(int) ((ch))] & (unsigned short int) _ISalpha)) {
            ch = tolower(ch);
            alPhrase[((ch)-'a')].uFrequency++;
            cchPhraseLength++;
        }
    }


    iq = 0;
    cbtUsed = 0;

    for (i = 0; i < 26; i++) {
        if (alPhrase[i].uFrequency == 0) {
            auGlobalFrequency[i] = ~0;
        } else {
            auGlobalFrequency[i] = 0;
            for (cbtNeed = 1, qNeed = 1;
                 alPhrase[i].uFrequency >= qNeed;
                 cbtNeed++, qNeed <<= 1);
            if (cbtUsed + cbtNeed > (sizeof(Quad)*8)) {
                if (++iq >= 2)
      Fatal("MAX_QUADS not large enough\n", 0);
                cbtUsed = 0;
            }
            alPhrase[i].uBits = qNeed-1;
            if (cbtUsed)
  qNeed <<= cbtUsed;
            aqMainSign[iq] |= qNeed;
            aqMainMask[iq] |= (Quad)alPhrase[i].uFrequency << cbtUsed;
            alPhrase[i].uShift = cbtUsed;
            alPhrase[i].iq = iq;
            cbtUsed += cbtNeed;
        }
    }
}

PWord 
NewWord(void) {
    PWord pw = ((void *)0);

    pw = (_Ptr<Word>)malloc<Word>(sizeof(Word));
    if (pw == ((void*)0))
        Fatal("Out of memory after %d candidates\n", cpwCand);
    return pw;
}






void wprint(_Nt_array_ptr<char> pch) {
    printf("%s ", pch);
}

PWord  NextWord(void);


PWord  NextWord(void) {
    PWord pw = ((void *)0);
    if (cpwCand >= 5000)
 Fatal("Too many candidates\n", 0);
    pw = apwCand[cpwCand++];
    if (pw != ((void*)0))
 return pw;
    apwCand[cpwCand-1] = NewWord();
    return apwCand[cpwCand-1];
}




void BuildWord(_Nt_array_ptr<char> pchWord) {
    unsigned char cchFrequency[26];
    int i;
    _Array_ptr<char> pch = pchWord;
    PWord pw = ((void *)0);
    int cchLength = 0;

    bzero(cchFrequency, sizeof(unsigned char)*26);



    while ((i = *pch++) != '\0') {
        if (!((*__ctype_b_loc ())[(int) ((i))] & (unsigned short int) _ISalpha)) continue;
        i = ((tolower(i))-'a');
        if (++cchFrequency[i] > alPhrase[i].uFrequency)
     return;
        ++cchLength;
    }




    for (i = 0; i < 26; i++)
        auGlobalFrequency[i] += cchFrequency[i];




    pw = NextWord();
    bzero(pw->aqMask, sizeof(Quad)*2);

    pw->pchWord = pchWord;
    pw->cchLength = cchLength;
    for (i = 0; i < 26; i++) {
        pw->aqMask[alPhrase[i].iq] |=
            (Quad)cchFrequency[i] << alPhrase[i].uShift;
    }
}


void
AddWords(void) {
    char * pch = pchDictionary;

    cpwCand = 0;

    while (*pch) {
        if ((pch[1] >= cchMinLength && pch[1]+cchMinLength <= cchPhraseLength)
            || pch[1] == cchPhraseLength)
     BuildWord(_Assume_bounds_cast<_Nt_array_ptr<char>>(pch+2, byte_count(0)));
        pch += *pch;
    }

    fprintf(stderr, "%d candidates\n", cpwCand);
}

void DumpCandidates(void) {
    unsigned u;

    for (u = 0; u < cpwCand; u++)
        printf("%15s%c", apwCand[u]->pchWord, (u % 4 == 3) ? '\n' : ' ');
    printf("\n");
}

PWord apwSol _Checked[51] = {((void *)0)};
int cpwLast;
















void DumpWords(void) {
static int X;
  int i;
  X = (X+1) & 1023;
  if (X != 0) return;
    for (i = 0; i < cpwLast; i++) wprint(apwSol[i]->pchWord);
    printf("\n");
}



jmp_buf jbAnagram;

#define OneStep(i) \
    if ((aqNext[i] = pqMask[i] - pw->aqMask[i]) & aqMainSign[i]) { \
        ppwStart++; \
        continue; \
    }


void
FindAnagram(_Array_ptr<Quad> pqMask : count(2), PPWord ppwStart, int iLetter)
{
    Quad aqNext _Checked[2];
    register PWord pw = ((void *)0);
    Quad qMask;
    unsigned iq;
    PPWord ppwEnd = &apwCand[0];
    ppwEnd += cpwCand;

    ;

    if (0) longjmp(jbAnagram, 1);



    for (;;) {
        iq = alPhrase[achByFrequency[iLetter]].iq;
        qMask = alPhrase[achByFrequency[iLetter]].uBits <<
                alPhrase[achByFrequency[iLetter]].uShift;
        if (pqMask[iq] & qMask) break;
        iLetter++;
    }



    while (ppwStart < ppwEnd) {
        pw = *ppwStart;



#if MAX_QUADS > 0
        if ((aqNext[0] = pqMask[0] - pw->aqMask[0]) & aqMainSign[0]) { ppwStart++; continue; };
#endif

#if MAX_QUADS > 1
        if ((aqNext[1] = pqMask[1] - pw->aqMask[1]) & aqMainSign[1]) { ppwStart++; continue; };
#endif

#if MAX_QUADS > 2

#endif

#if MAX_QUADS > 3

#endif

#if MAX_QUADS > 4

#endif


        if ((pw->aqMask[iq] & qMask) == 0) {
            *ppwStart = *--ppwEnd;
            *ppwEnd = pw;
            continue;
        }


        apwSol[cpwLast++] = pw;
        if (cchPhraseLength -= pw->cchLength) {




     ppwEnd = &apwCand[0];
     ppwEnd += cpwCand;
            FindAnagram(&aqNext[0],
   ppwStart, iLetter);
        } else DumpWords();
        cchPhraseLength += pw->cchLength;
        --cpwLast;
        ppwStart++;
        continue;
    }

    ;
}

int CompareFrequency(char *pch1, char *pch2) {
    if (auGlobalFrequency[*pch1] < auGlobalFrequency[*pch2])
        return -1;
 if (auGlobalFrequency[*pch1] > auGlobalFrequency[*pch2])
        return 1;
    if (*pch1 < *pch2)
        return -1;
 if (*pch1 > *pch2)
        return 1;
    return 0;
}

void SortCandidates(void) {
    int i;


    for (i = 0; i < 26; i++) achByFrequency[i] = i;
    qsort(achByFrequency, 26, sizeof(char),
          (int (*)(const void *, const void *))CompareFrequency);

    fprintf(stderr, "Order of search will be ");
    for (i = 0; i < 26; i++)
 fputc(((achByFrequency[i])+'a'), stderr);
    fputc('\n', stderr);
}

int fInteractive;

_Array_ptr<char> GetPhrase(_Array_ptr<char> pch : count(size), int size) : count(size) {
    if (fInteractive) printf(">");
    fflush(stdout);
    if (fgets(pch, size, stdin) == ((void*)0)) {
#ifdef PLUS_STATS


#endif 
 exit(0);
    }
    return(pch);
}

char achPhrase _Nt_checked[255];

int main(int cpchArgc, _Array_ptr<_Nt_array_ptr<char>> ppchArgv : count(cpchArgc)) {

    if (cpchArgc != 2 && cpchArgc != 3)
        Fatal("Usage: anagram dictionary [length]\n", 0);

    if (cpchArgc == 3)
 cchMinLength = atoi(ppchArgv[2]);

    fInteractive = isatty(1);

    ReadDict(ppchArgv[1]);

    while (GetPhrase(&achPhrase[0], sizeof(achPhrase)) != ((void*)0)) {
        if (((*__ctype_b_loc ())[(int) ((achPhrase[0]))] & (unsigned short int) _ISdigit)) {
            cchMinLength = atoi(achPhrase);
            printf("New length: %d\n", cchMinLength);
        } else if (achPhrase[0] == '?') {
            DumpCandidates();
        } else {
            BuildMask(&achPhrase[0]);
            AddWords();
            if (cpwCand == 0 || cchPhraseLength == 0) continue;


            cpwLast = 0;
            SortCandidates();
            if (_setjmp (jbAnagram) == 0)
                FindAnagram(_Assume_bounds_cast<_Array_ptr<Quad>>(&aqMainMask[0],  count(2)), &apwCand[0], 0);

        }
    }
    return 0;
}
