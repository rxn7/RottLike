all: compile link

compile:
	g++ -Os -I src -I include -c src/*.cpp include -c src/States/*.cpp include -c src/Engine/*.cpp include -c src/Engine/Networking/*.cpp include -c src/Engine/GUI/*.cpp
link:
	g++ chat.o textbox.o mainmenustate.o serverclient.o input.o button.o utils.o splashscreenstate.o Tilemap.o nametag.o gamestate.o entity.o statemachine.o server.o game.o networkmanager.o client.o fpstimer.o assetmanager.o main.o localplayer.o onlineplayer.o -o RottLike -L lib -l sfml-graphics -l sfml-window -l sfml-system -l sfml-audio -l sfml-network