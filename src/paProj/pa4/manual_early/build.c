
#include "build.h"
#include "hbt.h"
#include "pa4.h"
#include "manip.h"
//building  tree from input file

#pragma CHECKED_SCOPE on

_Ptr<Tnode> buildFromFile(_Ptr<FILE> fh, _Ptr<int> formatScore)
{
    _Ptr<Tnode> newRoot = malloc<Tnode>(sizeof(*newRoot));

    char code = '\0';
    int read;

    if(!feof(fh))
    {
        read = fread(&(newRoot -> key), sizeof(int), 1, fh);
        if(read !=  1)
        {
            *formatScore = 0;
            _Unchecked {
							fprintf(stderr, "failed to read key in BFF\nread: %d\n", read);
            }
						return NULL;
        }
        read = fread(&code, sizeof(char), 1, fh);
        if(read !=  1)
        {
            *formatScore = 0;
            _Unchecked {
							fprintf(stderr, "failed to read code in BFF\nread: %d\n", read);
            }
						return NULL;
        }
    }


    newRoot -> left = NULL;
    newRoot -> right = NULL;

    if(code == 3 || code == 2)
    {
        newRoot -> left = buildFromFile(fh, formatScore);
    }
    if(code == 3 || code == 1)
    {
        newRoot -> right = buildFromFile(fh, formatScore);
    }
    return newRoot;
}

int buildFromOps(_Ptr<FILE> fh, _Ptr<Tnode> root, _Nt_array_ptr<char> outputFile)
{
    int key;
    char op;
    int read;
    _Ptr<FILE> writeFile = fopen(outputFile, "wb");
    while(!feof(fh))
    {
            read = fread(&key, sizeof(int), 1, fh);
            if(read != 1 && !feof(fh))
            {
                _Unchecked {
									fprintf(stdout, "%d\n", 0);
                }
								printTreeOutput(root, writeFile);
                return EXIT_FAILURE;
            }

            read = fread(&op, sizeof(char), 1, fh);
            if(read != 1 && !feof(fh))
            {
                _Unchecked {
									fprintf(stdout, "%d\n", 0);
                }
								printTreeOutput(root, writeFile);
                return EXIT_FAILURE;
            }
            
            if(!feof(fh))
            {     
                
                if(op == 'i')
                {
                    //Tnode* previous = NULL;
                    //fprintf(stderr, "\ninsert: %d\n", key);
                    root = insertKey(root, key);
                    //fprintf(stderr, "post insertKey call\n");
                   	//printTree(root);
                    //fprintf(stderr, "\n");
                }
                if(op == 'd')
                {
                    //fprintf(stderr, "pre deleteKey call: %d\n", key);
                    //printTree(root);
                    //fprintf(stderr, "\n");
                    root = deleteKey(root, key);
                    //fprintf(stderr, "post deleteKey call\n");
                    //printTree(root);
                    //fprintf(stderr, "\n");
                    
                }
            }
    }

    printTreeOutput(root, writeFile);

    fclose(writeFile);

    // printTree(root);

    destroyTree(root);

    return EXIT_SUCCESS;
}

void destroyTree(_Ptr<Tnode> root)
{
    if(root == NULL)
        return;
    destroyTree(root -> left);
    destroyTree(root -> right);
    free<Tnode>(root);
    return;
}
