#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"project.h"
int flag;
Status validation(char *argv[],file_node **head)
{
      int i=1;
      if(argv[i] == NULL)            //checking command line argument
      {
            printf("ERROR: Please pass sufficient command line arguments ,usage:./a.out file1.txt\n");
            return FAILURE;
      }
      while(argv[i] != NULL)
      {
            if(strchr(argv[i],'.') == NULL)        //checking argument is "." file
            {
                  printf("ERROR: Please pass extension along with %s filename\n",argv[i]);
                  i++;
                  continue;
                  //return FAILURE;
            }
            else
            {
                  if(strcmp(strstr(argv[i],"."),".txt") == 0)    //checking argument is ".txt" file
                  {
                        printf("INFO: file %s is with correct extension\n",argv[i]);
                       //       strcpy(head->filename,argv[i]);
                        FILE *file=fopen(argv[i],"r");             //opening the file
                        if(file != NULL)
                        {
                              printf("INFO: File %s is exist\n",argv[i]);
                              fseek(file,0,SEEK_END);              //checking file empty or not
                              long size=ftell(file);
                              if(size != 0)
                              {
                                    printf("INFO:File %s is not empty\n",argv[i]);
                                    if(check_duplicates(*head,argv[i]) == SUCCESS)         //checking duplicate present or not
                                    {
                                          printf("INFO: Check duplicate for %s file is success\n",argv[i]);

                                          if(insert_at_last(head, argv[i]) == SUCCESS)    //inserting file to the linkedlist
                                          {
                                                printf("INFO: Inserted %s into the linked list\n",argv[i]);
                                                //i++;
                                                if(head!=NULL)
                                                flag=1;
                                                //return SUCCESS;
                                          }
                                          else
                                          {
                                                printf("ERROR: Insertion failed %s into the linked list\n",argv[i]);
                                                i++;
                                                continue;
                                                //return FAILURE;
                                          }
                                    }
                                    else
                                    {
                                          printf("ERROR: File name %s already exists\n",argv[i]);
                                          i++;
                                          continue;
                                    }
                              }
                              else
                              {
                                    printf("ERROR:File %s is empty\n",argv[i]);
                                    i++;
                                    continue;
                                   // return FAILURE;
                              }
                              fclose(file);
                        }
                        else
                        {
                              printf("ERROR: File %s not exist\n",argv[i]);
                              i++;
                              continue;
                              //return FAILURE;
                        }
            }
            i++;
            }

      }
      if(flag == 1)
      {
            return SUCCESS;
      }
      return FAILURE;
}

Status insert_at_last(file_node **head,char *argv)
{
      file_node *new=malloc(sizeof(file_node));
    if(new == NULL)                        //checking memory allocation done  or not
    {
        return FAILURE; 
    }
    new -> filename = argv;
    new -> link=NULL;
    if(*head == NULL)                   //insert at first if no element present
    {
        *head =new;
        return SUCCESS;
    }
    file_node *temp=*head;
    while(temp -> link != NULL)           //tarvel to the last and insert if list is not null
    {
        temp=temp -> link;
    }
    temp ->link=new;
    return SUCCESS;
}
Status check_duplicates(file_node *head,char *argv)
{
      file_node *temp=head;
      while(temp != NULL)
      {
            if(strcmp(temp->filename,argv) == 0)       //tarvel through the list and compare filename with current one
            {
                  return FAILURE;
            }
            temp=temp->link;
      }
      return SUCCESS;

}
