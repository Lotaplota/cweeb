#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

// ---- QUEUE FUNCTIONS
Queue * CreateQueue(int capacity) {
    Queue * q = (Queue *) malloc(sizeof(Queue));

    q->Capacity = capacity;
    q->Start = NULL;
    q->End = NULL;
    q->Size = 0;

    return q;
}

Link * CreateLink(char * url) {
    if (url[0] == '\0') { perror("String is empty"); return NULL; }

    Link * l = (Link *) malloc(sizeof(Link)); // UNSAFE
    l->Url = (char *) malloc(strlen(url) + 1); // UNSAFE

    strcpy(l->Url, url);
    l->Next = NULL;

    return l;
}

void AddLink(Queue * q, Link * l) {
    if (q->Size == q->Capacity) { perror("Queue is full"); return; }
    if (l == NULL) { perror("The link is null"); return; }

    if (q->Start == NULL) { // CONTINUE is this working?
        q->Start = l;
        q->End = l;
    }
    else {
        q->End->Next = l;
        q->End = l;
    }

    q->Size++;
}

// Runs through the links in a queue and returns the link in the position chosen
Link * getLinkByIndex(Queue * q, int position)
{
    // TODO: check for numeric input
    if (position > q->Size || position < 0) { perror("Number out of the list's range"); return NULL; }

    Link * l = q->Start;

    for (int i = 1; i < position; i++)
    {
        if (!l->Next) break;
        l = l->Next;
    }

    return l;
}

void printQueue(Queue * q)
{
    if (q->Start == NULL) { perror("Queue is empty"); return; }

    printf("\n---- Queue of capacity %i, currently with %i links:\n", q->Capacity, q->Size);

    Link * cur = q->Start;
    while(cur != NULL)
    {
        printf("%s\n", cur->Url);
        cur = cur->Next;
    }

    printf("\n---- End of queue.\n");
}
// QUEUE FUNCTIONS ----

// Gets the HTML data  of a page and saves it as [filename].txt
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

int extractLinkURLAndAppendToQueue(char * filename, Queue * q, char * initiator, char terminator)
{
    FILE * file = fopen(filename, "r");

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
            
            // If the terminator is found, changes it to a \0 and creates a link in the end of the queue
            if (end)
            {
                *end = '\0';
                
                // Adding a new link to the queue
                AddLink(q, CreateLink(start));

                if (q->Capacity == q->Size) { return 0;}
            }
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

void displayOptions(char arr[CHAPTER_QT][MAX_LINK_SIZE]) // DEPRECATED
{
    printf("---- Chapter Options ----\n\n");
    for (int i = 0; i < CHAPTER_QT; i++)
    {
        printf("%i. %s\n", i, arr[i]);
    }

    printf("\n");
}

void displayQueueOptions(Queue * q)
{
    if (q->Start == NULL) { perror("Queue is empty"); return; }

    printf("---- Chapter Options ----\n\n");

    Link * cur = q->Start;
    int i = 1;
    while(cur != NULL)
    {
        printf("%i. %s\n", i, cur->Url);
        cur = cur->Next;
        i++;
    }

    printf("\n");
}

char getUserInput(char * prompt)
{
    printf("%s", prompt); // Using printf(prompt) can lead to a bug

    char buffer[256];
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        char input;
        if (sscanf(buffer, "%c", &input) == 1) return input;
    }

    return NULL;
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
