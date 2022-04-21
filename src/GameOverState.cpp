#include "header.h"
#include "GameOverState.h"
#include "FileHandler.h"
#include "ImagePixelMapping.h"
#include "Constant.h"

void GameOverState::updateHighest10Scores()
{
	if (m_strUserName == "<Name>") {
		m_strUserName = "[anonymous]";
	}
	FileReader fr("resources/high_score.txt");
	std::vector<std::string> vecHighScore = fr.readWholeFile();
	bool bIsInserted = false;
	for (int i = 0; i < size(vecHighScore); i += 3) {
		if (stoi(vecHighScore[i + 2]) <= m_iNumOfPassengers) {
			char cstrNumOfPassengers[6];
			snprintf(cstrNumOfPassengers, 6, "%05d", m_iNumOfPassengers);
			vecHighScore.insert(vecHighScore.begin() + i, std::string(cstrNumOfPassengers));
			vecHighScore.insert(vecHighScore.begin() + i, std::to_string(m_iLevel));
			vecHighScore.insert(vecHighScore.begin() + i, m_strUserName);
			bIsInserted = true;
			break;
		}
	}
	if (!bIsInserted) {
		vecHighScore.emplace_back(m_strUserName);
		vecHighScore.emplace_back(std::to_string(m_iLevel));
		char cstrNumOfPassengers[6];
		snprintf(cstrNumOfPassengers, 6, "%05d", m_iNumOfPassengers);
		vecHighScore.emplace_back(std::string(cstrNumOfPassengers));
	}
	for (int i = size(vecHighScore); i > 3 * MAX_SCORES_IN_HIGH_SCORE; i--) {
		vecHighScore.pop_back();
	}

	FileWriter fw("resources/high_score.txt");
	for (std::string str : vecHighScore) {
		fw.write(str);
	}
}

void GameOverState::inputUserName(int iKeyCode)
{
	if (size(m_strUserName) >= 12) {
		return;
	}
	else if (m_strUserName == "<Name>") {
		m_strUserName.clear();
	}
	m_strUserName.push_back(iKeyCode);
}

void GameOverState::deleteUserName()
{
	if (m_strUserName == "<Name>") {
		return;
	}
	m_strUserName.pop_back();
	if (size(m_strUserName) == 0) {
		m_strUserName = "<Name>";
	}
}

int GameOverState::virtInitialise(Scyyz12Engine2* pContext)
{
	return pContext->BaseEngine::virtInitialise();
}

void GameOverState::virtSetupBackgroundBuffer(Scyyz12Engine2* pContext)
{
	pContext->getForegroundSurface()->setDrawPointsFilter(pContext);
	m_strUserName = "<Name>";

	pContext->fillBackground(0xffffff);

	// Title
	// TODO: the recrangle is for justifying position of string, please delete in release, or use a better / more beautiful way
	pContext->drawBackgroundRectangle(650 - 115, 70, 650 + 115, 75, 0xF94144);
	pContext->drawBackgroundString(650 - 105, 30, "Game Over", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 40));

	// Status & text field to enter name
	// TODO: 显示第几关的相关信息
	pContext->drawBackgroundString(200, 160, "Overcrouding at your stations has forced your railway to close.",
		0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
	char strScore[100]; sprintf(strScore, "%d passengers traveled on your railway over %d days.", m_iNumOfPassengers, m_iNumOfDays);
	pContext->drawBackgroundString(200, 200, strScore, 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
	pContext->drawBackgroundString(398, 320, "Great work! Please enter your name:",
		0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
	pContext->drawBackgroundRectangle(460, 380, 840, 435, 0x666666);
	pContext->drawBackgroundRectangle(463, 383, 837, 432, 0xEEEEEE);
	pContext->drawBackgroundString(580, 445, "-  Player name can only consist of A-Z, 0-9",
		0x666666, pContext->getFont("Ubuntu-Medium.ttf", 20));
	pContext->drawBackgroundString(580, 470, "-  please make your name 12 characters or less",
		0x666666, pContext->getFont("Ubuntu-Medium.ttf", 20));

	// btn to HighScore state
	pContext->drawBackgroundRectangle(550, 680, 750, 730, 0xF94144);
	pContext->drawBackgroundString(650 - 55, 685, "Ranking", 0xFFFFFF, pContext->getFont("Ubuntu-Medium.ttf", 30));

	// Exit btn
	SimpleImage backArrow = ImageManager::loadImage("resources/arrow-right-50-50.png", true);
	ImagePixelMappingRotateAndColour mapping(0, backArrow.getWidth() / 2, backArrow.getHeight() / 2);
	mapping.setTransparencyColour(0xffffff);
	mapping.setRotation(M_PI);
	backArrow.renderImageApplyingMapping(pContext, pContext->getBackgroundSurface(), 30, 30, backArrow.getWidth(), backArrow.getHeight(), &mapping);
}

void GameOverState::virtDrawStringsOnTop(Scyyz12Engine2* pContext)
{
	pContext->drawForegroundString(470, 390, m_strUserName.c_str(), 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
}

int GameOverState::virtInitialiseObjects(Scyyz12Engine2* pContext)
{
	return pContext->BaseEngine::virtInitialiseObjects();
}

void GameOverState::virtMouseDown(Scyyz12Engine2* pContext, int iButton, int iX, int iY)
{
	printf("## Debug - click at %d %d\n", iX, iY);
	if (iButton == SDL_BUTTON_LEFT)
	{
		if (iX > 550 && iX < 750) {
			if (iY > 680 && iY < 730) {
				updateHighest10Scores();
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

void GameOverState::virtMouseWheel(Scyyz12Engine2* pContext, int x, int y, int which, int timestamp)
{
	pContext->BaseEngine::virtMouseWheel(x, y, which, timestamp);
}

void GameOverState::virtMainLoopDoBeforeUpdate(Scyyz12Engine2* pContext)
{
	pContext->BaseEngine::virtMainLoopDoBeforeUpdate();
}

void GameOverState::copyAllBackgroundBuffer(Scyyz12Engine2* pContext)
{
	pContext->BaseEngine::copyAllBackgroundBuffer();
}

void GameOverState::virtKeyDown(Scyyz12Engine2* pContext, int iKeyCode)
{
	printf("## debug - keyboard iKeyCode: %d; ", iKeyCode);
	if (iKeyCode >= 0x61 && iKeyCode <= 0x7A) {
		printf(" value: %c\n", iKeyCode - 32);
		inputUserName(iKeyCode - 32);
	}
	else if (iKeyCode >= 48 && iKeyCode <= 57) {
		printf(" value: %c\n", iKeyCode);
		inputUserName(iKeyCode);
	}
	else if (iKeyCode == 8) {
		printf(" value: 'backspace'\n");
		deleteUserName();
	}
	else {
		printf(" key code not handled\n");
	}
	pContext->redrawDisplay();
}
