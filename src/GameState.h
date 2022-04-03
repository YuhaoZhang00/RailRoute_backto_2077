#pragma once
#include "header.h"
#include "State.h"
#include "SelectionArea.h"

class GameState :
	public State
{
private:
	SelectionArea* m_tSelectionArea;

public:
	void virtSetupBackgroundBuffer(Scyyz12Engine2* pContext) override;
	void virtDrawStringsOnTop(Scyyz12Engine2* pContext) override;
	int virtInitialiseObjects(Scyyz12Engine2* pContext) override;
	void virtMouseDown(Scyyz12Engine2* pContext, int iButton, int iX, int iY) override;
};

