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
Queue * CreateQueue(int capacity);
Link * CreateLink(char * url);
void AddLink(Queue * q, Link * l);
Link * getLinkByIndex(Queue * queue, int position);
void printQueue(Queue *);
// ---- QUEUE FUNCTIONS

// EXTRACTION / INPUT FUNCTIONS
void getHtmlData(char * url, char * filename);
int extractLinks(char * filename, Queue * queue, char * initiator, char terminator);
void displayOptions(Queue * queue);
char getUserInput(char * prompt);
void empty(char *, int);
void downloadImages(Queue * queue);
// EXTRACTION / INPUT FUNCTIONS

#endif