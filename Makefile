all: compile link

compile:
	g++ -I src\include -c sourceFiles\main.cpp sourceFiles\Game.cpp
link:
	g++ main.o Game.o -o flappybird.exe -L src\lib -l sfml-graphics -l sfml-window -l sfml-system