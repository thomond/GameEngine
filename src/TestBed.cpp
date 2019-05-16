#include "Game.cpp"
#include "Player.cpp"
#include "Tilemapper.cpp"
#include "AIActor.cpp"
#include <iostream>
#include <vector>

class TestBed : public Game
{
private:
    Player * player;
    AIActor * aiactor;
    Tilemapper * tilemapper;
public:
    TestBed(){
        Game();
    }
    
    void init(){
        Game::init();
        Texture * tex = display->loadTexture( "tilesheet.png");
        Texture * tex2 = display->loadTexture("soldier_blk.png");
        // Set player colision rect, tilemap tex,  and dimensions
        player = new Player();
        aiactor = new AIActor();
        SDL_Rect rect = {6,16,26,6};
        player->init(tex, Point(32,300), Point(32,32), rect);
        aiactor->init(tex2,Point(256,256), Point(32,32), rect );
        
        // Add actor to game Actor queue
        addActor(player);
        addActor(aiactor);
        // Add a toolbar
        ui->addToolbar({0,0,display->getViewPort()->w,50},"test");
        
        // Create and set a tilemapper to random, set to bg layer of game
        tilemapper = new Tilemapper();
        tilemapper->init("tiles.png",Point(32,32),9);
        Texture * background = tilemapper->randomize(display->getRenderer(), Point(1920,1080));
        //display->setLayer(0,background);
        
        // Add new rect to the game Collison grid in broder around stage
        std::vector<SDL_Rect> rects;
        std::vector<int> tileIDs;
        for(int y=0;y<1920/32;y++)
            for(int x =0; x<1080/32;x++)
                if(x==0||y==0) {
                    SDL_Rect r = {x*32,y*32,32,32};
                    tileIDs.push_back(8);
                    rects.push_back(r);
                }
        
        // Add a square box to test Enemy collision detection
        for(int y=6;y<=10;y++)
            for(int x =6; x<=10;x++){
                if(x==10 || y == 6 || x==6 || y==10){
                    SDL_Rect r = {x*32,y*32,32,32};
                    tileIDs.push_back(8);
                    rects.push_back(r);
                }

            }
            

        addCollisionRects(rects);
        int rgb[3] = {0,255,0};
        Texture * walls = Texture::generate(display->getRenderer(), {32, 32},{0,255,0},{0,255,0});
        //tilemapper->generate(display->getRenderer(), Point(1920,1080), rects , tileIDs);
        display->setLayer(1,walls);
        
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
                case SDLK_l: display->scrollViewport( 5, 0); break;
                case SDLK_j: display->scrollViewport(-5, 0); break;
                case SDLK_i: display->scrollViewport( 0,-5); break;
                case SDLK_k: display->scrollViewport( 0,+5); break;
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
