#pragma once
#include "header.h"
#include "State.h"
#include "TestObject.h"

class HighScoreState :
    public State
{
private:
	//TestObject* m_oBall;

public:
	//HighScoreState() :
	//	m_oBall(NULL)
	//{}

	void virtSetupBackgroundBuffer(Scyyz12Engine2* pContext) override;
	void virtDrawStringsOnTop(Scyyz12Engine2* pContext) override;
	int virtInitialiseObjects(Scyyz12Engine2* pContext) override;
	void virtMouseDown(Scyyz12Engine2* pContext, int iButton, int iX, int iY) override;
};

