#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    FILE * text = fopen("text.txt", "r");

    char buffer[100];
    char select[100];

    while (fgets(buffer, sizeof(buffer), text) != NULL)
    {
        printf(buffer); // DONKEY
        char * ptr = strstr(buffer, "<");
        if (ptr == NULL) 
        {
            printf("! text not found\n");
        } else {
            printf(ptr); // DONKEY
        }
        // strcpy(buffer, select);
        // printf("selected text: %s", select); // DONKEY
    }

}