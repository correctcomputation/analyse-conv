
#include "build.h"
#include "hbt.h"
#include "pa4.h"
#include "manip.h"
//building  tree from input file
Tnode* buildFromFile(FILE* fh, int* formatScore)
{
    Tnode* newRoot = malloc(sizeof(*newRoot));

    char code;
    int read;

    if(!feof(fh))
    {
        read = fread(&(newRoot -> key), sizeof(int), 1, fh);
        if(read !=  1)
        {
            *formatScore = 0;
            fprintf(stderr, "failed to read key in BFF\nread: %d\n", read);
            return NULL;
        }
        read = fread(&code, sizeof(char), 1, fh);
        if(read !=  1)
        {
            *formatScore = 0;
            fprintf(stderr, "failed to read code in BFF\nread: %d\n", read);
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

int buildFromOps(FILE* fh, Tnode* root, char* outputFile)
{
    int key;
    char op;
    int read;
    FILE* writeFile = fopen(outputFile, "wb");
    while(!feof(fh))
    {
            read = fread(&key, sizeof(int), 1, fh);
            if(read != 1 && !feof(fh))
            {
                fprintf(stdout, "%d\n", 0);
                printTreeOutput(root, writeFile);
                return EXIT_FAILURE;
            }

            read = fread(&op, sizeof(char), 1, fh);
            if(read != 1 && !feof(fh))
            {
                fprintf(stdout, "%d\n", 0);
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

void destroyTree(Tnode* root)
{
    if(root == NULL)
        return;
    destroyTree(root -> left);
    destroyTree(root -> right);
    free(root);
    return;
}
