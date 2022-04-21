#pragma once
#include "header.h"
#include "Scyyz12Engine2.h"

class Scyyz12Engine2;

class State
{
public:
    virtual ~State() {}

    virtual int virtInitialise(Scyyz12Engine2* pContext) = 0;
    virtual void virtSetupBackgroundBuffer(Scyyz12Engine2* pContext) = 0;
    virtual void virtDrawStringsOnTop(Scyyz12Engine2* pContext) = 0;
    virtual int virtInitialiseObjects(Scyyz12Engine2* pContext) = 0;
    virtual void virtMouseDown(Scyyz12Engine2* pContext, int iButton, int iX, int iY) = 0;
    virtual void virtMouseWheel(Scyyz12Engine2* pContext, int x, int y, int which, int timestamp) = 0;
    virtual void virtMainLoopDoBeforeUpdate(Scyyz12Engine2* pContext) = 0;
    virtual void copyAllBackgroundBuffer(Scyyz12Engine2* pContext) = 0;
    virtual void virtKeyDown(Scyyz12Engine2* pContext, int iKeyCode)  = 0;
    virtual void virtCreateSurfaces(Scyyz12Engine2* pContext) = 0;
};

