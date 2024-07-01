#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"project.h"

Status update(hash_t hashtable[],file_node **bkhead,file_node **head)
{
    for(int a=0; a<=27; a++)
    {
        if(hashtable[a].link != NULL)
        {
            printf("ERROR: Database is not empty . Can't update\n");
            return FAILURE;
        }
    }
    char backup[100];
    printf("Enter the file to be updated in database: ");
    scanf("%s", backup);
    char ch1,ch2;
    //validation part for file extension and format
    if(strchr(backup, '.') == NULL)
    {
        printf("ERROR: Please pass extension alongwith filename for %s\n", backup);
        return FAILURE;
    }
    else
    {
        if(strcmp(strstr(backup, "."),".txt")  != 0)        //checking the file is with ".txt" extension
        {
            printf("ERROR! Please pass file name with correct extension for %s Usage: file.txt\n", backup);
            return FAILURE;
        }
        else
        {
            FILE *back_fptr = fopen(backup, "r");
            fscanf(back_fptr,"%c", &ch1);
            fseek(back_fptr, -2, SEEK_END);
            fscanf(back_fptr,"%c", &ch2);
            fseek(back_fptr, 0, SEEK_SET);
            if(ch1 == '#' & ch2 == '#')
            {
                char str[100];
                int index;
                while(fscanf(back_fptr,"%s",str) != EOF)       //reading each line of backup file
                {
                    index = atoi(strtok(str+1,";"));
                    if(hashtable[index].link == NULL)
                    {
                                                               //creating mainnode
                        main_t *mnew = malloc(sizeof(main_t));
                        if(mnew == NULL)
                        {
                            printf("ERROR: No space for dynamic memory allocation of mainnode\n");
                            return FAILURE;
                        }
                                                               //updating values
                        strcpy(mnew ->word,strtok(NULL,";"));
                        mnew ->filecount = atoi(strtok(NULL,";"));
                       
                        mnew ->mlink = NULL;
                        for(int i =1; i<= mnew->filecount; i++)
                        {
                                                                //creating subnode
                            sub_t *snew = malloc(sizeof(sub_t));
                            if(snew == NULL)
                            {
                                printf("ERROR: No space for dynamic memory allocation of subnode\n");
                                return FAILURE;
                            }
                            sub_t * sptr;
                            sub_t *sprev = sptr;
                            sptr = snew;
                            strcpy(snew->filename,strtok(NULL,";"));
                            if(check_duplicates(*bkhead, snew ->filename) == SUCCESS)
                            {
                                insert_at_last(bkhead,snew ->filename);
                            }                                  //creting backup list
                            snew ->wordcount = atoi(strtok(NULL,";"));
                            snew ->slink = NULL;
                            if(i == 1)
                            {
                                mnew ->slink = snew;
                            }
                            else
                            {
                                sprev ->slink = snew;
                            }
                        }
                        hashtable[index].link = mnew;
                    }
                    else
                    {
                        main_t *main = hashtable[index].link;       //temporary pointer for main node
                        main_t *mprev = NULL;            //previous pointer for mainnode
                                                           //traversing the loop
                        while(main != NULL)
                        {
                            mprev = main;
                            main = main ->mlink;
                        }
                                                            //create mainnode
                        main_t *mnew = malloc(sizeof(main_t));
                        if(mnew == NULL)
                        {
                            printf("ERROR: No space for dynamic memory allocation of mainnode\n");
                            return FAILURE;
                        }
                                                           //updating values
                        strcpy(mnew->word,strtok(NULL,";"));
                        mnew->filecount = atoi(strtok(NULL,";"));
                        mnew->mlink = NULL;
                        for(int i =1; i<= mnew->filecount; i++)
                        {
                                                           //create subnode
                            sub_t *snew = malloc(sizeof(sub_t));
                            if(snew == NULL)
                            {
                                printf("ERROR: No space for dynamic memory allocation of subnode\n");
                                return FAILURE;
                            }
                            sub_t *sptr;
                            sub_t *sprev = sptr;
                            sptr = snew;
                            //update subnode values
                            strcpy(snew ->filename,strtok(NULL,";"));
                            //create backup list if necessary
                            if(check_duplicates(*bkhead, snew->filename)==SUCCESS)
                            {
                                 insert_at_last(bkhead,snew->filename);
                            }                                 //creting backup list
                            snew ->wordcount = atoi(strtok(NULL,";"));
                            snew ->slink = NULL;
                            if(i==1)
                            {
                                mnew->slink = snew;
                            }
                            else
                            {
                                sprev->slink = sptr;
                            }
                        }  //link new main node to the end
                        mprev->mlink = mnew;
                    }
                }
                                                         //removing updated filenames for list
                file_node *temp1 = *head;
                file_node *prev = NULL;
                file_node *flist = *head;               //initialixzing the variables
                while(temp1 != NULL)
                {
                    file_node *temp  = *bkhead;
                    int found = 0;
                    while(temp != NULL)
                    {
                        if(strcmp(temp1->filename,temp->filename) == 0)       //compare the file names
                        {
                            found = 1;
                            break;
                        }
                        temp = temp->link;
                    }
                    if(found)                                             
                    {
                          if(prev == NULL)             
                        {
                            *head = (*head) ->link;
                            free(temp1);
                            temp1 =*head;
                        }
                        else
                        {
                            prev ->link = temp1 ->link;
                            free(temp1);
                            temp1 = prev ->link;
                        }
                    }
                    else
                    {
                        prev = temp1;
                        temp1 = temp1 ->link;
                    }
                }
            }
            else
            {
                printf("ERROR: Please pass a correct backup file\n");
                return FAILURE;
            }
        }
    }
}


