CC = gcc
dirLibs = Libs/

all: binTrans.o errorHandler.o backingStore.o arq.o vm

vm:  main.c
	$(CC) $< -o $@ $(dirLibs)binTrans/binTrans.o $(dirLibs)ErrorHandler/errorHandler.o $(dirLibs)backingStore/backingStore.o $(dirLibs)outArchive/arq.o -lpthread

binTrans.o: $(dirLibs)binTrans/binTrans.c
	$(CC) -c $< -o $(dirLibs)binTrans/$@

errorHandler.o: $(dirLibs)ErrorHandler/errorHandler.c
	$(CC) -c $< -o $(dirLibs)ErrorHandler/$@

backingStore.o: $(dirLibs)backingStore/backingStore.c
	$(CC) -c $< -o $(dirLibs)backingStore/$@

arq.o: $(dirLibs)outArchive/arq.c
	$(CC) -c $< -o $(dirLibs)outArchive/$@

.PHONY: clean

clean:
	rm $(dirLibs)binTrans/binTrans.o $(dirLibs)ErrorHandler/errorHandler.o $(dirLibs)backingStore/backingStore.o $(dirLibs)outArchive/arq.o vm