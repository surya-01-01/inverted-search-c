/*
------------------------------------------------------------------------------------------
NAME : SURYA G
DATE : 05-03-2025
DESCRIPTION : The purpose of storing an index is to optimize speed and performance in finding relevant documents for a search query.
Without an index, the search engine would scan every document in the corpus, 
which would require considerable time and computing power.
------------------------------------------------------------------------------------------
*/
#include "invert.h"

int cflag=0,uflag=0;
int main(int argc,char *argv[])
{
    Flist *file_name=NULL;//Linked list to store file names
    char choice;
    main_node *hash_t[27]={NULL}; // Hash table to store data, initialized to NULL
    if(argc<1)
    {
        printf("less number of arguments.\n");
        return 1;
    }
    else
    {
        if(validate_arg(argc,argv,&file_name))// Validate the arguments and file names
        {
            if(print_file_names(file_name))// Print the valid file names 
            {
                printf("\033[1;34mVALIDATION IS DONE\033[0m\n");
            }
        }
        else
        {
            printf("\033[1;31mNO VALID FILES TO OPERATE\033[0m\n");
        }
    }
    int option;
    while (1)// Infinite loop to show options until user chooses to exit
    {
        printf("Select your choice among following options:\n");
        printf("1.Create DATABASE\n2.Display DATABASE\n3.SEARCH\n4.SAVE\n5.Update DATABASE\n");
        printf("Enter your option\n");
        scanf("%d", &option);// User input for option
        switch (option)
        {
        case 1:
           /* Create the database if not already created */
            if(cflag==0)
            {
                if (create_ht(file_name, hash_t)) // Create hash table if not created
                {
                    printf("\033[1;34mSucessful : Creation of DATABASE\033[0m\n");
                    cflag++;// Set flag indicating database is created
                }
            }
            else
            {
                printf("\033[1;31mAlready DATABASE created for these files\033[0m\n");
            }
            break;
        case 2:
            if (display_ht(hash_t))// Display the hash table
            {
                printf("CONTENTS DISPLAYED\033[0m\n");
            }
            break;
        case 3:
            char str[20];
            printf("Enter the word to search\n");
            scanf("%s", str);// User input for word to search
            if (search_ht(str, hash_t))// User input for word to search
            {
                printf("CONTENT DISPLAYED\n");
            }
            else
            {
                printf("Word not found\n");
            }
            break;
        case 4:
            char temp[20];
            printf("Enter the .txt filename to save data\n");
            scanf("%s", temp);// User input for filename to save data
            char *ch;
            if (ch = strstr(temp, ".txt"))// Check if the filename contains with .txt
            {
                if (strcmp(ch, ".txt") == 0)// Check if the filename ends with .txt

                {
                    if (save_ht(hash_t, temp))// Save the hash table to the file
                    {
                        printf("SAVED SUCCESSFULLY\n");
                    }
                    else
                        printf("SAVING FAILED\n");
                }
                else
                {
                    printf("INVALID FILE NAME\n");
                }
            }
            else
            {
                printf("INVALID FILE NAME\n");
            }
            break;
        case 5:
            if (uflag==0 && cflag==0)// Check if database creation is done before updating
            {
                char src_file[20];
                printf("Enter the .txt filename to update database\n");
                scanf("%s", src_file);// User input for filename to update database
                if (ch = strstr(src_file, ".txt")) // Check if the filename ends with .txt
                {
                    if (strcmp(ch, ".txt") == 0)
                    {
                        if (update_ht(hash_t, src_file,&file_name))// Update the hash table from the file
                        {
                            printf("\033[1;34mUPDATED SUCCESSFULLY\033[0m\n");
                            uflag++; // Set flag indicating update
                        }
                        else
                            printf("UPDATING FAILED\n");
                    }
                    else
                    {
                        printf("INVALID FILE NAME\n");
                    }
                }
                else
                {
                    printf("INVALID FILE NAME\n");
                }
            }
            else
            {
                printf("\033[1;31mUpdate DATABASE not possible\033[0m\n");
            }
            break;
        default:
            printf("enter valid option\n");
            break;
        }
        do
        {
            printf("Do you want to continue?\n");
            printf("Enter y/Y to continue and n/N to discontinue\n");
            scanf(" %c", &choice);// User input to continue or discontinue
            if (choice == 'y'||choice=='Y')
                continue;
            else if (choice == 'n'||choice=='N')
            {
                printf("\n...Thanks For Suppoting Us...\n...Have a Nice Day...\n");
                exit(EXIT_SUCCESS);
            }
            else
                printf("INVALID INPUT TRY AGAIN\n");
        } while (choice != 'y' && choice !='Y');
    }

    return 0;
}

int validate_arg(int argc,char *argv[],Flist **file_name)
{
    char *ch;
    int count=0;
    for(int i=1;i<argc;i++)// Loop through all arguments
    {
        if ((ch = strstr(argv[i], ".txt")))// Check if the argument is a .txt file
        {
            if (strcmp(ch, ".txt") == 0)
            {
                if(open_files(argv[i]))// Open the file
                {
                    if(create_node_fname(file_name,argv[i]))// Insert file name into the linked list
                    {
                        printf("\033[1;35mSuccessful:Inserting file name : %s into file linked list\033[0m\n",argv[i]);
                        count++;
                    }
                }
            }
            else
            {
                printf("\033[1;31mERROR-->not a valid text file\033[0m\n");
                continue;
            }
        }
        else
        {
            printf("\033[1;31ERROR-->not a  text file\033[0m\n");
            continue;
        }
    }
    if(count==0)
        return 0;
    return 1;
}

int create_node_fname(Flist **file_name,char *argv)
{
    Flist *new=malloc(sizeof(Flist)); // Allocate memory for new file node
    if(new == NULL)
        return 0;
    strcpy(new->files,argv);// Copy file name into the node
    new->link=NULL;// Set the link points to NULL
    if((*file_name)==NULL)
    {
        *file_name=new;// If list is empty, set new node as the head
        return 1;
    }
    Flist *temp=*file_name;
    Flist *prev=NULL;
    while(temp)
    {
        if(strcmp(temp->files,argv)==0)// Check if the file already exists in the list
        {
            printf("FILE ALREADY FOUND>>>SKIPPED\n");
            free(new);// Free the allocated memory if file is duplicate
            return 0;
        }
        prev=temp;
        temp=temp->link;
    }
    if(prev)
        prev->link=new;// Insert the new node at the end of the list
    else
        temp->link=new;
    return 1;
}

int print_file_names(Flist *file_name)
{
    Flist *temp=file_name;
    if(temp==NULL)
    {
        printf("EMPTY");// If no files in the list, print "EMPTY"
        return 0;
    }
    while(temp)
    {
        printf("%s\n",temp->files);// Print each file name in the list
        temp=temp->link;
    }
    return 1;
}

int open_files(char *argv)
{
    //int size;
    FILE *fptr=fopen(argv,"r");// Open the file in read mode
    if (fptr== NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n",argv);
    	return 0;
    }
    //fseek(fptr,1,SEEK_SET);
    //size=ftell(fptr);
    //printf("%d ",size);
    //fread(&ch,1,1,fptr);
    char ch=fgetc(fptr);
    if(ch==EOF)
    {
        printf("EMPTY FILE>>>>SKIPPED\n"); // If the file is empty, print a message
        return 0;
    }
    return 1;
}