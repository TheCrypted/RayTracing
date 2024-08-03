//
// Created by Aman's Laptop on 28-07-2024.
//

#include "include/utils.h"

namespace qbRT::Utils
{
    void PrintVector(const qbVector3<double>& vec)
    {
        for (int i = 0; i < 3; i++)
        {
            std::cout << vec.GetElement(i) << " ";
        }
        std::cout << std::endl;
    }
}