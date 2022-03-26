#pragma once
#include "header.h"
#include "ImagePixelMapping.h"

class Scyyz12ImagePixelMapping :
    public ImagePixelMapping
{
public:
    bool mapCoordinates(double& x, double& y, const SimpleImage& image) override {
        return true;
    }
};

