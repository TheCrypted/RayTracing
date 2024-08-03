//
// Created by Aman's Laptop on 30-06-2024.
//

#include "include/scene.h"



namespace qbRT {
    Scene::Scene()
    {
        m_camera.set_camera_position(qbVector3{6.0, -12.0, 0.0});
        m_camera.set_camera_look_at(qbVector3{0.0, 0.0, 0.0});
        m_camera.set_camera_up(qbVector3{0.0, 0.0, 1.0});
        m_camera.set_camera_hor_len(0.25);
        m_camera.set_camera_asp_ratio(16.0/9.0);
        m_camera.UpdateCameraGeometry();

        auto floorTexture = std::make_shared<TextureBase::Checker> (TextureBase::Checker());
        auto imageTexture = std::make_shared<TextureBase::Checker> (TextureBase::Checker());
        auto gradientTexture = std::make_shared<TextureBase::Gradient> (TextureBase::Gradient());
        auto check1Texture = std::make_shared<TextureBase::Checker> (TextureBase::Checker());
        auto check2Texture = std::make_shared<TextureBase::Checker> (TextureBase::Checker());
        auto layeredTexture = std::make_shared<TextureBase::Checker> (TextureBase::Checker());
        auto noiseTexture = std::make_shared<TextureBase::MarbleText> (TextureBase::MarbleText());
        auto stoneTexture = std::make_shared<TextureBase::Stone> (TextureBase::Stone());

        floorTexture -> SetTransform(qbVector2{0.0, 0.0}, 0.0,
            qbVector2{16.0, 16.0});

        gradientTexture -> SetTransform(qbVector2{0.0, 0.0}, 0.0,
            qbVector2{1.0, 1.0});
        gradientTexture -> SetStop(0.0, qbVector4{1.0, 0.0, 0.0, 1.0});
        gradientTexture -> SetStop(0.5, qbVector4{0.0, 1.0, 0.0, 1.0});
        gradientTexture -> SetStop(1.0, qbVector4{0.0, 0.0, 1.0, 1.0});

        check1Texture -> SetTransform(qbVector2{0.0, 0.0}, 0.0,
            qbVector2{8.0, 8.0});
        check1Texture -> SetColor(qbVector4{1.0, 1.0, 1.0, 1.0}, qbVector4{0.2, 0.2, 0.8, 1.0});

        check2Texture -> SetTransform(qbVector2{0.0, 0.0}, -M_PI/4.0,
            qbVector2{8.0, 8.0});
        check2Texture -> SetColor(qbVector4{0.0, 0.0, 0.0, 1.0}, qbVector4{1.0, 0.2, 0.1, 1.0});

        layeredTexture -> SetTransform(qbVector2{0.0, 0.0}, 0.0,
            qbVector2{4.0, 4.0});
        layeredTexture -> SetColor(check1Texture, check2Texture);

        imageTexture -> SetColor(qbVector4{0.2, 0.2, 0.8, 1.0}, qbVector4{1.0, 0.5, 0.0, 1.0});
        imageTexture -> SetTransform(qbVector2{0.0, 0.0}, 0.0,
            qbVector2{8.0*(M_PI/2.0), 8.0} );

        stoneTexture -> SetTransform(qbVector2{0.0, 0.0}, 0.0,
            qbVector2{4.0, 4.0});

        auto normMap = std::make_shared<Normal::TextureNormal>(Normal::TextureNormal());
        normMap -> AssignTexture(stoneTexture);
        normMap -> scale = 0.015;

        auto roughNormMap = std::make_shared<Normal::BasicRough>(Normal::BasicRough());
        roughNormMap -> amplitude = 0.1;

        auto noiseMap = std::make_shared<TextureBase::Colormap> (TextureBase::Colormap());
        noiseMap -> SetStop(0.0, qbVector4{1.0, 1.0, 1.0, 1.0});
        noiseMap -> SetStop(0.2, qbVector4{1.0, 1.0, 1.0, 1.0});
        noiseMap -> SetStop(0.5, qbVector4{1.0, 0.4, 0.0, 1.0});
        noiseMap -> SetStop(0.8, qbVector4{1.0, 1.0, 1.0, 1.0});
        noiseMap -> SetStop(1.0, qbVector4{1.0, 1.0, 1.0, 1.0});

        noiseTexture -> SetColor(noiseMap);
        noiseTexture -> SetAmplitude(4.0, 2.0);
        noiseTexture -> SetScale(6.0, 40.0);
        noiseTexture -> SetMinMax(-1.0, 1.0);
        noiseTexture -> SetSin(1.0, 4.0);


        auto floorMaterial = std::make_shared<SimpleMaterial> (SimpleMaterial());
        auto imageMaterial = std::make_shared<SimpleMaterial> (SimpleMaterial());
        auto cylMaterial = std::make_shared<SimpleMaterial> (SimpleMaterial());
        auto coneMaterial = std::make_shared<SimpleMaterial> (SimpleMaterial());
        auto sphereMaterial = std::make_shared<SimpleMaterial> (SimpleMaterial());
        auto sphereMaterial2 = std::make_shared<SimpleMaterial> (SimpleMaterial());
        auto sphereMaterial3 = std::make_shared<SimpleMaterial> (SimpleMaterial());
        auto glassMaterial = std::make_shared<SimpleRefractive> (SimpleRefractive());
        auto wallMaterial = std::make_shared<SimpleMaterial> (SimpleMaterial());
        auto stoneMaterial = std::make_shared<SimpleMaterial> (SimpleMaterial());
        auto checkedMaterial = std::make_shared<SimpleMaterial> (SimpleMaterial());

        cylMaterial -> baseColor = qbVector3{std::vector{0.2, 0.3, 0.8}};
        cylMaterial -> reflectivity = 0.05;
        cylMaterial -> shine = 5.0;

        imageMaterial -> baseColor = qbVector3{std::vector{1.0, 0.125, 0.125}};
        imageMaterial -> reflectivity = 0.0;
        imageMaterial -> shine = 0.0;
        imageMaterial -> AssignTexture(noiseTexture);

        checkedMaterial -> baseColor = qbVector3{std::vector{1.0, 0.125, 0.125}};
        checkedMaterial -> reflectivity = 0.3;
        checkedMaterial -> shine = 10.0;
        checkedMaterial -> AssignTexture(check1Texture);

        coneMaterial -> baseColor = qbVector3{std::vector{0.8, 0.3, 0.4}};
        coneMaterial -> reflectivity = 0.05;
        coneMaterial -> shine = 5.0;
        coneMaterial -> AssignTexture(imageTexture);

        wallMaterial -> baseColor = qbVector3{std::vector{1.0, 0.125, 0.125}};
        wallMaterial -> reflectivity = 0.75;
        wallMaterial -> shine = 0.0;

        floorMaterial -> baseColor = qbVector3{std::vector{1.0, 1.0, 1.0}};
        floorMaterial -> reflectivity = 0.25;
        floorMaterial -> shine = 0.0;
        floorMaterial -> AssignTexture(floorTexture);
        floorMaterial -> AssignNormalMap(roughNormMap);

        stoneMaterial -> baseColor = qbVector3{std::vector{1.0, 1.0, 1.0}};
        stoneMaterial -> reflectivity = 0.25;
        stoneMaterial -> shine = 32.0;
        stoneMaterial -> AssignTexture(stoneTexture);
        stoneMaterial -> AssignNormalMap(normMap);

        sphereMaterial -> baseColor = qbVector3{std::vector{1.0, 0.2, 0.2}};
        sphereMaterial -> reflectivity = 0.8;
        sphereMaterial -> shine = 32.0;

        sphereMaterial2 -> baseColor = qbVector3{std::vector{0.2, 1.0, 0.2}};
        sphereMaterial2 -> reflectivity = 0.8;
        sphereMaterial2 -> shine = 32.0;

        sphereMaterial3 -> baseColor = qbVector3{std::vector{0.2, 0.2, 1.0}};
        sphereMaterial3 -> reflectivity = 0.8;
        sphereMaterial3 -> shine = 32.0;

        glassMaterial -> baseColor = qbVector3{std::vector{0.7, 0.7, 0.2}};
        glassMaterial -> reflectivity = 0.25;
        glassMaterial -> shine = 32.0;
        glassMaterial -> translucency = 0.75;
        glassMaterial -> refractiveIndex = 1.333;

        auto floor = std::make_shared<ObjPlane> (ObjPlane());
        floor -> SetTransform(GTform{qbVector3{std::vector{0.0, 0.0, 1.0}},
            qbVector3{std::vector{0.0, 0.0, 0.0}},
            qbVector3{std::vector{16.0, 16.0, 1.0}}});
        floor ->AssignMaterial(floorMaterial);
        floor -> uvMapType = uvPlane;

        auto img = std::make_shared<ObjPlane> (ObjPlane());
        img -> SetTransform(GTform {	qbVector3{std::vector{0.0, 5.0, -0.75}},
            qbVector3{std::vector{-M_PI/2.0, 0.0, 0.0}},
            qbVector3{std::vector{1.75, 1.75, 1.0}}}	);
        img -> AssignMaterial(imageMaterial);

        auto sphere = std::make_shared<ObjSphere> (ObjSphere());
        sphere -> SetTransform(GTform	{	qbVector3{std::vector{-2.0, -2.0, 0.25}},
            qbVector3{std::vector{0.0, 0.0, 0.0}},
            qbVector3{std::vector{0.75, 0.75, 0.75}}}	);
        sphere -> AssignMaterial(sphereMaterial);

        auto sphere2 = std::make_shared<ObjSphere> (ObjSphere());
        sphere2 -> SetTransform(GTform	{	qbVector3{std::vector{-2.0, -0.5, 0.25}},
            qbVector3{std::vector{0.0, 0.0, 0.0}},
            qbVector3{std::vector{0.75, 0.75, 0.75}}}	);
        sphere2 -> AssignMaterial(sphereMaterial2);

        auto sphere3 = std::make_shared<ObjSphere> (ObjSphere());
        sphere3 -> SetTransform(GTform	{	qbVector3{std::vector{-2.0, -1.25, -1.0}},
            qbVector3{std::vector{0.0, 0.0, 0.0}},
            qbVector3{std::vector{0.75, 0.75, 0.75}}}	);
        sphere3 -> AssignMaterial(sphereMaterial3);

        auto sphere4 = std::make_shared<ObjSphere> (ObjSphere());
        sphere4 -> SetTransform(GTform	{	qbVector3{std::vector{2.0, -1.25, 0.25}},
            qbVector3{std::vector{0.0, 0.0, 0.0}},
            qbVector3{std::vector{0.75, 0.75, 0.75}}}	);
        sphere4 -> AssignMaterial(glassMaterial);

        auto cylinder = std::make_shared<ObjCylinder>(ObjCylinder());
        cylinder -> SetTransform(GTform{qbVector3{std::vector{0.0, 0.0, 0.0}},
            qbVector3{std::vector{0.0, 0.0, 0.0}},
            qbVector3{std::vector{0.5, 0.5, 1.0}}});
        cylinder->AssignMaterial(checkedMaterial);

        auto cube = std::make_shared<ObjCube>(ObjCube());
        cube -> SetTransform(GTform{qbVector3{std::vector{0.0, 0.0, 0.0}},
            qbVector3{std::vector{0.0, 0.0, 0.0}},
            qbVector3{std::vector{0.5, 0.5, 1.0}}});
        cube->AssignMaterial(sphereMaterial2);

        // composite shape ******************************************

        auto bottleBody = std::make_shared<ObjCylinder>(ObjCylinder());
        bottleBody -> SetTransform(GTform{qbVector3{std::vector{0.0, 0.0, 0.5}},
            qbVector3{std::vector{0.0, 0.0, M_PI/5.0}},
            qbVector3{std::vector{0.4, 0.4, 1.0}}});
        bottleBody -> AssignMaterial(floorMaterial);
        bottleBody -> uvMapType = uvCylinder;

        auto bottleCone = std::make_shared<ObjCone>(ObjCone());
        bottleCone -> SetTransform(GTform{qbVector3{std::vector{0.0, 0.0, -2.0}},
            qbVector3{std::vector{0.0, 0.0, 0.0}},
            qbVector3{std::vector{0.4, 0.4, 0.5}}});
        bottleCone -> AssignMaterial(sphereMaterial);

        auto bottleCap = std::make_shared<ObjCylinder>(ObjCylinder());
        bottleCap -> SetTransform(GTform{qbVector3{std::vector{0.0, 0.0, -1.5}},
            qbVector3{std::vector{0.0, 0.0, 0.0}},
            qbVector3{std::vector{0.2, 0.2, 0.5}}});
        bottleCap -> AssignMaterial(sphereMaterial2);
        bottleCap -> uvMapType = uvCylinder;

        auto bottle = std::make_shared<Shape::Composite>(Shape::Composite());
        bottle -> AddSubShape(bottleBody);
        bottle -> AddSubShape(bottleCone);
        bottle -> AddSubShape(bottleCone);
        bottle -> SetTransform(GTform{qbVector3{std::vector{1.0, -1.75, 0.0}}, qbVector3{std::vector{0.0, 0.0, 0.0}},
        qbVector3{std::vector{1.0, 1.0, 1.0}}});

        // ******************************************

        objList.push_back(floor);
        objList.push_back(img);
        objList.push_back(sphere);
        objList.push_back(sphere2);
        objList.push_back(sphere3);
        objList.push_back(sphere4);
        objList.push_back(cylinder);

        lightList.push_back(std::make_shared<PointLight>(PointLight()));
        lightList.at(0) -> m_position = qbVector3{std::vector{5.0, -10.0, -5.0}};
        lightList.at(0) -> m_color = qbVector3{std::vector{1.0, 1.0, 1.0}};

        lightList.push_back(std::make_shared<PointLight>(PointLight()));
        lightList.at(1) -> m_position = qbVector3 {std::vector {-5.0, -10.0, -5.0}};
        lightList.at(1) -> m_color = qbVector3 {std::vector {1.0, 1.0, 1.0}};

        // lightList.push_back(std::make_shared<PointLight>(PointLight()));
        // lightList.at(2) -> m_position = qbVector3 {std::vector {0.0, -10.0, -5.0}};
        // lightList.at(2) -> m_color = qbVector3 {std::vector {0.0, 1.0, 0.0}};
    }

