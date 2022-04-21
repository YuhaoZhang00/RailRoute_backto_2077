#pragma once
#include "header.h"
#include "State.h"

class StartState :
	public State
{
private:
	DrawingSurface* m_oTheExtraSurface1;
	DrawingSurface* m_oTheExtraSurface2;
	DrawingSurface* m_oTheExtraSurface3;
	DrawingSurface* m_oTheExtraSurface4;
	DrawingSurface* m_oTheExtraSurface5;
	int m_iCurrentSurfaceNumber;

public:
	StartState()
		: m_oTheExtraSurface1(nullptr), m_oTheExtraSurface2(nullptr), m_oTheExtraSurface3(nullptr),
		m_oTheExtraSurface4(nullptr), m_oTheExtraSurface5(nullptr), m_iCurrentSurfaceNumber(0)
	{}

	~StartState() {
		delete m_oTheExtraSurface1;
		delete m_oTheExtraSurface2;
		delete m_oTheExtraSurface3;
		delete m_oTheExtraSurface4;
		delete m_oTheExtraSurface5;
	}

	int virtInitialise(Scyyz12Engine2* pContext) override;
	void virtSetupBackgroundBuffer(Scyyz12Engine2* pContext) override;
	void virtDrawStringsOnTop(Scyyz12Engine2* pContext) override;
	int virtInitialiseObjects(Scyyz12Engine2* pContext) override;
	void virtMouseDown(Scyyz12Engine2* pContext, int iButton, int iX, int iY) override;
	void virtMouseWheel(Scyyz12Engine2* pContext, int x, int y, int which, int timestamp) override;
	void virtMainLoopDoBeforeUpdate(Scyyz12Engine2* pContext) override;
	void copyAllBackgroundBuffer(Scyyz12Engine2* pContext) override;
	void virtKeyDown(Scyyz12Engine2* pContext, int iKeyCode) override;
	void virtCreateSurfaces(Scyyz12Engine2* pContext) override;
};

