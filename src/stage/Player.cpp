/*
Player class

*/

// The player that will move around on the screen
class Player : public Actor
{

public:
	static const int PLAYER_WIDTH = 32;
	static const int PLAYER_HEIGHT = 32;
	static const int PLAYER_POSY = 0;
	static const int PLAYER_POSX = 0;
	static const int PLAYER_FRAME_ROW = 0;
	static const int PLAYER_FRAME_COL = 0;
	// axis velocity of the player
	static const int PLAYER_VEL = 10;
	//static const char * PLAYER_SHOOT_SND_PATH = "./res//smw_coin.wav";

	Player() : Actor() {}

	void init(Texture *tex, Point pos, Point dim)
	{
		SDL_Rect rect = {0, 0, dim.x, dim.y};
		init(tex, pos, dim, rect); // Collider same size as character
	}

	void init(Texture *tex, Point pos, Point dim, SDL_Rect colliderDim)
	{
		mPosition = pos;
		mCollider = colliderDim;
		mSpeedDef = 2;
		Sprite::init(tex, dim);
		Point pointData[][4] = {
			{Point(0, 0), Point(32, 0), Point(64, 0), Point(-1, -1)}, {Point(0, 32), Point(32, 32), Point(64, 32), Point(-1, -1)}, {Point(0, 64), Point(32, 64), Point(64, 64), Point(-1, -1)}, {Point(0, 96), Point(32, 96), Point(64, 96), Point(-1, -1)}};
		char *names[] = {"walk-up", "walk-right", "walk-down", "walk-left"};

		for (int i = 0; i < 4; i++)
		{
			addAnimation(names[i], pointData[i]);
		}
		setAnimation("walk-down");
	}

	// player event handler
	void handleEvent(SDL_Event &e)
	{
		// handle key
		if (e.key.type == SDL_KEYDOWN && !e.key.repeat)
		{
			// adjust velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_a:
				setVelocity(Point(-mSpeedDef, 0));
				break;
			case SDLK_d:
				setVelocity(Point(mSpeedDef, 0));
				break;
			case SDLK_w:
				setVelocity(Point(0, -mSpeedDef));
				break;
			case SDLK_s:
				setVelocity(Point(0, mSpeedDef));
				break;
			}
		}
		if (e.key.type == SDL_KEYUP)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_a:
			case SDLK_d:
			case SDLK_w:
			case SDLK_s:
				mSpeed = 0;
				break;
			}
		}
		//const Uint8 *state = SDL_GetKeyboardState(NULL);
		//if (state[SDL_SCANCODE_D
	}

	void die()
	{
	}

	void reset()
	{
	}

	void toString()
	{
		SDL_Log("Pos: %d, %d Dim: %d, %d\f", mPosition.x, mPosition.y, PLAYER_WIDTH, PLAYER_HEIGHT);
		SDL_Log("Pos: %d, %d Dim: %d, %d\f", mCollider.x, mCollider.y, mCollider.w, mCollider.h);
	}
};
