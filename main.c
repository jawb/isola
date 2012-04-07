#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdlib.h>
#include "structs.h"
#include "methods.h"
#include "draw.h"
#include "save.h"

int main ()
{
    SDL_Surface * icon;
    game.step = 0;
    game.play = true;
    SDL_Surface* surf = NULL;
    SDL_Event event;
    SDL_Rect pos;
    game.numplayers = 2;
    cmm = 0;

    // initialiser SDL video
    if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 ) {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }
    //initialiser le son
    int audio_rate = 22050;
    Uint16 audio_format = AUDIO_S16SYS;
    int audio_channels = 2;
    int audio_buffers = 4096;
     
    if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
        fprintf(stderr, "Unable to initialize audio: %s\n", Mix_GetError());
        exit(1);
    }
    //initialiser TTF
    if (TTF_Init() < 0) {
        printf( "Unable to init SDL TTF: %s\n", SDL_GetError() );
        return 1;
    }

    // forcer SDL a liberer l'espace avant de quitter
    atexit(SDL_Quit);
    atexit(TTF_Quit);
    //icon
    icon = IMG_Load("res/icon.png");
    SDL_WM_SetIcon(icon, NULL);
    SDL_WM_SetCaption("Isola", "Isola");
    // les fonts TTF
    font = TTF_OpenFont("res/Nilland.ttf", 36);
    fontb = TTF_OpenFont("res/Nilland-ExtraBold.ttf", 36);

    // creer nouvelle fenetre
    screen = SDL_SetVideoMode(800, 600, 16, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_NOFRAME);
    if ( !screen ) {
        printf("Unable to set 800x600 video: %s\n", SDL_GetError());
        return 1;
    }

    s = IMG_Load("res/img.png");
    
    InitDraw();
    firstDraw();
    
    while ( game.play )
    {
        SDL_WaitEvent(&event);//attendre un evenement
        eventHandler(event);// traiter l'evenement
        SDL_Flip(screen);//mise a jour de l'ecran
    }
    //liberer l'espace
    Mix_CloseAudio();
    SDL_FreeSurface(s);
    SDL_FreeSurface(icon);
    printf("Exited cleanly\n");
    return 0;
}