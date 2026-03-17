#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int extractNthLink(FILE * file, char * dst, int dst_size, char * initiator, char terminator)
{
    char line[1024];

    while (fgets(line, sizeof(line), file) != NULL)
    {
        char * start = NULL; char * end = NULL;
        
        // Finding the position of the substring
        start = strstr(line, initiator);
        
        if (start)
        {
            printf("found: %x\n", start); // DEBUG 2
            start += strlen(initiator);

            end = strchr(start, terminator);
            
            if (end)
            {
                *end = '\0';
                
                strncpy(dst, start, dst_size - 1);
                dst[dst_size - 1] = '\0'; // CONTINUE
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
    char links[linkAmount][64];
    char init[] = "<a href=\"/chapters\0";
    
    
    extractNthLink(fr, links[0], 64, init, '\"');
    extractNthLink(fr, links[1], 64, init, '\"');
    extractNthLink(fr, links[2], 64, init, '\"');
    extractNthLink(fr, links[3], 64, init, '\"');
    extractNthLink(fr, links[4], 64, init, '\"');

    for (int i = 0; i < 5; i++) // DEBUG 1
        printf("%i. %s\n", i + 1, links[i]); // DEBUG 1
}