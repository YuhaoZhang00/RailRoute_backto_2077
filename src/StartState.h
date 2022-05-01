#pragma once
#include "header.h"
#include "State.h"

class StartState :
	public State
{
private:
	DrawingSurface* m_oTheExtraSurface11;
	DrawingSurface* m_oTheExtraSurface12;
	DrawingSurface* m_oTheExtraSurface13;
	DrawingSurface* m_oTheExtraSurface21;
	DrawingSurface* m_oTheExtraSurface22;
	DrawingSurface* m_oTheExtraSurface23;
	DrawingSurface* m_oTheExtraSurface31;
	DrawingSurface* m_oTheExtraSurface32;
	DrawingSurface* m_oTheExtraSurface33;
	int m_iCurrentSurfaceNumber;
	bool m_bIsContinue = false;

public:
	StartState()
		: m_oTheExtraSurface11(nullptr), m_oTheExtraSurface12(nullptr), m_oTheExtraSurface13(nullptr),
		m_oTheExtraSurface21(nullptr), m_oTheExtraSurface22(nullptr), m_oTheExtraSurface23(nullptr),
		m_oTheExtraSurface31(nullptr), m_oTheExtraSurface32(nullptr), m_oTheExtraSurface33(nullptr), 
		m_iCurrentSurfaceNumber(0)
	{}

	~StartState() {
		delete m_oTheExtraSurface11;
		delete m_oTheExtraSurface12;
		delete m_oTheExtraSurface13;
		delete m_oTheExtraSurface21;
		delete m_oTheExtraSurface22;
		delete m_oTheExtraSurface23;
		delete m_oTheExtraSurface31;
		delete m_oTheExtraSurface32;
		delete m_oTheExtraSurface33;
	}

	int virtInitialise(Scyyz12Engine2* pContext) override;
	void virtSetupBackgroundBuffer(Scyyz12Engine2* pContext) override;
	void virtDrawStringsOnTop(Scyyz12Engine2* pContext) override;
	int virtInitialiseObjects(Scyyz12Engine2* pContext) override;
	void virtMouseMoved(Scyyz12Engine2* pContext, int iX, int iY) override;
	void virtMouseDown(Scyyz12Engine2* pContext, int iButton, int iX, int iY) override;
	void virtMouseWheel(Scyyz12Engine2* pContext, int x, int y, int which, int timestamp) override;
	void virtMainLoopDoBeforeUpdate(Scyyz12Engine2* pContext) override;
	void copyAllBackgroundBuffer(Scyyz12Engine2* pContext) override;
	void virtKeyDown(Scyyz12Engine2* pContext, int iKeyCode) override;
	void virtCreateSurfaces(Scyyz12Engine2* pContext) override;
};

