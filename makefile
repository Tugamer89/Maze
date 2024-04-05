compile:./main.cpp
	g++ -c ./main.cpp ./drawer.cpp
	g++ main.o drawer.o -o maze -lsfml-graphics -lsfml-window -lsfml-system
	rm main.o drawer.o

run:
	./maze
