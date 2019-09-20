
#ifndef TMXCONFIGMANAGER_H
#define TMXCONFIGMANAGER_H
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
/**
 * @todo write docs
 */
class TMXConfigManager
{
public:

    bool load(std::string filename);

    std::vector<Layer>* getTileLayers();
    std::vector<Tileset>*  getTilesets();
    std::vector<Animation>* getAnimations();
    tmx::Map mTMXMap;

};

#endif // TMXCONFIGMANAGER_H
