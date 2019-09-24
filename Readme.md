# SDL based 2d Game Engine  
* Basic UI Manager
* Basic Sound Manager
* Display Manager
   * 
* Resource Manager
   * TMX file support

## SDL control types
* Renderable - Abstract type that is be rendered on screen with SDL_Renderer
* Updateable - Abstract type that is to be  updated in game loop
* EventHandler - Abstract type for processinf of SDL_Events

## Display types
* Sprites - Texture(tilemap) and Animation
* Animation - contains frame information
* Textures
* Tilemapper 
* TextTextures

## Higher Level Types
* Stage
  * Multiple Layers
    * Viewport for scrolling
    * Tilemapper
    * Colour Primitive
    * Collision layers
* Actor 
  * Player
  * AIActor
 
