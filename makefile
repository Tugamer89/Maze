compile:
	g++ ./source/*.cpp -lsfml-graphics -lsfml-window -lsfml-system -Wno-narrowing -O3 -o maze

run:
	./maze
