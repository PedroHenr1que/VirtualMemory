#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Libs/binTrans/binTrans.h"
#include "Libs/ErrorHandler/errorHandler.h"
#include "Libs/backingStore/backingStore.h"

struct physicalMemoryFrame {
        signed char pageFromBackingStore[256];
};
struct pageTableElement {
        int frame;
        int isValid;
};

#define PHYSICAL_MEMORY_SIZE 128
#define VALID 1
#define NOT_VALID 0
int countPhysicalMemory = 0;
int fullPhysicalMemory = 0;

void passValuesFromBackStoreToFrame(signed char valuesFromBackStore[256]);
void findAndPutInvalidBitInPageTableForRelatedFrame();

struct pageTableElement pageTable[256];
struct physicalMemoryFrame physicalMemory[PHYSICAL_MEMORY_SIZE];


//phsycalMemory lista
//TLB lista

int main(int argc, char *argv[]) {

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

                                printf("Virtual address: %d Physical address: %d Value: %d\n", virtualAddressDec, physicalAddress, value);
                                
                                isInPageTable = 1;

                        } else { //page fault
                                //find in backingstore, update pageTable
                                if (strcmp(physicalMemoryReplacementAlgo, "fifo") == 0) {
                                        if (fullPhysicalMemory == 1) {
                                                findAndPutInvalidBitInPageTableForRelatedFrame();
                                        }
                                }
                                

                                signed char temporaryArrayPage[256];
                                findPageInBackingStore(currentPage, temporaryArrayPage);
                                passValuesFromBackStoreToFrame(temporaryArrayPage);
                                
                                pageTable[currentPage].frame = countPhysicalMemory;
                                pageTable[currentPage].isValid = VALID;
                                

                                if (countPhysicalMemory == 127) {
                                        fullPhysicalMemory = 1;
                                }
                                
                                countPhysicalMemory = (countPhysicalMemory + 1) % PHYSICAL_MEMORY_SIZE;
                                totalPageFaults ++;  
                        }
                }

                
                //printf("Virtual Address: %s - Page: %d - Offset: %d\n", stringNum, page, offset);

                totalOfVirtualAddressesTranslated ++;
        }
        
        fclose(file);

        totalPageFaultRate = totalPageFaults / totalOfVirtualAddressesTranslated;

        printf("Number of Translated Addresses = %.0f\n", totalOfVirtualAddressesTranslated);
        printf("Page Faults = %.0f\n", totalPageFaults);
        printf("Page Fault Rate = %.3f\n", totalPageFaultRate);
}

void passValuesFromBackStoreToFrame(signed char valuesFromBackStore[256]) {

        for (int i = 0; i < 256; i++) {
                physicalMemory[countPhysicalMemory].pageFromBackingStore[i] = valuesFromBackStore[i];
        }
        
}

void findAndPutInvalidBitInPageTableForRelatedFrame() {
        int frameToSearch = countPhysicalMemory;
        for (int i = 0; i < 256; i++) {
                if (pageTable[i].frame == frameToSearch && pageTable[i].isValid == VALID) {
                        pageTable[i].isValid = NOT_VALID;
                        break;
                }
        }
}