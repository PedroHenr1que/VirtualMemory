//functions to get data from backing_store
#include <stdio.h>

void findPageInBackingStore(int page, signed char returnArray[256]) {

        int pageStartInBackingStore = page * 256;

        FILE *file;
        file = fopen("BACKING_STORE.bin", "rb");
        fseek(file, pageStartInBackingStore, SEEK_SET);
        fread(returnArray, sizeof(signed char), 256, file);
        fclose(file);
}