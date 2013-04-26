#ifndef BOMB_H
#define BOMB_H
#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

class Bomb
{
    public:
    int x;
    int y;
    int velocity;
    int acceleration;
    int current_frame;
    SDL_Surface *images[3];
    SDL_Surface *screen;

    Bomb(SDL_Surface *screen);
    void logic();
    void render();
    void jump();
    virtual ~Bomb();
};

#endif // BOMB_H
