#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main(void)
{
    // Gets the main page's HTML
    getHtmlData("https://tcbonepiecechapters.com/mangas/5/one-piece", "main-page.txt");

    // QUEUE RESTRUCTURING
    Queue * links = CreateQueue()

    // Creating an array to store the URLs of the possible chapters
    char chapterLinks[CHAPTER_QT][MAX_LINK_SIZE];
    populateLinkArray(chapterLinks, CHAPTER_QT, "main-page.txt", "<a href=\"/chapters");

    // Displaying the chapters to the user
    displayOptions(chapterLinks);

    // Getting the user's choice for the chapter number and building the url from it
    char input = getUserInput("Input the option's number: ");
    int choice = input - '0';
    char choiceUrl[MAX_LINK_SIZE];
    sprintf(choiceUrl, "%s%s", "https://tcbonepiecechapters.com/chapters", chapterLinks[choice]);

    // Using the built URL to get the chapter's HTML data
    getHtmlData(choiceUrl, "chapter-page.txt");

    // Creating an array to store the links to the chapter page's images
    char imageLinks[PAGE_QT][MAX_LINK_SIZE];
    populateLinkArray(imageLinks, PAGE_QT, "chapter-page.txt", "fixed-ratio-content\" src=\"");

    // downloadImages(); // CONTINUE
}