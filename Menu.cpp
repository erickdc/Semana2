#include "Menu.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include <string>


Menu::Menu(SDL_Surface *screen)
{
    this->screen = screen;
    this->image = IMG_Load( "menu1.png" );
    this->x = 0;
    this->y = -2500;
    this->termino = false;
}

Menu::~Menu()
{
    SDL_FreeSurface( image );
}
void Menu::logic()
{
    if(y<-1560)
    y+=20;
    else {
        termino=true;
    }
}
void Menu::render()
{


    SDL_Rect offset;


    offset.x = 0;
    offset.y = y+image->h;

    SDL_BlitSurface( image, NULL, screen, &offset );
}
void Menu::backMenu(){
    this->x = 0;
    this->y = -2500;
    this->termino = false;
}




