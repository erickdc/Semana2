/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

//The headers
#include "SDL/SDL.h"

#include "SDL/SDL_image.h"

#include "Background.h"
#include "Player.h"
#include "Enemy.h"
#include "Timer.h"
#include <string>

//Screen attributes
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 500;
const int SCREEN_BPP = 32;

SDL_Surface *screen = NULL;
Timer* update;
bool isJumping=false;

bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    //Set the window caption
    SDL_WM_SetCaption( "SDL Runner Lab Progra 3", NULL );

    //If everything initialized fine
    return true;
}

void frameCap()
{
    int frames_per_seccond = 15;
    if(update->get_ticks() < 1000 / frames_per_seccond)
    {
        //Sleep the remaining frame time
        SDL_Delay( ( 1000 / frames_per_seccond ) - update->get_ticks() );
    }
    update->start();
}

int main( int argc, char* args[] )
{
    //Initialize
    init();
    update=new Timer();
    update->start();
    int current_frame=0;
    SDL_Surface *images[5];
    images[0] = IMG_Load( "assets/perder01.png" );
    images[1] = IMG_Load( "assets/perder02.png" );
    images[2] = IMG_Load( "assets/perder03.png" );
    images[3] = IMG_Load( "assets/perder04.png" );
    images[4]=  IMG_Load( "assets/perder05.png" );

    SDL_Surface * game_over = IMG_Load( "game_over.png" );

    Background background(screen);
    Player player(screen);
    Enemy enemy(screen);
    Enemy enemy2(screen);
    SDL_Event event;
    //Quit flag
    enemy2.x=50;

    bool quit = false;
    while( quit == false )
    {
        //If there's an event to handle
        if( SDL_PollEvent( &event ) )
        {
            //If a key was pressed
            if( event.type == SDL_KEYDOWN )
            {
                //Set the proper message surface
                switch( event.key.keysym.sym )
                {
                    case SDLK_ESCAPE: quit = true; break;
                    case SDLK_UP:
                        isJumping=true;
                        if(player.velocity==0 && player.y>-30){
                          player.jump();
                        }
                        break;
                }
            }
            //If the user has Xed out the window
            else if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }

        background.logic();
        player.logic();
        enemy.logic();
        enemy2.logic();
        if(player.x-enemy.x<50
           && player.x-enemy.x>-50
           && player.y-enemy.y<50
           && player.y-enemy.y>-50
           || player.x-enemy2.x>-50
           && player.y-enemy2.y<50
           && player.y-enemy2.y>-50
           )
        {
           break;
        }

        background.render();
        if(isJumping){
        player.render(14);
        if(player.velocity==0){
            isJumping=false;
        }
        }else{
        player.render(3);
        }
        enemy.render();
        enemy2.render();
        frameCap();

        //Update the screen
        if( SDL_Flip( screen ) == -1 )
        {
            return 1;
        }

    }

    while( quit == false )
    {
        //If there's an event to handle
        if( SDL_PollEvent( &event ) )
        {
            //If a key was pressed
            if( event.type == SDL_KEYDOWN )
            {
                //Set the proper message surface
                switch( event.key.keysym.sym )
                {
                    case SDLK_ESCAPE: quit = true; break;
                }
            }
            //If the user has Xed out the window
            else if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }

        SDL_Rect offset;
        offset.x = 0;
        offset.y = 0;

        do{
        SDL_BlitSurface( images[current_frame], NULL, screen, &offset );
        current_frame++;

        }while(current_frame<4);
        if(current_frame>4){

        SDL_BlitSurface( game_over, NULL, screen, &offset );

        }

        frameCap();

        //Update the screen
        if( SDL_Flip( screen ) == -1 )
        {
            return 1;
        }

}

    //SDL_Quit();

    return 0;
}
