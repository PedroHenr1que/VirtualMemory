typedef struct{
    struct Node *start;
    struct Node *end;
    int size;
} Queue;

struct Node{
    int frame;
    struct Node *next;
};

Queue* createQueue();
void insert(Queue *theQueue, int dado);
int remove(Queue *theQueue);