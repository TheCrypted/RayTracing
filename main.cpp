#include <SDL.h>
#include <stdio.h>
#include <iostream>

#include "include/CApp.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int main(int argc, char** argv){
    CApp theApp;
    return theApp.OnExecute();
}