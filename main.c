#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "Libs/binTrans/binTrans.h"
#include "Libs/ErrorHandler/errorHandler.h"
#include "Libs/backingStore/backingStore.h"
#include "Libs/outArchive/arq.h"

struct physicalMemoryFrame {
        int lastTimeUsed;
        signed char pageFromBackingStore[256];
};

struct pageTableElement {
        int frame;
        int isValid;
};

struct tlbElement {
        int page;
        int frame;
        int lastTimeUsed;
};

struct argsToSearchTLB {
        int indexToSearch;
        int pageToFind;
};

#define PHYSICAL_MEMORY_SIZE 128
#define TLB_SIZE 16
#define PAGE_TABLE_SIZE 256
#define VALID 1
#define NOT_VALID 0

void passValuesFromBackStoreToFrame(signed char valuesFromBackStore[256], int frame);
void findAndPutInvalidBitInPageTableForRelatedFrame(int frameToSearch);
int findLessUsedFrame();
int searchTlbThreads(int page);
void *searchPageInTLB(void *args);
void updateTLB(int newPage, int newFrame);
int findLessUsedPageTLB();


struct pageTableElement pageTable[PAGE_TABLE_SIZE];
struct physicalMemoryFrame physicalMemory[PHYSICAL_MEMORY_SIZE];
struct tlbElement tlb[TLB_SIZE];

int clk = 0;
int tlbIsFull = 0;
char *tlbReplacementAlgo;
int countTLB = 0;

int main(int argc, char *argv[]) {

        //Check if the args are wrong, if they are the program exit
        int checkErrors = checkArgs(argc, argv);
        if (checkErrors < 0) {
                exit(1);
        }

        //aux vars for replacement algo
        int countPhysicalMemory = 0;
        int fullPhysicalMemory = 0;

        //args
        char *virtualAddressesFile = argv[1];
        char *physicalMemoryReplacementAlgo = argv[2];
        tlbReplacementAlgo = argv[3];

        //statistics
        double totalOfVirtualAddressesTranslated = 0.0;
        double totalPageFaults = 0.0;
        double totalPageFaultRate = 0.0;
        double tlbHits = 0.0;
        double tlbHitRate = 0.0;

        //Initialize page table with invalid bit
        for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
                pageTable[i].isValid = NOT_VALID;
        }

        //Initialize tlb
        for (int i = 0; i < TLB_SIZE; i++) {
                tlb[i].page = -1;
        }
        
        //Contains the [0]page and the [1]offset in decimal
        int returnArray[2];

        //Vars to use in file managment
        FILE *file;
        file = fopen(virtualAddressesFile, "r");
        char virtualAddressStr[6];

        //####################################################################################
        while ((fscanf(file, "%[^\n]", virtualAddressStr)) != EOF) {
                //cast string address to decimal
                int virtualAddressDec = atoi(virtualAddressStr);
                int currentPage, currentOffset;
                int isInPageTable = 0;

                //get page and offset for the current address
                getPageAndOffset(virtualAddressDec, returnArray);

                currentPage = returnArray[0];
                currentOffset = returnArray[1];

                //#########################################################################
                //search in tlb through threads
                int indexFrameFromTlb = searchTlbThreads(currentPage);
                
                if (indexFrameFromTlb != -1) {
                        tlbHits++;
                        int physicalAddress = (tlb[indexFrameFromTlb].frame * 256) + currentOffset;
                        int value = physicalMemory[tlb[indexFrameFromTlb].frame].pageFromBackingStore[currentOffset];

                        //update tlb time
                        tlb[indexFrameFromTlb].lastTimeUsed = clk;

                        //update physical memory time
                        physicalMemory[tlb[indexFrameFromTlb].frame].lastTimeUsed = clk;

                        writeInOutArchive(virtualAddressDec, physicalAddress, value);

                        //allow to go to the next instruction
                        fgetc(file);
                } else {

                        while (isInPageTable == 0) {
                                
                                //if page is already in page table
                                if (pageTable[currentPage].isValid == VALID) {
                                        //find frame, then offset and print int
                                        int currentFrame = pageTable[currentPage].frame;
                                        int physicalAddress = (currentFrame * 256) + currentOffset;
                                        int value = physicalMemory[currentFrame].pageFromBackingStore[currentOffset];
                                        
                                        //update physical memory
                                        physicalMemory[currentFrame].lastTimeUsed = clk;

                                        writeInOutArchive(virtualAddressDec, physicalAddress, value);

                                        //update tlb if page it's not already there
                                        //search in tlb through threads
                                        if (searchTlbThreads(currentPage) == -1) {
                                                updateTLB(currentPage, currentFrame);
                                        }
                                        
                                        isInPageTable = 1;

                                        //allow to go to the next instruction
                                        fgetc(file);
                                } else {
                                        //page fault
                                        //find page in backingstore
                                        signed char temporaryArrayPage[256];
                                        findPageInBackingStore(currentPage, temporaryArrayPage);

                                        //if fifo or physical memory it's not full        
                                        if (fullPhysicalMemory == 0 || strcmp(physicalMemoryReplacementAlgo, "fifo") == 0) {
                                                findAndPutInvalidBitInPageTableForRelatedFrame(countPhysicalMemory);
                                                passValuesFromBackStoreToFrame(temporaryArrayPage, countPhysicalMemory);
                                        
                                                pageTable[currentPage].frame = countPhysicalMemory;
                                                pageTable[currentPage].isValid = VALID;

                                                updateTLB(currentPage, countPhysicalMemory);

                                        //lru
                                        } else {
                                                int lessUsedFrame = findLessUsedFrame();
                                                findAndPutInvalidBitInPageTableForRelatedFrame(lessUsedFrame);
                                                passValuesFromBackStoreToFrame(temporaryArrayPage, lessUsedFrame);

                                                physicalMemory[lessUsedFrame].lastTimeUsed = clk;

                                                pageTable[currentPage].frame = lessUsedFrame;
                                                pageTable[currentPage].isValid = VALID;

                                                updateTLB(currentPage, lessUsedFrame);
                                        }
                                        
                                        if (countPhysicalMemory == (PHYSICAL_MEMORY_SIZE - 1)) {
                                                fullPhysicalMemory = 1;
                                        }
                                        
                                        countPhysicalMemory = (countPhysicalMemory + 1) % PHYSICAL_MEMORY_SIZE;
                                        totalPageFaults ++;
                                        
                                        //read instruction and translate it again, because it was a page fault
                                        fscanf(file, "%[^\n]", virtualAddressStr);
                                        virtualAddressDec = atoi(virtualAddressStr);
                                        getPageAndOffset(virtualAddressDec, returnArray);
                                        currentPage = returnArray[0];
                                        currentOffset = returnArray[1];
                                }

                        }
                }
                
                clk++;
                totalOfVirtualAddressesTranslated ++;
        }
        
        fclose(file);

        totalPageFaultRate = totalPageFaults / totalOfVirtualAddressesTranslated;
        tlbHitRate = tlbHits / totalOfVirtualAddressesTranslated;

        writeEndArchive(totalOfVirtualAddressesTranslated, totalPageFaults, totalPageFaultRate, tlbHits, tlbHitRate);
        return 0;
}

