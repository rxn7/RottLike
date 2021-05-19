OBJS = PlayerBase.o Sword.o MeleeWeapon.o Item.o JoinGameState.o RichText.o Chat.o GameState.o Textbox.o MainMenuState.o ServerClient.o Input.o Button.o Utils.o SplashScreenState.o Tilemap.o NameTag.o Entity.o Server.o Client.o Game.o FpsTimer.o AssetManager.o Main.o LocalPlayer.o OnlinePlayer.o

SRCS = -c src/States/*.cpp -c src/Engine/*.cpp -c src/Engine/Rendering/*.cpp -c src/Engine/Networking/*.cpp -c src/Engine/GUI/*.cpp -c src/*.cpp -c include/SFML/Graphics/*.cpp -c src/Item/*.cpp

INCLUDES = -I src -I include 

lin: compile lin_link

win: compile win_link

compile:
	g++ -Wall $(INCLUDES) $(SRCS)	
lin_link:
	g++ $(OBJS) -o bin/RottLike -L /usr/local/lib -l sfml-system -l sfml-window -l sfml-graphics -l sfml-network -lpthread
win_link:
	g++ $(OBJS) -o bin/RottLike.exe -L /usr/local/lib -l sfml-system -l sfml-window -l sfml-graphics -l sfml-network
