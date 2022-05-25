#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Libs/binTrans/binTrans.h"
#include "Libs/Queue/queue.h"

#define MAX_PAGE_TABLE_SIZE 256
int physicalMemory[32768];
int pageTableSize = 0;

int main(int argc, char *argv[]) {

        //create page table queue
        struct Queue *pageTable;
        pageTable = createQueue();

        //contains the [0]page and the [1]offset in decimal
        int returnArray[2];

        //Vars to use in file managment
        FILE *file;
        file = fopen(argv[1], "r");
        char stringNum[6];

        while ((fscanf(file, "%[^\n]", stringNum)) != EOF) {
                //cast string address to decimal
                int addressDec = atoi(stringNum), page, offset;

                fgetc(file);
                //get page and offset for the current address
                getPageAndOffset(addressDec, returnArray);

                page = returnArray[0];
                offset = returnArray[1];

                //int frameFromTLB = searchPage(tlb, page);

                //check TLB (there is no TLB yet)
                if ( 1 /*frameFromTLB == -1*/) {

                        int frameFromPageTable = searchPage(pageTable, page);

                        if (frameFromPageTable == -1) {
                                //find it in BACKING_STORE.bin, update pageTable and TLB
                                //read physical memory

                        } else {
                                //update TLB
                                //read physical memory
                        }
                        

                }
                
                //printf("Virtual Address: %s - Page: %d - Offset: %d\n", stringNum, page, offset);
        }
        
        fclose(file);
}