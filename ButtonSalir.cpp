#include "ButtonSalir.h"

ButtonSalir::ButtonSalir(int x,int y, int w, int h, SDL_Surface* screen)
{
    this->screen = screen;
    this->images[0]= IMG_Load("menuPrueba3.png");
    this->images[1]= IMG_Load("menuPrueba4.png");
    this->current_frame=0;
    this->x=x;
    this->y= y ;
    this->w= w;
    this->h=h;

}

ButtonSalir::~ButtonSalir()
{
    SDL_FreeSurface( images[0] );
    SDL_FreeSurface( images[1] );
}
void ButtonSalir::render()
{
    SDL_Rect offset;

    offset.x = x - images[current_frame]->w/2;
    offset.y = y - images[current_frame]->h/2;

    SDL_BlitSurface( images[current_frame], NULL, screen, &offset );


}
