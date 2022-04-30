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
	virtInitialise();
}

void Scyyz12Engine2::changeState(std::string strState, int iTemp1, int iTemp2)
{
	try {
		m_pState = m_mAllState.at(strState);
		m_pState->virtSetSelfDefinedValue(iTemp1, iTemp2);
		printf("## Debug - state changed to %s\n", strState.c_str());
	}
	catch (std::out_of_range) {
		printf("!! Error @ Scyyz12Engine2.cpp changeState() - state not found\n");
		m_pState = m_mAllState.at("start");
	}
	redrawDisplay();
	virtInitialise();
}

void Scyyz12Engine2::changeState(std::string strState, bool bTemp1, bool bTemp2, int iTemp1)
{
	try {
		m_pState = m_mAllState.at(strState);
		m_pState->virtSetSelfDefinedValue(bTemp1, bTemp2, iTemp1);
		printf("## Debug - state changed to %s\n", strState.c_str());
	}
	catch (std::out_of_range) {
		printf("!! Error @ Scyyz12Engine2.cpp changeState() - state not found\n");
		m_pState = m_mAllState.at("start");
	}
	redrawDisplay();
	virtInitialise();
}

void Scyyz12Engine2::setBackgourndSurface(DrawingSurface* pBackgroundSurface)
{
	m_pBackgroundSurface = pBackgroundSurface;
}

DrawingSurface& Scyyz12Engine2::getTheDefaultBackgroundSurface()
{
	return m_oTheBackgroundSurface;
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

void Scyyz12Engine2::virtCreateSurfaces()
{
	m_pState->virtCreateSurfaces(this);
}

void Scyyz12Engine2::virtMouseMoved(int iX, int iY)
{
	m_pState->virtMouseMoved(this, iX, iY);
}
