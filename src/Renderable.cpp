
// Abstarct class for rendering
class Renderable{
public:
virtual void render(SDL_Renderer * r, int x, int y){}
virtual void render(SDL_Renderer * r){}
virtual void render(){}
virtual void render(SDL_Renderer * r, Point pointOffset){}
}; 
