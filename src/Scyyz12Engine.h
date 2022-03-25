#pragma once
#include "header.h"
#include "BaseEngine.h"
#include "Scyyz12TileManager.h"

class Part1Object;
class Part1Object2;

class Scyyz12Engine :
    public BaseEngine
{
private:
    Part1Object* m_oBall;
    Part1Object2* m_oSquare;
    Scyyz12TileManager tm;

public:
    void virtSetupBackgroundBuffer() override;
    void virtDrawStringsOnTop() override;
    int virtInitialiseObjects() override;
    void virtMouseDown(int iButton, int iX, int iY) override;
};

