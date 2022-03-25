#pragma once
#include "header.h"
#include "DisplayableObject.h"
#include "TileManager.h"

class Part1Object :
    public DisplayableObject
{
private:
    double m_dSpeedX;
    double m_dSpeedY;
    TileManager* m_pTileManager;
    int m_iLastUpdatedTime;

public:
    Part1Object(BaseEngine* pEngine, TileManager* pTileManager, int iSize = 50,
        int iX = 50, int iY = 50, double dSpeedX = 0, double dSpeedY = 0)
        : DisplayableObject(iX, iY, pEngine, iSize, iSize, false),
        m_dSpeedX(dSpeedX), m_dSpeedY(dSpeedY), m_pTileManager(pTileManager), m_iLastUpdatedTime(0)
    {
    }

    void virtDraw() override;
    void virtDoUpdate(int iCurrentTime) override;
    void setPosition(int x, int y) override;
    double getSpeedX();
    double getSpeedY();
};

class Part1Object2 :
    public DisplayableObject
{
private:
    bool m_bDirection; // true: x; false: y
    double m_dSpeed;
    int m_iCounter;

public:
    Part1Object2(BaseEngine* pEngine, int iSize = 50,
        int iX = 500, int iY = 500, double dSpeed = 2, bool bDirection = true)
        : DisplayableObject(iX, iY, pEngine, iSize, iSize, false), m_dSpeed(dSpeed), m_bDirection(bDirection), m_iCounter(0)
    {
    }

    void virtDraw() override;
    void virtDoUpdate(int iCurrentTime) override;
    bool getDirection();
};