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


#include "SDL/SDL_ttf.h"
#include "SDL_audio.h"

#include <string>
#include "Bomb.h"

//Screen attributes
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 500;
const int SCREEN_BPP = 32;
int contadorMuertes=0;
SDL_Surface *screen = NULL;
Timer* update;
bool isJumping=false;
bool muerto=false;
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
    int current_frame=0;
    SDL_Surface *images[5];
    images[0] = IMG_Load( "assets/perder01.png" );
    images[1] = IMG_Load( "assets/perder02.png" );
    images[2] = IMG_Load( "assets/perder03.png" );
    images[3] = IMG_Load( "assets/perder04.png" );
    images[4]=  IMG_Load( "assets/perder05.png" );

    SDL_Surface * game_over = IMG_Load( "game_over.png" );

    TTF_Font *font = TTF_OpenFont( "lazy.ttf", 30 );
    SDL_Color textColor = { 0, 0, 0 };
    SDL_Surface * score_surface = NULL;

    TTF_Font *font2 = TTF_OpenFont( "lazy.ttf", 80 );
    SDL_Color textColor2 = { 255, 0, 0 };
    SDL_Surface * score_surface2 = NULL;

    Mix_Chunk *jump = Mix_LoadWAV( "jump.ogg" );
    Mix_Chunk *explosion = Mix_LoadWAV( "explosion.wav" );
    int score=0;
    Mix_PlayChannel( -1, jump, 0 );
    Background background(screen);
    Player player(screen);

    Enemy enemy2(screen);
    SDL_Event event;
    //Quit flag


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
                        if(player.y==372){

                          player.jump();
                        Mix_PlayChannel( -1, jump, 0 );
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

        enemy2.logic();

        SDL_Rect offset;
        offset.x = 0;
        offset.y = 0;
        SDL_Surface * score_surface = TTF_RenderText_Solid( font, toString(score+=5).c_str(), textColor );
        SDL_BlitSurface( score_surface, NULL, screen, &offset );


        offset.x = 800;
        offset.y = 0;
        SDL_Surface * score_surface2 = TTF_RenderText_Solid( font2, toString(contadorMuertes=contadorMuertes).c_str(), textColor2 );
        SDL_BlitSurface( score_surface2, NULL, screen, &offset );

        SDL_Flip( screen );
        SDL_FreeSurface( score_surface );

        if(player.x-enemy2.x<50
           && player.x-enemy2.x>-50
           && player.y-enemy2.y<50
           && player.y-enemy2.y>-50
           )
        {


        offset.x = 0;
        offset.y = 0;


        do{
        SDL_BlitSurface( images[current_frame], NULL, screen, &offset );

         current_frame++;
       }while(current_frame<4  && enemy2.x>(40+player.x));
       if(current_frame>4){
            current_frame=0;
       }
        SDL_Flip( screen );
          muerto=true;
        }
        if(muerto && enemy2.x==player.x

           ){
            contadorMuertes+=1;
            Mix_PlayChannel( -1, explosion, 0 );
            muerto=false;
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
