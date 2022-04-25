#pragma once
#include "header.h"
#include "State.h"
#include "SelectionArea.h"
#include "StationMap.h"
#include "LineRoute.h"
#include "Scyyz12FilterPoints.h"

class GameState :
	public State
{
private:
	SelectionArea* m_sa;

	Scyyz12FilterPointsScaling m_filterScaling;
	Scyyz12FilterPointsTranslation m_filterTranslation;

	StationMap* m_sm;

	LineRoute* m_lr1;

	int m_timeCount = 0;

public:
	GameState()
		: m_sa(nullptr), m_filterScaling(0, nullptr), m_filterTranslation(0, 0, nullptr),
		m_sm(nullptr), m_lr1(nullptr)
	{}

	~GameState() {
		delete m_sa;
		delete m_sm;
		delete m_lr1;
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

