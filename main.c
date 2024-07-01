#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "project.h"

int main(int argc, char *argv[]) 
{
    file_node *head = NULL;
    file_node *bkhead=NULL;
    int opt,set=0;;
    char str[20],choice;
    hash_t hashtable[28];
    file_node *temp=head;
    for(int i=0;i<28;i++)                                             //creating hashtable
    {
        hashtable[i].index=i;
        hashtable[i].link=NULL;
    }
    if (argc < 2)                                                     //checking argument count
    {
        printf("No file specified through argument\n");
        return FAILURE;
    }
    if (validation(argv,&head) == SUCCESS)                           //checking files is valid or not
    {
        printf("INFO: Validation successful\n");
    }
    else 
    {
        printf("ERROR: Validation failed\n");
    }
    do
    {
        printf("1.Create database:\n");
        printf("2.display database:\n");
        printf("3.search database:\n");
        printf("4.save database:\n");
        printf("5.update database:\n");
        printf("\nEnter the option\n");
        scanf("%d",&opt);
        switch (opt)
        {
            case 1:if(!set)    //creating database
                {

                if (create_HT(&head,hashtable)== SUCCESS)
                {

                    printf("INFO: Create Database successful\n");
                    set=1;
                }
                else 
                {
                    printf("ERROR: Create Database failed\n");
                }
                }
                else
                {
                    printf("ERROR:Create Database is already done\n");
                }

                break;
            case 2://display database
                if (display_hash_table(hashtable)== SUCCESS)
                {
                    printf("INFO: Display Database successful\n");
                }
                else 
                {
                    printf("ERROR: Display Database failed\n");
                }
                break;
            case 3://searching word in database
                printf("enter the word to search:");
                scanf("%s",str);
                search_word(hashtable,str);
                break;
            case 4://saving database
               
                if( save_hash_table(hashtable)!=FAILURE)
                {
                    printf("save is successfull\n");
                }
                else
                {
                    printf("save is not success\n");
                }
                break;
            case 5://update database
                if(update(hashtable,&bkhead,&head)!=FAILURE)
                {
                    printf("Update is successfull\n");
                }
                else
                {
                    printf("Update is not success\n");
                }
                break;
           default://condition for invalid option
                printf("ERROR:Invalid input\n");
        }
        printf("Do you want to continue?\n");
        printf("Enter y/Y to continue and n/N to discontinue\n");
        scanf(" %c",&choice);

    } while(choice=='y' || choice=='Y');

    return 0;
}
































