//
// Created by Aman's Laptop on 30-06-2024.
//

#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>
#include <SDL.h>
#include "qbImage.h"
#include "camera.h"
#include "objSphere.h"
#include "pointLight.h"

namespace qbRT
{
    class Scene {
        public:
            Scene();

            bool Render(qbImage &outputImage);

        private:

        private:
            Camera m_camera;

            std::vector<std::shared_ptr<Object>> objList;
            std::vector<std::shared_ptr<PointLight>> lightList;
    };
}



#endif //SCENE_H
