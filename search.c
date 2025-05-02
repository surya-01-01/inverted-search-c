#include "invert.h"

int search_ht(char *str,main_node**hash_t)
{
    int ind;
    char ch=str[0];// Get the first character of the search string

    // Check if the first character is a letter (either uppercase or lowercase)
    if((ch>='a'&& ch<='z')||(ch>='A'&& ch<='Z'))
    {
        if(isupper(ch))// If the character is uppercase
            ind=ch-'A'; // Convert the letter to an index (0-25 for A-Z)
        else
            ind =ch-32-'A';// Convert lowercase letter to an index (0-25 for a-z)
    }
    else
        ind=26;// If the first character is not a letter, set the index to 26

    
    if(hash_t[ind]!=NULL)// If the hash table at this index is not empty
    {
            main_node *mtemp=hash_t[ind];// Set a temporary pointer to the first main node at this index
            while(mtemp)// Traverse
            {
                if(strcmp(mtemp->word,str)==0)// If the word matches the search string
                {
                    printf("\033[1;36m%s found in %d files in %d index\033[0m\n",str,mtemp->filecount,ind);// Print the word and the number of files 
                    sub_node *stemp=mtemp->sublink;// Set a pointer to the sub nodes of the current main node
                    while(stemp)// Traverse through all the sub nodes
                    {
                        printf("WORDCOUNT:%d IN %s FILE\n",stemp->wordcount,stemp->filename);// Print the word count and filename for each sub node
                        stemp=stemp->sublink; // Move to the next sub node
                    }
                    return 1;// Return success
                }
                mtemp=mtemp->mainlink; // Move to the next main node if no match was found
                printf("\n");
            }
        return 0;// Return failure
    }
    else
    {
        return 0;// Return failure
    }
}