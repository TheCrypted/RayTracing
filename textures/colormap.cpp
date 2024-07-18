//
// Created by Aman's Laptop on 18-07-2024.
//

#include "../include/colormap.h"

namespace qbRT::Textures
{
    Colormap::Colormap()
    = default;

    Colormap::~Colormap()
    = default;

    void Colormap::SetStop(double stop, const qbVector<double>& color)
    {
        stops.push_back(stop);
        colors.push_back(color);
    }

    qbVector<double> Colormap::GetColor(double stop)
    {
        int numStops = stops.size();
        int preStop = 0;
        int postStop = 0;
        double diff = 0.0;

        for (int i = 0; i < numStops; ++i)
        {
            double locDiff = stops[i] - stop;
            if(fabs(locDiff) < diff)
            {
                diff = locDiff;
                if(locDiff < 0)
                {
                    postStop = std::min(numStops, i+1);
                }
                else if (locDiff > 0)
                {
                    postStop = std::max((i-1), 0);
                } else
                {
                    postStop = i;
                }
            }
        }

        if(preStop == postStop) return colors[preStop];

        if(postStop < preStop) std::swap(postStop, preStop);

        double x_0 = stops[preStop];
        double x_1 = stops[postStop];
        return colors.at(preStop) + (stop - x_0) * (colors.at(postStop) - colors.at(preStop)) * (1.0 / (x_1 - x_0));

    }



}