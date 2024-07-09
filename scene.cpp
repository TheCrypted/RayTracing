//
// Created by Aman's Laptop on 30-06-2024.
//

#include "include/scene.h"

namespace qbRT {
    Scene::Scene()
    {
        m_camera.set_camera_position(qbVector<double>{std::vector<double>{0.0, -10.0, -1.0}});
        m_camera.set_camera_look_at(qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}});
        m_camera.set_camera_up(qbVector<double>{std::vector<double>{0.0, 0.0, 1.0}});
        m_camera.set_camera_hor_len(0.25);
        m_camera.set_camera_asp_ratio(16.0/9.0);
        m_camera.UpdateCameraGeometry();

        objList.push_back(std::make_shared<ObjSphere>(ObjSphere()));
        objList.push_back(std::make_shared<ObjSphere>(ObjSphere()));
        objList.push_back(std::make_shared<ObjSphere>(ObjSphere()));
        objList.push_back(std::make_shared<ObjPlane>(ObjPlane()));

        GTform planeTrans;
        planeTrans.SetTransform(qbVector{std::vector{0.0, 0.0, 0.75}},
            qbVector{std::vector{0.0, 0.0, 0.0}},
            qbVector{std::vector{4.0, 4.0, 1.0}});

        GTform obj1Trans, obj2Trans, obj3Trans;
        obj1Trans.SetTransform(	qbVector<double>{std::vector<double>{-1.5, 0.0, 0.0}},
            qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
            qbVector<double>{std::vector<double>{0.5, 0.5, 0.75}});

        obj2Trans.SetTransform(	qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
            qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
            qbVector<double>{std::vector<double>{0.75, 0.5, 0.5}});

        obj3Trans.SetTransform(	qbVector<double>{std::vector<double>{1.5, 0.0, 0.0}},
            qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
            qbVector<double>{std::vector<double>{0.75, 0.75, 0.75}});

        objList.at(0) -> SetTransform(obj1Trans);
        objList.at(1) -> SetTransform(obj2Trans);
        objList.at(2) -> SetTransform(obj3Trans);
        objList.at(3) -> SetTransform(planeTrans);

        objList.at(0) -> baseColor = qbVector{std::vector{1.0, 0.5, 0.0}};
        objList.at(1) -> baseColor = qbVector{std::vector{0.0, 1.0, 0.5}};
        objList.at(2) -> baseColor = qbVector{std::vector{0.5, 0.0, 1.0}};
        objList.at(3) -> baseColor = qbVector{std::vector{0.5, 0.5, 0.5}};

        lightList.push_back(std::make_shared<PointLight>(PointLight()));
        lightList.at(0) -> m_position = qbVector{std::vector{5.0, -10.0, -5.0}};
        lightList.at(0) -> m_color = qbVector{std::vector{1.0, 1.0, 1.0}};

        lightList.push_back(std::make_shared<PointLight> (PointLight()));
        lightList.at(1) -> m_position = qbVector {std::vector {-5.0, -10.0, -5.0}};
        lightList.at(1) -> m_color = qbVector {std::vector {1.0, 0.0, 0.0}};

        lightList.push_back(std::make_shared<PointLight> (PointLight()));
        lightList.at(2) -> m_position = qbVector {std::vector {0.0, -10.0, -5.0}};
        lightList.at(2) -> m_color = qbVector {std::vector {0.0, 1.0, 0.0}};
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

                std::shared_ptr<Object> closestObj;
                qbVector<double> closestIntPoint{3};
                qbVector<double> closestNormal{3};
                qbVector<double> closestColor{3};
                double closestDist = 1.0e10;
                bool validIntersection = false;

                for (auto object : objList)
                {
                    if(object->TestIntersections(cameraRay, intPoint, localNormal, localColor))
                    {
                        validIntersection = true;
                        double dist = (intPoint - cameraRay.m_point1).norm();
                        if(dist < closestDist)
                        {
                            closestDist = dist;
                            closestObj = object;
                            closestIntPoint = intPoint;
                            closestNormal = localNormal;
                            closestColor = localColor;
                        }

                    } else
                    {
                        // outputImage.SetPixel(x, y, 0.0, 0.0, 0.0);
                    }

                }

                qbVector<double> color;
                double red = 0.0;
                double green = 0.0;
                double blue = 0.0;
                bool validIllum = false;
                bool illumFound = false;
                double intensity;

                if(validIntersection)
                {
                    for(auto light : lightList)
                    {
                        validIllum = light -> CalculateLighting(closestIntPoint, closestNormal, objList, closestObj, color, intensity);
                        if(validIllum)
                        {
                            illumFound = true;
                            red += color.GetElement(0) * intensity;
                            green += color.GetElement(1) * intensity;
                            blue += color.GetElement(2) * intensity;
                        }
                    }

                    if(illumFound)
                    {
                        red *= closestColor.GetElement(0);
                        green *= closestColor.GetElement(1);
                        blue *= closestColor.GetElement(2);
                        outputImage.SetPixel(x, y, red, green, blue);
                    }
                }
            }
        }
        return true;
    }
}