#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <dirent.h>

int endsWith(char * str, char * fragment)
{
    int sLen = strlen(str);
    int fLen = strlen(fragment);

    if (sLen < fLen) { perror("Fragment is longer than the string"); return -1; }

    int pos = sLen - fLen;
    char * end;
    strcpy(end, str + pos);
    printf("string: %s\nfragment: %s\n end of string: %s\n"); // DONKEY

    if (strcmp(end, fragment)) return 1;
    else return 0;
}

// Counts how many files are there in a folder
int countFiles(char * fdr, char * extension) // CONTINUE not working...
{
    // Opening the folder
    DIR * folder = opendir(fdr);
    if (!folder) { perror("Pasta invalida"); return -1 ;}

    struct dirent * curFile;

    // Skipping folder files /./ e /../
    curFile = readdir(folder); curFile = readdir(folder);

    int qt = 0;
    while (curFile)
    {
        curFile = readdir(folder);
        if (!curFile) { break; }

        // Increments the counter if the end of the current file matches the extension
        if (endsWith(curFile->d_name, ".png")) qt++;
    }

    return qt;
}

int main(void)
{
    int count = countFiles("../images", ".png");
    printf("the folder has %i files\n");
}