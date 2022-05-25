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

// int main(void){
//     struct Queue *theQueue;
//     theQueue = createQueue();
    
//     insert(theQueue, 244, 200);
//     insert(theQueue, 30, 89);
//     insert(theQueue, 66, 150);

//     struct Node *aux = theQueue->start;

//     while (aux!=NULL) {
//         printf("%d %d\n", aux->page, aux->frame);
//         aux = aux->next;
//     }
    
//     removeFromQueue(theQueue);

//     aux = theQueue->start;

//     while (aux!=NULL) {
//         printf("%d %d\n", aux->page, aux->frame);
//         aux = aux->next;
//     }
//     // int result = searchPage(theQueue, 244);
//     // printf("\nFrame again: %d", result);

//     // result = searchPage(theQueue, 66);
//     // printf("\nFrame again: %d", result);

//     // result = searchPage(theQueue, 30);
//     // printf("\nFrame again: %d", result);

//     // result = searchPage(theQueue, 50);
//     // if (result == -1) {
//     //     printf("\nPagina 50 não encontrada");
//     // }

//     // result = searchPage(theQueue, 66);
//     // printf("\nFrame again: %d", result);
    
//     // 
//     // result = searchPage(theQueue, 66);
//     // if (result == -1) {
//     //     printf("\nPagina 66 não encontrada");
//     // }
//     // insert(theQueue, 150);
//     // insert(theQueue, 300);
//     // removeFromQueue(theQueue);
//     // removeFromQueue(theQueue);
//     // removeFromQueue(theQueue);
//     // removeFromQueue(theQueue);
//     // removeFromQueue(theQueue);
// }

struct Queue* createQueue() {
    struct Queue *theQueue;
    theQueue = (struct Queue *)malloc(sizeof(struct Queue *));

    if (theQueue != NULL) {
        theQueue->start = NULL;
        theQueue->end = NULL;
    }

    return theQueue;
}

void insert(struct Queue *theQueue, int newPage, int newFrame) {

    struct Node *new;
    new = (struct Node *)malloc(sizeof(struct Node *));
    new->next = NULL;
    new->frame = newFrame;
    new->page = newPage;

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

int searchPage(struct Queue *theQueue, int pageToBeSearched) {

    struct Node *aux = theQueue->start;

    while (aux != NULL) {
        
        if (aux->page == pageToBeSearched) {

            //printf("\nPage %d - Points to frame %d", aux->page, aux->frame);
            return aux->frame;

        }
        
        aux = aux->next;
    }
    
    return -1;
}