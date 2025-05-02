#include "invert.h"

int update_ht(main_node**hash_t,char *src_file,Flist **file_name)
{
    int ind,filecnt,wordcnt;
    char word[20],filename[20];
    FILE *fptr=fopen(src_file,"r");// Open the backup file for reading
    if(fptr==NULL)// If the file can't be opened
    {
        printf("Backup file is not found\n");// Print an error message
        return 0;// Return failure
    }
    char st,end;
    st=fgetc(fptr); // Read the first character
    fseek(fptr,-2,SEEK_END);// Move to the second last character in the file
    end=fgetc(fptr);// Read the second last character
    rewind(fptr);// Move the file pointer to the beginning
    if(st!=end)// If the first and second last characters are not the same
    {
        return 0;// Return failure
    }

    // Read the content of the backup file
    while(!feof(fptr))
    {
        main_node *main_temp=NULL,*main_prev=NULL;
        fscanf(fptr, "#%d;%[^;];%d;",&ind, word, &filecnt);// Read the index, word, and file count
        main_node *newM = malloc(sizeof(main_node));// Allocate memory for a new main node
        newM->filecount = filecnt;// Set the file count
        newM->mainlink = NULL;// No next main node yet
        newM->sublink=NULL;// No sub nodes yet
        strcpy(newM->word, word);// Copy the word into the main node

        if (hash_t[ind] == NULL) // If no node exists at this index in the hash table
        {
            hash_t[ind]=newM;// Set the new node as the first node at this index
        }
        else
        {
            main_temp=hash_t[ind]; // Set the temporary pointer to the first node
            main_prev=NULL;
            while(main_temp)// Traverse to the last main node 
            {
                main_prev=main_temp;
                main_temp=main_temp->mainlink;
            }
            main_prev->mainlink=newM;// Link the new node to the last main node
        }

        for(int i=0;i<filecnt;i++)// Loop through all files for the current word
        {
            fscanf(fptr,"%[^;];%d;",filename,&wordcnt);// Read the filename and word count
            Flist *temp=*file_name,*prv=*file_name;
            while(temp)
            {
                if(strcmp(temp->files,filename)==0) // If the file matches
                {
                    if(prv==(*file_name)) // If it's the first file in the list
                    {
                        *file_name=temp->link;// Update the file list head
                    }
                    else
                    {
                        prv->link=temp->link; // Remove the file from the list

                    }
                    free(temp);// Free the memory for the removed file
                    break;
                }
                 prv=temp;
                 temp=temp->link;
            }
            sub_node *newS=malloc(sizeof(sub_node));// Create a new sub node
            newS->wordcount=wordcnt; // Set the word count for the sub node
            strcpy(newS->filename,filename);// Set the filename for the sub node
            newS->sublink=NULL; // No next sub node yet
            if(newM->sublink==NULL)// If no sub node exists for this word
            {
                newM->sublink=newS;// Set the new sub node as the first sub node
            }
            else
            {
                sub_node *sub_temp=newM->sublink;
                sub_node *sub_prev=NULL;
                while (sub_temp)// Traverse to the last sub node for this word
                {
                    sub_prev = sub_temp;
                    sub_temp = sub_temp->sublink;
                }
                sub_prev->sublink = newS;// Link the new sub node to the last sub node
            }
        }
        fscanf(fptr,"#\n");// Skip the ; and \n
    }
    return 1;// Return success

}