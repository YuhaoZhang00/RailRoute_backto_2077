#include "header.h"
#include "InstructionState.h"

void InstructionState::virtSetupBackgroundBuffer(Scyyz12Engine2* pContext)
{
	pContext->fillBackground(0xffffff);

	pContext->drawBackgroundThickLine(200, 0, 0, 200, 0xF9C74F, 10);
	pContext->drawBackgroundThickLine(100, 0, 100, 800, 0x52B69A, 10);
	pContext->drawBackgroundOval(80, 80, 120, 120, 0x000000);
	pContext->drawBackgroundOval(85, 85, 115, 115, 0xFFFFFF);
	pContext->drawBackgroundRectangle(84, 484, 116, 516, 0x000000);
	pContext->drawBackgroundRectangle(89, 489, 111, 511, 0xFFFFFF);

	pContext->drawBackgroundRectangle(125, 480, 135, 490, 0x000000);
	pContext->drawBackgroundOval(140, 480, 151, 491, 0x000000);
	pContext->drawBackgroundTriangle(160, 481, 165, 490, 155, 490, 0x000000);

	pContext->drawBackgroundRectangle(88, 597, 112, 639, 0x52B69A);
	pContext->drawBackgroundOval(88, 590, 112, 604, 0x52B69A);

	int iR = (0xff & (0x52B69A >> 16)) * 50 + (0xff & (0xFFFFFF >> 16)) * 50;
	int iG = (0xff & (0x52B69A >> 8)) * 50 + (0xff & (0xFFFFFF >> 8)) * 50;
	int iB = (0xff & 0x52B69A) * 50 + (0xff & 0xFFFFFF) * 50;
	int color2 = (((iR / 100) & 0xff) << 16) | (((iG / 100) & 0xff) << 8) | ((iB / 100) & 0xff);

	pContext->drawBackgroundRectangle(90, 601, 99, 610, color2);
	pContext->drawBackgroundOval(101, 600, 112, 611, color2);
	pContext->drawBackgroundOval(88, 612, 99, 623, color2);
	pContext->drawBackgroundRectangle(102, 613, 111, 622, color2);
	pContext->drawBackgroundTriangle(94, 625, 89, 634, 99, 634, color2);

	pContext->drawBackgroundString(650 - 28, 640, "Idea from: Mini Metro by Dinosaur Polo Club", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 20));

	// Exit btn
	pContext->drawBackgroundRectangle(550, 680, 750, 730, 0xF94144);
	pContext->drawBackgroundString(650 - 28, 685, "Exit", 0xFFFFFF, pContext->getFont("Ubuntu-Medium.ttf", 30));
}

void InstructionState::virtDrawStringsOnTop(Scyyz12Engine2* pContext)
{
	pContext->BaseEngine::virtDrawStringsOnTop();
}

int InstructionState::virtInitialiseObjects(Scyyz12Engine2* pContext)
{
	return pContext->BaseEngine::virtInitialiseObjects();
}

void InstructionState::virtMouseDown(Scyyz12Engine2* pContext, int iButton, int iX, int iY)
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
