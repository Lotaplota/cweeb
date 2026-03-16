#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getHtmlData()
{
    // FILE * fw = fopen("content.txt", "w");

    // int linkAmount = 5;
    // char links[linkAmount][64];
    
    // char buffer[1024];

    // while (fgets(buffer, sizeof(buffer), ))
    // {
    //     /* code */
    // }

    // Requesting the URL from the user
    char url[64];
    printf("insert the desired url\nhttp://");
    scanf("%s", url);

    // Appending the desired url to the curl command
    char argument[128] = "curl -o content.txt https://"; // won't run without the s in https FOR SOME REASON
    strcat(argument, url);

    system(argument);
    
    fclose(fw);
}

void empty(char * a, int size)
{
    memset(a, 0, size * (sizeof a[0]));
}

void separateLinks()
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
    separateLinks();
    downloadImages();
}