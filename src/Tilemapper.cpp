#ifndef SDL_H
#define SDL_H
#include "SDL2/SDL.h"
#endif
#ifndef TEXTURE_CPP
#define TEXTURE_CPP
#include "Texture.cpp"
#endif
#ifndef UTIL_CPP
#define UTIL_CPP
#include "Util.cpp"
#endif

class Tilemapper{
public:
    Tilemapper(){}
    
    void init(char * filename, Point tileDim, int tilesAmnt){
        mTilemap = Texture::loadSurfacefromFile(filename);
        mTileDim = tileDim;
        mTilesAmnt = tilesAmnt;
    }
    
    Point getTileCoords(int index){
        return Point(mTileDim.x * index, 0);
    }

    /*
     * generate a texture of texDim dimensions using given tile tileIDs
     * Tile IDs can be translated to absolute tilemap co-ords using internal function
    */
    Texture * generate(SDL_Renderer * r , Point texDim, std::vector<int> tileIDs){
        SDL_Surface * destSurface = SDL_CreateRGBSurface(0, texDim.x, texDim.y, 32, 0, 0, 0, 0);
        SDL_SetColorKey(destSurface,SDL_TRUE,SDL_MapRGB(destSurface->format,0x00,0x00,0x00));
        int x=0,y=0;
        for(int& i : tileIDs){
            if(i=='\n'){ y++; x=0;} // New row
            else{ // Treat as column; get abs co-ords of tile on map and transpose to surface
                Point loc = getTileCoords(i);
                SDL_Rect src = {loc.x, loc.y, mTileDim.x, mTileDim.y};
                SDL_Rect dest = {x*mTileDim.x , y*mTileDim.y ,texDim.x, texDim.y};
                SDL_BlitSurface(mTilemap, &src , destSurface, &dest);
                x++;
            }
           
            SDL_Texture * newTexture = SDL_CreateTextureFromSurface(r,destSurface);
            if(!newTexture){
                SDL_Log("Unable to load texture: %s\n",SDL_GetError());
                return NULL;
            }
            int width = destSurface->w;
            int height = destSurface->h;
            SDL_FreeSurface(destSurface);
            return new Texture(newTexture, width, height);
                
                
            }
    }

    static Texture* generate(SDL_Renderer * r, Point dim, std::vector<SDL_Rect> rects, SDL_Color color, SDL_Color outlineColor){
        
        SDL_Texture * newTexture = SDL_CreateTexture(r, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,dim.x,dim.y);
        SDL_SetRenderTarget(r,newTexture);
        for(SDL_Rect rect : rects){
            SDL_SetRenderDrawColor(r, color.r, color.g, color.b, 0x00);
            Texture * recttex = Texture::generate(r,{rect.w,rect.h},color,outlineColor);
            SDL_RenderDrawRect(r,&rect);
            
        }
            
        SDL_SetRenderTarget(r,NULL);
        return  new Texture(newTexture, dim.x, dim.y);
    }
    
    Texture * generate(SDL_Renderer * r , Point texDim, std::vector<SDL_Rect> rects, std::vector<int> tileID){
        SDL_Surface * destSurface = SDL_CreateRGBSurface(0, texDim.x, texDim.y, 32, 0, 0, 0, 0);
        SDL_SetColorKey(destSurface,SDL_TRUE,SDL_MapRGB(destSurface->format,0x00,0x00,0x00));
        for(int i=0;i<rects.size();i++)
        {
            Point srcTileIndex = getTileCoords(tileID[i]);
            SDL_Rect src = {srcTileIndex.x, srcTileIndex.y, mTileDim.x, mTileDim.y};
            SDL_BlitSurface(mTilemap, &src , destSurface, &rects[i]);
        }
            
        SDL_Texture * newTexture = SDL_CreateTextureFromSurface(r,destSurface);
		if(!newTexture){
			SDL_Log("Unable to load texture: %s\n",SDL_GetError());
			return NULL;
		}
		int width = destSurface->w;
		int height = destSurface->h;
		SDL_FreeSurface(destSurface);
		return new Texture(newTexture, width, height);
    }
        
    Texture * randomize(SDL_Renderer * r , Point texDim){
        
        SDL_Surface * destSurface = SDL_CreateRGBSurface(0, texDim.x, texDim.y, 32, 0, 0, 0, 0);
        for(int y=0; y<texDim.y; y += mTileDim.y)
            for(int x=0; x<texDim.x;x += mTileDim.x)
            {
                Point srcTileIndex = getTileCoords(Random::randInt(0,mTilesAmnt));
                SDL_Rect src = {srcTileIndex.x, srcTileIndex.y, mTileDim.x, mTileDim.y};
                SDL_Rect dest = {x,y, mTileDim.x, mTileDim.y};
                SDL_BlitSurface(mTilemap, &src , destSurface, &dest);
            }
            
        SDL_Texture * newTexture = SDL_CreateTextureFromSurface(r,destSurface);
		if(!newTexture){
			SDL_Log("Unable to load texture: %s\n",SDL_GetError());
			return NULL;
		}
		int width = destSurface->w;
		int height = destSurface->h;
		SDL_FreeSurface(destSurface);
		return new Texture(newTexture, width, height);
    }
    
private:
    SDL_Surface * mTilemap;
    Point mTileDim;
    int mTilesAmnt;
};
