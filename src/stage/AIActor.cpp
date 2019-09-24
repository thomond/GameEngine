

class AIActor : public Actor
{
public:
    AIActor() : Actor() {

    }

    void init(Texture * tex, Point pos, Point dim, SDL_Rect colliderDim ) {
        mSpeed = 1;
        mPosition = pos;
        mCollider = colliderDim;

        Sprite::init(tex,dim);
        Point  pointData[][4] = {
            {Point(0,0),Point(32,0),Point(64,0),Point(-1,-1)}, {Point(0,32),Point(32,32),Point(64,32),Point(-1,-1)},
            {Point(0,64),Point(32,64),Point(64,64),Point(-1,-1)},
            {Point(0,96),Point(32,96),Point(64,96),Point(-1,-1)}
        };
        char * names[] = {"walk-up", "walk-right","walk-down", "walk-left"};

        for(int i=0; i<4; i++) {
            addAnimation(names[i],pointData[i]);
        }
        setAnimation("walk-down");

    }

    void handleEvent(SDL_Event& e){}

};
