#include "invert.h"

int create_ht(Flist *file_name,main_node *hash_t[])
{
    char buffer[20];// Buffer to store each word read from the file
    while(file_name) // Traverse through the linked list of files
    {
        FILE *fptr=fopen(file_name->files,"r");// Open the current file
        while (fscanf(fptr, "%s", buffer) == 1) { // Read each word from the file
            //printf("BUFFER-->%s\n",buffer);
            find_index_storing(buffer,hash_t,file_name->files);// Find the index and store word in the hash table
        }
        fclose(fptr);// Close the current file
        file_name=file_name->link;// Move to the next file in the linked list
    }
    return 1;
}

int find_index_storing(char *buffer,main_node **hast_t,char *files)
{
    char ch=buffer[0];// First character of the word
    int ind;
    if((ch>='a'&& ch<='z')||(ch>='A'&& ch<='Z'))// If the character is a letter
    {
        if(isupper(ch))// If the letter is uppercase
            ind=ch-'A';// Index based on uppercase letter
        else
            ind =ch-32-'A';// Index based on lowercase letter(convert to uppercase index)
    }
    else
        ind=26; // If it's not a letter, place in the 27th index
    //printf("index-->%d \n",ind);
    create_mainnode(buffer,hast_t,ind,files);// Create the main node for this word at the calculated index
    return 1;
}

int create_mainnode(char *buffer,main_node **hast_t,int ind,char *files)
{
    if(hast_t[ind]==NULL)// If no node exists at the index
    {
        main_node *newM=malloc(sizeof(main_node));// Create a new main node
        newM->filecount=1;// Initialize file count to 1
        newM->mainlink=NULL;// No other main node links yet
        strcpy(newM->word,buffer);// Store the word

        sub_node *newS=malloc(sizeof(sub_node));// Create a new sub node
        newS->wordcount=1;// Initialize word count to 1
        strcpy(newS->filename,files);// Store the filename in the sub node
        newS->sublink=NULL;// No other sub node links yet
        newM->sublink=newS;// Link the sub node to the main node
        hast_t[ind]=newM;// Set the new main node in the hash table at the correct index
        return 1;
    }
    main_node *main_temp=hast_t[ind];// Traverse through existing main nodes at this index
    main_node *main_prev=NULL;
    while(main_temp)// Traverse through all the main nodes
    {
        sub_node *sub_temp=main_temp->sublink;// Traverse through the sub nodes for this word
        sub_node *sub_prev=NULL;
        if(strcmp(buffer,main_temp->word)==0)// If the word already exists in the main node
        {
            while(sub_temp)// Traverse through all sub nodes for this word
            {
                if(strcmp(sub_temp->filename,files)==0)// If the file already exists for this word
                {
                    sub_temp->wordcount++;// Increment the word count
                    //printf("wordcount->%s-%s %d\n",sub_temp->filename,files,sub_temp->wordcount);
                    return 1;// Return after updating word count
                }
                sub_prev=sub_temp;
                sub_temp=sub_temp->sublink;
            }
                sub_node *newS=malloc(sizeof(sub_node)); // Create a new sub node for this file
                newS->wordcount=1;// Initialize word count to 1
                strcpy(newS->filename,files);// Store the filename in the sub node
                newS->sublink=NULL;// No further sub node links
                sub_prev->sublink=newS;// Link the new sub node
                main_temp->filecount++; // Increment the file count for this word
                return 1; // Return after inserting 
        }
        main_prev=main_temp;
        main_temp=main_temp->mainlink;// Move to the next main node
    }
        main_node *newM=malloc(sizeof(main_node));// Create a new main node for this word
        newM->filecount=1;// Initialize file count to 1
        newM->mainlink=NULL;// No further main node links
        strcpy(newM->word,buffer);// Store the word

        sub_node *newS=malloc(sizeof(sub_node));// Create a new sub node for this file
        newS->wordcount=1;// Initialize word count to 1
        strcpy(newS->filename,files);// Store the filename in the sub node
        newS->sublink=NULL;// No further sub node links
        newM->sublink=newS;// Link the sub node 
        main_prev->mainlink=newM; // Link the new main node to the previous main node
        return 1;
}

