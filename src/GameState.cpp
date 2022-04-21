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
	pContext->getForegroundSurface()->setDrawPointsFilter(&m_filterTranslation);

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

	if (m_tSelectionArea == nullptr) {
		m_tSelectionArea = new SelectionArea({ 0x52B69A, 0xF9C74F, 0xF94144 ,0x4361EE ,0xF19C79 ,0x90BE6D }, 0xAAAAAA, true, true, true, true, false);
		m_tSelectionArea->setProperty(-5, 5);
		m_tSelectionArea->setProperty(-4, 3);
		m_tSelectionArea->setProperty(-3, 1);
		m_tSelectionArea->setProperty(-6, 7);
		m_tSelectionArea->setProperty(-2, 10);
		m_tSelectionArea->setProperty(-1, 8);

		m_tSelectionArea->addNewLineState2Discovered();
		m_tSelectionArea->addNewLineState2Discovered();
		m_tSelectionArea->addNewLineState2Discovered();
		m_tSelectionArea->addNewLineState2Discovered();
		m_tSelectionArea->setLineState2Using(1);
		m_tSelectionArea->setLineState2Using(2);
		m_tSelectionArea->setLineState2Using(3);
		m_tSelectionArea->setLineState2Discovered(1); // 0 discovered  1 discovered  2 using  3 using  4 undiscovered  5 undiscovered
	}
	m_tSelectionArea->setTopLeftPositionOnScreen(300, 720);
	m_tSelectionArea->drawAllTiles(pContext, pContext->getBackgroundSurface());
}

void GameState::virtDrawStringsOnTop(Scyyz12Engine2* pContext)
{
	char buf[128];
	sprintf(buf, "Time %6d", rand());
	pContext->drawForegroundString(150, 40, buf, 0xff00ff, NULL);

	pContext->drawForegroundString(650 - 40, 100, "game", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 40));

	pContext->drawForegroundString(650 - 80, 600, "test pause", 0x777777, pContext->getFont("Ubuntu-Medium.ttf", 20));
	pContext->drawForegroundString(650 - 80, 650, "test game over", 0x777777, pContext->getFont("Ubuntu-Medium.ttf", 20));
}

int GameState::virtInitialiseObjects(Scyyz12Engine2* pContext)
{
	return 0;
}

void GameState::virtMouseDown(Scyyz12Engine2* pContext, int iButton, int iX, int iY)
{
	printf("## Debug - click at %d %d\n", iX, iY);
	if (iButton == SDL_BUTTON_LEFT) {
		if (iX > 550 && iX < 750) {
			if (iY > 590 && iY < 640) {
				pContext->changeState("pause");
			}
			else if (iY > 640 && iY < 690) {
				pContext->changeState("game_over");
			}
		}
		else if (iX > 30 && iX < 80) {
			if (iY > 30 && iY < 80) {
				pContext->changeState("start");
			}
		}
	}
	else if (iButton == SDL_BUTTON_MIDDLE) { // TODO: 修改鼠标缩放的监听，增加滚轮的监听，增加键盘移动的监听，增加拖拽移动的监听（参考ZoomingDemo.cpp）
		m_filterScaling.compress();
		pContext->redrawDisplay();
	}
	else if (iButton == SDL_BUTTON_RIGHT) {
		m_filterScaling.stretch();
		pContext->redrawDisplay();
	}
}

void GameState::virtMainLoopDoBeforeUpdate(Scyyz12Engine2* pContext)
{
	pContext->BaseEngine::virtMainLoopDoBeforeUpdate();
}

void GameState::copyAllBackgroundBuffer(Scyyz12Engine2* pContext)
{
	pContext->BaseEngine::copyAllBackgroundBuffer();
}

void GameState::virtKeyDown(Scyyz12Engine2* pContext, int iKeyCode)
{
	pContext->BaseEngine::virtKeyDown(iKeyCode);
}
