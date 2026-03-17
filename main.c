#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINK_AMOUNT 5
#define MAX_LINK_SIZE 256

void getHtmlData()
{
    FILE * fw = fopen("main-page.txt", "w");
    system("curl -o main-page.txt https://tcbonepiecechapters.com/mangas/5/one-piece");
    fclose(fw);
}

int extractNthLink(FILE * file, char * dst, int dst_size, char * initiator, char terminator)
{
    if (!file)
    {
        printf("No html data to read from!\n");
        return 1;
    }

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
                char fullLink[MAX_LINK_SIZE] = "https://tcbonepiecechapters.com/chapters";
                strcat(fullLink, start);
                
                // Copying the full link to the destination
                strncpy(dst, fullLink, dst_size - 1);
                dst[dst_size - 1] = '\0';
            }

            return 0;
        }
    }
}

int populateLinkArray(char arr[LINK_AMOUNT][MAX_LINK_SIZE])
{
    FILE * mainPage = fopen("main-page.txt", "r");

    for (int i = 0; i < LINK_AMOUNT; i++)
    {
        extractNthLink(mainPage, arr[i], MAX_LINK_SIZE, "<a href=\"/chapters", '\"');
    }
}

void empty(char * a, int size)
{
    memset(a, 0, size * (sizeof a[0]));
}

void downloadImages()
{
    system("mkdir images");
    FILE * links = fopen("links.txt", "r");

    // Creating page counter to be appended to the filenames
    int pageNum = 1;
    char buff[1024] = "";
    
    while (fgets(buff, sizeof(buff), links) != NULL)
    {
        char command[64];
        sprintf(command, "curl -o images/page%02i.png %s", pageNum, buff);

        system(command);
        pageNum++;
    }
}


int main(void)
{
    getHtmlData();

    char links[LINK_AMOUNT][MAX_LINK_SIZE];

    populateLinkArray(links);
    // separateLinks();
    // downloadImages();
}