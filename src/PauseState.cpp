#include "PauseState.h"

int PauseState::virtInitialise(Scyyz12Engine2* pContext)
{
	m_iRnd = rand() % 4;
	return pContext->BaseEngine::virtInitialise();
}

void PauseState::virtSetupBackgroundBuffer(Scyyz12Engine2* pContext)
{
	pContext->getForegroundSurface()->setDrawPointsFilter(pContext);

	pContext->fillBackground(0xffffff);

	pContext->drawBackgroundRectangle(650 - 55, 70, 650 + 55, 75, 0xF94144);
	pContext->drawBackgroundString(650 - 54, 30, "Pause", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 40));

	pContext->drawBackgroundString(130, 270, "Tips / Interesting facts", 0x777777, pContext->getFont("Ubuntu-Medium.ttf", 30));

	switch (m_iRnd)
	{
	case 0:
		pContext->drawBackgroundString(130, 370, "> Try to make each line connect all types of stations.", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
		break;
	case 1:
		pContext->drawBackgroundString(130, 370, "> Most passengers are smart enough to reach the nearest station, ", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
		pContext->drawBackgroundString(130, 410, "   but there are some ......", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
		break;
	case 2:
		pContext->drawBackgroundString(130, 370, "> If you want a shorter headway, add more trains; if you want more", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
		pContext->drawBackgroundString(130, 410, "   capacity, add more carriages.", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
		break;
	case 3:
		pContext->drawBackgroundString(130, 370, "> Please plan your route across the river carefully, ", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
		pContext->drawBackgroundString(130, 410, "   bridges are very valuable.", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
		break;
	default:
		break;
	}

	// Exit btn
	pContext->drawBackgroundRectangle(550, 680, 750, 730, 0xF94144);
	pContext->drawBackgroundString(650 - 32, 685, "Back", 0xFFFFFF, pContext->getFont("Ubuntu-Medium.ttf", 30));
}

void PauseState::virtDrawStringsOnTop(Scyyz12Engine2* pContext)
{
}

int PauseState::virtInitialiseObjects(Scyyz12Engine2* pContext)
{
	return pContext->BaseEngine::virtInitialiseObjects();
}

void PauseState::virtMouseMoved(Scyyz12Engine2* pContext, int iX, int iY)
{
	pContext->BaseEngine::virtMouseMoved(iX, iY);
}

void PauseState::virtMouseDown(Scyyz12Engine2* pContext, int iButton, int iX, int iY)
{
	printf("## Debug - click at %d %d\n", iX, iY);
	if (iButton == SDL_BUTTON_LEFT)
	{
		if (iX > 550 && iX < 750) {
			if (iY > 680 && iY < 730) {
				pContext->changeState("gaming", false, false, m_iLevelId);
			}
		}
	}
}

void PauseState::virtMouseWheel(Scyyz12Engine2* pContext, int x, int y, int which, int timestamp)
{
	pContext->BaseEngine::virtMouseWheel(x, y, which, timestamp);
}

void PauseState::virtMainLoopDoBeforeUpdate(Scyyz12Engine2* pContext)
{
	pContext->BaseEngine::virtMainLoopDoBeforeUpdate();
}

void PauseState::copyAllBackgroundBuffer(Scyyz12Engine2* pContext)
{
	pContext->BaseEngine::copyAllBackgroundBuffer();
}

void PauseState::virtKeyDown(Scyyz12Engine2* pContext, int iKeyCode)
{
	pContext->BaseEngine::virtKeyDown(iKeyCode);
}

void PauseState::virtCreateSurfaces(Scyyz12Engine2* pContext)
{
	pContext->BaseEngine::virtCreateSurfaces();
}
