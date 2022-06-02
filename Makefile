CC = gcc

vm:
	CC main.c Libs/binTrans/binTrans.c Libs/ErrorHandler/errorHandler.c Libs/backingStore/backingStore.c Libs/outArchive/arq.c -o $@ -lpthread

.PHONY: clean

clean:
	rm vm