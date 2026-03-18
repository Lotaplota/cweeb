#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHAPTER_QT 5
#define PAGE_QT 20
#define MAX_LINK_SIZE 256

void getHtmlData(char * url, char * filename)
{
    char command[256];
    sprintf(command, "%s %s %s", "curl -o", filename, url);

    system(command);
}

int extractLink(FILE * file, char * dst, int dst_size, char * initiator, char terminator)
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
                
                // Copying the full link to the destination
                strncpy(dst, start, dst_size - 1);
                dst[dst_size - 1] = '\0';
            }

            return 0;
        }
    }
}

int populateLinkArray(char arr[][MAX_LINK_SIZE], int lineAmount, char * filename, char * initiator)
{
    FILE * pageData = fopen(filename, "r");

    for (int i = 0; i < lineAmount; i++)
    {
        extractLink(pageData, arr[i], MAX_LINK_SIZE, initiator, '\"');
    }

    fclose(pageData);
}

void displayOptions(char arr[CHAPTER_QT][MAX_LINK_SIZE])
{
    printf("---- Chapter Options ----\n\n");
    for (int i = 0; i < CHAPTER_QT; i++)
    {
        printf("%i. %s\n", i, arr[i]);
    }

    printf("\n");
}

char getUserInput(char * prompt)
{
    printf(prompt);

    char input;
    scanf("%c", &input);

    return input;
}

void empty(char * a, int size)
{
    memset(a, 0, size * (sizeof a[0]));
}

void getImageLinks() // DEPRECATED
{
    FILE * html = fopen("content.txt", "r");
    FILE * links = fopen("links.txt", "w");

    char line[1024];
    char select[1024];

    while (fgets(line, sizeof(line), html) != NULL)
    {
        // Finding the position of the substring
        char * pos = strstr(line, "ratio-content\" src=\"");

        if (pos != NULL)
        {
            // Should start printing from the i-th character
            // i should be the length of the initiator substring minus 1 for the \0
            int i = sizeof("ratio-content\" src=\"") - 1; int j = 0;

            // Prints while the current character is not the chosen terminator
            while (pos[i] != '\"')
            {
                select[j] = pos[i];
                i++; j++;
            }

            // Saving the extracted link found to the file
            fprintf(links,"%s\n", select);
        }

        // Emptying the array for the next link
        empty(select, 1024);
    }

    fclose(html); fclose(links);
}

void downloadImages(char * chapterUrl) // i should change this function a little bit. make it a loop that scans through the links array and download the images
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
    getHtmlData("https://tcbonepiecechapters.com/mangas/5/one-piece", "main-page.txt");

    // Creating an array to store the URLs of the possible chapters
    char chapterLinks[CHAPTER_QT][MAX_LINK_SIZE];
    populateLinkArray(chapterLinks, CHAPTER_QT, "main-page.txt", "<a href=\"/chapters");

    // Displaying the chapters to the user
    displayOptions(chapterLinks);

    // Getting the user's choice for the chapter number and building the url from it
    char input = getUserInput("Input the option's number: ");
    int choice = input - '0';
    char choiceUrl[MAX_LINK_SIZE];
    sprintf(choiceUrl, "%s%s", "https://tcbonepiecechapters.com/chapters", chapterLinks[choice]);

    // Using the built URL to get the chapter's HTML data
    getHtmlData(choiceUrl, "chapter-page.txt");

    // Creating an array to store the links to the chapter page's images
    char imageLinks[PAGE_QT][MAX_LINK_SIZE];
    populateLinkArray(imageLinks, PAGE_QT, "chapter-page.txt", "fixed-ratio-content\" src=\"");

    // downloadImages(); // CONTINUE
}