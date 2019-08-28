

class Animation{

    
public:

    enum State
    {
      Undefined, // USed when uninitialised 
      Playing,
      Stopped,
      Paused
    };
    
    Animation(int tilesetid , int id, Point dimensions){mTilesetID = tilesetid; mID = id; mFrameDim =  dimensions; }
    
    Animation(char * name, Point dimensions){
        mFrameIndex = 0;
        mFrameAmnt = 0;
        mName = name;
        mTimer.start(1000);
        mFrameDim = dimensions;
    }
    

    // Returns the absolute position of the frame in x,y co-ords
    Point getFrame(){
        if(mFrameAmnt<=0) return Point(0,0);
        return mFrames[mFrameIndex];
    }
    
    void setFrame(int frame){
        if(frame >= mFrameAmnt-1) return;
        mFrameIndex = frame;
    }
    
    SDL_Rect getFrameRect(){
        return {mFrames[mFrameIndex].x,mFrames[mFrameIndex].y,mFrameDim.x,mFrameDim.y};
    }
    
    int nextFrame(){
        if(mFrameIndex>=4 || mFrameIndex+1 >= mFrameAmnt){ mFrameIndex=0;return -1;}// Reset
        mFrameIndex++;
    }
    
    int addFrame(Point frameCoords, int index){
        if(index>=4 || index<0) {
            return -1;
        }
        mFrames[index] = frameCoords;
        mFrameAmnt++;
    }
   
    void play(){
        mState = Playing;
    }
    
    void stop(){
        mState = Stopped;
    }
    
    int update(){
        // Update animation when timer is finished
        if(mTimer.isDone() && mState == Animation::Playing ){
            nextFrame();
            mTimer.reset();
        }
    }

	
	// Sets the current frame to draw using x,y pair representing col and row of tilesheet
	//bool setFrame(int _framex, int _framey){
	//	mFramePos.x = _framex;
	//	mFramePos.y = _framey;
	//}
	
	int getFrameWidth(){
		return mFrameDim.x;
	}
	
	int getFrameHeight(){
		return mFrameDim.y;
	}
    
    char * getName(){
        return mName;
    }
private:
    enum Animation::State mState = Animation::Undefined;
    // The current frames dimensions and position on the tilesheet
    Point mFrameDim;
    //Point mFramePos;
    int mFrameIndex;
    Point mFrames[4]; // Max four frames
    char * mName;
    int mID;
    int mTilesetID;
    int mFrameAmnt;
    Timer mTimer;    

};