//######################## TLB ########################
int searchTlbThreads(int page) {

        pthread_t threadsSearchTLB[TLB_SIZE];

        //create threads to search in tlb
        for (int i = 0; i < TLB_SIZE; i++) {
                struct argsToSearchTLB *argsToTLB = malloc(sizeof(struct argsToSearchTLB));
                argsToTLB->indexToSearch = i;
                argsToTLB->pageToFind = page;
                pthread_create(&threadsSearchTLB[i], NULL, searchPageInTLB, (void *)(size_t)argsToTLB);
        }

        //returns from threads
        int indexFrameFromTlb = -1;
        for (int i = 0; i < TLB_SIZE; i++) {
                int returnFromThread;
                pthread_join(threadsSearchTLB[i], (void *) &returnFromThread);
                if (returnFromThread != -1) {
                        indexFrameFromTlb = returnFromThread;
                }
                        
        }

        return indexFrameFromTlb;
}

void *searchPageInTLB(void *args) {
        
        struct argsToSearchTLB *argsCasted = (struct argsToSearchTLB *)(size_t) args;

        if (tlb[argsCasted->indexToSearch].page == argsCasted->pageToFind) {
                return ((void *) (size_t)argsCasted->indexToSearch);
        }
        
        return ((void *)-1);
}

int findLessUsedPageTLB() {
        int index = 0;
        int min = tlb[0].lastTimeUsed;

        for (int i = 1; i < TLB_SIZE; i++) {
                if (tlb[i].lastTimeUsed < min) {
                        min = tlb[i].lastTimeUsed;
                        index = i;
                }
                
        }
        return index;
}

void updateTLB(int newPage, int newFrame) {

        if (tlbIsFull == 0 || strcmp(tlbReplacementAlgo, "fifo") == 0) {
                tlb[countTLB].frame = newFrame;
                tlb[countTLB].page = newPage;
                tlb[countTLB].lastTimeUsed = clk;
                
        } else {
                int lessUsedIndex = findLessUsedPageTLB();
                tlb[lessUsedIndex].frame = newFrame;
                tlb[lessUsedIndex].page = newPage;
                tlb[lessUsedIndex].lastTimeUsed = clk;
        }       

        if (countTLB == (TLB_SIZE - 1)) {
                tlbIsFull = 1;
        }
        
        countTLB = (countTLB + 1) % TLB_SIZE;
}

//######################## Main Memory ########################
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

void passValuesFromBackStoreToFrame(signed char valuesFromBackStore[256], int frame) {

        for (int i = 0; i < 256; i++) {
                physicalMemory[frame].pageFromBackingStore[i] = valuesFromBackStore[i];
        }
}

//######################## Page Table ########################
void findAndPutInvalidBitInPageTableForRelatedFrame(int frameToSearch) {

        for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
                if (pageTable[i].frame == frameToSearch && pageTable[i].isValid == VALID) {
                        pageTable[i].isValid = NOT_VALID;
                        break;
                }
        }
}