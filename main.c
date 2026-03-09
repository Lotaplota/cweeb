#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    FILE * fw = fopen("content.txt", "w");

    // Getting the arguments
    char url[64] = "";
    printf("insert the desired url\nhttp://");
    scanf("%s", url);

    // Appending the desired url to the curl command
    char argument[128] = "curl -o content.txt https://"; // won't run without the s in https FOR SOME REASON
    strcat(argument, url);

    system(argument);

    char img[1024];
    fscanf(fw, "%*[^flex]flex %s items-", img);
    
    fclose(fw);
}