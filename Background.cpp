#include "Background.h"

Background::Background(SDL_Surface *screen)
{
    this->screen = screen;
    this->image = IMG_Load( "background.png" );
    this->x = 0;
}

Background::~Background()
{
    SDL_FreeSurface( image );
}

void Background::logic()
{
    x--;
}

void Background::render()
{
    SDL_Rect offset;

    if(x<-image->w)
        x=0;
    offset.x = x;
    offset.y = 0;

    SDL_BlitSurface( image, NULL, screen, &offset );

    offset.x = x+image->w;
    offset.y = 0;

    SDL_BlitSurface( image, NULL, screen, &offset );
}
