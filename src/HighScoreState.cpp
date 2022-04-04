#include "header.h"
#include "HighScoreState.h"

void HighScoreState::virtSetupBackgroundBuffer(Scyyz12Engine2* pContext)
{
	pContext->fillBackground(0xffffff);

	// Exit btn
	pContext->drawBackgroundRectangle(550, 680, 750, 730, 0xF94144);
	pContext->drawBackgroundString(650 - 28, 685, "Exit", 0xFFFFFF, pContext->getFont("Ubuntu-Medium.ttf", 30));
}

void HighScoreState::virtDrawStringsOnTop(Scyyz12Engine2* pContext)
{
	pContext->BaseEngine::virtDrawStringsOnTop();
}

int HighScoreState::virtInitialiseObjects(Scyyz12Engine2* pContext)
{
	return pContext->BaseEngine::virtInitialiseObjects();
}

void HighScoreState::virtMouseDown(Scyyz12Engine2* pContext, int iButton, int iX, int iY)
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

void HighScoreState::virtMainLoopDoBeforeUpdate(Scyyz12Engine2* pContext)
{
	pContext->BaseEngine::virtMainLoopDoBeforeUpdate();
}

void HighScoreState::copyAllBackgroundBuffer(Scyyz12Engine2* pContext)
{
	pContext->BaseEngine::copyAllBackgroundBuffer();
}
