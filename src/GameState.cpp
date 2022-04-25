#include "header.h"
#include "GameState.h"
#include "ImagePixelMapping.h"

int GameState::virtInitialise(Scyyz12Engine2* pContext)
{
	return pContext->BaseEngine::virtInitialise();
}

void GameState::virtSetupBackgroundBuffer(Scyyz12Engine2* pContext)
{
	m_filterScaling = Scyyz12FilterPointsScaling(0, pContext);
	m_filterTranslation = Scyyz12FilterPointsTranslation(0, 0, &m_filterScaling);
	pContext->getForegroundSurface()->setDrawPointsFilter(&m_filterTranslation); // TODO: 增加拖拽移动的监听

	pContext->fillBackground(0xffffff);

	// Exit btn
	SimpleImage backArrow = ImageManager::loadImage("resources/arrow-right-50-50.png", true);
	ImagePixelMappingRotateAndColour mapping(0, backArrow.getWidth() / 2, backArrow.getHeight() / 2);
	mapping.setTransparencyColour(0xffffff);
	mapping.setRotation(M_PI);
	backArrow.renderImageApplyingMapping(pContext, pContext->getBackgroundSurface(), 30, 30, backArrow.getWidth(), backArrow.getHeight(), &mapping);

	// Selection area
	pContext->drawBackgroundRectangle(280, 710, 1020, 800, 0xeeeeee);
	pContext->drawBackgroundThickLine(280, 710, 1020, 710, 0xaaaaaa, 2);

	if (m_sa == nullptr) {
		m_sa = new SelectionArea({ 0x52B69A, 0xF9C74F, 0xF94144 ,0x4361EE ,0xF19C79 ,0x90BE6D }, 0xAAAAAA, true, true, true, true, false);
		m_sa->setProperty(-5, 5);
		m_sa->setProperty(-4, 3);
		m_sa->setProperty(-3, 1);
		m_sa->setProperty(-6, 7);
		m_sa->setProperty(-2, 10);
		m_sa->setProperty(-1, 8);

		m_sa->addNewLineState2Discovered();
		m_sa->addNewLineState2Discovered();
		m_sa->addNewLineState2Discovered();
		m_sa->addNewLineState2Discovered();
		m_sa->setLineState2Using(1);
		m_sa->setLineState2Using(2);
		m_sa->setLineState2Using(3);
		m_sa->setLineState2Discovered(1); // 0 discovered  1 discovered  2 using  3 using  4 undiscovered  5 undiscovered
	}
	m_sa->setTopLeftPositionOnScreen(300, 720);
	m_sa->drawAllTiles(pContext, pContext->getBackgroundSurface());
}

