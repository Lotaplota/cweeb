#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// char * find(char filename[64], char initiator[64], char terminator[2])
// {
//     FILE * file = fopen(filename, "r");

//     // Creating buffers for the current line and the selected substring
//     char line[1024];
//     char select[1024];

//     while (fgets(line, sizeof(line), file) != NULL)
//     {
//         // Finding the position of the substring
//         char * pos = strstr(line, initiator);

//         if (pos == NULL) 
//         {
//             printf("Substring \"%s\" not found\n", initiator);
//         }
//         else
//         {
//             printf("Found: ");

//             // Should start printing from the i-th character
//             // i should be the length of the initiator substring minus 1 for the \0
//             int i = sizeof(initiator) - 1; int j = 0;

//             // Prints while the current character is not the chosen terminator
//             while (pos[i] != terminator[0])
//             {
//                 select[j] = pos[i];
//                 i++; j++;
//             }
//         }
//     }
// } // CONTINUE don't do separate functions, do everything in main and later separate it in functions

void getHtmlData()
{
    FILE * fw = fopen("content.txt", "w");

    // Requesting the URL from the user
    char url[64] = "";
    printf("insert the desired url\nhttp://");
    scanf("%s", url);

    // Appending the desired url to the curl command
    char argument[128] = "curl -o content.txt https://"; // won't run without the s in https FOR SOME REASON
    strcat(argument, url);

    // 
    system(argument);
    
    fclose(fw);
}

void empty(char * a)
{
    int i = 0;
    while (a[i] != "\0")
    {
        a[i] = NULL;
    }
}

int main(void)
{
    getHtmlData();

    FILE * html = fopen64("content.txt", "r");

    char line[1024];
    char select[1024];
    empty(select);

    printf("%s\n", select); // DONKEY

    while (fgets(line, sizeof(line), html) != NULL)
    {
        // Finding the position of the substring
        char * pos = strstr(line, "ratio-content\" src=\"");

        if (pos == NULL)
        {
            printf("Substring \"%s\" not found\n", "ratio-content\" src=\""); // DEBUG
        }
        else
        {
            printf("Found: ");

            // Should start printing from the i-th character
            // i should be the length of the initiator substring minus 1 for the \0
            int i = sizeof("ratio-content\" src=\"") - 1; int j = 0;

            // Prints while the current character is not the chosen terminator
            while (pos[i] != '\"')
            {
                select[j] = pos[i];
                i++; j++;
            }
            printf("%s\n", select); // DEBUG
        }
    }
}

