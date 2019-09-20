
// Texture wrapper class
class Texture
{
	private:
	
	public:	
    // Color consts
	static constexpr SDL_Color COLOR_GREEN = {0,255,0};
	static constexpr SDL_Color COLOR_RED = {255,0,0};
	static constexpr SDL_Color COLOR_BLUE = {0,0,255};
	static constexpr SDL_Color COLOR_WHITE = {255,255,255};
	// init vars
	Texture(){
		tex = NULL;
		width = 0;
		height = 0;
	}
	
	// init vars
	Texture(SDL_Texture * _tex, int _w, int _h){
		tex = _tex;
		width = _w;
		height = _h;
	}
	
	
	~Texture(){
		free();
	}

    SDL_Texture * getSDL_Texture()
    {
        return tex;
    }
	
	static SDL_Surface * loadSurfacefromFile(char *  path){
        // Load img
		SDL_Surface * loadedSurface = IMG_Load(path);
		if (!loadedSurface){
			SDL_Log("Unable to load image: %s\n",IMG_GetError());
			return NULL;
		}
		// Set colour key
		SDL_SetColorKey(loadedSurface,SDL_TRUE,SDL_MapRGB(loadedSurface->format,0xff,0x00,0xff));
        
        return loadedSurface;
    }
	
	static SDL_Texture * loadTextureFromFile(SDL_Renderer * renderer, char *  path){
		return SDL_CreateTextureFromSurface(renderer,loadSurfacefromFile(path));
    }
	
	static Texture * loadFromFile(SDL_Renderer * renderer, char *  path){

		SDL_Texture * newTexture = loadTextureFromFile(renderer, path);
		if(!newTexture){
			SDL_Log("Unable to load texture: %s\n",SDL_GetError());
			return NULL;
		}
		int w,h;
		SDL_QueryTexture(newTexture,
                     NULL,
                     NULL,
                     &w,
                     &h);
		return new Texture(newTexture, w, h);
	}

	

	
	// Generates a flood filled prim for display of width and height
	// Uses SDL_FillRect (https://wiki.libsdl.org/SDL_FillRect)
	static Texture* generate(SDL_Renderer * renderer, Point dim, SDL_Color color, SDL_Color outlineColor){
		SDL_Texture * newTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,dim.x,dim.y);
		
        SDL_SetRenderTarget(renderer,newTexture);
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0x00);
        SDL_Rect rect = {0,0,dim.x,dim.y};
        SDL_RenderFillRect(renderer,&rect);
        SDL_SetRenderDrawColor(renderer, outlineColor.r, outlineColor.g, outlineColor.b, 0x00);
        SDL_RenderDrawRect(renderer,&rect);
        SDL_SetRenderDrawColor(renderer, 0,0,0, 0x00);
		SDL_SetRenderTarget(renderer,NULL);

		return  new Texture(newTexture, dim.x, dim.y);
    }

	static Texture* generate(SDL_Renderer * renderer, Point dim, SDL_Color color){
   
        return Texture::generate(renderer,dim,color,color);
    }
	
	static Texture* generateRandom(SDL_Renderer * renderer, int w, int h){
        SDL_Texture * newTexture = NULL;
		
		// Load img
		SDL_Surface * loadedSurface = SDL_CreateRGBSurface(0,w,h,32,0,0,0,0);
		
		// Set colour key
		SDL_SetColorKey(loadedSurface,SDL_TRUE,SDL_MapRGB(loadedSurface->format,0xff,0x00,0xff));
		newTexture = SDL_CreateTextureFromSurface(renderer,loadedSurface);
		if(!newTexture){
			SDL_Log("Unable to load texture: %s\n",SDL_GetError());
			return NULL;
		}
		
		SDL_SetRenderTarget(renderer,newTexture);
        
        for(int y=0;y<h;y++)
            for(int x=0;x<w;x++)
            {
                int r,g,b;
                r = Random::randInt(0,255);
                g = Random::randInt(0,255);
                b = Random::randInt(0,255);
                SDL_SetRenderDrawColor(renderer, r,g,b,255);
                SDL_RenderDrawPoint(renderer,x,y);
            }

        SDL_SetRenderTarget(renderer,NULL);
        
		int width = loadedSurface->w;
		int height = loadedSurface->h;
		SDL_FreeSurface(loadedSurface);
		return  new Texture(newTexture,width, height);
    }
	
	static void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
    {
        uint * target_pixel = ( uint *) surface->pixels + y * surface->pitch + x * sizeof * target_pixel;
        *target_pixel = pixel;
    }
    
	// Renders text to texture
	bool loadFromRenderedText(SDL_Renderer * renderer,TTF_Font * textFont,char * text, SDL_Color textColor)
	{
		// Remove any previous image
		free();
		//The final texture to be returned
		SDL_Texture * newTexture = NULL;
		
		// Load img
		SDL_Surface * loadedSurface = TTF_RenderText_Solid(textFont,text,textColor);
		if (!loadedSurface){
			SDL_Log("Unable to render: %s\n",TTF_GetError());
			return false;
		}
		// Set colour key
		//SDL_SetColorKey(loadedSurface,SDL_TRUE,SDL_MapRGB(loadedSurface->format,0xff,0x00,0xff));
		
		newTexture = SDL_CreateTextureFromSurface(renderer,loadedSurface);
		if(!newTexture){
			SDL_Log("Unable to load texture: %s\n",SDL_GetError());
			return false;
		}
		width = loadedSurface->w;
		height = loadedSurface->h;
		SDL_FreeSurface(loadedSurface);
		tex =  newTexture;
		
		return tex != NULL;
	}
	
	// Set color modulation
	void setColor(Uint8 r, Uint8 g, Uint8 b)
	{
		return;
	}
	
	void free(){
		if (tex != NULL)
		{
			SDL_DestroyTexture(tex);
			tex = NULL;
			width = 0;
			height = 0;
		}
	}
	
	void render(SDL_Renderer * renderer, int x, int y){
		SDL_Rect  renderQuad = {x,y,width,height};
		// Render texture to screen
		SDL_RenderCopy(renderer, tex,NULL,&renderQuad);
	}
	
	void render(SDL_Renderer * renderer, SDL_Rect rect){
		render(renderer,rect.x,rect.y);
	}
	
	void render(SDL_Renderer * renderer, Point loc){
		render(renderer,loc.x,loc.y);
	}

	int getWidth(){
		return width;
	}
	int getHeight(){
		return height;
	}

protected:
		SDL_Texture * tex;
		int width;
		int height;		
};

