CC = gcc

vm: main.c
	CC $< -o $@

.PHONY: run clean

run:
	./vm

clean:
	rm vm