#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Libs/binTrans/binTrans.h"
#include "Libs/ErrorHandler/errorHandler.h"
#include "Libs/backingStore/backingStore.h"

struct physicalMemoryFrame {
        int lastTimeUsed;
        signed char pageFromBackingStore[256];
};
struct pageTableElement {
        int frame;
        int isValid;
};

#define PHYSICAL_MEMORY_SIZE 128
#define VALID 1
#define NOT_VALID 0


void passValuesFromBackStoreToFrame(signed char valuesFromBackStore[256], int frame);
void findAndPutInvalidBitInPageTableForRelatedFrame(int frameToSearch);
void addIfNotFullOrIfFifo(int currentPage, signed char temporaryArrayPage[256], int countPhysicalMemory);
int findLessUsedFrame();

struct pageTableElement pageTable[256];
struct physicalMemoryFrame physicalMemory[PHYSICAL_MEMORY_SIZE];
int time = 0;
int main(int argc, char *argv[]) {

        

        //aux vars for replacement algo
        int countPhysicalMemory = 0;
        int fullPhysicalMemory = 0;

        //Check if the args are wrong, if they are the program exit
        int checkErrors = checkArgs(argc, argv);
        if (checkErrors < 0) {
                exit(1);
        }

        //args
        char *virtualAddressesFile = argv[1];
        char *physicalMemoryReplacementAlgo = argv[2];
        char *tlbReplacementAlgo = argv[3];

        //statistics
        double totalOfVirtualAddressesTranslated = 0;
        double totalPageFaults = 0;
        double totalPageFaultRate = 0.0;

        //Initialize page table with invalid bit
        for (int i = 0; i < 256; i++) {
                pageTable[i].isValid = NOT_VALID;
        }
        
        //Contains the [0]page and the [1]offset in decimal
        int returnArray[2];

        //Vars to use in file managment
        FILE *file;
        file = fopen(virtualAddressesFile, "r");
        char virtualAddressStr[6];

        while ((fscanf(file, "%[^\n]", virtualAddressStr)) != EOF) {
                //cast string address to decimal
                int virtualAddressDec = atoi(virtualAddressStr), currentPage, currentOffset;
                int /*isInTLB = 0,*/ isInPageTable = 0;

                fgetc(file);
                //get page and offset for the current address
                getPageAndOffset(virtualAddressDec, returnArray);

                currentPage = returnArray[0];
                currentOffset = returnArray[1];

                while (isInPageTable == 0 /*&& isInTLB == 0*/) {
                        
                        if (pageTable[currentPage].isValid == VALID) {
                                //find frame and print int
                                int currentFrame = pageTable[currentPage].frame;
                                int physicalAddress = (currentFrame * 256) + currentOffset;
                                signed char value = physicalMemory[currentFrame].pageFromBackingStore[currentOffset];
                                physicalMemory[currentFrame].lastTimeUsed = time;
                                printf("Virtual address: %d Physical address: %d Value: %d\n", virtualAddressDec, physicalAddress, value);
                                
                                isInPageTable = 1;

                        } else { //page fault
                                //find in backingstore, update pageTable
                                printf("Page fault %.0f\n", totalPageFaults);
                                signed char temporaryArrayPage[256];
                                findPageInBackingStore(currentPage, temporaryArrayPage);

                                if (fullPhysicalMemory == 1) {
                                        if (strcmp(physicalMemoryReplacementAlgo, "fifo") == 0) {
                                                findAndPutInvalidBitInPageTableForRelatedFrame(countPhysicalMemory);
                                                addIfNotFullOrIfFifo(currentPage, temporaryArrayPage, countPhysicalMemory);

                                        } else {
                                                int lessUsedFrame = findLessUsedFrame();
                                                findAndPutInvalidBitInPageTableForRelatedFrame(lessUsedFrame);
                                                passValuesFromBackStoreToFrame(temporaryArrayPage, lessUsedFrame);

                                                pageTable[currentPage].frame = lessUsedFrame;
                                                pageTable[currentPage].isValid = VALID;
                                        }
                                        
                                } else {
                                        addIfNotFullOrIfFifo(currentPage, temporaryArrayPage, countPhysicalMemory);
                                }
                                

                                if (countPhysicalMemory == 127) {
                                        fullPhysicalMemory = 1;
                                }
                                
                                countPhysicalMemory = (countPhysicalMemory + 1) % PHYSICAL_MEMORY_SIZE;
                                totalPageFaults ++;  
                        }
                }

                
                //printf("Virtual Address: %s - Page: %d - Offset: %d\n", stringNum, page, offset);
                time++;
                totalOfVirtualAddressesTranslated ++;
        }
        
        fclose(file);

        totalPageFaultRate = totalPageFaults / totalOfVirtualAddressesTranslated;

        printf("Number of Translated Addresses = %.0f\n", totalOfVirtualAddressesTranslated);
        printf("Page Faults = %.0f\n", totalPageFaults);
        printf("Page Fault Rate = %.3f\n", totalPageFaultRate);
}

int findLessUsedFrame() {
        int frameIndex = 0;
        int min = physicalMemory[0].lastTimeUsed;

        for (int i = 1; i < PHYSICAL_MEMORY_SIZE; i++) {
                
                if (physicalMemory[i].lastTimeUsed < min) {
                        min = physicalMemory[i].lastTimeUsed;
                        frameIndex = i;
                }
                
        }
        
        return frameIndex;
}

void addIfNotFullOrIfFifo(int currentPage, signed char temporaryArrayPage[256], int countPhysicalMemory) {
        passValuesFromBackStoreToFrame(temporaryArrayPage, countPhysicalMemory);
                                
        pageTable[currentPage].frame = countPhysicalMemory;
        pageTable[currentPage].isValid = VALID;

}

void passValuesFromBackStoreToFrame(signed char valuesFromBackStore[256], int frame) {

        for (int i = 0; i < 256; i++) {
                physicalMemory[frame].pageFromBackingStore[i] = valuesFromBackStore[i];
        }

        physicalMemory[frame].lastTimeUsed = time;
}

void findAndPutInvalidBitInPageTableForRelatedFrame(int frameToSearch) {

        for (int i = 0; i < 256; i++) {
                if (pageTable[i].frame == frameToSearch && pageTable[i].isValid == VALID) {
                        pageTable[i].isValid = NOT_VALID;
                        break;
                }
        }
}