#include <stdio.h>
#include <SDL2/SDL.h>

bool _handle_sdl_event( SDL_Event* );

int main( int argc, char** argv ) {
    
    
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf( "SDL Failed to Initialize\n" );
        return -1;
    }
    
    SDL_Window* Window = SDL_CreateWindow("Gamelan Fun House",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          640,
                                          480,
                                          SDL_WINDOW_RESIZABLE);
    
    // primary event loop
    while(true) {
        SDL_Event event;
        SDL_WaitEvent(&event);
        
        if( event.type == SDL_QUIT ) {
            break;
        }
    }
    
    SDL_Quit();
    
    return 0;
}

