#include "checkCollision.h"

bool check_collision_character_barrier(character dinosour, barrier cactus )
{
    //The sides of the rectangles
    int leftDinosour, leftCactus;
    int rightDinosour, rightCactus;
    int topDinosour, topCactus;
    int bottomDinosour, bottomCactus;

    //Calculate the sides of rect A
    leftDinosour = dinosour.X();
    rightDinosour = dinosour.X() + 30;
    topDinosour = dinosour.Y();
    bottomDinosour = dinosour.Y() + 30;

    //Calculate the sides of rect B
    leftCactus = cactus.X() + 15;
    rightCactus = cactus.X() + 30;
    topCactus = cactus.Y();
    bottomCactus = cactus.Y() + 30;

    //If any of the sides from A are outside of B
    if( bottomDinosour <= topCactus )
    {
        return false;
    }

    if( topDinosour >= bottomCactus )
    {
        return false;
    }

    if( rightDinosour <= leftCactus )
    {
        return false;
    }

    if( leftDinosour >= rightCactus )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}

bool check_collision_character_bird(character dinosour, fly bird)
{
           //The sides of the rectangles
    int leftDinosour, leftBird;
    int rightDinosour, rightBird;
    int topDinosour, topBird;
    int bottomDinosour, bottomBird;

    //Calculate the sides of rect A
    leftDinosour = dinosour.X();
    rightDinosour = dinosour.X() + 30;
    topDinosour = dinosour.Y();
    bottomDinosour = dinosour.Y() + 30;

    //Calculate the sides of rect B
    leftBird = bird.X() ;
    rightBird = bird.X() + 30;
    topBird = bird.Y() + 20;
    bottomBird = bird.Y() + 40;

    //If any of the sides from A are outside of B
    if( bottomDinosour <= topBird )
    {
        return false;
    }

    if( topDinosour >= bottomBird )
    {
        return false;
    }

    if( rightDinosour <= leftBird )
    {
        return false;
    }

    if( leftDinosour >= rightBird )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}
