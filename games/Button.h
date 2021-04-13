#ifndef BUTTON_H_
#define BUTTON_H_
#include "LTexture.h"
#include "GameBase.h"

class LButton
{
	public:
		//Initializes internal variables
		LButton();

		//Sets top left position
		void setPosition( int x, int y );

		//Handles mouse event
		void handleEvent( SDL_Event& e, bool &play );

		//Shows button sprite
		void render(LTexture& gButtonTexture, SDL_Rect gSpriteClips[], SDL_Renderer* gRenderer);

	private:
		//Top left position
		SDL_Point mPosition;

		//Currently used global sprite
		LButtonSprite mCurrentSprite;
};

#endif // BUTTON_H_
