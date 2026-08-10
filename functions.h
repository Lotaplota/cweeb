#ifndef FUNCTIONS_H

#define CAMINHO_H
#define CHAPTER_QT 5
#define PAGE_QT 20
#define MAX_LINK_SIZE 256

void getHtmlData(char *, char *);
int extractLink(FILE *, char *, int, char *, char);
int populateLinkArray(char arr[][MAX_LINK_SIZE], int, char *, char *);
void displayOptions(char arr[CHAPTER_QT][MAX_LINK_SIZE]);
char getUserInput(char *);
void empty(char *, int);
void getImageLinks(); // DEPRECATED
void downloadImages(char *); // i should change this function a little bit. make it a loop that scans through the links array and download the images;

#endif