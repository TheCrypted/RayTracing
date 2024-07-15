//
// Created by Aman's Laptop on 30-06-2024.
//

#include "include/scene.h"



namespace qbRT {
    Scene::Scene()
    {
        m_camera.set_camera_position(qbVector{std::vector{6.0, -12.0, 0.0}});
        m_camera.set_camera_look_at(qbVector{std::vector{0.0, 0.0, 0.0}});
        m_camera.set_camera_up(qbVector{std::vector{0.0, 0.0, 1.0}});
        m_camera.set_camera_hor_len(0.25);
        m_camera.set_camera_asp_ratio(16.0/9.0);
        m_camera.UpdateCameraGeometry();

        auto floorTexture = std::make_shared<TextureBase::Checker> (TextureBase::Checker());
        auto imageTexture = std::make_shared<TextureBase::Checker> (TextureBase::Checker());

        floorTexture -> SetTransform(qbVector{std::vector{0.0, 0.0}}, 0.0,
            qbVector{std::vector{16.0, 16.0}});


        imageTexture -> SetColor(qbVector{std::vector{0.2, 0.2, 0.8}}, qbVector{std::vector{1.0, 0.5, 0.0}});
        imageTexture -> SetTransform(qbVector{std::vector{0.0, 0.0}}, 0.0,
            qbVector{std::vector{8.0*(M_PI/2.0), 8.0}} );


        auto floorMaterial = std::make_shared<SimpleMaterial> (SimpleMaterial());
        auto imageMaterial = std::make_shared<SimpleMaterial> (SimpleMaterial());
        auto cylMaterial = std::make_shared<SimpleMaterial> (SimpleMaterial());
        auto coneMaterial = std::make_shared<SimpleMaterial> (SimpleMaterial());
        auto sphereMaterial = std::make_shared<SimpleMaterial> (SimpleMaterial());
        auto sphereMaterial2 = std::make_shared<SimpleMaterial> (SimpleMaterial());
        auto sphereMaterial3 = std::make_shared<SimpleMaterial> (SimpleMaterial());
        auto glassMaterial = std::make_shared<SimpleRefractive> (SimpleRefractive());
        auto wallMaterial = std::make_shared<SimpleMaterial> (SimpleMaterial());

        cylMaterial -> baseColor = qbVector{std::vector{0.2, 0.3, 0.8}};
        cylMaterial -> reflectivity = 0.05;
        cylMaterial -> shine = 5.0;

        imageMaterial -> baseColor = qbVector{std::vector{1.0, 0.125, 0.125}};
        imageMaterial -> reflectivity = 0.0;
        imageMaterial -> shine = 0.0;
        imageMaterial -> AssignTexture(imageTexture);

        coneMaterial -> baseColor = qbVector{std::vector{0.8, 0.3, 0.4}};
        coneMaterial -> reflectivity = 0.05;
        coneMaterial -> shine = 5.0;
        coneMaterial -> AssignTexture(imageTexture);

        wallMaterial -> baseColor = qbVector{std::vector{1.0, 0.125, 0.125}};
        wallMaterial -> reflectivity = 0.75;
        wallMaterial -> shine = 0.0;

        floorMaterial -> baseColor = qbVector{std::vector{1.0, 1.0, 1.0}};
        floorMaterial -> reflectivity = 0.25;
        floorMaterial -> shine = 0.0;
        floorMaterial -> AssignTexture(floorTexture);

        sphereMaterial -> baseColor = qbVector{std::vector{1.0, 0.2, 0.2}};
        sphereMaterial -> reflectivity = 0.8;
        sphereMaterial -> shine = 32.0;

        sphereMaterial2 -> baseColor = qbVector{std::vector{0.2, 1.0, 0.2}};
        sphereMaterial2 -> reflectivity = 0.8;
        sphereMaterial2 -> shine = 32.0;

        sphereMaterial3 -> baseColor = qbVector{std::vector{0.2, 0.2, 1.0}};
        sphereMaterial3 -> reflectivity = 0.8;
        sphereMaterial3 -> shine = 32.0;

        glassMaterial -> baseColor = qbVector{std::vector{0.7, 0.7, 0.2}};
        glassMaterial -> reflectivity = 0.25;
        glassMaterial -> shine = 32.0;
        glassMaterial -> translucency = 0.75;
        glassMaterial -> refractiveIndex = 1.333;

        auto floor = std::make_shared<ObjPlane> (ObjPlane());
        floor -> SetTransform(GTform{qbVector{std::vector{0.0, 0.0, 1.0}},
            qbVector{std::vector{0.0, 0.0, 0.0}},
            qbVector{std::vector{16.0, 16.0, 1.0}}});
        floor ->AssignMaterial(floorMaterial);

        auto img = std::make_shared<ObjPlane> (ObjPlane());
        img -> SetTransform(GTform {	qbVector{std::vector{0.0, 5.0, -0.75}},
            qbVector{std::vector{-M_PI/2.0, 0.0, 0.0}},
            qbVector{std::vector{1.75, 1.75, 1.0}}}	);
        img -> AssignMaterial(imageMaterial);

        auto sphere = std::make_shared<ObjSphere> (ObjSphere());
        sphere -> SetTransform(GTform	{	qbVector{std::vector{-2.0, -2.0, 0.25}},
            qbVector{std::vector{0.0, 0.0, 0.0}},
            qbVector{std::vector{0.75, 0.75, 0.75}}}	);
        sphere -> AssignMaterial(sphereMaterial);

        auto sphere2 = std::make_shared<ObjSphere> (ObjSphere());
        sphere2 -> SetTransform(GTform	{	qbVector{std::vector{-2.0, -0.5, 0.25}},
            qbVector{std::vector{0.0, 0.0, 0.0}},
            qbVector{std::vector{0.75, 0.75, 0.75}}}	);
        sphere2 -> AssignMaterial(sphereMaterial2);

        auto sphere3 = std::make_shared<ObjSphere> (ObjSphere());
        sphere3 -> SetTransform(GTform	{	qbVector{std::vector{-2.0, -1.25, -1.0}},
            qbVector{std::vector{0.0, 0.0, 0.0}},
            qbVector{std::vector{0.75, 0.75, 0.75}}}	);
        sphere3 -> AssignMaterial(sphereMaterial3);

        auto sphere4 = std::make_shared<ObjSphere> (ObjSphere());
        sphere4 -> SetTransform(GTform	{	qbVector{std::vector{2.0, -1.25, 0.25}},
            qbVector{std::vector{0.0, 0.0, 0.0}},
            qbVector{std::vector{0.75, 0.75, 0.75}}}	);
        sphere4 -> AssignMaterial(glassMaterial);

        auto cylinder = std::make_shared<ObjCylinder>(ObjCylinder());
        cylinder -> SetTransform(GTform{qbVector{std::vector{0.0, 0.0, 0.0}},
            qbVector{std::vector{0.0, 0.0, 0.0}},
            qbVector{std::vector{0.5, 0.5, 1.0}}});
        cylinder->AssignMaterial(glassMaterial);

        auto cube = std::make_shared<ObjCube>(ObjCube());
        cube -> SetTransform(GTform{qbVector{std::vector{0.0, 0.0, 0.0}},
            qbVector{std::vector{0.0, 0.0, 0.0}},
            qbVector{std::vector{0.5, 0.5, 1.0}}});
        cube->AssignMaterial(sphereMaterial2);

        objList.push_back(floor);
        objList.push_back(img);
        objList.push_back(sphere);
        objList.push_back(sphere2);
        objList.push_back(sphere3);
        objList.push_back(sphere4);
        objList.push_back(cube);

        lightList.push_back(std::make_shared<PointLight>(PointLight()));
        lightList.at(0) -> m_position = qbVector{std::vector{5.0, -10.0, -5.0}};
        lightList.at(0) -> m_color = qbVector{std::vector{0.0, 0.0, 1.0}};

        lightList.push_back(std::make_shared<PointLight>(PointLight()));
        lightList.at(1) -> m_position = qbVector {std::vector {-5.0, -10.0, -5.0}};
        lightList.at(1) -> m_color = qbVector {std::vector {1.0, 1.0, 1.0}};

        // lightList.push_back(std::make_shared<PointLight>(PointLight()));
        // lightList.at(2) -> m_position = qbVector {std::vector {0.0, -10.0, -5.0}};
        // lightList.at(2) -> m_color = qbVector {std::vector {0.0, 1.0, 0.0}};
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
                        qbVector<double> color = closestObject -> m_pMaterial -> ComputeColor(objList, lightList,
                            closestObject, closestIntPoint, closestLocalNormal, cameraRay);
                        outputImage.SetPixel(x, y, color.GetElement(0), color.GetElement(1), color.GetElement(2));
                    }
                    else
                    {
                        qbVector<double> matColor = Material::ComputeDiffuseColor(objList, lightList,
                            closestObject, closestIntPoint, closestLocalNormal, closestObject->baseColor);
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
