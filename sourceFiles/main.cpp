//#include<iostream>
//#include"event.h"
#include"Game.h"
using namespace std;
int main()
{
    //srand time
    srand(time(NULL));

    //Init game engine
    Game game;
    
    while(game.running())
    {
        //Update
        game.update();


        //Render
        game.render();
   }

    return 0;
}