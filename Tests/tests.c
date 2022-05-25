#include <stdio.h>
#include <stdlib.h>

void checkArgs(int argc, char *argv[]) {

        if (argc < 4 || argc > 5) {
                printf("##### Error - Number of arguments do not match #####\n");
                printf("--- Enter the arguments again ---\n");
                printf("1 - <file>.txt (File with addresses)-> ");
                scanf("%s", argv[1]);
                
                printf("\n");

                printf("2 - Replacement algorithm for the page table (lru/fifo)-> ");
                scanf("%s", argv[2]);
                while (strcmp(argv[2], "fifo") != 0 || strcmp(argv[2], "lru") != 0) {
                        printf("\nError - Insert a valid algorithm (lru/fifo)");
                        printf("\nAlgorithm-> ");
                        scanf("%s", argv[2]);
                }

                printf("\n");

                printf("3 - Replacement algorithm for TLB (lru/fifo)-> ");
                scanf("%s", argv[3]);
                while (strcmp(argv[3], "fifo") != 0 || strcmp(argv[3], "lru") != 0) {
                        printf("\nError - Insert a valid algorithm (lru/fifo)");
                        printf("\nAlgorithm-> ");
                        scanf("%s", argv[3]);
                }

        } else {

                if (strcmp(argv[2], "fifo") != 0 || strcmp(argv[2], "lru") != 0) {
                        while (strcmp(argv[2], "fifo") != 0 || strcmp(argv[2], "lru") != 0) {
                                printf("\n### Error - Insert a valid algorithm for page table replacement (lru/fifo) ###");
                                printf("\nAlgorithm-> ");
                                scanf("%s", argv[2]);
                        }
                }

                printf("\n");
                
                if (strcmp(argv[3], "fifo") != 0 || strcmp(argv[3], "lru") != 0) {
                        while (strcmp(argv[3], "fifo") != 0 || strcmp(argv[3], "lru") != 0) {
                                printf("\n### Error - Insert a valid algorithm for TLB replacement (lru/fifo) ###");
                                printf("\nAlgorithm-> ");
                                scanf("%s", argv[3]);
                        }
                }
                
        }
        
}

void checkFile(char *fileName[]) {

        FILE *file;

        file = fopen(fileName, "r");

        if (file == NULL) {
                while (file == NULL) {
                        fclose(file);
                        printf("\nError - Could not open the file or it does not exist");
                        print("\nTry again - File Name-> ");
                        scanf("%s", fileName);
                        file = fopen(fileName, "r");
                }
        }

        fclose(file);
}