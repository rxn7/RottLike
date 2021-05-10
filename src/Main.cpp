#include "Game.hpp"
#include <Windows.h>
//#define DEBUG

int main(int argc, const char** argv){
    #ifndef DEBUG
        ShowWindow(GetConsoleWindow(), SW_HIDE);
    #endif

    Game game;
}