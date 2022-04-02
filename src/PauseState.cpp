#include "PauseState.h"

void PauseState::virtSetupBackgroundBuffer(Scyyz12Engine2* pContext)
{
	pContext->fillBackground(0xffffff);

	pContext->drawBackgroundString(650 - 40, 100, "pause", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 40));

	// Exit btn
	pContext->drawBackgroundRectangle(550, 680, 750, 730, 0xF94144);
	pContext->drawBackgroundString(650 - 28, 685, "back to game", 0xFFFFFF, pContext->getFont("Ubuntu-Medium.ttf", 30));
}

void PauseState::virtDrawStringsOnTop(Scyyz12Engine2* pContext)
{
}

int PauseState::virtInitialiseObjects(Scyyz12Engine2* pContext)
{
	return 0;
}

void PauseState::virtMouseDown(Scyyz12Engine2* pContext, int iButton, int iX, int iY)
{
	printf("## Debug - click at %d %d\n", iX, iY);
	if (iButton == SDL_BUTTON_LEFT)
	{
		if (iX > 550 && iX < 750) {
			if (iY > 680 && iY < 730) {
				pContext->changeState("gaming");
			}
		}
	}
}
