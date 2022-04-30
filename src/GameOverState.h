#pragma once
#include "header.h"
#include "State.h"

class GameOverState :
    public State
{
private:
	std::string m_strUserName = "<Name>";
	int m_iLevel = 5;
	int m_iNumOfDays = 100;
	int m_iNumOfPassengers = 45;

	void updateHighest10Scores();
	void inputUserName(int iKeyCode);
	void deleteUserName();

public:
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

	void virtSetSelfDefinedValue(int i, int j) override;
};

