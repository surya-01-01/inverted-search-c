#include "invert.h"

int display_ht(main_node **hash_t)
{
    // Display the header for the table
    printf("\033[1;34m|Index|\t|%-10s|\t|%-10s|\t|%-10s| |Word count|\033[0m\n","Word","File count","File name");

    // Loop through all 27 possible indices in the hash table
    for (int i = 0; i < 27; i++)
    {
        if(hash_t[i]!=NULL)// If there are nodes at this index
        {
            main_node *mtemp=hash_t[i];// Set a temporary pointer to the main node at this index
            while(mtemp)// Traverse through all main nodes at this index
            {
                sub_node *stemp=mtemp->sublink;// Set a pointer to the first sub node for the current main node
                printf("\033[1;35m[%d]\t[%-10s]\t%d file/s:\t",i,mtemp->word,mtemp->filecount);
                while(stemp)// Traverse through all sub nodes for the current main node
                {
                    printf("%-10s %d  ",stemp->filename,stemp->wordcount);
                    stemp=stemp->sublink;// Move to the next sub node
                }
                mtemp=mtemp->mainlink;// Move to the next main node at the current index
                printf("\n");
            }
        }
    }
    return 1; // Return success
}