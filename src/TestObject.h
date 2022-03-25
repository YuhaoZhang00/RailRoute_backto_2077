#pragma once
#include "header.h"
#include "DisplayableObject.h"
class TestObject :
    public DisplayableObject
{
private:
    bool m_bDirection; // true: x; false: y
    double m_dSpeed;
    int m_iCounter;

public:
    TestObject(BaseEngine* pEngine, int iSize = 50,
        int iX = 500, int iY = 500, double dSpeed = 2, bool bDirection = true)
        : DisplayableObject(iX, iY, pEngine, iSize, iSize, false), m_dSpeed(dSpeed), m_bDirection(bDirection), m_iCounter(0)
    {
    }

    void virtDraw() override;
    void virtDoUpdate(int iCurrentTime) override;
    bool getDirection();
};

