#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * find(char filename[64], char initiator[64], char terminator[2])
{
    FILE * file = fopen(filename, "r");

    // Creating buffers for the current line and the selected substring
    char line[1024];
    char select[1024];

    while (fgets(line, sizeof(line), file) != NULL)
    {
        // Finding the position of the substring
        char * pos = strstr(line, initiator);

        if (pos == NULL) 
        {
            printf("Substring \"%s\" not found\n", initiator);
        }
        else
        {
            printf("Found: ");

            // Should start printing from the i-th character
            // i should be the length of the initiator substring minus 1 for the \0
            int i = sizeof(initiator) - 1; int j = 0;

            // Prints while the current character is not the chosen terminator
            while (pos[i] != terminator[0])
            {
                select[j] = pos[i];
                i++; j++;
            }
        }
    }
} // CONTINUE don't do separate functions, do everything in main and later separate it in functions

// int main(void)
// {
//     FILE * fw = fopen("content.txt", "w");

//     // Getting the arguments
//     char url[64] = "";
//     printf("insert the desired url\nhttp://");
//     scanf("%s", url);

//     // Appending the desired url to the curl command
//     char argument[128] = "curl -o content.txt https://"; // won't run without the s in https FOR SOME REASON
//     strcat(argument, url);

//     system(argument);

//     char img[1024];
//     fscanf(fw, "%*[^flex]flex %s items-", img);
    
//     fclose(fw);
// }

