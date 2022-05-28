#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct element {
        char Caracter;
        int lastTimeUsed;
};


int time = 0;

int isFull = 0;
void addToArray(struct element array[], char value);
int isCharInArray(struct element array[], char value);

int main () {
        struct element array[4];
        int count = 0;
                        //0   1   2   3   4   5   6   7   8   9  10
        char entrys[] = {'a','b','b','c','c','d','e','b','x','d','z','b','d', 'h'};
                        // 0  2  4  5
                        //[a, b, c, d]

                        // 6  2  4  5
                        //[e, b, c, d]

                        // 6  7  4  5
                        //[e, b, c, d]

                        // 6  7  8  5
                        //[e, b, x, d]

                        // 6  7  8  9
                        //[e, b, x, d]

                        // 10  7  8  9
                        //[z, b, x, d]

        for (int i = 0; i < sizeof(entrys); i++) {

                if (isFull == 0) {

                        if (!isCharInArray(array,entrys[i])) {
                                array[count].Caracter = entrys[i];
                                array[count].lastTimeUsed = time;

                                if (count == 3) {
                                  isFull = 1;
                                }
                                count = (count + 1) % 4;
                        }
                        
                } else {
                        addToArray(array,entrys[i]);
                }
                
                time ++;
                
                for (int i = 0; i < 4; i ++) {
                  printf("%d ", array[i].lastTimeUsed);
                }

                printf("\n");

                for (int i = 0; i < 4; i++) {
                  printf("%c ", array[i].Caracter);
                }
                printf("\n");
                printf("\n");
        }
        
}
int isCharInArray(struct element array[], char value) {

        for (int i = 0; i < 4; i++) {
                if (array[i].Caracter == value) {
                        array[i].lastTimeUsed = time;
                        return 1;
                }
        }
        
        return 0;
}

struct naosei {
        int index, lastTime;
};

void addToArray(struct element array[],char value) {

        if (!isCharInArray(array, value)) {
          struct naosei *test = (struct naosei *)malloc(sizeof(struct naosei *));
          test->index = 0;
          test->lastTime = array[0].lastTimeUsed;
  
          for (int i = 1; i < 3; i++) {
                  if (array[i].lastTimeUsed < test->lastTime) {
                          test->index = i;
                          test->lastTime = array[i].lastTimeUsed;
                  }
          }
  
          array[test->index].Caracter = value;
          array[test->index].lastTimeUsed = time;
        }
}