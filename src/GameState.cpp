#include "header.h"
#include "GameState.h"
#include "ImagePixelMapping.h"

void GameState::virtSetupBackgroundBuffer(Scyyz12Engine2* pContext)
{
	pContext->fillBackground(0xffffff);

	pContext->drawBackgroundString(650 - 40, 100, "game", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 40));

	SimpleImage backArrow = ImageManager::loadImage("resources/arrow-right-50-50.png", true);
	ImagePixelMappingRotateAndColour mapping(0, backArrow.getWidth() / 2, backArrow.getHeight() / 2);
	mapping.setTransparencyColour(0xffffff);
	mapping.setRotation(M_PI);
	backArrow.renderImageApplyingMapping(pContext, pContext->getBackgroundSurface(), 30, 30, backArrow.getWidth(), backArrow.getHeight(), &mapping);

	pContext->drawBackgroundString(650 - 80, 640, "test pause", 0x777777, pContext->getFont("Ubuntu-Medium.ttf", 20));
	pContext->drawBackgroundString(650 - 80, 690, "test game over", 0x777777, pContext->getFont("Ubuntu-Medium.ttf", 20));
}

void GameState::virtDrawStringsOnTop(Scyyz12Engine2* pContext)
{
	pContext->BaseEngine::virtDrawStringsOnTop();
}

int GameState::virtInitialiseObjects(Scyyz12Engine2* pContext)
{
	return pContext->BaseEngine::virtInitialiseObjects();
}

void GameState::virtMouseDown(Scyyz12Engine2* pContext, int iButton, int iX, int iY)
{
	printf("## Debug - click at %d %d\n", iX, iY);
	if (iButton == SDL_BUTTON_LEFT)
	{
		if (iX > 550 && iX < 750) {
			if (iY > 630 && iY < 680) {
				pContext->changeState("pause");
			}
			else if (iY > 680 && iY < 730) {
				pContext->changeState("game_over");
			}
		}
		else if (iX > 30 && iX < 80) {
			if (iY > 30 && iY < 80) {
				pContext->changeState("start");
			}
		}
	}
}
