#include <stdio.h>
#include <stdlib.h>

struct pageTableElement {
        int frame;
        int isValid;
};

struct pageTableElement pageTable[256];
void printPageTable();

int main() {

        for (int i = 0; i < 256; i++) {
                pageTable[i].frame = 0;
        }

        printPageTable();

        for (int i = 0; i < 256; i++) {
                pageTable[i].isValid = 1;
                pageTable[i].frame = i;
        }
        
        printf("\n\n\nAnother timer");
        printPageTable();
        return 0;
}

void printPageTable() {

        for (int i = 0; i < 256; i++) {
                printf("Page %d - Frame %d - Bit %d\n", i, pageTable[i].frame, pageTable[i].isValid);
        }
        
}