//functions to write in the archive
#include <stdio.h>

void writeInOutArchive(int virtualAddress, int physicalAddress, int value) {

        FILE *file = fopen("correct.txt", "a");

        fprintf(file, "Virtual address: %d Physical address: %d Value: %d\n", virtualAddress, physicalAddress, value);

        fclose(file);
}

void writeEndArchive(double totalOfVirtualAddressesTranslated, double totalPageFaults,
double totalPageFaultRate, double tlbHits, double tlbHitRate) {

        FILE *file = fopen("correct.txt", "a");

        fprintf(file,"Number of Translated Addresses = %.0f\n", totalOfVirtualAddressesTranslated);
        fprintf(file,"Page Faults = %.0f\n", totalPageFaults);
        fprintf(file,"Page Fault Rate = %.3f\n", totalPageFaultRate);
        fprintf(file,"TLB Hits = %.0f\n", tlbHits);
        fprintf(file,"TLB Hit Rate = %.3f\n", tlbHitRate);

        fclose(file);
}