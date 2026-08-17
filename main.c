#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main(void)
{
    // Gets the main page's HTML
    getHtmlData("https://tcbonepiecechapters.com/mangas/5/one-piece", "main-page.txt");

    // QUEUE RESTRUCTURING
    Queue * links = CreateQueue(CHAPTER_QT);

    extractLinks("main-page.txt", links, "<a href=\"/chapters", '\"');
    printQueue(links); // DONKEY

    // Displaying the chapters to the user
    displayOptions(links);
    
    // Getting the user's choice for the chapter number and building the url from it
    // TODO: turn this into a single function getUserInput, with input checks and basic safekeeping
    char input = getUserInput("Input the option's number: ");
    Link * chosenLink = getLinkByIndex(links, input - '0');

    char chapterUrl[MAX_LINK_SIZE];
    sprintf(chapterUrl, "%s%s", "https://tcbonepiecechapters.com/chapters", chosenLink->Url);
    printf("chosen chapter url: %s\n", chapterUrl); // DONKEY
    
    // Using the built URL to get the chapter's HTML data
    getHtmlData(chapterUrl, "chapter-page.txt");
    
    Queue * imgs = CreateQueue(PAGE_QT);
    extractLinks("chapter-page.txt", imgs, "fixed-ratio-content\" src=\"", '\"');
    printQueue(imgs); // DONKEY

    downloadImages(imgs);
}