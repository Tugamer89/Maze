compile:./main.cpp
	g++ ./main.cpp ./drawer.cpp -o maze -lsfml-graphics -lsfml-window -lsfml-system -Wno-narrowing

run:
	./maze
