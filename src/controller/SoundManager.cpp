

class SoundManager
{
    
    SoundManager * INSTANCE = NULL;
    
    // Sound states
    enum State
    {
      Undefined, // USed when uninitialised 
      Playing,
      Stopped,
      Paused
    };
   // enum State mBGMState = State.Undefined;
    
    // singleton
    SoundManager * getInstance()
    {
        if (INSTANCE == NULL) INSTANCE = new SoundManager();
        else return INSTANCE;
    }
    
    bool init(){
         //Initialize SDL_mixer
        if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        {
            SDL_Log( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
            return false;
        } 
    }
    
    
    void playBGM(char* filename){}
    
    void playFX(char* filename){}
    
    
};
