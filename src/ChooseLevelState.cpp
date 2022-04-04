#include "header.h"
#include "ChooseLevelState.h"
#include "ImagePixelMapping.h"

void ChooseLevelState::virtSetupBackgroundBuffer(Scyyz12Engine2* pContext)
{
	// Backgournd (Sea)
	pContext->fillBackground(0xffffff);
	SimpleImage sea = ImageManager::loadImage("resources/sea.png", true);
	//map.renderImage(pContext->getBackgroundSurface(), 0, 0, -90, 115, map.getWidth(), map.getHeight());
	sea.renderImageWithMaskAndTransparency(pContext->getBackgroundSurface(), 0, 0, 0, 90, 1300, 680, 0xffffff, 30);
}

void ChooseLevelState::virtDrawStringsOnTop(Scyyz12Engine2* pContext)
{
	// Map
	SimpleImage map = ImageManager::loadImage("resources/map_2-1457-650.png", true);
	//map.renderImage(pContext->getForegroundSurface(), 0, 0, -90, 115, map.getWidth(), map.getHeight());
	map.renderImageWithMaskAndTransparency(pContext->getForegroundSurface(), 0, 0, -90, 105, map.getWidth(), map.getHeight(), 0xffffff, 90);
	//map.renderImageWithMaskAndTransparency(pContext->getBackgroundSurface(), 0, 0, -80, 115, map.getWidth(), map.getHeight(), 0xffffff, 90);
	//map.renderImageBlit(pContext, pContext->getBackgroundSurface(), 0, 0, 1331, 800, 0, 0, map.getWidth(), map.getHeight());

	// Title
	// TODO: the recrangle is for justifying position of string, please delete in release, or use a better / more beautiful way
	pContext->drawForegroundRectangle(650 - 115, 70, 650 + 115, 75, 0xF94144);
	pContext->drawForegroundString(650 - 115, 30, "Select a City", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 40));

	// Exit btn
	SimpleImage backArrow = ImageManager::loadImage("resources/arrow-right-50-50.png", true);
	ImagePixelMappingRotateAndColour mapping(0, backArrow.getWidth() / 2, backArrow.getHeight() / 2);
	mapping.setTransparencyColour(0xffffff);
	mapping.setRotation(M_PI);
	backArrow.renderImageApplyingMapping(pContext, pContext->getForegroundSurface(), 30, 30, backArrow.getWidth(), backArrow.getHeight(), &mapping);

	// Levels
	pContext->drawForegroundOval(585, 195, 625, 235, 0xF94144);
	pContext->drawForegroundString(520, 240, "Level 1 - London, UK", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 20));

	pContext->drawForegroundOval(1135, 258, 1175, 298, 0xF9C74F);
	pContext->drawForegroundString(1040, 230, "Level 2 - Tokyo, Japan", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 20));

	pContext->drawForegroundOval(1065, 300, 1105, 340, 0x52B69A);
	pContext->drawForegroundString(960, 345, "Level 3 - Shanghai, China", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 20));

	pContext->drawForegroundOval(415, 325, 455, 365, 0x4361EE);
	pContext->drawForegroundString(320, 370, "Level 4 - Under the Atlantic", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 20));
}

int ChooseLevelState::virtInitialiseObjects(Scyyz12Engine2* pContext)
{
	return pContext->BaseEngine::virtInitialiseObjects();
}

void ChooseLevelState::virtMouseDown(Scyyz12Engine2* pContext, int iButton, int iX, int iY)
{
	printf("## Debug - click at %d %d\n", iX, iY);
	if (iButton == SDL_BUTTON_LEFT)
	{
		if (iX > 30 && iX < 80) {
			if (iY > 30 && iY < 80) {
				pContext->changeState("start");
			}
		}
	}
}

void ChooseLevelState::virtMainLoopDoBeforeUpdate(Scyyz12Engine2* pContext)
{
	m_iOffset = (m_iOffset + 1) % 60;
	pContext->redrawDisplay();
	//pContext->lockBackgroundForDrawing();
	//virtSetupBackgroundBuffer(pContext);
	//pContext->unlockBackgroundForDrawing();
}

void ChooseLevelState::copyAllBackgroundBuffer(Scyyz12Engine2* pContext)
{
	// left half
	pContext->getForegroundSurface()->copyRectangleFrom(pContext->getBackgroundSurface(),
		0, 0, pContext->getWindowWidth(), pContext->getWindowHeight(),
		m_iOffset / 3, 0);
	// right half
	pContext->getForegroundSurface()->copyRectangleFrom(pContext->getBackgroundSurface(),
		pContext->getWindowWidth() - m_iOffset / 3, 0, pContext->getWindowWidth(),
		pContext->getWindowHeight(), m_iOffset / 3 - pContext->getWindowWidth(), 0);
}
