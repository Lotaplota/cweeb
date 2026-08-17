#include <stdlib.h>

void createFolderStructure()
{
    system("mkdir -v epub-folder");
    system("mkdir -v epub-folder/META-INF epub-folder/OEBPS");
    system("mkdir -v epub-folder/OEBPS/images epub-folder/OEBPS/text");
}

void addFiles()
{
    system("echo \"application/epub+zip\" > epub-folder/mimetype");
}

int main(void)
{
    createFolderStructure();
    addFiles();
}