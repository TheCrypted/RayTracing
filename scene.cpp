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
        double minDist = 1e6;
        double maxDist = 0.0;
        for(int x = 0; x < xSize; x++)
        {
            for(int y = 0; y < ySize; y++)
            {
                double xNorm = (static_cast<double>(x) * xFact) - 1.0;
                double yNorm = (static_cast<double>(y) * yFact) - 1.0;
                m_camera.GenerateRay(xNorm, yNorm, cameraRay);

                bool validInt = m_sphere.TestIntersections(cameraRay, intPoint, localNormal, localColor);

                if(validInt)
                {
                    outputImage.SetPixel(x, y, 255.0, 0.0, 0.0);
                } else
                {
                    outputImage.SetPixel(x, y, 0.0, 0.0, 0.0);
                }
            }
        }
    }
}