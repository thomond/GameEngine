

class DisplayManager : Renderable
{

    SDL_Window* mWindow = NULL;
    SDL_Renderer* mRenderer = NULL;
    std::vector<Renderable*> mRenderPipeline;



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
        //mViewport = { 0, 0, scr_w, scr_h};
    }

    bool clear()
    {
        SDL_RenderClear(mRenderer);
    }

    // add renderable obj to render pipeline
    void addToRenderPipeline(Renderable * ren){
        if(ren==NULL){
            SDL_LogError(SDL_LOG_PRIORITY_WARN, "Renderable is NULL!...");
            return;
        }
        mRenderPipeline.push_back(ren);
    }

    // Process all Renderables
    void renderAll(){
        for(auto renderable : mRenderPipeline){
            renderable->render(mRenderer);
        }
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

    void render() {
        SDL_RenderPresent(mRenderer);
    }

    Texture * loadTexture(char * filename) {
        return Texture::loadFromFile(mRenderer,filename);
    }

};


