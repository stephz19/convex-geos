SOURCE_DIR=src/cpp/
HEADER_DIR=src/headers/
EXEC_FILE=main

all: Editor.o Representation.o
	g++ -c $(SOURCE_DIR)main.cpp -I$(HEADER_DIR)
	g++ -o main Editor.o Representation.o main.o -lsfml-graphics -lsfml-window -lsfml-system

Editor.o: $(SOURCE_DIR)Editor.cpp $(HEADER_DIR)Editor.hpp
	g++ -c $(SOURCE_DIR)Editor.cpp -I$(HEADER_DIR)

Representation.o: $(SOURCE_DIR)Representation.cpp $(HEADER_DIR)Representation.hpp
	g++ -c $(SOURCE_DIR)Representation.cpp -I$(HEADER_DIR)

clean:
	rm -rf $(EXEC_FILE)
	rm -rf *.o
