SOURCE_DIR=src/cpp/

all:
	g++ -c $(SOURCE_DIR)main.cpp -Isrc/cpp/ -Isrc/headers/
	g++ main.o -o main
	rm -rf *.o
editor:
	g++ -c $(SOURCE_DIR)Editor.cpp -Isrc/cpp/ -Isrc/headers/
	g++ Editor.o -o editor -lsfml-graphics -lsfml-window -lsfml-system
	rm -rf *.o
clean:
	rm -rf editor main
