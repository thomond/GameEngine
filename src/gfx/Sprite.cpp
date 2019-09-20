#include "includes.h"


class Sprite : public Renderable
{
private:

    int mAnimationIndex;
    int mAnimationAmnt;
    static const int mAnimationMax = 4;
    Point mDim;
    Animation * mAnimations[mAnimationMax]; // 4 max animations
    Texture * mTilesheet = NULL;

public:

    Sprite() {}

    bool init(SDL_Renderer * r, char * srcFile, int _w, int _h) {
        // Load a new texture
        mTilesheet = Texture::loadFromFile(r,srcFile);
        mDim = Point(_w,_h);
        mAnimationIndex=-1;
        mAnimationAmnt=0;
    }

    bool init(Texture * tex, Point dim) {
        mTilesheet = tex;
        mDim = dim;
        mAnimationIndex=-1;
        mAnimationAmnt=0;
    }


    bool init(SDL_Renderer * r, char * srcFile, Point dim) {
        init(r, srcFile, dim.x, dim.y );
    }
    // Adds new animation with given name and co-rdinates on tilesheet
    bool addAnimation(char * name, Point coords[]) {
        if(mAnimationIndex+1>=mAnimationMax) return false;
        mAnimationIndex++;
        // Add points given to new animation object
        int i=0;
        mAnimations[mAnimationIndex] = new Animation(name,mDim);
        do {

            mAnimations[mAnimationIndex]->addFrame(coords[i],i);
            i++;
        } while(coords[i].x!=-1);


        mAnimationAmnt = mAnimationIndex+1;
        return true;

    }

    // Adds new animation with given name and co-rdinates on tilesheet
    bool addAnimation(Animation& ani) {
        if(mAnimationIndex+1>=mAnimationMax) return false;
        mAnimationIndex++;
        // Add points given to new animation object
        int i=0;
        mAnimations[mAnimationIndex] = ani;
        mAnimationAmnt = mAnimationIndex+1;
        return true;

    }
    
    // Returns current frame of current animation
    Point getFrame() {
        return mAnimations[mAnimationIndex]->getFrame();
    }

    int setAnimation(int index) {
        if(index>=4 || index<0) {
            return -1;
        }
        mAnimationIndex = index;
        //setFrame(mAnimations[mAnimationIndex]);
    }

    int setAnimation(char * name) {
        for(int i =0; i<mAnimationAmnt; i++)
        {
            if(!strcmp(mAnimations[i]->getName(),name)) {
                mAnimationIndex = i;
                mAnimations[mAnimationIndex]->play();
                return 1;

            } else
            {
                SDL_LogError("Animation does not exist: %s",name);
            }
        }
    }

    int stop(int frame) {
        mAnimations[mAnimationIndex]->setFrame(frame);

    }

    int stop() {
        mAnimations[mAnimationIndex]->stop();
    }

    void nextFrame() {
        // update animation
        mAnimations[mAnimationIndex]->update();
    }


    void render(SDL_Renderer * r, int x, int y,Point viewPortOffset)
    {
        render(r,x - viewPortOffset.x, y - viewPortOffset.y);
    }

    // Using the renderer context render to x,y using row and col of tilesheet
    void render(SDL_Renderer * renderer, int x, int y) {
        int w = mAnimations[mAnimationIndex]->getFrameWidth();
        int h = mAnimations[mAnimationIndex]->getFrameHeight();
        SDL_Rect  dstQuad = {x,y,w,h};
        // where in the tile sheet to copy
        // The parameters sent in are row and column which is tranlated to real x,y coords by multiplying by the frame w/h
        SDL_Rect srcQuad = mAnimations[mAnimationIndex]->getFrameRect();
        // Render texture to screen based on frame co-ords
        SDL_RenderCopy(renderer, mTilesheet->getSDL_Texture(),&srcQuad,&dstQuad);
    }



};

