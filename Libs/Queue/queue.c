#include <stdio.h>
#include <stdlib.h>

typedef struct{
    struct Node *start;
    struct Node *end;
    int size;
} Queue;

struct Node{
    int frame;
    struct Node *next;
};

// Queue* createQueue();
// void insert(Queue *theQueue, int dado);
// int remove(Queue *theQueue);

// int main(void){
//     Queue *theQueue;
//     theQueue = createQueue();
//     //theQueue = (Queue *)malloc(sizeof(Queue *));
//     insert(theQueue, 10);
//     insert(theQueue, 85);
//     insert(theQueue, 150);
//     insert(theQueue, 300);
//     remove(theQueue);
//     remove(theQueue);
//     remove(theQueue);
//     remove(theQueue);
//     remove(theQueue);
// }

Queue* createQueue() {
    Queue *theQueue;
    theQueue = (Queue *)malloc(sizeof(Queue *));

    if (theQueue != NULL) {
        theQueue->start = NULL;
        theQueue->end = NULL;
        theQueue->size = 0;
    }

    return theQueue;
}

void insert(Queue *theQueue, int dado){

    struct Node *new;
    new = (struct Node *)malloc(sizeof(struct Node *));

    new->next = NULL;
    new->frame = dado;

    if (theQueue->start == NULL) {
        theQueue->end = new;
        theQueue->start = new;
        theQueue->size = theQueue->size + 1;

    } else {
        theQueue->end->next = new;
        theQueue->end = new;
        theQueue->size = theQueue->size + 1;
    }
}

int remove(Queue *theQueue){
    struct Node *out;

    if (theQueue->start == NULL) {
      theQueue->end = NULL;
      return(0);
    }
    
    out = theQueue->start;
    theQueue->start = out->next;
    theQueue->size = theQueue->size -1;

    free(out);

    return(1);
}