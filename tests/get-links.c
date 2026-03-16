#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * extractLink(FILE * file, char * dst, int dst_size, char * initiator, char terminator)
{
    char line[1024];
    char select[1024];

    while (fgets(line, sizeof(line), file) != NULL)
    {
        char * start; char * end;
        // Finding the position of the substring
        start = strstr(line, initiator);

        if (start)
        {
            start += strlen(start); // maybe this will have to be +1(?)
            end = strchr(start, terminator);

            if (end)
            {
                *end = '\0';

                strncpy(dst, start, dst_size - 1);
                dst[dst_size - 1] = '\0'; // CONTINUE
            }
            // Should start printing from the i-th character
            // i should be the length of the initiator substring minus 1 for the \0
            int i = sizeof(initiator) - 1; int j = 0;

            // Prints while the current character is not the chosen terminator
            while (start[i] != terminator)
            {
                select[j] = start[i];
                i++; j++;
            }
        }

        // Emptying the array for the next link
        empty(select, 1024);
    }

    return select;
    // ok... now how can i use this function in a loop without starting to read from the top of the file?
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
    
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fr))
    {
        
    }

}