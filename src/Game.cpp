//Game include
#ifndef SDL_H
#define SDL_H
#include "SDL2/SDL.h"
#endif
#ifndef SDL_MIXER_H
#define SDL_MIXER_H
#include "SDL2/SDL_mixer.h"
#endif
#ifndef SDL_IMAGE_H
#define SDL_IMAGE_H
#include "SDL2/SDL_image.h"
#endif
#ifndef SDL_TTF_H
#define SDL_TTF_H
#include "SDL2/SDL_ttf.h"
#endif
#ifndef SPRITE_H
#define SPRITE_H
#include "Sprite.cpp"
#endif
#include "DisplayManager.cpp"
#include "UIManager.cpp"
//#include "SoundManager.cpp"
#ifndef RENDERABLE_CPP
#define RENDERABLE_CPP
#include "Renderable.cpp"
#endif
#ifndef UPDATEABLE_CPP
#define UPDATEABLE_CPP
#include "Updateable.cpp"
#endif
#ifndef EVENTHANDLER_CPP
#define EVENTHANDLER_CPP
#include "EventHandler.cpp"
#endif
#ifndef ACTOR_CPP
#define ACTOR_CPP
#include "Actor.cpp"
#endif
#include <vector>
class Game : public Renderable, public Updateable, public EventHandler
{
protected:
	// Screen renderer
	DisplayManager * display;
    UIManager * ui;
    //SoundManager * sound;
    // TODO: use List or Queue
    Actor * mActorList[8] = {NULL};
    int mActorAmnt = 0;
    
    int mCollisionRectAmnt;
    int mCollisionRectMax = 20;
    std::vector<SDL_Rect> mCollisionGrid;
	bool inLoop = true;
    bool DEBUG = true;
public:
	

    
	Game(){}

	bool init()
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

	// game looper
    void doLoop()
    {
        while(inLoop){
            SDL_Delay(30);
            clear();
            handleEvents();
            updateAll();
            renderAll();
        }
    }
    
    void handleEvents(){
        SDL_Event e;
        // Handle basic game evnts and then defer to any implemented event handler
        while(SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
                inLoop = false;
            if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
            {
                // adjust velocity
                switch(e.key.keysym.sym){
                    case SDLK_ESCAPE: inLoop = false; break;
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

    
	void clear(){
		display->clear();
        //SDL_RenderClear(renderer);
	}
	
	
	void updateAll(){
        int i=0;
        while(i!=mActorAmnt)
        {
            int ii=0;
            // Check collisions grid wiwith each acttor and determine if a collision will happen 
            while(ii!=mCollisionRectAmnt)
            {
                if(mActorList[i]->collidesWith(&mCollisionGrid[ii])){
                    mActorList[i]->setState(Entity::Blocked);// TODO: mmaybe chnage to modifyiable state
                }
                ii++;
            }
            // Call Actor update function after sttaes hav been set by game
            mActorList[i]->update();
            i++;
        }
        // Call game update virtual func
        update();
    }
	
	// Main Game rnderer function
	void renderAll(){  
        // Render BG texture if any
        display->renderLayer(0);
        display->renderLayer(1);
        // Render any actor stored
        int i=0;
        while(i!=mActorAmnt)
        {
            if(display->getViewPort()!=NULL)
                mActorList[i]->render(display->getRenderer(), Point(display->getViewPort()->x,display->getViewPort()->y));
            i++;
        }
        
        //if(DEBUG && mCollisionRectAmnt>0)
        //    SDL_RenderDrawRects(display->getRenderer(), mCollisionGrid,mCollisionRectAmnt);
        
        render(display->getRenderer());
        ui->render(display->getRenderer());
        display->render();
    }
    
    void addActor(Actor * actor){
        if(mActorAmnt==8) {
            SDL_LogError("Too many actors",NULL);
            return;
        }
        mActorList[mActorAmnt] = actor;
        mActorAmnt++;
    }
    
    
    void addCollisionRects(std::vector<SDL_Rect> rect)
    {
        for(SDL_Rect r : rect)
            addCollisionRect(r);
    }
    
    // Add new rect to collision grid
    void addCollisionRect(SDL_Rect& rect)
    {
        //mCollisionGrid[mCollisionRectAmnt] = rect;
        mCollisionGrid.push_back(rect);
        mCollisionRectAmnt++;
    }
};
