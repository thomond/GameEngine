#include "includes.h"
#include "Texture.cpp"

/*
    * Represents a tiled layer composited from a tileset
    * Also contains collison detection information
    */
struct Layer {
    int id = -1;
    std::vector<std::vector<int>> IDs;
    Texture * texture;
    std::string name;
    SDL_Point dim;
    std::vector<SDL_Rect> colliders;
    int actionState = -1;
    void (*actionFunc)() = NULL;
    std::string tilesetName;
};

#include "TextTexture.cpp"
#include "Animated.cpp"
#include "Sprite.cpp"
#include "Tilemapper.cpp"
#include "tmxconfigmanager.cpp"

class DisplayManager : Renderable
{

    SDL_Window* mWindow = NULL;
    SDL_Renderer* mRenderer = NULL;

    SDL_Rect mViewport = {0};
    Point stageDim = Point(1000,1000);
    Texture * mBgTexture = NULL;
    std::vector<Texture *> mFgTexture;




public:
    static DisplayManager * INSTANCE = NULL;
    // singleton
    static  DisplayManager * getInstance()
    {
        if (DisplayManager::INSTANCE == NULL) {
            DisplayManager::INSTANCE = new DisplayManager();
            return DisplayManager::INSTANCE;
        }
        else return DisplayManager::INSTANCE;
    }

    // Returns  blank SDL_Texture that can be set as render target
    static SDL_Texture*  createNewTargetTexture(SDL_Renderer* renderer, int w, int h) {
        return SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);// SDL_TEXTUREACCESS_TARGET must be set
    }

    DisplayManager() {}

    SDL_Rect * getViewPort() {
        if (mViewport.w == 0 && mViewport.h == 0) return NULL;
        return &mViewport;

    }

    void scrollViewport(int x, int y) {
        // TODO: check bounds of camera
        mViewport.x += x;
        mViewport.y += y;
    }

    bool init(char* title, int scr_w, int scr_h) {
        // create main mWindow and renderer
        // Show mWindow
        mWindow = SDL_CreateWindow(title,SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, scr_w, scr_h, SDL_WINDOW_SHOWN);
        if (!mWindow) {
            SDL_Log("Window could not be created",SDL_GetError());
            return false;
        }

        // Create renderer
        mRenderer = SDL_CreateRenderer(mWindow,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC|SDL_RENDERER_TARGETTEXTURE);
        if(!mRenderer) {
            SDL_Log("renderer could not be created",SDL_GetError());
            return false;
        }
        // load support for the PNG image formats
        int flags = IMG_INIT_PNG;
        int initted=IMG_Init(flags);
        if((initted&flags) != flags) {
            SDL_Log("IMG_Init: Failed to init required image support!\n");
            SDL_Log("IMG_Init: %s\n", IMG_GetError());
            return false;
        }
        // Renderer BG color
        SDL_SetRenderDrawColor(mRenderer, 0x00,0x00,0x00,0x00);
        // Set mViewport to start pos of stage
        mViewport = { 0, 0, scr_w, scr_h};
    }

    bool clear()
    {
        SDL_RenderClear(mRenderer);
    }

    bool setRenderScale(float scale) {
        SDL_RenderSetScale(mRenderer,scale,scale);
    }

    SDL_Renderer * getRenderer() {
        return mRenderer;
    }

    bool * setRenderer(SDL_Renderer * r) {
        mRenderer = r;
    }

    /* Render a src texture to a destination texture, e.g. layer. Texture nust have the right flags
    bool renderTo(SDL_Texture *texSrc, SDL_Texture *texDest){
        SDL_SetRenderTarget(mRenderer, texDest);

        //SDL_SetRenderTarget(mRenderer, texDest);
    }*/


    // Directly Render layer by index
    void renderLayer(int layerID) {
        if (layerID == 0 && mBgTexture != NULL)
            // render relative to viewport
            mBgTexture->render(mRenderer,-mViewport.x, -mViewport.y);
        else if (layerID > 0 && !mFgTexture.empty())
            for(auto tex : mFgTexture)
                // render relative to viewport
                tex->render(mRenderer,-mViewport.x, -mViewport.y);
        //else SDL_Log("Layer not defined: %d",layerID);
    }

    // Set layer texture
    void setLayer(int layerID, Texture* tex) {
        if (layerID == 0) {
            mBgTexture = tex;
        }
        else if (layerID > 0) {
            mFgTexture.push_back(tex);
        } else SDL_Log("Layer not defined: %d",layerID);
    }


    void render() {
        SDL_RenderPresent(mRenderer);
    }

//     bool render(Renderable r) {
//         r.render();
//         SDL_RenderPresent();
//     }

    Texture * loadTexture(char * filename) {
        return Texture::loadFromFile(mRenderer,filename);
    }

};


