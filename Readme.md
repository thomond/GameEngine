# SDL based 2d Game Engine  
A toy 2d game engine targetting the SDL library. Primarilly for me to touch up on C++ and learn some of the newer concepts (c++11 etc)

Comprises
* Basic UI Manager - Text output and a basic HUD
* Basic Sound Manager - Not yet implemented 
* Display Manager - Encapsulates SDL_Renderer and SDL_Window related functionality 
* Resource Manager - Manages resources and the Model
   * TMX file support - Supports the TMX file format which defines, tilemaps, maps and animations

## Base types
* Renderable - Abstract type that is be rendered on screen with SDL_Renderer and the Display Manager 
* Updateable - Abstract type that defines what is to be updated in game loop
* EventHandler - Abstract type for processing of SDL_Events

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
 
