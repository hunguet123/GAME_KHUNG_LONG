#ifndef FLY_H_
#define FLY_H_
#include "LTexture.h"

class fly
{
    public:
        fly();
        void move(double speed);
        void stop(double speed);
        void render(LTexture& birdTexture, SDL_Rect* clip, SDL_Renderer* gRenderer);
        double X();
        double Y();
    private:
        double Fx;
        double Fy;

};

#endif // FLY_H_
