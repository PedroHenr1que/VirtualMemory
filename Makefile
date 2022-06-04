CC = gcc
dirLibs = Libs/
OBJECTS = $(shell find Libs -name '*.o')

all: binTrans.o errorHandler.o backingStore.o arq.o vm

vm:  main.c 
	
	$(CC) $< -o $@ $(OBJECTS) -lpthread


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
	find Libs -name '*.o' -type f -delete 
	rm vm