/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

//The headers
#include "SDL/SDL.h"

#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "Background.h"
#include "Player.h"
#include "Enemy.h"
#include "Timer.h"
#include <string>
#include "Menu.h"
#include "Button.h"
#include "SDL/SDL_ttf.h"
#include "SDL_audio.h"
#include "ButtonSalir.h"
#include <string>
#include "Bomb.h"

//Screen attributes
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 500;
const int SCREEN_BPP = 32;

int contadorMuertes=0;
SDL_Surface *screen = NULL;
Timer* update;

bool muerto=false;
bool StartGame= false;
bool quit = false;



std::string toString(int number)
{
    if (number == 0)
        return "0";
    std::string temp="";
    std::string returnvalue="";
    while (number>0)
    {
        temp+=number%10+48;
        number/=10;
    }
    for (int i=0;i<(int)temp.length();i++)
        returnvalue+=temp[temp.length()-i-1];
    return returnvalue;
}

bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Initialize SDL_mixer
     if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        return false;
    }

    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
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


    TTF_Font *font = TTF_OpenFont( "lazy.ttf", 30 );
    SDL_Color textColor = { 0, 0, 0 };
    SDL_Surface * score_surface = NULL;

    TTF_Font *font2 = TTF_OpenFont( "lazy.ttf", 80 );
    SDL_Color textColor2 = { 255, 0, 0 };
    SDL_Surface * score_surface2 = NULL;

    int score=0;
    Background background(screen);

    Bomb enemy3(screen);
    Player player(screen);
    Menu menu(screen);
    Button Start(250,370,750,370,202,109,screen);
    Enemy enemy2(screen);
    enemy2.x=600;
    SDL_Event event;


    quit=false;
    while( quit== false )
    {

        if(!Start.termino){
            SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
            menu.logic();

            Start.Controles();
            menu.render();
            if(menu.termino)
            Start.render();
            SDL_Flip(screen);
        }else{
            if(player.menu){
               Start.termino=false;
               player.backMenu();
               enemy2.backMenu();
               menu.backMenu();
               Start.backMenu();
                score=0;
            }
        player.Controles();

        background.logic();
        player.logic();
        menu.logic();
        enemy2.logic();

        enemy3.logic();
        SDL_Rect offset;
        offset.x = 0;
        offset.y = 0;
        SDL_Surface * score_surface = TTF_RenderText_Solid( font, toString(score+=5).c_str(), textColor );
        SDL_BlitSurface( score_surface, NULL, screen, &offset );


        offset.x = 800;
        offset.y = 0;
        SDL_Surface * score_surface2 = TTF_RenderText_Solid( font2, toString(player.contadorMuertes).c_str(), textColor2 );
        SDL_BlitSurface( score_surface2, NULL, screen, &offset );

        SDL_Flip( screen );
        SDL_FreeSurface( score_surface );


        background.render();
         player.playerDead(player.x,enemy3.x,player.y,enemy3.y,enemy2.x,enemy2.y);
        player.render();
        enemy2.render();

        enemy3.render();

        frameCap();

        //Update the screen
        if( SDL_Flip( screen ) == -1 )
        {
            return 1;
        }

        }

        if(player.quitProgram || Start.quitProgram ){
            quit=true;
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
