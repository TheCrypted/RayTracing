//
// Created by Aman's Laptop on 28-06-2024.
//

#include "include/CApp.h"
#include "include/qbLinAlg/qbVector.h"

CApp::CApp() {
    running = true;
    window = NULL;
    renderer = NULL;
}

bool CApp::OnInit()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        return false;
    }
    window = SDL_CreateWindow("Testing Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);

    if(window != NULL){
        renderer = SDL_CreateRenderer(window, -1, 0);
        image.Initialize(1280, 720, renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        scene.Render(image);
        image.Display();
        SDL_RenderPresent(renderer);

    } else return false;

    return true;
}

int CApp::OnExecute()
{
    SDL_Event event;
    if(OnInit() == false) return -1;

    while(running)
    {
        while(SDL_PollEvent(&event) != 0)
        {
            OnEvent(&event);
        }
        OnLoop();
        OnRender();
    }
    return 0;
}

void CApp::OnEvent(SDL_Event* event)
{
    if(event->type == SDL_QUIT) running = false;
}

void CApp::OnLoop()
{

}

void CApp::OnRender()
{
    // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);
    // SDL_RenderClear(renderer);
    // scene.Render(image);
    // image.Display();
    // SDL_RenderPresent(renderer);
}

void CApp::OnExit()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
}

void CApp::printVec(const qbVector<double> &vector)
{
    for (int i = 0; i < vector.GetNumDims(); i++)
    {
        std::cout << std::fixed << std::setprecision(3) << vector.GetElement(i) << " ";
    }
    std::cout << std::endl;
}