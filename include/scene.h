//
// Created by Aman's Laptop on 30-06-2024.
//

#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <SDL.h>
#include "qbImage.h"
#include "camera.h"
#include "objSphere.h"

namespace qbRT
{
    class Scene {
        public:
            Scene();

            bool Render(qbImage &outputImage);

        private:

        private:
            Camera m_camera;
            ObjSphere m_sphere;
    };
}



#endif //SCENE_H
