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
#include "objectPlane.h"
#include "objectCylinder.h"
#include "simpleMaterial.h"
#include "light.h"
#include "objCone.h"
#include "objCube.h"
#include "pointLight.h"
#include "checkerText.h"
#include "simpleRefractive.h"
#include "gradient.h"
#include "basicNoiseText.h"
#include "marbleText.h"

namespace qbRT
{
    class Scene {
        public:
            Scene();

            bool Render(qbImage &outputImage);
            bool CastRay(Ray &castRay, std::shared_ptr<Object> &closestObject,
                qbVector<double> &closestIntPoint, qbVector<double> &closestLocalNormal,
                qbVector<double> &closestLocalColor);

        private:

        private:
            Camera m_camera;
            std::vector<std::shared_ptr<Object>> objList;
            std::vector<std::shared_ptr<Light>> lightList;
    };
}



#endif //SCENE_H
