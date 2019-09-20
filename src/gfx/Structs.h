struct Collider {
    int ID;
    int state;
};

// Structure representing a tileset
struct Tileset {
    int id=-1;
    std::string filename;
    std::string name;
    int firstGID;
    int lastGID;
    int num;
    int rows;
    int cols;
    SDL_Point dim;
    std::vector<Collider> colliders;
    SDL_Texture * tilemap;
};

/*
    * Represents a tiled layer composited from a tileset
    * Also contains collison detection information
    */
struct Layer {
    int id=-1;
    std::vector<std::vector<int>> IDs;
    Texture * texture;
    std::string name;
    SDL_Point dim;
    std::vector<SDL_Rect> colliders;
    int actionState =  0;
    void (*actionFunc)() = NULL;
    std::string tilesetName;
    std::string stageName;
};
