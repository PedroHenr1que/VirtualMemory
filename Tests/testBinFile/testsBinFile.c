#include <stdio.h>
// Virtual address: 16916 Physical address: 20 Value: 0
// Virtual address: 62493 Physical address: 285 Value: 0
// Virtual address: 30198 Physical address: 758 Value: 29
// Virtual address: 53683 Physical address: 947 Value: 108
int main() {

        FILE *file;

        file = fopen("BACKING_STORE.bin", "rb");

        if (file == NULL) {
                printf("Não abriu");
        }
        

        int value[256];

        fseek(file, 16896, SEEK_SET);

        fread(&value, 256, 1, file);

        printf("\nValor %d", value[20]);

        fclose(file);
}