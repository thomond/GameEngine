#ifndef SDL_TTF_H
#define SDL_TTF_H
#include "SDL2/SDL_ttf.h"
#endif

#ifndef SDL_H
#define SDL_H
#include "SDL2/SDL.h"
#endif

#include "TextTexture.cpp"


class UIManager
{
protected:
    class Toolbar{
        TextTexture * mTextTexture = NULL;
        SDL_Rect rect;
        SDL_Color color;
        UIManager * UIManager;
        static const int PADDING_H = 15;
        static const int PADDING_V = 2;
        enum TextAlign {
            Right,
            Left,
            Top,
            Bottom,
        };
    public:
        Toolbar(class UIManager * parent, int x, int y, int w, int h, char* text ){
            UIManager = parent;
            rect = {x,y,w,h};
            color = TextTexture::COLOR_WHITE;
            
            mTextTexture = new TextTexture(parent->getFont(),TextTexture::COLOR_WHITE,text,x+PADDING_H,y+PADDING_V);
        }
        
        SDL_Rect * getRect(){
            return &rect;
        }
        
        void render(SDL_Renderer * r){
            SDL_RenderFillRect(r,&rect);
            if(mTextTexture != NULL) mTextTexture->render(r);
                
        }
    };
    
    
    UIManager * INSTANCE = NULL;
    TTF_Font * mFont = NULL;
    // TODO: chnage this to List or Hash map
    TextTexture * mTextTextures[8];
    int texIdx = 0;
    Toolbar * mToolbar;
    
    enum ScreenPosition
    {
      Undefined, // USed when uninitialised 
      Top,
      Bottom,
      Left,
      Right
    };
    //enum State mBGMState = State.Undefined;
    

public:
    // singleton
    UIManager * getInstance()
    {
        if (INSTANCE == NULL){ INSTANCE = new UIManager(); return INSTANCE;}
        else return INSTANCE;
    }
    
    UIManager() {}
    
    bool init(char* fontNm,char* fontSz){
        
		// Init TTF_lib
		if(TTF_Init()==-1){
			SDL_Log("TTF_Init: %s\n", TTF_GetError());
			return false;
		}
		mFont = TTF_OpenFont(fontNm, fontSz);
        if(!mFont) SDL_Log("TTF_OpenFont: %s\n", TTF_GetError());
        mToolbar = NULL;
    }
    
    TTF_Font * getFont(){
        return mFont;
    }
    
    void addText(char* text, int x, int y){
        mTextTextures[texIdx++] = new TextTexture(mFont,TextTexture::COLOR_WHITE,text,x,y);
    }
    
    void addToolbar(SDL_Rect renderRect, char * text)
    {
        mToolbar = new Toolbar(this,renderRect.x,renderRect.y,renderRect.w,renderRect.h,text);
    }
    
    void render(SDL_Renderer * r){
        for(int i=0;i<texIdx;i++)
        {
            mTextTextures[i]->render(r);
        }
        if(mToolbar!=NULL) mToolbar->render(r);
        
    }
};
