#include "Button.h"
#include <iostream>

LButton::LButton()
{
	mPosition.x = 0;
	mPosition.y = 0;

	mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void LButton::setPosition( int x, int y )
{
	mPosition.x = x;
	mPosition.y = y;
}

void LButton::handleEvent( SDL_Event& e, bool &play, Mix_Chunk* gButton, Mix_Chunk* gButtonOn )
{
	//If mouse event happened
	if( e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN )
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if( x < mPosition.x )
		{
			inside = false;
		}
		//Mouse is right of the button
		else if( x > mPosition.x + BUTTON_WIDTH )
		{
			inside = false;
		}
		//Mouse above the button
		else if( y < mPosition.y )
		{
			inside = false;
		}
		//Mouse below the button
		else if( y > mPosition.y + BUTTON_HEIGHT )
		{
			inside = false;
		}

		//Mouse is outside button
		if( !inside )
		{
			mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;

		}
		//Mouse is inside button
		else
		{
			switch( e.type )
			{
				case SDL_MOUSEMOTION:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
				break;

				case SDL_MOUSEBUTTONDOWN:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
				Mix_PlayChannel(-1, gButton, 0);
				play = true;
				break;


			}
        }
	}
}

void LButton::render(LTexture& gButtonTexture, SDL_Rect gSpriteClips[], SDL_Renderer* gRenderer)
{
	//Show current button sprite
	gButtonTexture.render( mPosition.x, mPosition.y, &gSpriteClips[ mCurrentSprite ], gRenderer );
}
