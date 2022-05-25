#include <stdio.h>
// Virtual address: 16916 Physical address: 20 Value: 0
// Virtual address: 62493 Physical address: 285 Value: 0
// Virtual address: 30198 Physical address: 758 Value: 29
// Virtual address: 53683 Physical address: 947 Value: 108
int main() {

        FILE *file;

        file = fopen("BACKING_STORE.bin", "rb");

        int *valor;

        fseek(file, 285, SEEK_SET);

        fread(valor, 256, 1, file);

        printf("Valor %d", *valor);

        fclose(file);
}