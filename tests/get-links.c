#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINK_LENGTH 256

int extractNthLink(FILE * file, char * dst, int dst_size, char * initiator, char terminator)
{
    char line[1024];

    while (fgets(line, sizeof(line), file) != NULL)
    {
        char * start = NULL; char * end = NULL;
        
        // Finding the position of the substring
        start = strstr(line, initiator);
        
        // If the initiator is found, searches for the terminator
        if (start)
        {
            start += strlen(initiator);

            end = strchr(start, terminator);
            
            // If the terminator is found, changes it to a \0 and copies the string to the destination
            if (end)
            {
                *end = '\0';

                // Setting up the start of the link that couldn't be obtained from the pages HTML and joining it to the part that could
                char fullLink[LINK_LENGTH] = "https://tcbonepiecechapters.com/chapters";
                strcat(fullLink, start);
                
                // Copying the full link to the destination
                strncpy(dst, fullLink, dst_size - 1);
                dst[dst_size - 1] = '\0';
            }

            return 0;
        }
    }
}

int main(void)
{
    FILE * fw = fopen("main-page.txt", "w");
    system("curl -o main-page.txt https://tcbonepiecechapters.com/mangas/5/one-piece");
    fclose(fw);

    FILE * fr = fopen("main-page.txt", "r");

    // Setting up the array that will store the extracted links
    int linkAmount = 5;
    char links[linkAmount][LINK_LENGTH];
    char init[] = "<a href=\"/chapters\0";
    
    for (int i = 0; i < linkAmount; i++)
    {
        extractNthLink(fr, links[i], LINK_LENGTH, init, '\"');
    }
    for (int i = 0; i < linkAmount; i++)
    {
        printf("Option %i: %s\n", i + 1, links[i]);
    }
}