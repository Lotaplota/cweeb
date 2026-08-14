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

    extractLinkURLAndAppendToQueue("main-page.txt", links, "<a href=\"/chapters", '\"');
    printQueue(links); // DONKEY

    // Displaying the chapters to the user
    displayQueueOptions(links);
    
    // Getting the user's choice for the chapter number and building the url from it
    // TODO: turn this into a single function getUserInput, with input checks and basic safekeeping
    char input = getUserInput("Input the option's number: ");
    Link * chosenLink = getLinkByIndex(links, input - '0');

    char chapterUrl[MAX_LINK_SIZE];
    sprintf(chapterUrl, "%s%s", "https://tcbonepiecechapters.com/chapters", chosenLink->Url);
    printf("chosen chapter url: %s\n", chapterUrl); // DONKEY
    
    /* ---- CHANGE IT TO QUEUE STRUCTURE
    // Using the built URL to get the chapter's HTML data
    getHtmlData(choiceUrl, "chapter-page.txt");

    // Creating an array to store the links to the chapter page's images
    char imageLinks[PAGE_QT][MAX_LINK_SIZE];
    populateLinkArray(imageLinks, PAGE_QT, "chapter-page.txt", "fixed-ratio-content\" src=\"");
    CHANGE IT TO QUEUE STRUCTURE ---- */
}