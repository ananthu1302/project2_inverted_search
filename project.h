#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum
{
    SUCCESS,   
    FAILURE    
}Status;

typedef struct filename
{
    char *filename;
    struct filename *link;
}file_node;

typedef struct hashtable
{
    int index;
    struct main_node *link;
}hash_t;

typedef struct main_node
{
    int filecount;
    char word[20];
    struct main_node *mlink;
    struct sub_node *slink;
}main_t;

typedef struct sub_node
{
    int wordcount;
    char filename[20];
    struct sub_node *slink;
}sub_t;


Status validation(char *argv[],file_node **head);
Status check_duplicates(file_node *head,char *argv);
Status insert_at_last(file_node **head,char *argv);
Status create_HT(file_node **head,hash_t hashtable[]);
Status  display_hash_table(hash_t hashtable[]);
Status  search_word(hash_t hashtable[], char *word);
Status save_hash_table(hash_t hashtable[]);
Status update(hash_t hashtable[],file_node **bkhead,file_node **head);
