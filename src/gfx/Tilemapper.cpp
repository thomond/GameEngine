#include "Tilemapper.h"


Tilemapper::Tilemapper(SDL_Renderer * r) {
    mRenderer = r;
}

Point Tilemapper::getTileCoords(int index) {
    // transform tilemap lindex to x,y absolure co-ords on tilesheet
    if(index!=0) index = index-1;
    int index_y = 0;
    if(index/mTiles.cols > 0)
        index_y=1;
    int index_x = abs((mTiles.cols *  index_y)-index);
    return Point(mTiles.dim.x * index_x, mTiles.dim.y * index_y);

}

Point Tilemapper::getTileCoords(Tileset& tileset,int index) {
    // transform tilemap lindex to x,y absolure co-ords on tilesheet
    if(index!=0) index = index-1;
    int index_y = 0;
    if(index/tileset.cols > 0)
        index_y=1;
    int index_x = abs((tileset.cols *  index_y)-index);
    return Point(tileset.dim.x * index_x, tileset.dim.y * index_y);

}





Texture * Tilemapper::randomize(SDL_Renderer * r, Point texDim) {

//     SDL_Surface * destSurface = SDL_CreateRGBSurface(0, texDim.x, texDim.y, 32, 0, 0, 0, 0);
//     for(int y=0; y<texDim.y; y += mTiles.dim.y)
//         for(int x=0; x<texDim.x;x += mTiles.dim.x)
//         {
//             Point srcTileIndex = getTileCoords(Random::randInt(0,mTiles.num));
//             SDL_Rect src = {srcTileIndex.x, srcTileIndex.y, mTiles.dim.x, mTiles.dim.y};
//             SDL_Rect dest = {x,y, mTiles.dim.x, mTiles.dim.y};
//             SDL_BlitSurface(mTiles.tilemap, &src , destSurface, &dest);
//         }
//
//     SDL_Texture * newTexture = SDL_CreateTextureFromSurface(r,destSurface);
//     if(!newTexture){
//         SDL_Log("Unable to load texture: %s\n",SDL_GetError());
}

Texture* Tilemapper::generateTexture(SDL_Renderer * renderer, std::vector<Tileset>& tilesets, Layer& layer)
{
    
    // generate layer texture
    SDL_Point gridSz = {layer.dim.x * tilesets[0].dim.x, layer.dim.y * tilesets[0].dim.y};
    SDL_Texture * newTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,gridSz.x,gridSz.y);
    SDL_SetTextureBlendMode(newTexture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(renderer,newTexture);


    for(int y=0; y < layer.dim.y ; y++) {
        for(int x=0; x < layer.dim.x ; x++) {
            // Get the needed tileset based on the Global tile ID of the layer
            auto tileset = getTilesetByGlobalID(layer.IDs[y][x],tilesets);
            
            SDL_Rect dstRect = { tileset.dim.x * x, tileset.dim.y * y, tileset.dim.x, tileset.dim.y };
            Point loc = getTileCoords(tileset, layer.IDs[y][x]);
            SDL_Rect srcRect = {loc.x, loc.y, tileset.dim.x, tileset.dim.y};
            // Add collision rects for layer
            for(int i=0; i<tileset.colliders.size(); i++) {
                if (layer.IDs[y][x] == tileset.colliders[i].ID) {
                    layer.colliders.push_back(dstRect);
                    layer.actionState = tileset.colliders[i].state;
                }
            }
            SDL_RenderCopy(renderer, tileset.tilemap,&srcRect, &dstRect );
        }
    }
    SDL_SetRenderTarget(renderer,NULL);
    return new Texture(newTexture,gridSz.x, gridSz.y);
}


Tileset& Tilemapper::getTilesetByGlobalID(int GlID, std::vector<Tileset>& tilesets)
{
    GlID++;
    for(Tileset& tileset : tilesets){
        if(GlID >= tileset.firstGID && GlID <= tileset.lastGID)
            return tileset;
    }
}

std::vector<SDL_Rect> Tilemapper::getGrid(SDL_Point gridDim, SDL_Point colsDim)
{
    std::vector<SDL_Rect> rects;
    for(int y=0; y<gridDim.y; y++)
        for(int x=0; x<gridDim.x; x++) {
            SDL_Rect r = {x*colsDim.x,y*colsDim.y,colsDim.x,colsDim.y};
            rects.push_back(r);
        }
    return rects;
}

