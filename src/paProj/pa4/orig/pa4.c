#include "hbt.h"
#include "pa4.h"
#include "build.h"
#include "manip.h"

int main(int argc, char** argv)
{
    if(argc != 3 && argc != 4)
    {
        fprintf(stderr, "incorrect number of inputs\n");
        return EXIT_FAILURE;
    }

    if(0 == strcmp(argv[1], "-e"))
    {
        int evalCheck;
        
        Tnode* root = NULL;

        evalCheck = evaluate(argv[2], root);
        
        if(evalCheck != EXIT_SUCCESS)
        {
            return EXIT_FAILURE;
        }
    }

    if(0 == strcmp(argv[1], "-b"))
    {
        int buildFromOpsCheck;

        FILE* fh = fopen(argv[2], "rb");

        if(fh == NULL)
        {
            fprintf(stdout, "%d\n", -1);
            return EXIT_FAILURE;
        }

        Tnode* root = NULL;

        buildFromOpsCheck = buildFromOps(fh, root, argv[3]);

        if(buildFromOpsCheck == EXIT_FAILURE)
        {
            return EXIT_FAILURE;
        }

        fclose(fh);
    }

    fprintf(stdout, "%d\n", 1);
    return EXIT_SUCCESS;

}
