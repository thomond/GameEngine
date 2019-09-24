#ifndef STAGE_H
#define STAGE_H

/**
 * @todo
 * @name Stage
 * @brief Represent a level or stage comprising of a scrolling map of muktiple layers
 */
class Stage : public Renderable, public Updateable
{
public:
    std::string name;
    ResourceManager *resources;
    SDL_Rect mViewport = {0};
    Point stageDim = Point(1000, 1000);

    Stage(std::string stagename, ResourceManager *res);

    /**
     * Destructor
     */
    ~Stage();
    void addActor(Actor *actor);
    void renderLayer(int layerID, SDL_Renderer *r);
    void setLayer(int layerID, Texture *tex);
    int addLayer(int priority, Layer &layer);
    SDL_Rect *getViewPort();
    void scrollViewport(int x, int y);
    void render(SDL_Renderer *r);
    void update();
    void handleEvent(SDL_Event& e);

private:
    std::vector<Actor *> mActorList;
    Texture *mBgTexture;
    std::vector<Texture *> mFgTexture;
    int mCollisionRectAmnt;
    int mCollisionRectMax = 20;
};

#endif // STAGE_H
