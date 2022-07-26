build: exe lib
	
exe: gol.c main.c lib
	gcc main.c -fPIC -L. -lGol -o gameoflife
lib: gol.h gol.c
	gcc -shared gol.c -fPIC -o libGol.so
clean:
	-rm gameoflife libGol.so 2>/dev/null