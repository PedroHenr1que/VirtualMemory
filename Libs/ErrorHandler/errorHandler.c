//functions to check errors
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkIfFileExistAndCanBeOpen(char fileName[]) {

        FILE *file;

        file = fopen(fileName, "r");

        if (file == NULL) {
                printf("############################ ERROR ############################\n");
                printf("# Could not open the file (%s) or it does not exist\n", fileName);
                printf("###############################################################\n\n");

                return -1;

        } else {
                
                return 0;
        }

        fclose(file);
}

int checkFileFormat(char fileName[]) {
        char *formatFromFileName = strstr(fileName, ".txt");
        
        if (formatFromFileName == NULL || strcmp(formatFromFileName, ".txt") != 0) {
                printf("############################ ERROR ############################\n");
                printf("# Format of the file does not match, it must be a .txt\n");
                printf("###############################################################\n\n");

                return -1;
        } else {
                
                return 0;
        }
}

int checkArgs(int argc, char *argv[]) {

        int result = 0;

        if (argc < 4 || argc > 4) {
                printf("############################ ERROR ############################\n");
                printf("# Number of arguments necessary for execution do not match\n");
                printf("# The necessary is 3 arguments\n");
                printf("# First - File with virtual addresses, it must be a .txt\n");
                printf("# Second - The physical memory replacement algorithm\n");
                printf("# Third - The TLB replacement algorithm\n");
                printf("###############################################################\n\n");

                result += -1;

        } else {

                if (checkFileFormat(argv[1]) == -1) {
                        result += -1;
                } else if (checkIfFileExistAndCanBeOpen(argv[1]) == -1) {
                        result += -1;
                }

                if (checkIfFileExistAndCanBeOpen("BACKING_STORE.bin") == -1) {
                        result += -1;
                }
                
                if (strcmp(argv[2], "fifo") != 0 && strcmp(argv[2], "lru") != 0) {
                        printf("############################ ERROR ############################\n");
                        printf("# Invalid physical memory replacement algorithm\n");
                        printf("# <%s> is not a valid algorithm, the options are fifo or lru\n", argv[2]);
                        printf("###############################################################\n\n");
                        
                        result += -1;
                }

                if (strcmp(argv[3], "fifo") != 0 && strcmp(argv[3], "lru") != 0) {
                        printf("############################ ERROR ############################\n");
                        printf("# Invalid TLB replacement algorithm\n");
                        printf("# <%s> is not a valid algorithm, the options are fifo or lru\n", argv[3]);
                        printf("###############################################################\n\n");

                        result += -1;
                }
                
        }
        
        return result;
}