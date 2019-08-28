#include "Game.cpp"
#include <iostream>
#include <vector>

class Pacman : public Game{

    Pacman() : Game(){}
    
    void init(SDL_Point windowSz, char * title){
        Game::init();
        
        // create player
        Player * pacman = new Player();
        pacman->init(Texture::generate(display->getRenderer(),Point(32,32),{128,128,0}), Point(0,0), Point(32,32));
        
        // Create ghosts

        // build walls of level
        std::vector<SDL_Rect> walls;
        walls.push_back({64,64,128,8});
        Texture * foreground = Tilemapper::generate(display->getRenderer(),{800,600}, walls,{0,255,0},{0,255,0});
        
        addActor(pacman);
        
        display->setLayer(1,foreground);
    }
    

};
