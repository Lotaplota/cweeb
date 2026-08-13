#ifndef FUNCTIONS_H

#define CAMINHO_H
#define CHAPTER_QT 5
#define PAGE_QT 20
#define MAX_LINK_SIZE 256

typedef struct Link {
    char * Url;
    struct Link * Next;
} Link;

typedef struct {
    Link * Start;
    Link * End;
    int Capacity;
    int Size;
} Queue;

// ---- QUEUE FUNCTIONS
Queue * CreateQueue(int);
Link * CreateLink(char * url);
void AddLink(Queue * q, Link * l);
void printQueue(Queue *);
// QUEUE FUNCTIONS ----


void getHtmlData(char *, char *);
int extractLink(FILE *, char *, int, char *, char);
int populateLinkArray(char arr[][MAX_LINK_SIZE], int, char *, char *);
int extractLinkURLAndAppendToQueue(char *, Queue *, char *, char);
void displayOptions(char arr[CHAPTER_QT][MAX_LINK_SIZE]);
char getUserInput(char *);
void empty(char *, int);
void getImageLinks(); // DEPRECATED
void downloadImages(char *); // i should change this function a little bit. make it a loop that scans through the links array and download the images;

#endif