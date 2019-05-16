#ifndef TEXTURE_CPP
#define TEXTURE_CPP
#include "Texture.cpp"
#endif

class AssetManager{    
    SDL_Renderer * mRenderer;
    char * mDirectory;
    
    AssetManager(){}
    
    bool init(SDL_Renderer * r, char* fsDir){
        mRenderer = r;
        mDirectory = strcat(fsDir,"\\");
    }
        
    Texture * loadTexture(char * name){
        return Texture::loadFromFile(mRenderer,strcat(mDirectory,name));
        
    }
        
};
