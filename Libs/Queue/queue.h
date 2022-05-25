#include <stdio.h>
#include <stdlib.h>

struct Queue{
    struct Node *start;
    struct Node *end;
};

struct Node{
    int page, frame;
    struct Node *next;
    
};

struct Queue* createQueue();
void insert(struct Queue *theQueue, int newPage, int newFrame);
int removeFromQueue(struct Queue *theQueue);
int searchPage(struct Queue *theQueue, int page);