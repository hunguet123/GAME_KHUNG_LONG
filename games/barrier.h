#ifndef BARRIER_H_
#define BARRIER_H_
#include "LTexture.h"
#include "character.h"


class barrier
{
        public:
        barrier();
        void move(double speed );

        void stop(double speed);
        double Y();
        double X();
        void render(LTexture &barrierTexture, SDL_Rect* clips, SDL_Renderer* gRenderer);

        double PosY;
        double PosX;

};


#endif // BARRIER_H_
