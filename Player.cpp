#include "Player.h"

Player::Player(SDL_Surface *screen)
{
    this->screen = screen;
    this->quitProgram=false;
    this->menu=false;
    this->images[0] = IMG_Load( "player/1.png" );
    this->images[1] = IMG_Load( "player/2.png" );
    this->images[2] = IMG_Load( "player/3.png" );
    this->images[3] = IMG_Load( "player/4.png" );
    this->images[4]=  IMG_Load( "player/5.png" );

   //Loading when the character die
    this->images[5] = IMG_Load( "assets/perder01.png" );
    this->images[6] = IMG_Load( "assets/perder02.png" );
    this->images[7] = IMG_Load( "assets/perder03.png" );
    this->images[8] = IMG_Load( "assets/perder04.png" );
    this->images[9]=  IMG_Load( "assets/perder05.png" );

    explosion = Mix_LoadWAV( "explosion.wav" );

    this->isJumping=false;
    this->x = 200;
    this->y = 0;
    this->acceleration=2;
    this->velocity=0;
    this->current_frame=0;
    this->current_frame2=5;
    this->muere = false;
    jumpSound = Mix_LoadWAV( "jump.ogg" );
    this->contadorMuertes=0;
    this->pintarse=false;
}

Player::~Player()
{
    SDL_FreeSurface( images[0] );
    SDL_FreeSurface( images[1] );
    SDL_FreeSurface( images[2] );
    SDL_FreeSurface( images[3] );
    SDL_FreeSurface( images[4] );



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
    Mix_PlayChannel( -1, jumpSound, 0 );
    isJumping=true;

}


void Player::Controles(){
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
                    case SDLK_UP:

                        if(y==372){

                          jump();

                        }
                        break;

                }
            }
           // If the user has Xed out the window
        else if( event.type == SDL_QUIT )
            {
                //Quit the program
                quitProgram = true;

        }

}
}
void Player::playerDead(int playerx, int enemyx, int playery, int enemyy, int enemy2x, int enemy2y){

    if(contadorMuertes>1){
        menu=true;
    }
    if(playerx-enemyx<50
           && playerx-enemyx>-50
           && playery-enemyy<50
           && playery-enemyy>-50
           ||

           playerx-enemy2x<50
           && playerx-enemy2x>-50
           && playery-enemy2y<50
           && playery-enemy2y>-50
           )
        {
        current_frame2=5;
        pintarse=true;

     /*   offset.x = 0;
        offset.y = 0;



        SDL_BlitSurface( images[current_frame2], NULL, screen, &offset );

         current_frame2++;

       if(current_frame2>9){
            current_frame2=5;
            current_frame=0;
       }

           muere=true;
        }
        if(muere && enemyx==playerx || muere && enemy2x==playerx

           ){
            contadorMuertes+=1;
            Mix_PlayChannel( -1, explosion, 0 );
            muere=false;



        }
*/
}

}
void Player::render()
{

    if(!pintarse &&this->isJumping==false){


    offset.x = x - images[current_frame]->w/2;
    offset.y = y - images[current_frame]->h/2;

    SDL_BlitSurface( images[current_frame], NULL, screen, &offset );

    current_frame++;
    if(current_frame>3)
        current_frame=0;

   }else if(this->isJumping){

    offset.x = x - images[4]->w/2;
    offset.y = y - images[4]->h/2;

    SDL_BlitSurface( images[4], NULL, screen, &offset );

        if(y==372){
            this->isJumping=false;
            current_frame=0;

        }
    }else if(pintarse){
        offset.x = x - images[current_frame2]->w/2;
        offset.y = y - images[current_frame2]->h/2;

        SDL_BlitSurface( images[current_frame2], NULL, screen, &offset );
        current_frame2++;
        if(current_frame2>9){

            current_frame=0;
            contadorMuertes++;
            pintarse =false;
            Mix_PlayChannel( -1, explosion, 0 );
        }
    }

}
void Player::backMenu(){
this->current_frame=0;
this->current_frame2=5;
this->menu=false;
this->contadorMuertes=0;
this->muere=false;

}
