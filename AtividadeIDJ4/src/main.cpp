#include <iostream>
using namespace std;
#include "SDL.h"
#include "SDL_include.h"
#include "Game.h"

int main(int argc, char* argv[])
{
   Game teste= Game::GetInstance();
   teste.~Game();
   system("pause");
    return 0;
}
