#include "header.h"
#include "HighScoreState.h"

void HighScoreState::virtSetupBackgroundBuffer(Scyyz12Engine2* pContext)
{
	pContext->fillBackground(0xffffff);

	// Exit btn
	pContext->drawBackgroundRectangle(550, 610, 750, 660, 0xF94144);
	pContext->drawBackgroundString(650 - 25, 615, "Exit", 0xFFFFFF, pContext->getFont("Ubuntu-Medium.ttf", 30));
}

void HighScoreState::virtDrawStringsOnTop(Scyyz12Engine2* pContext)
{
	pContext->BaseEngine::virtDrawStringsOnTop();
}

int HighScoreState::virtInitialiseObjects(Scyyz12Engine2* pContext)
{
	/*pContext->drawableObjectsChanged();
	pContext->destroyOldObjects(true);
	pContext->createObjectArray(1);
	m_oBall = new TestObject(pContext);
	pContext->storeObjectInArray(0, m_oBall);
	return 0;*/
	return pContext->BaseEngine::virtInitialiseObjects();
}

void HighScoreState::virtMouseDown(Scyyz12Engine2* pContext, int iButton, int iX, int iY)
{
	printf("## Debug - click at %d %d\n", iX, iY);
	if (iButton == SDL_BUTTON_LEFT)
	{
		if (iX > 550 && iX < 750) {
			if (iY > 610 && iY < 660) {
				pContext->changeState("start");
			}
		}
	}
}
