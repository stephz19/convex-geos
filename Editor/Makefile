SOURCE_DIR=src/cpp/
HEADER_DIR=src/headers/
EXEC_FILE=main
OBJ=Editor.o Representation.o

# generic rule for any .o dependency: depend on source and header, compile
%.o: $(SOURCE_DIR)%.cpp $(HEADER_DIR)%.hpp
	g++ -c $< -I$(HEADER_DIR)

all: $(OBJ)
	g++ -c $(SOURCE_DIR)main.cpp -I$(HEADER_DIR)
	g++ -o main $(OBJ) main.o -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -rf $(EXEC_FILE)
	rm -rf *.o
