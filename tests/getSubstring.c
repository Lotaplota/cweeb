#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    FILE * text = fopen("text.txt", "r");

    // Creating buffers for the current line and the selected substring
    char line[100];
    char select[100];

    while (fgets(line, sizeof(line), text) != NULL)
    {
        // Setting the substring "<<" to be found
        char * substr = "<<";
        char * pos = strstr(line, substr);

        if (pos == NULL) 
        {
            printf("Substring \"%s\" not found\n", substr);
        }
        else
        {
            printf("Found: ");

            // Should start printing from the i-th character
            // i should be the length of the substring minus 1 for the string terminator \0
            int i = sizeof(substr) - 1;

            // Prints while the current character is not the chosen terminator
            while (pos[i] != '>')
            {
                printf("%c ", pos[i]);
                i++;
            }
            printf("\n");
        }
    }

}