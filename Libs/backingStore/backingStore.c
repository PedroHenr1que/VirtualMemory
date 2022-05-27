#include <stdio.h>

// struct physicalMemoryFrame {
//         signed char pageFromBackingStore[256];
// };

// void findPageInBackingStore(int page, signed char returnArray[256]);

// int main() {

//         struct physicalMemoryFrame physicalMemory[256];
//         signed char returnedValues[256];
//         findPageInBackingStore(66, returnedValues);

//         for (int i = 0; i < 256; i++) {
//                 printf("%d Valor %d\n", i,returnedValues[i]);
//         }
        
// }

void findPageInBackingStore(int page, signed char returnArray[256]) {

        FILE *file;
        signed char valuesFromBackingStore[256];
        file = fopen("BACKING_STORE.bin", "rb");
        int pageStartInBackingStore = page * 256;
        
        fseek(file, pageStartInBackingStore, SEEK_SET);

        fread(valuesFromBackingStore, sizeof(signed char), 256, file);
        
        fclose(file);

        for (int i = 0; i < 256; i++) {
                returnArray[i] = valuesFromBackingStore[i];
        }
}