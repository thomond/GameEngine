#ifndef ENTITY_H
#define ENTITY_H
#include "Entity.cpp"
#endif
#ifndef SPRITE_H
#define SPRITE_H
#include "Sprite.cpp"
#endif
#ifndef RENDERABLE_CPP
#define RENDERABLE_CPP
#include "Renderable.cpp"
#endif
#ifndef UPDATEABLE_CPP
#define UPDATEABLE_CPP
#include "Updateable.cpp"
#endif
#ifndef EVENTHANDLER_CPP
#define EVENTHANDLER_CPP
#include "EventHandler.cpp"
#endif

class Actor : public Entity, public Renderable, public Updateable, public EventHandler
{
protected:
    
public:
    Sprite * mSprite;
    Actor():Entity(){}
    
    void update()
	{
        if(mState==Entity::Blocked) mSpeed = 0;
        if (mSpeed>0){
            mSprite->update();
            move();
        }
        else mSprite->stop(0);
        
        if      (mDirection.x == -1) mSprite->setAnimation("walk-left"); 
        else if (mDirection.x ==  1) mSprite->setAnimation("walk-right"); 
        else if (mDirection.y == -1) mSprite->setAnimation("walk-up"); 
        else if (mDirection.y ==  1) mSprite->setAnimation("walk-down");
        
       
        mState = Entity::Undefined;
	}
    
};