    bool Scene::Render(qbImage &outputImage)
    {
        int xSize = outputImage.GetXSize();
        int ySize = outputImage.GetYSize();

        Ray cameraRay;
        qbVector3<double> intPoint{3};
        qbVector3<double> localNormal{3};
        qbVector3<double> localColor{3};
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
                Data::HitData hitData;
                bool intersectionFound = CastRay(cameraRay, closestObject, hitData);

                if (intersectionFound)
                {
                    if (closestObject -> m_hasMaterial)
                    {
                        Material::reflectionRayCount = 0;
                        qbVector3<double> color = closestObject -> m_pMaterial -> ComputeColor(objList, lightList,
                            closestObject, hitData.intPoint, hitData.localNormal, cameraRay);
                        outputImage.SetPixel(x, y, color.GetElement(0), color.GetElement(1), color.GetElement(2));
                    }
                    else
                    {
                        qbVector3<double> matColor = Material::ComputeDiffuseColor(objList, lightList,
                            closestObject, hitData.intPoint, hitData.localNormal, closestObject->baseColor);
                        outputImage.SetPixel(x, y, matColor.GetElement(0), matColor.GetElement(1), matColor.GetElement(2));
                    }
                }
            }
        }
        return true;
    }

    bool Scene::CastRay(Ray &castRay, std::shared_ptr<Object> &closestObject,
        Data::HitData& closestHitData)
    {
        Data::HitData hitData;
        double minDist = 1e6;
        bool intersectionFound = false;
        for (auto currentObject : objList)
        {
            bool validInt = currentObject -> TestIntersections(castRay, hitData);

            if (validInt)
            {

                intersectionFound = true;

                double dist = (hitData.intPoint - castRay.m_point1).norm();

                if (dist < minDist)
                {
                    minDist = dist;
                    closestObject = currentObject;
                    closestHitData = hitData;
                }
            }
        }
        return intersectionFound;
    }
}
