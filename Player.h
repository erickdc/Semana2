#ifndef PLAYER_H
#define PLAYER_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include <string>

class Player
{
public:
    int x;
    int y;
    int velocity;
    int acceleration;
    int current_frame;
    int current_frame2;
    int contadorMuertes;
    bool menu;
    SDL_Surface *images[10];
    SDL_Surface *screen;
    bool muere;
    SDL_Rect offset;
    bool isJumping;
    Mix_Chunk *jumpSound;
    Mix_Chunk *explosion;
    bool quitProgram;
    Player(SDL_Surface *screen);
    void logic();
    void backMenu();
    void render();
    void jump();
   void playerDead(int playerx, int enemyx, int playery, int enemyy,int enemy2x, int enemy2y);
    void Controles();
    virtual ~Player();
};

#endif // PLAYER_H
