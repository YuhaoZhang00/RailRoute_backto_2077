#include "header.h"
#include "HighScoreState.h"
#include "ImagePixelMapping.h"
#include "Constant.h"
#include "FileHandler.h"

int HighScoreState::virtInitialise(Scyyz12Engine2* pContext)
{
	return pContext->BaseEngine::virtInitialise();
}

void HighScoreState::virtSetupBackgroundBuffer(Scyyz12Engine2* pContext)
{
	pContext->getForegroundSurface()->setDrawPointsFilter(pContext);

	pContext->fillBackground(0xffffff);

	// Title
	pContext->drawBackgroundRectangle(650 - 115, 70, 650 + 115, 75, 0xF94144);
	pContext->drawBackgroundString(650 - 100, 30, "High Score", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 40));

	// List of High Scores
	FileReader fr("resources/high_score.txt");
	m_vecHighScore = fr.readWholeFile();

	int iLen = size(m_vecHighScore);
	if (iLen % 3 != 0) {
		printf("!! Error @ HighScoreState.cpp virtSetupBackgroundBuffer - the size should be multiples to 3");
	}
	if (iLen > 3 * MAX_SCORES_IN_HIGH_SCORE) {
		printf("!! Error @ HighScoreState.cpp virtSetupBackgroundBuffer - too many high scores");
	}
	pContext->drawBackgroundString(350, 120, "Player", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
	pContext->drawBackgroundString(630, 120, "Day", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
	pContext->drawBackgroundString(790, 120, "Passengers", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
	pContext->drawBackgroundThickLine(350, 160, 950, 160, 0x000000, 2);
	for (int i = 0; i < 3 * MAX_SCORES_IN_HIGH_SCORE; i += 3) {
		if (i < iLen) {
			pContext->drawBackgroundString(350, 170 + 16 * i, m_vecHighScore[i].c_str(), 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 20));
			pContext->drawBackgroundString(645, 170 + 16 * i, m_vecHighScore[i + 1].c_str(), 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 20));
			pContext->drawBackgroundString(840, 170 + 16 * i, m_vecHighScore[i + 2].c_str(), 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 20));
		}
		else {
			pContext->drawBackgroundString(350, 170 + 16 * i, "-", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 20));
			pContext->drawBackgroundString(648, 170 + 16 * i, " -", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 20));
			pContext->drawBackgroundString(842, 170 + 16 * i, "    -", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 20));
		}
	}

	// btn to clear high score
	pContext->drawBackgroundString(650 - 70, 685, "Clear Rankings", 0x666666, pContext->getFont("Ubuntu-Medium.ttf", 20));

	// Exit btn
	SimpleImage backArrow = ImageManager::loadImage("resources/arrow-right-50-50.png", true);
	ImagePixelMappingRotateAndColour mapping(0, backArrow.getWidth() / 2, backArrow.getHeight() / 2);
	mapping.setTransparencyColour(0xffffff);
	mapping.setRotation(M_PI);
	backArrow.renderImageApplyingMapping(pContext, pContext->getBackgroundSurface(), 30, 30, backArrow.getWidth(), backArrow.getHeight(), &mapping);
}

void HighScoreState::virtDrawStringsOnTop(Scyyz12Engine2* pContext)
{
	pContext->BaseEngine::virtDrawStringsOnTop();
}

int HighScoreState::virtInitialiseObjects(Scyyz12Engine2* pContext)
{
	return pContext->BaseEngine::virtInitialiseObjects();
}

void HighScoreState::virtMouseMoved(Scyyz12Engine2* pContext, int iX, int iY)
{
	pContext->BaseEngine::virtMouseMoved(iX, iY);
}

void HighScoreState::virtMouseDown(Scyyz12Engine2* pContext, int iButton, int iX, int iY)
{
	printf("## Debug - click at %d %d\n", iX, iY);
	if (iButton == SDL_BUTTON_LEFT)
	{
		if (iX > 580 && iX < 720) {
			if (iY > 680 && iY < 710) {
				FileWriter fh("resources/high_score.txt");
				pContext->changeState("high_score");
			}
		}
		if (iX > 30 && iX < 80) {
			if (iY > 30 && iY < 80) {
				pContext->changeState("start");
			}
		}
	}
}

void HighScoreState::virtMouseWheel(Scyyz12Engine2* pContext, int x, int y, int which, int timestamp)
{
	pContext->BaseEngine::virtMouseWheel(x, y, which, timestamp);
}

void HighScoreState::virtMainLoopDoBeforeUpdate(Scyyz12Engine2* pContext)
{
	pContext->BaseEngine::virtMainLoopDoBeforeUpdate();
}

void HighScoreState::copyAllBackgroundBuffer(Scyyz12Engine2* pContext)
{
	pContext->BaseEngine::copyAllBackgroundBuffer();
}

void HighScoreState::virtKeyDown(Scyyz12Engine2* pContext, int iKeyCode)
{
	pContext->BaseEngine::virtKeyDown(iKeyCode);
}

void HighScoreState::virtCreateSurfaces(Scyyz12Engine2* pContext)
{
	pContext->BaseEngine::virtCreateSurfaces();
}


