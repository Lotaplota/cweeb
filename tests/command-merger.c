#include <stdio.h>
#include <stdlib.h>

void getHtmlData(char * url, char * filename)
{
    char command[256];
    sprintf(command, "%s %s %s", "curl -o", filename, url);
    printf("%s\n", command); // DONKEY

    system(command);
}

int main(void)
{
    getHtmlData("https://tcbonepiecechapters.com/mangas/5/one-piece", "chapter-page.txt");
}