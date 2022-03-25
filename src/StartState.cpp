#include "header.h"
#include "StartState.h"
#include "ImagePixelMapping.h"

void StartState::virtSetupBackgroundBuffer(Scyyz12Engine2* pContext)
{
	// background
	//pContext->fillBackground(0xffffff);
	SimpleImage image = ImageManager::loadImage("resources/bg-route-1300-800.png", true);
	ImagePixelMappingRotateAndColour mapping(0, image.getWidth() / 2, image.getHeight() / 2);
	mapping.setNthPixelColours(0xffffff);
	image.renderImageApplyingMapping(pContext, pContext->getBackgroundSurface(), 0, 0, image.getWidth(), image.getHeight(), &mapping);


	SimpleImage image2 = ImageManager::loadImage("resources/arrow-ini-50-50.png", true);
	ImagePixelMappingRotateAndColour mapping2(0, image2.getWidth() / 2, image2.getHeight() / 2);
	mapping2.setTransparencyColour(0xffffff);
	image2.renderImageApplyingMapping(pContext, pContext->getBackgroundSurface(), 480, 400, image2.getWidth(), image2.getHeight(), &mapping2);

	mapping2.setRotation(M_PI / 4);
	image2.renderImageApplyingMapping(pContext, pContext->getBackgroundSurface(), 480, 470, image2.getWidth(), image2.getHeight(), &mapping2);

	mapping2.setRotation(M_PI * 7 / 4);
	image2.renderImageApplyingMapping(pContext, pContext->getBackgroundSurface(), 480, 540, image2.getWidth(), image2.getHeight(), &mapping2);

	mapping2.setRotation(M_PI);
	image2.renderImageApplyingMapping(pContext, pContext->getBackgroundSurface(), 480, 610, image2.getWidth(), image2.getHeight(), &mapping2);

	// title (should be an image later)
	pContext->drawBackgroundString(650 - 210, 200, "RailRoute <- 2077", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 55));

	// Play btn
	pContext->drawBackgroundRectangle(550, 400, 750, 450, 0xF94144);
	pContext->drawBackgroundString(650 - 30, 405, "Play", 0xFFFFFF, pContext->getFont("Ubuntu-Medium.ttf", 30));

	// Continue btn
	pContext->drawBackgroundRectangle(550, 470, 750, 520, 0xF9C74F);
	pContext->drawBackgroundString(650 - 65, 475, "Continue", 0xFFFFFF, pContext->getFont("Ubuntu-Medium.ttf", 30));

	// High Score btn
	pContext->drawBackgroundRectangle(550, 540, 750, 590, 0x4361EE);
	pContext->drawBackgroundString(650 - 75, 545, "High Score", 0xFFFFFF, pContext->getFont("Ubuntu-Medium.ttf", 30));

	// Exit btn
	pContext->drawBackgroundRectangle(550, 610, 750, 660, 0x52B69A);
	pContext->drawBackgroundString(650 - 28, 615, "Exit", 0xFFFFFF, pContext->getFont("Ubuntu-Medium.ttf", 30));
}

void StartState::virtDrawStringsOnTop(Scyyz12Engine2* pContext)
{
	//char buf[128];
	//sprintf(buf, "Incrememt per 1000 ticks: %d (foreground & before moving object)", pContext->getModifiedTime() / 1000);
	//pContext->drawForegroundString(50, 600, buf, 0xffffff, pContext->getFont("Cornerstone Regular.ttf", 28));
	pContext->BaseEngine::virtDrawStringsOnTop();
}

int StartState::virtInitialiseObjects(Scyyz12Engine2* pContext)
{
	return pContext->BaseEngine::virtInitialiseObjects();
}

void StartState::virtMouseDown(Scyyz12Engine2* pContext, int iButton, int iX, int iY)
{
	printf("## Debug - click at %d %d\n", iX, iY);
	if (iButton == SDL_BUTTON_LEFT)
	{
		if (iX > 550 && iX < 750) {
			if (iY > 400 && iY < 450) {
				//pContext->changeState("high_score");
			}
			else if (iY > 470 && iY < 520) {
				//pContext->changeState("high_score");
			}
			else if (iY > 540 && iY < 590) {
				pContext->changeState("high_score");
			}
			else if (iY > 610 && iY < 660) {
				pContext->setExitWithCode(0);
			}
		}
	}
}
