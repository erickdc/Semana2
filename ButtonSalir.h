#ifndef BUTTONSALIR_H
#define BUTTONSALIR_H
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include <string>

class ButtonSalir
{
    public:
     SDL_Surface *images[2];
    SDL_Surface *screen;
    int x;
    int y;
    int w;
    int h;
    int current_frame;
    ButtonSalir(int x, int y, int w, int h,SDL_Surface *screen);
    void  render();
    virtual ~ButtonSalir();
    private:
};

#endif // BUTTONSALIR_H
