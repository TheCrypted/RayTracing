//
// Created by Aman's Laptop on 30-06-2024.
//

#include "include/scene.h"
#include "include/simpleMaterial.h"

namespace qbRT {
    Scene::Scene()
    {
        m_camera.set_camera_position(qbVector<double>{std::vector<double>{0.0, -10.0, -1.0}});
        m_camera.set_camera_look_at(qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}});
        m_camera.set_camera_up(qbVector<double>{std::vector<double>{0.0, 0.0, 1.0}});
        m_camera.set_camera_hor_len(0.25);
        m_camera.set_camera_asp_ratio(16.0/9.0);
        m_camera.UpdateCameraGeometry();

        auto testMaterial = std::make_shared<SimpleMaterial>(SimpleMaterial());
        auto testMaterial2 = std::make_shared<SimpleMaterial> (SimpleMaterial());
        auto testMaterial3 = std::make_shared<SimpleMaterial> (SimpleMaterial());
        auto floorMaterial = std::make_shared<SimpleMaterial> (SimpleMaterial());


        testMaterial -> baseColor = qbVector{std::vector{0.25, 0.5, 0.8}};
        testMaterial -> reflectivity = 0.1;
        testMaterial -> shine = 10.0;

        testMaterial2 -> baseColor = qbVector{std::vector{1.0, 0.5, 0.0}};
        testMaterial2 -> reflectivity = 0.75;
        testMaterial2 -> shine = 10.0;

        testMaterial3 -> baseColor = qbVector{std::vector{1.0, 0.8, 0.0}};
        testMaterial3 -> reflectivity = 0.25;
        testMaterial3 -> shine = 10.0;

        floorMaterial -> baseColor = qbVector{std::vector{1.0, 1.0, 1.0}};
        floorMaterial -> reflectivity = 0.5;
        floorMaterial -> shine = 0.0;

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
            qbVector<double>{std::vector<double>{0.5, 0.5, 0.5}});

        obj2Trans.SetTransform(	qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
            qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
            qbVector<double>{std::vector<double>{0.5, 0.5, 0.5}});

        obj3Trans.SetTransform(	qbVector<double>{std::vector<double>{1.5, 0.0, 0.0}},
            qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
            qbVector<double>{std::vector<double>{0.5, 0.5, 0.5}});

        objList.at(0) -> SetTransform(obj1Trans);
        objList.at(1) -> SetTransform(obj2Trans);
        objList.at(2) -> SetTransform(obj3Trans);
        objList.at(3) -> SetTransform(planeTrans);

        objList.at(0) -> baseColor = qbVector{std::vector{1.0, 0.5, 0.0}};
        objList.at(1) -> baseColor = qbVector{std::vector{0.0, 1.0, 0.5}};
        objList.at(2) -> baseColor = qbVector{std::vector{0.5, 0.0, 1.0}};
        objList.at(3) -> baseColor = qbVector{std::vector{0.5, 0.5, 0.5}};

        objList.at(0) -> AssignMaterial(testMaterial);
        objList.at(1) -> AssignMaterial(testMaterial2);
        objList.at(2) -> AssignMaterial(testMaterial3);
        objList.at(3) -> AssignMaterial(floorMaterial);

        lightList.push_back(std::make_shared<PointLight>(PointLight()));
        lightList.at(0) -> m_position = qbVector{std::vector{5.0, -10.0, -5.0}};
        lightList.at(0) -> m_color = qbVector{std::vector{1.0, 1.0, 1.0}};

        lightList.push_back(std::make_shared<PointLight>(PointLight()));
        lightList.at(1) -> m_position = qbVector {std::vector {-5.0, -10.0, -5.0}};
        lightList.at(1) -> m_color = qbVector {std::vector {1.0, 0.0, 0.0}};

        lightList.push_back(std::make_shared<PointLight>(PointLight()));
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
            setbuf(stdout, NULL);
            printf("check");
            std::cout << "Rendering: " << x << " / " << xSize << std::endl;
            for(int y = 0; y < ySize; ++y)
            {
                double xNorm = (static_cast<double>(x) * xFact) - 1.0;
                double yNorm = (static_cast<double>(y) * yFact) - 1.0;
                m_camera.GenerateRay(xNorm, yNorm, cameraRay);

                std::shared_ptr<Object> closestObject;
                qbVector<double> closestIntPoint		{3};
                qbVector<double> closestLocalNormal	{3};
                qbVector<double> closestLocalColor	{3};
                bool intersectionFound = CastRay(cameraRay, closestObject, closestIntPoint, closestLocalNormal, closestLocalColor);

                if (intersectionFound)
                {
                    if (closestObject -> m_hasMaterial)
                    {
                        Material::reflectionRayCount = 0;
                        qbVector<double> color = closestObject -> m_pMaterial -> ComputeColor(	objList, lightList,
                            closestObject, closestIntPoint,
                            closestLocalNormal, cameraRay);
                        outputImage.SetPixel(x, y, color.GetElement(0), color.GetElement(1), color.GetElement(2));
                    }
                    else
                    {
                        qbVector<double> matColor = Material::ComputeDiffuseColor(objList, lightList,
                            closestObject, closestIntPoint,
                            closestLocalNormal, closestObject->baseColor);
                        outputImage.SetPixel(x, y, matColor.GetElement(0), matColor.GetElement(1), matColor.GetElement(2));
                    }
                }
            }
        }
        return true;
    }

    bool Scene::CastRay(Ray &castRay, std::shared_ptr<Object> &closestObject,
        qbVector<double> &closestIntPoint, qbVector<double> &closestLocalNormal,
        qbVector<double> &closestLocalColor)
    {
        qbVector<double> intPoint			{3};
        qbVector<double> localNormal	{3};
        qbVector<double> localColor		{3};
        double minDist = 1e6;
        bool intersectionFound = false;
        for (auto currentObject : objList)
        {
            bool validInt = currentObject -> TestIntersections(castRay, intPoint, localNormal, localColor);

            if (validInt)
            {

                intersectionFound = true;

                double dist = (intPoint - castRay.m_point1).norm();

                if (dist < minDist)
                {
                    minDist = dist;
                    closestObject = currentObject;
                    closestIntPoint = intPoint;
                    closestLocalNormal = localNormal;
                    closestLocalColor = localColor;
                }
            }
        }
        return intersectionFound;
    }
}
