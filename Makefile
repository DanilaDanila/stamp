COMPILER = g++
I_DIR = -I.
L_DIR = -L.
RESULT = samp

all: main.o
	$(COMPILER) main.o $(L_DIR) -o $(RESULT)
main.o: main.cpp
	$(COMPILER) -c main.cpp $(I_DIR)
clean:
	rm *.o $(RESULT)