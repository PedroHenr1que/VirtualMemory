#include <stdio.h>
#include <stdlib.h>

// struct physicalMemoryFrame {
//         int pageFromBackingStore[256];
// };

struct Queue{
    struct Node *start;
    struct Node *end;
};

struct Node{
    int frame, pageFromBackingStore[256];
    struct Node *next;
    
};

int main() {


        return 0;
}

struct Queue* createQueue() {
    struct Queue *theQueue;
    theQueue = (struct Queue *)malloc(sizeof(struct Queue *));

    if (theQueue != NULL) {
        theQueue->start = NULL;
        theQueue->end = NULL;
    }

    return theQueue;
}

void insert(struct Queue *theQueue, int frame, int pageFromBackingStore[256]) {

    struct Node *new;
    new = (struct Node *)malloc(sizeof(struct Node *));
    new->next = NULL;
    new->frame = frame;
    
    for (int i = 0; i < 256; i++) {
            new->pageFromBackingStore[i] = pageFromBackingStore[i];
    }
    
    

    if (theQueue->start == NULL) {
        theQueue->start = new;
        theQueue->end = new;
        
    } else {
        theQueue->end->next = new;
        theQueue->end = new;
        
    }
}

int removeFromQueue(struct Queue *theQueue) {
    struct Node *out;

    if (theQueue->start == NULL) {
      theQueue->end = NULL;
      return 0;
    }
    
    out = theQueue->start;
    theQueue->start = out->next;

    free(out);

    return 1;
}