//Game include


#include "includes.h"
#pragma once
class Game : public Updateable, public EventHandler
{

public:



    Game();

    bool init();

    // game looper
    void doLoop();
    void handleEvents();
    void clear();
    void updateAll();
    // Main Game rnderer function
    void renderAll();
    void addActor(Actor * actor);
    int addLayer(int priority, Layer& layer);
    int addBGLayer(Texture * tex);
    int addFGLayer(Texture * tex, std::vector<SDL_Rect> rect, const char * name, Entity::State actionState);
    void loadFromTMX(char * TMXFilename);

protected:
    // Screen renderer
    DisplayManager * display;
    UIManager * ui;
    //SoundManager * sound;
    ResourceManager resources;
    Tilemapper * mTileMapper;
    // TODO: use List or Queue
    Actor * mActorList[8] = {NULL};
    int mActorAmnt = 0;

    int mCollisionRectAmnt;
    int mCollisionRectMax = 20;

    bool inLoop = true;
    bool DEBUG = true;
};

Game::Game() {}

bool Game::init()
{


    // Init SDL
    if ( SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO)< 0 )
    {
        SDL_Log("SDL could not initialize! SDL Error: %s\n",SDL_GetError());
        return false;
    }
    /* Enable standard application logging */
    SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);

    display = new DisplayManager();
    ui = new UIManager();
    //sound = SoundManager::getInstance();


    display->init("Test",1300,1000);
    ui->init("RobotoSlab-Regular.ttf",24);
    //sound->init();
    return true;
}

void Game::loadFromTMX(char * TMXFilename) {
    resources.init(display->getRenderer(), TMXFilename);
    int pri=0;
    for(auto& layer : resources.getLayers()) {

        addLayer(pri++,layer);
    }
}

// game looper
void Game::doLoop()
{
    while(inLoop) {
        SDL_Delay(30);
        clear();
        handleEvents();
        updateAll();
        renderAll();
    }
}

void Game::handleEvents() {
    SDL_Event e;
    // Handle basic game evnts and then defer to any implemented event handler
    while(SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
            inLoop = false;
        if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
        {
            // adjust velocity
            switch(e.key.keysym.sym) {
            case SDLK_ESCAPE:
                inLoop = false;
                break;
            }
        }
        int i;
        while(i!=mActorAmnt)
        {
            mActorList[i]->handleEvent(e);
            i++;
        }
        handleEvent(e);
    }
}


void Game::clear() {
    display->clear();
    //SDL_RenderClear(renderer);
}


void Game::updateAll() {
    int i=0;
    while(i!=mActorAmnt)
    {

        // For each collision grid check if there's a collison and either set the actor's state or call a callback func
        for(auto& layer : resources.getLayers())
        {
            if(layer.colliders.empty()) continue;// No Colliders in layer
            for(SDL_Rect rect :  layer.colliders )
            {
                if(layer.actionFunc != NULL) {
                    if(mActorList[i]->collidesWith(&rect))
                        layer.actionFunc();
                }
                if(layer.actionState!=NULL) {
                    if(mActorList[i]->collidesWith(&rect))
                        mActorList[i]->setState(layer.actionState);
                }

            }

        }
        // Call Actor update function after sttaes hav been set by game
        mActorList[i]->update();
        i++;
    }
    // Call game update virtual func
    update();
}

// Main Game rnderer function
void Game::renderAll() {
    // Render BG texture if any
    display->renderLayer(0);
    display->renderLayer(1);

    // Render any actor stored
    int i=0;
    while(i!=mActorAmnt)
    {
        if(display->getViewPort()!=NULL)
            mActorList[i]->render(display->getRenderer(), mActorList[i]->getPosx(), mActorList[i]->getPosy(), Point(display->getViewPort()->x,display->getViewPort()->y));
        i++;
    }
    for(auto& layer : resources.getLayers()) {
        for(SDL_Rect rect :  layer.colliders )
        {
            //if(DEBUG && mCollisionRectAmnt>0)
            SDL_RenderDrawRect(display->getRenderer(), &rect);
        }
    }
    ui->render(display->getRenderer());
    display->render();
}


void Game::addActor(Actor * actor) {
    if(mActorAmnt==8) {
        SDL_LogError("Too many actors",NULL);
        return;
    }
    mActorList[mActorAmnt] = actor;
    mActorAmnt++;
}

int Game::addLayer(int priority, Layer& layer)
{
    //resources.getLayers().push_back(layer);
    display->setLayer(priority, layer.texture);

}

int Game::addBGLayer(Texture * tex) {
    display->setLayer(0,tex);
    return 0;
}


int Game::addFGLayer(Texture * tex, std::vector<SDL_Rect> rect, const char * name, Entity::State actionState)
{
    display->setLayer(1,tex);
    //addCollisionRects(rect,name,actionState);
    return 0;
}
