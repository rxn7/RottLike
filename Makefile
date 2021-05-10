all: compile link

compile:
	g++ -Os -I src -I include -c src/States/*.cpp -c src/Engine/*.cpp -c src/Engine/Networking/*.cpp -c src/Engine/GUI/*.cpp -c src/*.cpp -c include/SFML/Graphics/*.cpp -c src/Item/*.cpp
link:
	g++ playerbase.o sword.o meleeweapon.o item.o joingamestate.o richtext.o chat.o gamestate.o textbox.o mainmenustate.o serverclient.o input.o button.o utils.o splashscreenstate.o Tilemap.o nametag.o entity.o statemachine.o server.o networkmanager.o client.o game.o fpstimer.o assetmanager.o main.o localplayer.o onlineplayer.o -o bin/RottLike -L lib -l sfml-graphics -l sfml-window -l sfml-system -l sfml-audio -l sfml-network