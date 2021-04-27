all: compile link

compile:
	g++ -I src -I include -c src/*.cpp
link:
	g++ localplayer.o fpstimer.o assetmanager.o entity.o main.o -o RottLike -L lib -l sfml-graphics -l sfml-window -l sfml-system -l sfml-audio