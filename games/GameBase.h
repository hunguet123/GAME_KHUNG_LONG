#ifndef GAMEBASE_H_
#define GAMEBASE_H_
#include <ctime>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <algorithm>
#include <fstream>

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 700;

const int BUTTON_WIDTH = 150;
const int BUTTON_HEIGHT = 98;
const int TOTAL_BUTTONS = 4;

enum LButtonSprite
{
	BUTTON_SPRITE_MOUSE_OUT = 0,
	BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
	BUTTON_SPRITE_MOUSE_DOWN = 2,
	BUTTON_SPRITE_TOTAL = 2
};

#endif // GAMEBASE_H_
