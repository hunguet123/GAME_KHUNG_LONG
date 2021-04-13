#ifndef GRASS_H_
#define GRASS_H_
#include "LTexture.h"

class grass
{
    public:

        grass();

        void move(double grass_speed );

        void stop(double grass_speed );

        void render(LTexture &grassTexture, SDL_Renderer *gRenderer);

        double X();
        double Y();
    private:
        double Gx;
        double Gy;
};


#endif // GRASS_H_
