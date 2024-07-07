//
// Created by Aman's Laptop on 30-06-2024.
//

#include "include/scene.h"

namespace qbRT {
    Scene::Scene()
    {
        m_camera.set_camera_position(qbVector<double>{std::vector<double>{0.0, -10.0, 0.0}});
        m_camera.set_camera_look_at(qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}});
        m_camera.set_camera_up(qbVector<double>{std::vector<double>{0.0, 0.0, 1.0}});
        m_camera.set_camera_hor_len(0.25);
        m_camera.set_camera_asp_ratio(16.0/9.0);
        m_camera.UpdateCameraGeometry();

        objList.push_back(std::make_shared<ObjSphere>(ObjSphere()));
        objList.push_back(std::make_shared<ObjSphere>(ObjSphere()));
        objList.push_back(std::make_shared<ObjSphere>(ObjSphere()));

        GTform obj1Trans, obj2Trans, obj3Trans;
        obj1Trans.SetTransform(	qbVector<double>{std::vector<double>{-1.5, 0.0, 0.0}},
            qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}}, qbVector<double>{std::vector<double>{0.5, 0.5, 0.75}});

        obj2Trans.SetTransform(	qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
            qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
            qbVector<double>{std::vector<double>{0.75, 0.5, 0.5}});

        obj3Trans.SetTransform(	qbVector<double>{std::vector<double>{1.5, 0.0, 0.0}},
            qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
            qbVector<double>{std::vector<double>{0.75, 0.75, 0.75}});

        objList.at(0) -> SetTransform(obj1Trans);
        objList.at(1) -> SetTransform(obj2Trans);
        objList.at(2) -> SetTransform(obj3Trans);

        objList.at(0) -> baseColor = qbVector{std::vector{255.0, 0.0, 0.0}};
        objList.at(1) -> baseColor = qbVector{std::vector{0.0, 255.0, 0.0}};
        objList.at(2) -> baseColor = qbVector{std::vector{0.0, 0.0, 255.0}};

        lightList.push_back(std::make_shared<PointLight>(PointLight()));
        lightList.at(0) -> m_position = qbVector{std::vector{5.0, -10.0, -5.0}};
        lightList.at(0) -> m_color = qbVector{std::vector{255.0, 255.0, 255.0}};
    }

    bool Scene::Render(qbImage &outputImage)
    {
        int xSize = outputImage.GetXSize();
        int ySize = outputImage.GetYSize();

        Ray cameraRay;
        qbVector<double> intPoint{3};
        qbVector<double> localNormal{3};
        qbVector<double> localColor{3};
        double xFact = 1.0 / (static_cast<double>(xSize)/2.0);
        double yFact = 1.0 / (static_cast<double>(ySize)/2.0);

        for(int x = 0; x < xSize; ++x)
        {
            for(int y = 0; y < ySize; ++y)
            {
                double xNorm = (static_cast<double>(x) * xFact) - 1.0;
                double yNorm = (static_cast<double>(y) * yFact) - 1.0;
                m_camera.GenerateRay(xNorm, yNorm, cameraRay);

                for (auto object : objList)
                {
                    if(object->TestIntersections(cameraRay, intPoint, localNormal, localColor))
                    {
                        double intensity;
                        qbVector<double> color{3};
                        bool validIllum = false;

                        for (auto light : lightList)
                        {
                            validIllum = light->CalculateLighting(intPoint, localNormal, objList, object, color, intensity);
                        }

                        if (validIllum)
                        {
                            outputImage.SetPixel(x, y, localColor.GetElement(0) * intensity,
                                localColor.GetElement(1) * intensity,
                                localColor.GetElement(2) * intensity);
                        }
                        else
                        {
                            // outputImage.SetPixel(x, y, 0.0, 0.0, 0.0);
                        }

                    } else
                    {
                        // outputImage.SetPixel(x, y, 0.0, 0.0, 0.0);
                    }

                }
            }
        }
        return true;
    }
}