#include "includes.h"
#ifndef TILEMAPPER_H
#define TILEMAPPER_H


struct Collider {
    int ID;
    int state;
};
// Structure representing a tileset
struct Tileset {
    int id=-1;
    std::string filename;
    std::string name;
    int firstGID;
    int lastGID;
    int num;
    int rows;
    int cols;
    SDL_Point dim;
    std::vector<Collider> colliders;
    SDL_Texture * tilemap;
};

class Tilemapper{

public:
    Tilemapper(){}
    Tilemapper(SDL_Renderer * r);
    void init( char * filename, SDL_Point tileDim, int tilesAmnt);
    void init(char * filename);
    Point getTileCoords(int index);
    static Point getTileCoords(Tileset& tileset,int index);
    Texture * randomize(SDL_Renderer * r , Point texDim);
    std::vector<SDL_Rect> getGrid(SDL_Point gridDim, SDL_Point colsDim);
    static Texture * generateTexture(SDL_Renderer *  renderer, std::vector<Tileset>& tilesets, Layer& layer);

     /*
     * Retirve a reference to a tileset struct based a global ID
     * Global ID is usually stored in layer
     */
    static Tileset& getTilesetByGlobalID(int GlID, std::vector<Tileset>& tilesets );
private:
    SDL_Renderer * mRenderer;
    
    Tileset mTiles;
    std::vector<Tileset> mTilesets;
    std::vector<Layer> mLayers;

};
#endif
