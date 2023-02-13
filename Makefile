CFLAGS = -Wall #-B -O3

all:    paralelo.cpp generateinput.c
	mpic++ paralelo.cpp -o teste $(CFLAGS)
	gcc generateinput.c -o generateinput

print: all
print: CFLAGS += -DPRINT

clean: 
	rm -f teste generateinput
