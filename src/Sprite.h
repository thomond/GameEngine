#ifndef SPRITE_H
#define SPRITE_H
#include "Animated.cpp"
#include "Texture.cpp"
/**
 * @todo write docs
 */
class Sprite :  Animated,  Texture tex 
{
public:
    Sprite();
    
    update();
    
    render();
    
private:
    
};

#endif // SPRITE_H
