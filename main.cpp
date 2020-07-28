#include <stdio.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include "gamelan.h"

bool _handle_sdl_event( SDL_Event* );

void morphPixels( DisplayState displayState, uint32* pixels, uint32 modifier ) {
    
    for( int x=0; x<displayState.WinWidth; x++ ) {
        for( int y = 0; y<displayState.WinHeight; y++ ) {
            pixels[y*displayState.WinWidth+x] = ( (y<<16) | (x<<8) | modifier ) * modifier;
        }
    }
    
    for( int x=0; x<displayState.WinWidth; x++ ) {
        for( int y = 0; y<10; y++ ) {
            pixels[y*displayState.WinWidth+x] = 0x00ff00ff;
        }
    }
    
    for( int x=0; x<displayState.WinWidth; x++ ) {
        for( int y = displayState.WinHeight-10; y<displayState.WinHeight; y++ ) {
            pixels[y*displayState.WinWidth+x] = 0xff00ff00;
        }
    }
    
}

int main( int argc, char** argv ) {
    
    DisplayState displayState;
    
    
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf( "SDL Failed to Initialize\n" );
        return -1;
    }
    
    SDL_Window* window = SDL_CreateWindow("Gamelan Fun House",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          640,
                                          480,
                                          SDL_WINDOW_RESIZABLE);
    // create a renderer
    
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    
    SDL_GetWindowSize(window, &displayState.WinWidth, &displayState.WinHeight);
    
    printf( "window size is %d x %d\n", displayState.WinWidth, displayState.WinHeight );
    
    
    SDL_Texture* texture = SDL_CreateTexture(renderer,
                                             SDL_PIXELFORMAT_ARGB8888,
                                             SDL_TEXTUREACCESS_STREAMING,
                                             displayState.WinWidth,
                                             displayState.WinHeight);
    
    
    uint32* pixels = (uint32*)malloc( displayState.WinWidth * displayState.WinHeight * sizeof(uint32) );
    
    
    // primary event loop
    
    uint32 modifier = 1;
    
    while(true) {
        SDL_Event event;
        SDL_PollEvent(&event);
        
        if( event.type == SDL_QUIT ) {
            break;
        }
        
        
        morphPixels( displayState, pixels, modifier );
        
        SDL_UpdateTexture(texture,
                          0,
                          pixels,
                          displayState.WinWidth * sizeof(*pixels));
        
        SDL_RenderCopy(renderer,texture,0,0);
        
        SDL_RenderClear(renderer);
        
        SDL_RenderPresent(renderer);
        
        SDL_RenderCopy(renderer,texture,0,0);
        
        SDL_RenderPresent(renderer);
        
        
        
        usleep( 1000 * 17 );
        
        if( modifier++ > 255 ) {
            modifier = 0;
        }
    }
    SDL_Quit();
    
    return 0;
    
    
}