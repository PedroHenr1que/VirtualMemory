#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Libs/binTrans/binTrans.h"
#include "Libs/ErrorHandler/errorHandler.h"
//#include "Libs/Queue/queue.h"

struct physicalMemoryFrame {
        int pageFromBackingStore[256];
};
struct pageTableElement {
        int frame;
        int isValid;
};

struct pageTableElement pageTable[256];
struct physicalMemoryFrame physicalMemory[256];
//phsycalMemory lista
//TLB lista

int main(int argc, char *argv[]) {

        //Check if the args are wrong, if they are the program exit
        int checkErrors = checkArgs(argc, argv);
        if (checkErrors < 0) {
                exit(1);
        }
        
        //Create page table
        for (int i = 0; i < 256; i++) {
                pageTable[i].isValid = 0;
        }
        
        //Contains the [0]page and the [1]offset in decimal
        int returnArray[2];

        //Vars to use in file managment
        FILE *file;
        file = fopen(argv[1], "r");
        char stringNum[6];

        while ((fscanf(file, "%[^\n]", stringNum)) != EOF) {

                //cast string address to decimal
                int addressDec = atoi(stringNum), page, offset;
                int /*isInTLB = 0,*/ isInPageTable = 0;

                fgetc(file);
                //get page and offset for the current address
                getPageAndOffset(addressDec, returnArray);

                while (isInPageTable == 0 /*&& isInTLB == 0*/) {
                        
                        page = returnArray[0];
                        offset = returnArray[1];

                        if (pageTable[page].isValid == 1) {
                                //find frame and print int

                                isInPageTable = 1;
                        } else {
                                //find in backingstore, update tlb, update pageTable


                                isInPageTable = 0;
                        }
                }
                //printf("Virtual Address: %s - Page: %d - Offset: %d\n", stringNum, page, offset);
        }
        
        fclose(file);
}