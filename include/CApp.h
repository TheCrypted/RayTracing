//
// Created by Aman's Laptop on 28-06-2024.
//

#ifndef CAPP_H
#define CAPP_H

#include <SDL.h>
#include "qbImage.h"
#include "scene.h"

class CApp
{
    public:
        CApp();
        int OnExecute();
        bool OnInit();
        void OnEvent(SDL_Event* event);
        void OnLoop();
        void OnRender();
        void OnExit();
    private:
        qbImage image;
        qbRT::Scene scene;
        bool running;
        SDL_Window* window;
        SDL_Renderer* renderer;
};



#endif //CAPP_H
