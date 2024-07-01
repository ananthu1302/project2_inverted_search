#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "project.h"



Status create_HT(file_node **head,hash_t hashtable[])
{ 
    if(*head==NULL)
{
printf("ERROR:database is already created\n");
return FAILURE;
}
    file_node *temp=*head;

    int index,mflag=0,sflag=0;

    while(temp!=NULL)  //treverse through the linked list of files
    {
        char word[200];//to store file content

        FILE *file=fopen((temp->filename),"r");
        while(fscanf(file,"%s",word)!=EOF)     //determine the index for the hash table
        {
            if( isalpha(word[0]))
            {
                index=tolower(word[0])-97;
            }
            else if(isdigit(word[0]))
            {
                index=27;
            }
            else
            {
                index=26;
            }
        if(hashtable[index].link==NULL)        //if the index in the hash table is empty
        {                                 //create new main node and sub node
            main_t *m_new=malloc(sizeof(main_t));
            sub_t *s_new=malloc(sizeof(sub_t));
            if(m_new==NULL)
            {
                //print error msg
                return FAILURE;
            }
            if(s_new==NULL)
            {//print error msg
                return FAILURE;
            }
            strcpy(m_new->word,word);          //initialize main node
            m_new->filecount=1;
            m_new->mlink=NULL;
            m_new->slink=s_new;
            s_new->wordcount=1;               //initialize the sub node
            strcpy(s_new->filename,temp->filename);
            s_new->slink=NULL;
            hashtable[index].link=m_new;      //update the hashtable
        }
        else
        {       //traverse through the main node in the hash table
            main_t *main=hashtable[index].link;
            sub_t *sub=main->slink;
            sub_t *sprev=NULL;
            main_t *mprev=NULL;
            while(main != NULL)
            {          //check if the word already exist or not
                if(strcmp(word,main->word) == 0)
                {
                    sub=main->slink;
                    mflag=1;
                    break;
                }
                else
                {
                    mflag=0;
                }
 		mprev=main;
                main=main->mlink;
            }
            if(mflag)
            {    //if the word exist check for the file in sun node
                while(sub != NULL)
                {
                    if(strcmp(temp->filename,sub->filename) == 0)
                    {
                        sflag=1;
                        break;
                    }
                    else
                    {
                        sflag=0;
                    }
                    sprev=sub;
                    sub=sub->slink;
                }
                if(sflag)
                {         //if the file exist  update word count
                    sub->wordcount +=1;
                }
                else     //if file doesn't exist ,create new sub node
                {
                    sub_t *snew=malloc(sizeof(sub_t));
                    if(snew == NULL)
                    {
                        printf("ERROR: No space \n");
                        return FAILURE;
                    }
                    snew ->wordcount=1;
                    strcpy(snew ->filename,temp->filename);
                    snew->slink=NULL;
                    sprev->slink=snew;
                    main->filecount +=1;
                }
            }
            else     //if the word doesn't exist create main node and sub node
            {
                sub_t *snew=malloc(sizeof(sub_t));
                if(snew==NULL)
                {
                    return FAILURE;
                }
                snew->wordcount=1;
                strcpy(snew->filename,temp->filename);
                snew->slink=NULL;
                main_t *mnew=malloc(sizeof(main_t));
                if(mnew == NULL)
                {
                    printf("ERROR: No space\n");
                    return FAILURE;

                }
                mnew->filecount=1;
                strcpy(mnew->word,word);
                mnew->slink=snew;
                mnew->mlink=NULL;
		mprev->mlink=mnew;
              }
            }

        }

        temp=temp->link;    //move to the next file

    }
    
    return SUCCESS;
}



Status display_hash_table(hash_t hashtable[])
{
    main_t *mainptr;
    sub_t *subptr;
    for(int i=0;i<28;i++)
    {
        if(hashtable[i].link != NULL)
        {
            mainptr=hashtable[i].link;   //traverse through the main nodes in the hashtable
            while(mainptr !=NULL)
            {
              printf("Index: %d         ",i);
              printf("word:%s           ",mainptr->word);
              printf("filecount:%d      ",mainptr->filecount);
              subptr=mainptr->slink;
              while(subptr!=NULL)      //traverse throgh the subnode in the main node
              {
                  printf("filename:%s          ",subptr->filename);
                  printf("wordcount:%d         ",subptr->wordcount);
                  subptr=subptr->slink; 
              }
              printf("\n");
              mainptr=mainptr->mlink;
            }
        }
    }
return SUCCESS;
}



