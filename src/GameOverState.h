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
	void virtSetupBackgroundBuffer(Scyyz12Engine2* pContext) override;
	void virtDrawStringsOnTop(Scyyz12Engine2* pContext) override;
	int virtInitialiseObjects(Scyyz12Engine2* pContext) override;
	void virtMouseDown(Scyyz12Engine2* pContext, int iButton, int iX, int iY) override;
	void virtMainLoopDoBeforeUpdate(Scyyz12Engine2* pContext) override;
	void copyAllBackgroundBuffer(Scyyz12Engine2* pContext) override;
	void virtKeyDown(Scyyz12Engine2* pContext, int iKeyCode) override;
};

