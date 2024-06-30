//
// Created by Aman's Laptop on 30-06-2024.
//

#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <SDL.h>
#include "qbImage.h"

namespace qbRT
{
    class Scene {
        public:
            Scene();

            bool Render(qbImage &outputImage);

        private:

        private:
    };
}



#endif //SCENE_H
