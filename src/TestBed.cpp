#include "Game.cpp"
#include <iostream>
#include <vector>
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
class TestBed : public Game
{
private:
    Player * player;
    AIActor * aiactor;
    Tilemapper * tilemapper;
public:
    TestBed() : Game(){
        //Game();
    }
    
    void init(){
        Game::init("tilemap.tmx");
        Texture * tex = display->loadTexture( "tilesheet.png");
        Texture * tex2 = display->loadTexture("soldier_blk.png");
        // Set player colision rect, tdilemap tex,  and dimensions
        player = new Player();
        aiactor = new AIActor();
        SDL_Rect rect = {6,16,26,6};
        player->init(tex, Point(32,300), Point(32,32), rect);
        aiactor->init(tex2,Point(256,256), Point(32,32), rect );
        


        addStage("test_stage");
        // Add actor to game Actor queue
        getStage()->addActor(player);
        getStage()->addActor(aiactor);
        //getStage()->addLayer(0,tilemapper->getLayer("BGLayer"));
        //getStage()->addLayer(1,tilemapper->getLayer("FGLayer"));
        //loadFromTMX();
        
        // Add a toolbar
        //ui->addToolbar({0,0,display->getViewPort()->w,50},"test");
        
        // Create and set a tilemapper to random, set to bg layer of game
        //tilemapper = getTilemapper();
        //tilemapper->init("tilemap.tmx");
        
    
            
        
    


        
        display->setRenderScale(1.5);
    }
    

    
    void update(){
        aiactor->pivotTo(player->getPos());
        Point p = (player->getPos() - aiactor->getPos()).normalized();
        if(p.dot(aiactor->getDirection())>0)
        {
            aiactor->setSpeed(1);
        }else aiactor->setSpeed(0);
    }
    
    void handleEvent(SDL_Event& e){
        if (e.type == SDL_KEYDOWN)
        {
            switch(e.key.keysym.sym){
                case SDLK_l: mCurrStage->scrollViewport( 5, 0); break;
                case SDLK_j: mCurrStage->scrollViewport(-5, 0); break;
                case SDLK_i: mCurrStage->scrollViewport( 0,-5); break;
                case SDLK_k: mCurrStage->scrollViewport( 0,+5); break;
            }
        }
    }
    
    void vectorTest(){
        Point p1 = {1,2};
        Point p2 = {2,3};
        
        Point p3 = p1 + p2;
        SDL_Log("Output: %d,%d", p1.x , p1.y);
        SDL_Log("Output: %d,%d", p2.x , p2.y);
        SDL_Log("Output: %d,%d", p3.x , p3.y);
        p3 = p3 - Point(1,1);
        SDL_Log("Output: %d,%d", p3.x , p3.y);
    }
};

int main(){
    TestBed * game = new TestBed();
    game->init();
    game->doLoop();
    return 0;
}
