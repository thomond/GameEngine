

class Actor : public Entity,public Sprite, public Updateable, public EventHandler
{
protected:

public:
    Actor():Entity() {}

    void update()
    {
        if(mState==State::Blocked) mSpeed = 0;
        if (mSpeed>0) {
            nextFrame();
            move();
        }
        else stop(0);

        if      (mDirection.x == -1) setAnimation("walk-left");
        else if (mDirection.x ==  1) setAnimation("walk-right");
        else if (mDirection.y == -1) setAnimation("walk-up");
        else if (mDirection.y ==  1) setAnimation("walk-down");


        mState = State::Undefined;
    }

};
