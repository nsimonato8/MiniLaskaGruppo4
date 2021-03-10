FLAGS = -Wall --ansi --pedantic -lm -g3 -O3 -std=gnu89 -Wextra 

exe: ml_main.c ml_lib.o Autoplay.o
	gcc ml_main.c ml_lib.o Autoplay.o -o ml_main $(FLAGS)
		
Autoplay.o: ml_lib.o Autoplay.c Autoplay.h
	gcc -c Autoplay.c -o Autoplay.o $(FLAGS)

ml_lib.o: ml_lib.c ml_lib.h
	gcc -c ml_lib.c -o ml_lib.o $(FLAGS)
		
clean: 
	rm *.o
	rm ml_main
	
