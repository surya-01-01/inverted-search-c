#include "invert.h"

int save_ht(main_node **hash_t, char *newfile)
{
    FILE *fptr = fopen(newfile, "w");
    if (fptr == NULL)
        return 0;
    for (int i = 0; i < 27; i++)
    {
        if (hash_t[i] != NULL)
        {
            main_node *mtemp = hash_t[i];
            while (mtemp)
            {
                sub_node *stemp = mtemp->sublink;
                fprintf(fptr,"#%d;%s;%d;",i,mtemp->word,mtemp->filecount);
                while (stemp)
                {
                    fprintf(fptr,"%s;%d;",stemp->filename,stemp->wordcount);
                    stemp = stemp->sublink;
                }
                fprintf(fptr,"#\n");
                mtemp = mtemp->mainlink;
            }
        }
    }
    fclose(fptr);
    return 1;
}