#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    FILE * fw = fopen("content.txt", "r");

    char img[1024];
    fscanf(fw, "%[^u]s", img);

    printf("%s", img);
    
    fclose(fw);
}