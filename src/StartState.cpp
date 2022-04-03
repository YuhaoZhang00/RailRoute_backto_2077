#include "header.h"
#include "StartState.h"
#include "ImagePixelMapping.h"

void StartState::virtSetupBackgroundBuffer(Scyyz12Engine2* pContext)
{
	// background
	pContext->fillBackground(0xffffff);
	SimpleImage background = ImageManager::loadImage("resources/bg-route-1300-800.png", true);
	background.renderImageWithMaskAndTransparency(pContext->getBackgroundSurface(), 0, 0, 0, 0, background.getWidth(), background.getHeight(), 0xffffff, 30);


	// title
	SimpleImage title = ImageManager::loadImage("resources/title-ver1-800-235.png", true);
	title.renderImageWithMaskAndTransparency(pContext->getBackgroundSurface(), 0, 0, 250, 80, title.getWidth(), title.getHeight(), 0xffffff, 90);


	//arrows before btns
	SimpleImage image2 = ImageManager::loadImage("resources/arrow-right-50-50.png", true);
	image2.renderImageWithMask(pContext->getBackgroundSurface(), 0, 0, 480, 400, image2.getWidth(), image2.getHeight());
	
	ImagePixelMappingRotateAndColour mapping2(0, image2.getWidth() / 2, image2.getHeight() / 2);
	mapping2.setTransparencyColour(0xffffff);
	//image2.renderImageApplyingMapping(pContext, pContext->getBackgroundSurface(), 480, 400, image2.getWidth(), image2.getHeight(), &mapping2);

	mapping2.setRotation(M_PI / 4);
	image2.renderImageApplyingMapping(pContext, pContext->getBackgroundSurface(), 480, 470, image2.getWidth(), image2.getHeight(), &mapping2);

	mapping2.setRotation(M_PI * 3 / 2);
	image2.renderImageApplyingMapping(pContext, pContext->getBackgroundSurface(), 480, 540, image2.getWidth(), image2.getHeight(), &mapping2);

	mapping2.setRotation(M_PI * 7 / 4);
	image2.renderImageApplyingMapping(pContext, pContext->getBackgroundSurface(), 480, 610, image2.getWidth(), image2.getHeight(), &mapping2);

	mapping2.setRotation(M_PI);
	image2.renderImageApplyingMapping(pContext, pContext->getBackgroundSurface(), 480, 680, image2.getWidth(), image2.getHeight(), &mapping2);


	// buttons
	pContext->drawBackgroundRectangle(550, 400, 750, 450, 0xF94144);
	pContext->drawBackgroundString(650 - 72, 405, "New Game", 0xFFFFFF, pContext->getFont("Ubuntu-Medium.ttf", 30));

	pContext->drawBackgroundRectangle(550, 470, 750, 520, 0xF9C74F);
	pContext->drawBackgroundString(650 - 65, 475, "Continue", 0xFFFFFF, pContext->getFont("Ubuntu-Medium.ttf", 30));

	pContext->drawBackgroundRectangle(550, 540, 750, 590, 0x4361EE);
	pContext->drawBackgroundString(650 - 85, 545, "How to Play", 0xFFFFFF, pContext->getFont("Ubuntu-Medium.ttf", 30));

	pContext->drawBackgroundRectangle(550, 610, 750, 660, 0xF19C79);
	pContext->drawBackgroundString(650 - 75, 615, "High Score", 0xFFFFFF, pContext->getFont("Ubuntu-Medium.ttf", 30));

	pContext->drawBackgroundRectangle(550, 680, 750, 730, 0x52B69A);
	pContext->drawBackgroundString(650 - 28, 685, "Exit", 0xFFFFFF, pContext->getFont("Ubuntu-Medium.ttf", 30));
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
				pContext->changeState("choose_level");
			}
			else if (iY > 470 && iY < 520) {
				pContext->changeState("gaming");
			}
			else if (iY > 540 && iY < 590) {
				pContext->changeState("instruction");
			}
			else if (iY > 610 && iY < 660) {
				pContext->changeState("high_score");
			}
			else if (iY > 680 && iY < 730) {
				pContext->setExitWithCode(0);
			}
		}
	}
}
