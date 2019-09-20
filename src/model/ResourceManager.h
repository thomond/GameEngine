
#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include "tmxconfigmanager.h"


/**
 * @todo write docs
 */
class ResourceManager
{
public:
    ResourceManager() {}
    void init();
    void init(SDL_Renderer * renderer,std::string filename );
    void loadFromTMX(std::string TMXFilename);
    void loadTilesets();
    void loadTileLayers();
    void loadSprites();
    std::vector<Layer>& getLayers() {
        return mLayers;
    }
    
    
    
private:
    std::vector<Layer> mLayers;
    std::vector<Tileset> mTilesets;
    std::vector<Sprite> mSprites;
    Tilemapper mTileMapper;
    TMXConfigManager mTMXConfig;
    


};



#endif // RESOURCEMANAGER_H
