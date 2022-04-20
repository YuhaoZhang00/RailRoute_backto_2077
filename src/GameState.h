#pragma once
#include "header.h"
#include "State.h"
#include "SelectionArea.h"
#include "Scyyz12FilterPoints.h"

class GameState :
	public State
{
private:
	SelectionArea* m_tSelectionArea;

	Scyyz12FilterPointsScaling m_filterScaling;
	Scyyz12FilterPointsTranslation m_filterTranslation;

public:
	GameState()
		: m_tSelectionArea(nullptr), m_filterScaling(0, nullptr), m_filterTranslation(0, 0, nullptr)
	{}

	~GameState() {
		delete m_tSelectionArea;
	}

	int virtInitialise(Scyyz12Engine2* pContext) override;
	void virtSetupBackgroundBuffer(Scyyz12Engine2* pContext) override;
	void virtDrawStringsOnTop(Scyyz12Engine2* pContext) override;
	int virtInitialiseObjects(Scyyz12Engine2* pContext) override;
	void virtMouseDown(Scyyz12Engine2* pContext, int iButton, int iX, int iY) override;
	void virtMainLoopDoBeforeUpdate(Scyyz12Engine2* pContext) override;
	void copyAllBackgroundBuffer(Scyyz12Engine2* pContext) override;
	void virtKeyDown(Scyyz12Engine2* pContext, int iKeyCode) override;
};

