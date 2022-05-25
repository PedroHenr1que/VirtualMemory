#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkArgs(int argc, char *argv[]);
int checkIfFileExistAndCanBeOpen(char *file[]);
//int checkFileFormat(char *file[]);

int main(int argc, char *argv[]) {
        //checkArgs(argc, argv);
        //checkFileFormat("BACKING_STORE.bin");

}

int checkArgs(int argc, char *argv[]) {

        int result = 0;

        if (argc < 4 || argc > 4) {
                printf("############################ ERROR ############################\n");
                printf("# Number of arguments necessary for execution do not match\n");
                printf("# The necessary is 3 arguments\n");
                printf("# First - File with virtual addresses, it must be a .txt\n");
                printf("# Second - The page table replacement algorithm\n");
                printf("###############################################################\n");

                result += -1;

        } else {

                // if (checkFileFormat(argv[1]) == -1) {
                //         result += -1;
                // }

                if (checkIfFileExistAndCanBeOpen(argv[1]) == -1) {
                        result += -1;
                }
                
                if (strcmp(argv[2], "fifo") != 0 && strcmp(argv[2], "lru") != 0) {
                        printf("############################ ERROR ############################\n");
                        printf("# Invalid Page Table replacement algorithm\n");
                        printf("# %s is not a valid algorithm, the options are fifo or lru\n", argv[2]);
                        printf("###############################################################\n");
                        
                        result += -1;
                }

                if (strcmp(argv[3], "fifo") != 0 && strcmp(argv[3], "lru") != 0) {
                        printf("############################ ERROR ############################\n");
                        printf("# Invalid TLB replacement algorithm\n");
                        printf("# %s is not a valid algorithm, the options are fifo or lru\n", argv[3]);
                        printf("###############################################################\n");

                        result += -1;
                }
                
        }
        
        return result;
}

int checkIfFileExistAndCanBeOpen(char *fileName[]) {

        FILE *file;

        file = fopen(fileName, "r");

        if (file == NULL) {
                printf("############################ ERROR ############################\n");
                printf("# Could not open the file (%s) or it does not exist\n", fileName);
                printf("###############################################################\n");

                return -1;

        } else {
                return 0;

        }

        fclose(file);
}

// int checkFileFormat(char *file[]) {
//         printf("Checking %s\n", file);

//         int indexPoint = 0;

//         for (int i = 0; i < 20; i++) {
//                 if (strcmp(file[i], ".") == 0) {
//                         indexPoint = i;
//                         break;
//                 }
//         }

//         char format[5];

//         for (int i = 0; i < 5; i++) {
//                 format[i] = file[indexPoint];
//                 indexPoint++;
//         }

//         printf("Format %s\n", format);

//         if (strcmp(format, ".txt") != 0) {
//                 printf("############################ ERROR ############################\n");
//                 printf("# Format of the file does not match, it must be a .txt\n");
//                 printf("# But it is %s\n", format);
//                 printf("###############################################################\n");

//                 return -1;

//         } else {
//                 return 0;

//         }
           
// }