void GameState::virtDrawStringsOnTop(Scyyz12Engine2* pContext)
{
	pContext->drawForegroundString(650 - 450, 33, "Week 1", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
	pContext->drawForegroundString(650 - 330, 33, "Sun.", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
	pContext->drawForegroundRectangle(650 - 250, 48, 650 + 450, 52, 0xDDDDDD);
	pContext->drawForegroundRectangle(650 - 250, 40, 650 - 246, 60, 0x777777);
	pContext->drawForegroundRectangle(650 + 446, 40, 650 + 450, 60, 0x777777);
	int x = 400+ (++m_timeCount / 10)%697;
	pContext->drawForegroundRectangle(x, 40, x+4, 60, 0x000000);
	

	pContext->drawForegroundString(650 - 80, 600, "test pause", 0x777777, pContext->getFont("Ubuntu-Medium.ttf", 20));
	pContext->drawForegroundString(650 - 80, 650, "test game over", 0x777777, pContext->getFont("Ubuntu-Medium.ttf", 20));
}

int GameState::virtInitialiseObjects(Scyyz12Engine2* pContext)
{
	pContext->destroyOldObjects(true);

	if (m_sm == nullptr) {
		m_sm = new StationMap(pContext);
		m_sm->addStation(201, 0, 200, 100);
		m_sm->addStation(202, 1, 100, 200);
		m_sm->addStation(203, 2, 100, 400);
		m_sm->addStation(204, 3, 200, 500);
		m_sm->addStation(205, 4, 200, 600);
		m_sm->addStation(206, 5, 400, 600);
	}
	if (m_lr1 == nullptr) {
		m_lr1 = new LineRoute(pContext, 0x52B69A);
		m_lr1->iniAdd2Stations(m_sm->getStation(0), m_sm->getStation(1), false, 0, 50, 1);
		m_lr1->addStationTail(m_sm->getStation(2), false, 51);
		m_lr1->addStationTail(m_sm->getStation(3), false, 52);
		m_lr1->addStationTail(m_sm->getStation(4), false, 53);
		m_lr1->addStationTail(m_sm->getStation(5), false, 54);
		m_lr1->addTrain(300, 0, 100, 350);
		m_lr1->addTrain(350, 1, 100, 250);
		m_lr1->addTrain(350, 2, 200, 550);
		m_lr1->addCarriage(0);
		m_lr1->addCarriage(1);
		m_lr1->addCarriage(1);
		m_lr1->addCarriage(2);
	}

	m_lr1->drawInitialise();
	m_sm->drawInitialise();

	return 0;
}

void GameState::virtMouseDown(Scyyz12Engine2* pContext, int iButton, int iX, int iY)
{
	int iXClicked = pContext->convertVirtualPixelToClickedXPosition(iX), iYClicked = pContext->convertVirtualPixelToClickedYPosition(iY);
	printf("## Debug - click at %d %d (virtual), %d %d (to clicked)\n", iX, iY, iXClicked, iYClicked);
	if (iButton == SDL_BUTTON_LEFT) {
		if (iX > 550 && iX < 750) {
			if (iY > 590 && iY < 640) {
				pContext->changeState("pause");
			}
			else if (iY > 640 && iY < 690) {
				pContext->changeState("game_over");
			}
		}
		else if (iXClicked > 30 && iXClicked < 80) {
			if (iYClicked > 30 && iYClicked < 80) {
				pContext->changeState("start");
			}
		}
	}
	//else if (iButton == SDL_BUTTON_MIDDLE) {
	//	m_filterScaling.compress();
	//	pContext->redrawDisplay();
	//}
	//else if (iButton == SDL_BUTTON_RIGHT) {
	//	m_filterScaling.stretch();
	//	pContext->redrawDisplay();
	//}
}

void GameState::virtMouseWheel(Scyyz12Engine2* pContext, int x, int y, int which, int timestamp)
{
	int iOldCentreX = pContext->convertClickedToVirtualPixelXPosition(pContext->getWindowWidth() / 2);
	int iOldCentreY = pContext->convertClickedToVirtualPixelYPosition(pContext->getWindowHeight() / 2);

	if (y < 0) m_filterScaling.compress();
	else if (y > 0) m_filterScaling.stretch();

	int iNewCentreX = pContext->convertClickedToVirtualPixelXPosition(pContext->getWindowWidth() / 2);
	int iNewCentreY = pContext->convertClickedToVirtualPixelYPosition(pContext->getWindowHeight() / 2);

	m_filterTranslation.changeOffset(iNewCentreX - iOldCentreX, iNewCentreY - iOldCentreY);
	pContext->redrawDisplay();
}

void GameState::virtMainLoopDoBeforeUpdate(Scyyz12Engine2* pContext)
{
	m_lr1->update();
	m_sm->update();
}

void GameState::copyAllBackgroundBuffer(Scyyz12Engine2* pContext)
{
	pContext->BaseEngine::copyAllBackgroundBuffer();
}

void GameState::virtKeyDown(Scyyz12Engine2* pContext, int iKeyCode)
{
	switch (iKeyCode)
	{
	case SDLK_LEFT:
		m_filterTranslation.changeOffset(-20, 0);
		pContext->redrawDisplay();
		break;
	case SDLK_RIGHT:
		m_filterTranslation.changeOffset(20, 0);
		pContext->redrawDisplay();
		break;
	case SDLK_UP:
		m_filterTranslation.changeOffset(0, -20);
		pContext->redrawDisplay();
		break;
	case SDLK_DOWN:
		m_filterTranslation.changeOffset(0, 20);
		pContext->redrawDisplay();
		break;
	case SDLK_SPACE:
		m_filterTranslation.setOffset(0, 0);
		m_filterScaling.setStretch(0);
		pContext->redrawDisplay();
		break;
	}
}

void GameState::virtCreateSurfaces(Scyyz12Engine2* pContext)
{
	pContext->BaseEngine::virtCreateSurfaces();
}
