#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "project.h"

Status search_word(hash_t hashtable[], char *word)
{
    int index;

    // Convert the first character of the word to lowercase
    if (isalpha(word[0]))
        index = tolower(word[0]) - 97;
    else if (isdigit(word[0]))
        index = 27;
    else
        index = 26;

    // Traverse through the hash table
    main_t *mainptr = hashtable[index].link;
    while (mainptr != NULL)       //treverse through the main node
    {
        if (strcmp(word, mainptr->word) == 0)  //compare the word and the word in main node
        {
            printf("Word found at index %d:\n", index);
            printf("Word: %s\n", mainptr->word);
            printf("File count: %d\n", mainptr->filecount);
            sub_t *subptr = mainptr->slink;
            while (subptr != NULL)           //traverse through the sub node
            {
                printf("File Name: %s\n", subptr->filename);
                printf("Word Count: %d\n", subptr->wordcount);
                subptr = subptr->slink;
            } 
            return SUCCESS;
        }
        mainptr = mainptr->mlink;
    }

    printf("Word \"%s\" not found in the hash table.\n", word);
    return FAILURE;
}



Status save_hash_table(hash_t hashtable[])
{
    char filename[200];
    printf("Enter the filename to save the hash table data: ");
    scanf("%199s", filename);  // Limit input to 199 characters to avoid buffer overflow
    if(strchr(filename,'.') == NULL)             //check the file have "." 
    {
        printf("Please pass extension alongwith filename for %s\n",filename);
        return FAILURE;
    }
    else
    {
        if(strcmp(strstr(filename,"."),".txt") != 0)   //check the file extension is ".txt"
        {
            printf("ERROR: Please pass file name with correct extension for %s usage: file.txt\n",filename);
            return FAILURE;
        }
        else
        {
            FILE *file=fopen(filename,"w");         //file open in the write node
            if(file == NULL)
            {
                printf("file can't be opened in write mode\n");
                return FAILURE;
            }
            for(int i=0; i<28; i++)
            {
                if(hashtable[i].link != NULL)
                {
                    main_t *mainptr=hashtable[i].link;
                    while(mainptr != NULL)             //traverse throgh the mainnode
                    {
                        fprintf(file,"#%d;",i);          //save the file using fprintf
                        fprintf(file,"%s;",mainptr->word);
                        fprintf(file,"%d;",mainptr->filecount);
                        sub_t *subptr=mainptr->slink;
                        while(subptr != NULL)          //traverse throgh the subnode
                        {
                            fprintf(file,"%s;",subptr->filename);
                            if(subptr->slink != NULL)
                            {
                                fprintf(file,"%d;",subptr->wordcount);
                            }
                            else
                            {
                                fprintf(file,"%d#",subptr->wordcount);
                            }
                            subptr=subptr->slink;
                        }
                        fputc('\n',file);
                        mainptr=mainptr->mlink;
                    }
                }
            }
            fclose(file);
            return SUCCESS;
}
}
}
