#include "ResourceManager.h"




void ResourceManager::init(SDL_Renderer * renderer, std::string filename)
{
    if(!mTMXConfig.load(filename))
        SDL_LogError("%s couldn' be loaded. ",filename.c_str());
    loadTileLayers();
    loadTilesets();
    for(auto& tileset : mTilesets){
            tileset.tilemap = Texture::loadTextureFromFile(renderer, tileset.filename.c_str());
            // Get rols and cols of map's tilesheet
            int w,h;
            SDL_QueryTexture(tileset.tilemap, NULL, NULL, &w, &h);
            tileset.cols = (w /  tileset.dim.x);
            tileset.rows = (h /  tileset.dim.y);
        }
    for(auto& layer : mLayers)
        layer.texture = Tilemapper::generateTexture(renderer, mTilesets, layer);
    
    loadSprites();
}


void ResourceManager::loadTileLayers()
{
    mLayers = *mTMXConfig.getTileLayers();
    //mLayers.assign(mTMXConfig.getTileLayers().begin(), mTMXConfig.getTileLayers().end());
}

void ResourceManager::loadTilesets()
{
    mTilesets = *mTMXConfig.getTilesets();
    //mTilesets.assign(mTMXConfig.getTilesets().begin(), mTMXConfig.getTilesets().end());
}

void ResourceManager::loadSprites()
{
    //Sprite sprite;
   // sprite.init(r, );
    
    //mSprites.push_back(Sprite())
    
    std::vector<Animation> anis =  *mTMXConfig.getAnimations();
    
    //mTilesets.assign(mTMXConfig.getTilesets().begin(), mTMXConfig.getTilesets().end());
}
