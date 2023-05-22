
#include "userInterface.h"

#include "game.h"
#include "log.h"
#include <locale>
#include <codecvt>
int main(int argc, char *argv[]) {
    Log::Out("+++BEGIN+++");
    setlocale(LC_ALL, "");
    UserInterface::Init();

    Game g;
    g.LoadMap(0);
    
    g.Run();
    UserInterface::Exit();
    Log::Out("+++END+++");
}