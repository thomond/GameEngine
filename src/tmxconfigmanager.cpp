#include "tmxconfigmanager.h"

bool TMXConfigManager::load(char* filename)
{
     if(mTMXMap.load(filename))
     {
          
//          for (auto& tl : mTMXMap.getLayers())
//           {
//              mTMXTilelayer.push_back(tl);
//           }
//           for (auto& ts : mTMXMap.getTilesets())
//           {
//              mTMXTileset.push_back(ts);
//           }
         
     }else return false;
    
}


std::vector<Layer>* TMXConfigManager::getTileLayers()
{
    std::vector<Layer> * returnedLayers = new std::vector<Layer>();
    
    auto& TMXTilelayer = mTMXMap.getLayers();
    // Iterate through each defined layer
    // Populate layer struct and also generate texture
    for(auto& layer : TMXTilelayer){
        Layer mLayer;
        mLayer.name =  layer->getName();
        mLayer.dim = {mTMXMap.getTileCount().x, mTMXMap.getTileCount().y};
        
        if(layer->getType() == tmx::Layer::Type::Tile)
        {
            auto& tileLayer = layer->getLayerAs<tmx::TileLayer>();
            auto& tiles = tileLayer.getTiles();
            int i=0; // Tile index
            for(int y=0;y<mLayer.dim.y;y++)
            {
                // TMX uses 1d array to store grid of tiles
                // splits tile ID data into rows for convienence sakel
                std::vector<int> layerRow;
                for(int x=0;x<mLayer.dim.x;x++){
                    layerRow.push_back(tiles[i++].ID);
                }
                mLayer.IDs.push_back(layerRow);
            }
        }
        returnedLayers->push_back(mLayer);
    }

    
    return returnedLayers;
}

std::vector<Tileset>* TMXConfigManager::getTilesets()
{
        std::vector<Tileset>* returnedTiles = new std::vector<Tileset>();
        auto& TMXTilesets = mTMXMap.getTilesets();
        // Read tilesets and populate tiles data struct
        for(auto& tileset : TMXTilesets){
            Tileset tiles;
            
            tiles.filename = tileset.getImagePath();
            tiles.num = tileset.getTileCount();
            tiles.dim = {(int)tileset.getTileSize().x, (int)tileset.getTileSize().y};
            tiles.firstGID = tileset.getFirstGID();
            tiles.lastGID = tileset.getLastGID();
            // retrive properties in tileset if any
            for(auto tile : tileset.getTiles())
            {
                
                auto props = tile.properties;
                int id;
                int state;
                if(!props.empty()){
                    for(auto prop : props){// push ids of tiles which are collidable based on property set
                        //if(!prop.getName().compare("collider") ){
                        if(!prop.getName().compare("state") ){ // Check state value and push to tileset property 
                            //if(prop.getIntValue()==1)
                            //   state  =  Entity::State::Blocked;
                            state = prop.getIntValue();
                            tiles.colliders.push_back({(int)tile.ID,state});
                        }
                    }
                }
            }
            
            returnedTiles->push_back(tiles);
        }
    
    return returnedTiles;
}

std::vector<Animation>* TMXConfigManager::getAnimations()
{
    std::vector<Animation>* returnedAnis = new std::vector<Animation>();
    auto& TMXTilesets = mTMXMap.getAnimatedTiles();
     for(auto& tileset : TMXTilesets){
            auto& TMXAnis = tileset.second;
            Point imgSz = {(int)TMXAnis.imageSize.x,(int)TMXAnis.imageSize.y};
            Animation ani(tileset.first, TMXAnis.ID, imgSz);
            for(auto frame : TMXAnis.animation.frames){
                int frameid = frame.tileID - tileset.first; // tileID is stored as global ID; subtract firstGUID of tileset 
                Point framePos = {(int)(TMXAnis.imageSize.x * frameid), (int)TMXAnis.imagePosition.y };// pos is frame ID * tilesize and y pos of current animation
                ani.addFrame(framePos,frameid);
            }
        returnedAnis->push_back(ani);
            
     }
     return returnedAnis;
}
