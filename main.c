#include <stdio.h>
#include <stdlib.h>
#include "Libs/binTrans/binTrans.h"

#define MAX_PAGE_NUMBER 256

int main(int argc, char *argv[]) {

        int returnArray[2];

        FILE *file;
        file = fopen(argv[1], "r");
        char stringNum[6];

        while ((fscanf(file, "%[^\n]", stringNum)) != EOF) {
                int addressBin = atoi(stringNum), page, offset;

                fgetc(file);
                getPageAndOffset(addressBin, returnArray);

                page = returnArray[0];
                offset = returnArray[1];

                printf("Address bin: %s - Page: %d - Offset: %d\n", stringNum, page, offset);
        }
        
        fclose(file);
}