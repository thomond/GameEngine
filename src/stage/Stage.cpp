#include "Stage.h"

Stage::Stage(std::string stagename, ResourceManager * res)
{
    // Set mViewport to start pos of stage
    // TODO: add universial way to get screen h/w
    int scr_w = 800;
    int scr_h = 600;
    mViewport = { 0, 0, scr_w, scr_h};

    // Set resources pointer and load layers from resources if any
    resources = res;

    int pri=0;
    for(auto& layer : resources->getLayers()) {
        // Verify layer has correct id/name
        if (layer.stageName,stagename);
        Stage::addLayer(pri++,layer);
    }
}

Stage::~Stage() {
   

}

void Stage::handleEvents(SDL_Event e) {
    int i;
    while(i!=mActorAmnt)
    {
        mActorList[i]->handleEvent(e);
        i++;
    }
}

void Stage::render(SDL_Renderer * r) {
    // Render BG texture if any
    renderLayer(0,r);
    renderLayer(1,r);

    // Render any actor stored
    int i=0;
    while(i!=mActorAmnt)
    {
        if(mViewport.h != 0)
            mActorList[i]->render(r, mActorList[i]->getPosx(), mActorList[i]->getPosy(), Point(mViewport.x,mViewport.y));
        i++;
    }
}

void Stage::update() {
    int i=0;
    while(i!=mActorAmnt)
    {

        // For each collision grid check if there's a collison and either set the actor's state or call a callback func
        for(auto& layer : resources->getLayers())
        {
            if(layer.colliders.empty()) continue;// No Colliders in layer
            for(SDL_Rect rect :  layer.colliders )
            {
                if(layer.actionFunc != NULL) {
                    if(mActorList[i]->collidesWith(&rect))
                        layer.actionFunc();
                }
                if(layer.actionState!=NULL) {
                    if(mActorList[i]->collidesWith(&rect))
                        mActorList[i]->setState(layer.actionState);
                }

            }

        }
        // Call Actor update function after sttaes hav been set by game
        mActorList[i]->update();
        i++;
    }
}



// Directly Render layer by index
void Stage::renderLayer(int layerID, SDL_Renderer *r) {
    if (layerID == 0 && mBgTexture != NULL)
        // render relative to viewport
        mBgTexture->render(r,-mViewport.x, -mViewport.y);
    else if (layerID > 0 && !mFgTexture.empty())
        for(auto tex : mFgTexture)
            // render relative to viewport
            tex->render(r,-mViewport.x, -mViewport.y);
    //else SDL_Log("Layer not defined: %d",layerID);
}

// Set layer texture
void Stage::setLayer(int layerID, Texture* tex) {
    if (layerID == 0) {
        mBgTexture = tex;
    }
    else if (layerID > 0) {
        mFgTexture.push_back(tex);
    } else SDL_Log("Layer not defined: %d",layerID);
}


SDL_Rect * Stage::getViewPort() {
    if (mViewport.w == 0 && mViewport.h == 0) return NULL;
    return &mViewport;

}

void Stage::scrollViewport(int x, int y) {
    // TODO: check bounds of camera
    mViewport.x += x;
    mViewport.y += y;
}

void Stage::addActor(Actor * actor) {
    if(mActorAmnt==8) {
        SDL_LogError("Too many actors",NULL);
        return;
    }
    mActorList[mActorAmnt] = actor;
    mActorAmnt++;
}

int Stage::addLayer(int priority, Layer& layer)
{
    //resources.getLayers().push_back(layer);
    setLayer(priority, layer.texture);

}


