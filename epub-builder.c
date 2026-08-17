#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

// Returns the time in the ISO-8601 format
void timeStr(char tm[25])
{
    time_t rawT = time(NULL);
    struct tm * utcTime = gmtime(&rawT);
    
    char string[25];
    
    strftime(string, sizeof(string), "%FT%TZ", utcTime);
    strcpy(tm, string);
}

// Loads the contents of a file into a buffer
char * loadFile(char * filename)
{
    FILE * f = fopen(filename, "r");
    if (!f) { perror("No such file to read"); return NULL; }

    // Sends the cursor to the end of the file, returns the position, then returns the cursor back to the start
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);
    
    // Allocates the necessary space for the content and appends a '\0'
    char * buffer = malloc(size + 1);
    fread(buffer, 1, size, f);
    buffer[size] = '\0';

    fclose(f);
    return buffer;
}

void createFolderStructure()
{
    system("mkdir -v epub-folder");
    system("mkdir -v epub-folder/META-INF epub-folder/OEBPS");
    system("mkdir -v epub-folder/OEBPS/images epub-folder/OEBPS/text");
}

// Replaces a bit of text for another one, returning a pointer to the result text
char * replaceBit(char * bit, char * replacement)
{
    // TODO
}

void addFiles()
{
    // Creating mimetype
    system("echo \"application/epub+zip\" > epub-folder/mimetype");

    // Creating content.opf
    char time[25];
    timeStr(time);

    char * contentTemp = loadFile("./templates/content-opf");
    char * title = "title";

    contentTemp = replaceBit("$/TITLE/$", title); // CONTINUE
}

int main(void)
{
    createFolderStructure();
    addFiles();
}