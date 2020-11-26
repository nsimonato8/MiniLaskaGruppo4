exe: ml_main.c ml_lib.o  
	gcc -o ml_main ml_main.c ml_lib.o -Wall --ansi --pedantic -lm -g3 -O3 -std=gnu89 -Wextra 
		
ip_lib.o: ml_lib.c ml_lib.h
	gcc -c ml_lib.c -o ml_lib.o -Wall --ansi --pedantic -lm -g3 -O3 -std=gnu89 -Wextra 
	
clean: 
	rm ml_lib.o
	
