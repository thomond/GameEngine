//Game include

#include "includes.h"
#pragma once
class Game : public Updateable, public EventHandler
{

public:
    Game();

    bool init(std::string TMXFilename);

    // game looper
    void doLoop();
    void handleEvents();
    void clear();
    void updateAll();
    // Main Game rnderer function
    void renderAll();

    // Set stage by first entry in list or id
    int setStage();
    int setStage(std::string stage_name);
    int addStage(std::string stage_name);
    Stage *getStage(); // Returns current stage
    void loadFromTMX(char *TMXFilename);

protected:
    // Screen renderer
    DisplayManager *display;
    UIManager *ui;
    //SoundManager * sound;
    ResourceManager *resources;
    std::vector<Stage *> stages;
    Stage *mCurrStage;

    bool inLoop = true;
    bool DEBUG = true;
};

Game::Game() {}

bool Game::init(std::string TMXFilename)
{

    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        SDL_Log("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    }
    /* Enable standard application logging */
    SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);

    display = new DisplayManager();
    ui = new UIManager();
    //sound = SoundManager::getInstance();
    resources = new ResourceManager();

    display->init("Test", 1300, 1000);
    ui->init("RobotoSlab-Regular.ttf", 24);
    //sound->init();
    resources->init(display->getRenderer(), TMXFilename);
    stages = std::vector<Stage *>();

    return true;
}

// game looper
void Game::doLoop()
{
    while (inLoop)
    {
        SDL_Delay(30);
        clear();
        handleEvents();
        updateAll();
        renderAll();
    }
}

void Game::handleEvents()
{
    SDL_Event e;
    // Handle basic game evnts and then defer to any implemented event handler
    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
            inLoop = false;
        if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
        {
            // adjust velocity
            switch (e.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                inLoop = false;
                break;
            }
        }
        mCurrStage->handleEvent(e);
        handleEvent(e);
    }
}

void Game::clear()
{
    display->clear();
    //SDL_RenderClear(renderer);
}

void Game::updateAll()
{
    mCurrStage->update();
    // Call game update virtual func
    update();
}

// Main Game rnderer function
void Game::renderAll()
{
    mCurrStage->render(display->getRenderer());
    for (auto &layer : resources->getLayers())
    {
        for (SDL_Rect rect : layer.colliders)
        {
            //if(DEBUG && mCollisionRectAmnt>0)
            SDL_RenderDrawRect(display->getRenderer(), &rect);
        }
    }
    ui->render(display->getRenderer());
    display->render();
}

int Game::setStage(std::string stage_name)
{
    for (Stage *stage : stages)
    {
        if (stage->name == stage_name)
            mCurrStage = stage;
    }
}

// @brief Add new stage to game called @stage_name
int Game::addStage(std::string stage_name)
{
    Stage *stage = new Stage(stage_name, resources);
    stages.push_back(stage);
    mCurrStage = stage;
}

int Game::setStage()
{
    if (stages.empty())
        return -1;
    mCurrStage = stages[0];
    return 0;
}

Stage *Game::getStage()
{
    if (mCurrStage == NULL)
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "No Stage defined");
    return mCurrStage;
}
