/*
Entity class

*/ 

class Entity
{
	protected:
	// x and y offsets of the player; mPosition.y will always be at fixed location
	Point mPosition;
	// Unit vecotr/ normal for enity
	Point mDirection;
	int mSpeed;
    int mSpeedDef;
	// player's collison box relative to the tile itself
	SDL_Rect mCollider;
    
	public:
	
    enum State
    {
      Undefined=0, // USed when uninitialised 
      Blocked,
      Dead=10 // States 0-10 reserved for entity
    };
	
    int mState = Entity::Undefined;
	
	Entity()
	{ 	
		mDirection.set(0,0); 
        mSpeed = 0;
        mSpeedDef = 0;
	} 
	
	Entity::State setState(State newState){
        int old = mState;
        mState = newState;
        return static_cast<State>(old);
    }
    
    Entity::State getState(){
        return static_cast<State>(mState);
    }

	bool collidesWith(SDL_Rect * obj)
	{
		// Get world coords of collider with velocity accounted for
		mCollider.x += mPosition.x + mDirection.x*mSpeed;
		mCollider.y += mPosition.y + mDirection.y*mSpeed;
		if (SDL_HasIntersection(&mCollider,obj)){
			SDL_Log("Collision.\n");
			SDL_Log("collision at %d ,%d.\n",mCollider.x,mCollider.y);
			// Reset collison quad
			mCollider.x -= mPosition.x + mDirection.x*mSpeed;
			mCollider.y -= mPosition.y + mDirection.y*mSpeed;
			return true;
		}
		else{// Reset collider to being relative to entiy pos
			mCollider.x -= mPosition.x + mDirection.x*mSpeed;
			mCollider.y -= mPosition.y + mDirection.y*mSpeed;
			return false;
		}
	}
	
	SDL_Rect * getCollisionRect(){
		return &mCollider;
	}

	void pivotTo(Point to)
    {
        Point product =  to - mPosition;
        mDirection = product.normalized();
    }
	
	// Absolute movment func
	void moveTo(int x, int y){
		mPosition.y = y;
		mPosition.x = x;
	}
	
	void move(){
		mPosition.x += mDirection.x*mSpeed;
        mPosition.y += mDirection.y*mSpeed;
	}

	
	Point getPos()
	{
		return mPosition;
	}
	
	
	int getPosx()
	{
		return mPosition.x;
	}
	int getPosy()
	{
		return mPosition.y;
	}
	
	Point getDirection()
	{
		return mDirection;
	}
	
	Point setDirection(Point direction)
	{
		mDirection = direction;
	}
	
	void setSpeed(int x){
        mSpeed = x;
    }
    
    int getSpeed(){
        return mSpeed;
    }
    
	int getVelx()
	{
		return mPosition.x;
	}
	int getVely()
	{
		return mPosition.y;
	}
	
	// Takes velocity vector and extracts speed and normal/direction vector
	void setVelocity(Point velocity){
        if(velocity.x==0) mSpeed = abs(velocity.y);
        else if(velocity.y==0) mSpeed = abs(velocity.x);
        else mSpeed = velocity.x;
        
        mDirection = velocity.normalized();
    }
	
	
	void setVelx(int v)
	{
		mDirection.x = v;
	}
	void setVely(int v)
	{
		mDirection.y = v;
	}
};
