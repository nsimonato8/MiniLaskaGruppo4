FLAGS = -Wall --ansi --pedantic -lm -g3 -O3 -std=gnu89 -Wextra 

STACK_SIZE = 10000000

gdb: ml_main
	gdb ./ml_main

valgrind: ml_main
	valgrind --leak-check=full --show-leak-kinds=all --main-stacksize=$(STACK_SIZE) --track-origins=yes -v ./ml_main

ml_main: ml_lib.o Autoplay.o ml_main.o 
	gcc ml_main.o ml_lib.o Autoplay.o -o ml_main

ml_main.o: ml_main.c
	gcc -c ml_main.c -o ml_main.o $(FLAGS) 

ml_lib.o: ml_lib.c 
	gcc -c ml_lib.c -o ml_lib.o $(FLAGS)
		
Autoplay.o: ml_lib.o Autoplay.c Autoplay.h
	gcc -c Autoplay.c -o Autoplay.o $(FLAGS)

clean: 
	rm *.o
	rm ml_main
