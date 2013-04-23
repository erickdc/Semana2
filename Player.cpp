#include "Player.h"

Player::Player(SDL_Surface *screen)
{
    this->screen = screen;
    this->images[0] = IMG_Load( "player/1.png" );
    this->images[1] = IMG_Load( "player/2.png" );
    this->images[2] = IMG_Load( "player/3.png" );
    this->images[3] = IMG_Load( "player/4.png" );
    this->images[4]=  IMG_Load( "player/5.png" );
    this->images[5]=  IMG_Load( "player/6.png" );
    this->images[6]=  IMG_Load( "player/7.png" );
    this->images[7]=  IMG_Load( "player/8.png" );
    this->images[8]=  IMG_Load( "player/9.png" );
    this->images[9]=  IMG_Load( "player/10.png" );
    this->images[10]= IMG_Load( "player/11.png" );
    this->images[11]= IMG_Load( "player/12.png" );
    this->images[12]= IMG_Load( "player/13.png" );
    this->images[13]= IMG_Load( "player/14.png" );
    this->images[14]= IMG_Load( "player/15.png" );

    this->x = 200;
    this->y = 0;
    this->acceleration=2;
    this->velocity=0;
    this->current_frame=0;
}

Player::~Player()
{
    SDL_FreeSurface( images[0] );
    SDL_FreeSurface( images[1] );
    SDL_FreeSurface( images[2] );
    SDL_FreeSurface( images[3] );
    SDL_FreeSurface( images[4] );
    SDL_FreeSurface( images[5] );
    SDL_FreeSurface( images[6] );
    SDL_FreeSurface( images[7] );
    SDL_FreeSurface( images[8] );
    SDL_FreeSurface( images[9] );
    SDL_FreeSurface( images[10] );
    SDL_FreeSurface( images[11] );
    SDL_FreeSurface( images[12] );
    SDL_FreeSurface( images[13] );
    SDL_FreeSurface( images[14] );
}

void Player::logic()
{
    y+=velocity;
    velocity+=acceleration;
    if(y>=500-images[current_frame]->w/2)
    {
        y=500-images[current_frame]->w/2;
        velocity=0;
    }
}

void Player::jump()
{
    velocity=-30;


}

void Player::render(int cant)
{
    SDL_Rect offset;

    offset.x = x - images[current_frame]->w/2;
    offset.y = y - images[current_frame]->h/2;

    SDL_BlitSurface( images[current_frame], NULL, screen, &offset );

    current_frame++;
    if(current_frame>cant)
        current_frame=0;
}
