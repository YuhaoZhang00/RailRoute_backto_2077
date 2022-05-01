#include "header.h"
#include "InstructionState.h"

int InstructionState::virtInitialise(Scyyz12Engine2* pContext)
{
	return pContext->BaseEngine::virtInitialise();
}

void InstructionState::virtSetupBackgroundBuffer(Scyyz12Engine2* pContext)
{
	pContext->getForegroundSurface()->setDrawPointsFilter(pContext);

	pContext->fillBackground(0xffffff);

	pContext->drawBackgroundThickLine(0, 200, 200, 0, 0xF9C74F, 10);

	pContext->drawBackgroundString(650 - 28, 640, "Idea from: Mini Metro by Dinosaur Polo Club", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 20));

	// Exit btn
	pContext->drawBackgroundRectangle(550, 680, 750, 730, 0xF94144);
	pContext->drawBackgroundString(650 - 28, 685, "Exit", 0xFFFFFF, pContext->getFont("Ubuntu-Medium.ttf", 30));
}

void InstructionState::virtDrawStringsOnTop(Scyyz12Engine2* pContext)
{
	pContext->BaseEngine::virtDrawStringsOnTop();
}

int InstructionState::virtInitialiseObjects(Scyyz12Engine2* pContext)
{
	pContext->destroyOldObjects(true);

	if (m_sm1 == nullptr) {
		m_sm1 = new StationMap(pContext);
		m_sm1->addStation(200, 1, 300, 100);
		m_sm1->addStation(201, 2, 100, 100);
		m_sm1->addStation(202, 0, 100, 200);
		m_sm1->addStation(203, 3, 100, 400);
		m_sm1->addStation(204, 4, 200, 600);
		m_sm1->addStation(205, 3, 300, 700);
		m_sm1->addStation(206, 5, 100, 600);
	}
	if (m_lr1 == nullptr) {
		m_lr1 = new LineRoute(pContext, 0x52B69A);
		m_lr1->iniAdd2Stations(m_sm1->getStation(2), m_sm1->getStation(3), false, 100, 50, 101);
		m_lr1->addStationTail(m_sm1->getStation(4), false, 51);
		m_lr1->addStationTail(m_sm1->getStation(5), false, 52);
		m_lr1->addStationHead(m_sm1->getStation(1), false, 53);
		m_lr1->addStationHead(m_sm1->getStation(0), false, 54);
		m_lr1->addStation(3, m_sm1->getStation(6), false, false, 55);
		m_lr1->addTrain(300, 0, 100, 500);
		m_lr1->addTrain(350, 1, 100, 300);
	}

	m_lr1->drawInitialise();
	m_sm1->drawInitialise();

	return 0;
}

void InstructionState::virtMouseMoved(Scyyz12Engine2* pContext, int iX, int iY)
{
	pContext->BaseEngine::virtMouseMoved(iX, iY);
}

void InstructionState::virtMouseDown(Scyyz12Engine2* pContext, int iButton, int iX, int iY)
{
	printf("## Debug - click at %d %d\n", iX, iY);
	if (iButton == SDL_BUTTON_LEFT)
	{
		if (iX > 550 && iX < 750) {
			if (iY > 680 && iY < 730) {
				pContext->changeState("start");
			}
		}
	}
}

void InstructionState::virtMouseWheel(Scyyz12Engine2* pContext, int x, int y, int which, int timestamp)
{
	pContext->BaseEngine::virtMouseWheel(x, y, which, timestamp);
}

void InstructionState::virtMainLoopDoBeforeUpdate(Scyyz12Engine2* pContext)
{
	//m_lr1->update(NULL);
	m_sm1->update();
}

void InstructionState::copyAllBackgroundBuffer(Scyyz12Engine2* pContext)
{
	pContext->BaseEngine::copyAllBackgroundBuffer();
}

void InstructionState::virtKeyDown(Scyyz12Engine2* pContext, int iKeyCode)
{
	pContext->BaseEngine::virtKeyDown(iKeyCode);
}

void InstructionState::virtCreateSurfaces(Scyyz12Engine2* pContext)
{
	pContext->BaseEngine::virtCreateSurfaces();
}
