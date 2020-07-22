#define SDL_MAIN_HANDLED
#include <windows.h>
#include <stdio.h>
#include "SDL2\SDL.h"

//SDL Variables
SDL_Window* window = NULL;
SDL_Surface* surface = NULL;
SDL_Surface* draw = NULL;
SDL_Event event;

//Variables
bool quit = false;

// Dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Functions
bool init();
bool loadMedia();
void close();



int main(int argc, char *args[]){

    if(init()){
        if(loadMedia()){

            SDL_BlitSurface(draw, NULL, surface, NULL);
            SDL_UpdateWindowSurface(window);
            
            while(!quit){
                while(SDL_PollEvent(&event) != 0)
                    if(event.type == SDL_QUIT)
                        quit = true;
            }
        }
    }
    close();
    return 0;
} 


bool init(){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Init error: %s.\n", SDL_GetError());
    }else{
        window = SDL_CreateWindow("Machine Learning Platform", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(window == NULL){
            printf("Window error: %s.\n", SDL_GetError());
            return false;
        }
        surface = SDL_GetWindowSurface(window);
    }
    return true;
}


bool loadMedia(){
    draw = SDL_LoadBMP("picture.bmp");
    if(draw == NULL){
        printf("Load error: %s.\n", SDL_GetError());
        return false;
    }
    return true;
}

void close(){
    SDL_FreeSurface(draw);
    draw = NULL;

    SDL_DestroyWindow(window);
    window = NULL;

    SDL_Quit();
}