compile:./main.cpp
	g++ ./*.cpp -o maze -lsfml-graphics -lsfml-window -lsfml-system -Wno-narrowing

run:
	./maze
