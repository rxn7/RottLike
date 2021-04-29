all: compile link

compile:
	g++ -Os -I src -I include -c src/*.cpp include -c src/Engine/*.cpp include -c src/Engine/Networking/*.cpp  -c src/Engine/StateMachine/*.cpp
link:
	g++ entity.o statemachine.o server.o game.o networkmanager.o client.o fpstimer.o assetmanager.o main.o localplayer.o onlineplayer.o -o RottLike -L lib -l sfml-graphics -l sfml-window -l sfml-system -l sfml-audio -l sfml-network