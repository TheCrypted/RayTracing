//
// Created by Aman's Laptop on 30-06-2024.
//

#include "include/scene.h"

qbRT::Scene::Scene()
{
}

bool qbRT::Scene::Render(qbImage &outputImage)
{
    int xSize = outputImage.GetXSize();
    int ySize = outputImage.GetYSize();
    for (int i = 0; i < xSize; i++)
    {
        for (int j = 0; j < ySize; j++)
        {
            auto red = (static_cast<double>(i) / static_cast<double>(xSize)) * 255.0;
            auto green = (static_cast<double>(j) / static_cast<double>(ySize)) * 255.0;
            outputImage.SetPixel(i, j, red, green, 0.0);
        }
    }
    return true;
}