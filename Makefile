COMPILER = g++
I_DIR = -I.
L_DIR = -L.
SFML = -lsfml-window -lsfml-graphics -lsfml-system
RESULT = stamp

all: main.o
	$(COMPILER) main.o $(L_DIR) $(SFML) -o $(RESULT)
main.o: main.cpp
	$(COMPILER) -c main.cpp $(I_DIR)
clean:
	rm *.o $(RESULT)