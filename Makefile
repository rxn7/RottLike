all: compile link

compile:
	g++ -Os -I src -I include -c src/States/*.cpp include -c src/Engine/*.cpp include -c src/Engine/Networking/*.cpp include -c src/Engine/GUI/*.cpp include -c src/*.cpp include -c include/SFML/Graphics/*.cpp
link:
	g++ joingamestate.o richtext.o chat.o gamestate.o textbox.o mainmenustate.o serverclient.o input.o button.o utils.o splashscreenstate.o Tilemap.o nametag.o entity.o statemachine.o server.o networkmanager.o client.o game.o fpstimer.o assetmanager.o main.o localplayer.o onlineplayer.o -o RottLike -L lib -l sfml-graphics -l sfml-window -l sfml-system -l sfml-audio -l sfml-network