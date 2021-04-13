#ifndef CHARACTER_H_
#define CHARACTER_H_
#include "LTexture.h"
#include "GameBase.h"

#define JUMP 1
#define FALL 2


class character
{
    public:

		int CHARACTER_JUMP_SPEED = 8;
		int CHARACTER_FALL_SPEED = 8;
        int t = 0;

		character();


		void handleEvent( SDL_Event& e, Mix_Chunk* gJump );


		void move();

        void stop();
		double X();
		double Y();

        void render(LTexture &character, SDL_Rect* clip, SDL_Renderer* gRenderer);
    private:

		double mPosX, mPosY;

		int status;

};


#endif
