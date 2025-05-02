#ifndef INVERT_H
#define INVERT_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>

#define ARR_SIZE 20

typedef struct node2
{
	char files[ARR_SIZE];
    struct node2 *link;
}Flist;

typedef struct node1{
    int wordcount;
    char filename[ARR_SIZE];
    struct node1 *sublink;   
}sub_node;

typedef struct node{
    int filecount;
    char word[ARR_SIZE];
    struct node1 *sublink;
    struct node *mainlink;
}main_node;

int validate_arg(int argc,char *argv[],Flist **file_name);
int print_file_names(Flist *file_name);
int create_node_fname(Flist **file_name,char *argv);
int open_files(char *argv);
int create_ht(Flist *file_name,main_node **hash_t);
int find_index_storing(char *buffer,main_node **hast_t,char *file_name);
int create_mainnode(char *buffer,main_node **hast_t,int ind,char *file_name);
int display_ht(main_node **hash_t);
int search_ht(char *str,main_node**hash_t);
int save_ht(main_node **hash_t,char *newfile);
int update_ht(main_node**hash_t,char *src_file,Flist **file_name);
//sub_node*  create_subnode(main_node **hast_t,Flist *file_name,int ind);
#endif
