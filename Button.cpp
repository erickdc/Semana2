#include "Button.h"

Button::Button(int x,int y, int x2, int y2,int w, int h, SDL_Surface* screen)
{
    this->screen = screen;
    this->images[0]= IMG_Load("menuPrueba1.png");
    this->images[1]= IMG_Load("menuPrueba2.png");
    this->images[2]= IMG_Load("menuPrueba3.png");
    this->images[3]= IMG_Load("menuPrueba4.png");
    buttonClick = Mix_LoadWAV( "buttonClick.wav" );
    this->current_frame=0;
    this->current_frame2=2;
    this->x2= x2;
    this->y2= y2;
    this->x=x;
    this->y= y ;
    this->w= w;
    this->h=h;
    this->izquierda=true;
    this->derecha=false;
    this->termino=false;
    this->quitProgram=false;
}

Button::~Button()
{
    SDL_FreeSurface( images[0] );
    SDL_FreeSurface( images[1] );
    SDL_FreeSurface( images[2] );
    SDL_FreeSurface( images[3] );

}
void Button::Controles(){
SDL_Event event;
 //If there's an event to handle
        if( SDL_PollEvent( &event ) )
        {

            //If a key was pressed
            if( event.type == SDL_KEYDOWN )
            {
                //Set the proper message surface
                switch( event.key.keysym.sym )
                {
                   // case SDLK_ESCAPE: quit = true; break;
                    case SDLK_RIGHT:
                        if(izquierda){
                        derecha=true;
                        izquierda=false;
                        Mix_PlayChannel( -1, buttonClick, 0 );
                        }
                        break;
                    case SDLK_LEFT:
                        if(derecha){
                        derecha=false;
                        izquierda=true;
                        Mix_PlayChannel( -1, buttonClick, 0 );
                        }
                        break;
                    case SDLK_SPACE:
                        if(current_frame2==2){
                            termino=true;
                        }else{
                        this->quitProgram=true;
                        }
                        break;
                }
            }
           // If the user has Xed out the window
           else if( event.type == SDL_QUIT )
            {

            quitProgram= true;

        }

}
}
void Button::render()
{
    SDL_Rect offset;

     if(izquierda){
    current_frame=1;
    current_frame2=2;
     }else if(derecha){
     current_frame=0;
    current_frame2=3;
     }
    offset.x = x - images[current_frame]->w/2;
    offset.y = y - images[current_frame]->h/2;

    SDL_BlitSurface( images[current_frame], NULL, screen, &offset );

    offset.x = x2 - images[current_frame2]->w/2;
    offset.y = y2 - images[current_frame2]->h/2;

    SDL_BlitSurface( images[current_frame2], NULL, screen, &offset );

}

void Button::backMenu(){
    this->current_frame=0;
    this->current_frame2=2;
    this->izquierda=true;
    this->derecha=false;
    this->termino=false;
    this->quitProgram=false;
}
