#include "header.h"
#include "Scyyz12Engine2.h"

State* Scyyz12Engine2::getState()
{
	return m_pState;
}

void Scyyz12Engine2::changeState(std::string strState)
{
	try {
		m_pState = m_mAllState.at(strState);
		printf("## Debug - state changed to %s\n", strState.c_str());
	}
	catch (std::out_of_range) {
		printf("!! Error @ Scyyz12Engine2.cpp changeState() - state not found\n");
		m_pState = m_mAllState.at("start");
	}
	redrawDisplay();
	lockAndSetupBackground();
	virtInitialiseObjects();
}


int Scyyz12Engine2::virtInitialise()
{
	return m_pState->virtInitialise(this);
}

void Scyyz12Engine2::virtSetupBackgroundBuffer()
{
	m_pState->virtSetupBackgroundBuffer(this);
}

void Scyyz12Engine2::virtDrawStringsOnTop()
{
	m_pState->virtDrawStringsOnTop(this);
}

int Scyyz12Engine2::virtInitialiseObjects()
{
	return m_pState->virtInitialiseObjects(this);
}

void Scyyz12Engine2::virtMouseDown(int iButton, int iX, int iY)
{
	m_pState->virtMouseDown(this, iButton, iX, iY);
}

void Scyyz12Engine2::virtMouseWheel(int x, int y, int which, int timestamp)
{
	m_pState->virtMouseWheel(this, x, y, which, timestamp);
}

void Scyyz12Engine2::virtMainLoopDoBeforeUpdate()
{
	m_pState->virtMainLoopDoBeforeUpdate(this);
}

void Scyyz12Engine2::copyAllBackgroundBuffer()
{
	m_pState->copyAllBackgroundBuffer(this);
}

void Scyyz12Engine2::virtKeyDown(int iKeyCode)
{
	m_pState->virtKeyDown(this, iKeyCode);
}
