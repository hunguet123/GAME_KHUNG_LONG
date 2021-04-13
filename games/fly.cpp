#include "fly.h"

fly::fly()
{
    Fx = rand() % 500 + 1280;
    Fy = rand() % 145 + 400;
}

void fly::move(double speed)
{
    if (Fx < 0) {
        Fx = rand() % 3000 + 1280;
        Fy = rand() % 145 + 400;
    }
    Fx -= speed;
}
void fly::stop(double speed)
{
    Fx += speed;
}

void fly::render(LTexture& birdTexture, SDL_Rect* clip, SDL_Renderer* gRenderer)
{
    birdTexture.render(Fx, Fy, clip, gRenderer);
}

double fly::X()
{
    return Fx;
}

double fly::Y()
{
    return Fy;
}
