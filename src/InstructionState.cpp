#include "header.h"
#include "InstructionState.h"

int InstructionState::virtInitialise(Scyyz12Engine2* pContext)
{
	return pContext->BaseEngine::virtInitialise();
}

void InstructionState::virtSetupBackgroundBuffer(Scyyz12Engine2* pContext)
{
	pContext->getForegroundSurface()->setDrawPointsFilter(pContext);

	pContext->fillBackground(0xffffff);

	pContext->drawBackgroundThickLine(0, 200, 200, 0, 0xF9C74F, 10);
	pContext->drawBackgroundThickLine(100, 0, 100, 1300, 0x52B69A, 10);

	pContext->drawBackgroundString(130, 90, "\"Hello mate, from now on you will be taking over several of the world's greatest", 0x777777, pContext->getFont("Ubuntu-Medium.ttf", 25));
	pContext->drawBackgroundString(130, 125, "underground systems through this little interface - what? You say you're worried", 0x777777, pContext->getFont("Ubuntu-Medium.ttf", 25));
	pContext->drawBackgroundString(130, 160, "you'll screw up? Well, then listen carefully to how it works. I'm only going to", 0x777777, pContext->getFont("Ubuntu-Medium.ttf", 25));
	pContext->drawBackgroundString(130, 195, "say it once.\"", 0x777777, pContext->getFont("Ubuntu-Medium.ttf", 25));

	pContext->drawBackgroundString(130, 270, "> Connect stations with underground lines", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
	pContext->drawBackgroundString(130, 310, "> And place trains and carriages on the lines to transport passengers", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
	pContext->drawBackgroundString(130, 350, "> Building the line across the river will consume the bridge", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
	pContext->drawBackgroundString(130, 410, "> Be careful! You only have limited lines, trains, and bridges", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
	pContext->drawBackgroundString(130, 450, "> If your railway doesn't close down during the week due to angry passengers,", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
	pContext->drawBackgroundString(130, 490, "   you can choose a bonus", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
	
	pContext->drawBackgroundString(130, 575, "\"Guess what, everything you do is NOT going to affect the real world HAHA you fo", 0x777777, pContext->getFont("Ubuntu-Medium.ttf", 25));
	pContext->drawBackgroundString(130, 610, "- what? You say you already know?!\"", 0x777777, pContext->getFont("Ubuntu-Medium.ttf", 25));

	pContext->drawBackgroundString(700, 750, "Idea of the game from: Mini Metro by Dinosaur Polo Club", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 20));

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
	pContext->destroyOldObjects(true);

	if (c1 == nullptr) {
		c1 = new TrainCollection(0, 0, pContext, 100, 500, 0x52B69A);
		c1->getTrain()->addHead();
		c1->getTrain()->addCarriage();
		c1->getTrain()->addCarriage();
	}
	if (s1 == nullptr) {
		s1 = new StationCollection(0, 0, pContext, 100, 100);
	}
	if (s2 == nullptr) {
		s2 = new StationCollection(0, 1, pContext, 100, 500);
	}

	for (CarriageCollection* c : c1->getTrain()->getCarriageList())
		pContext->appendObjectToArray(c->getCarriage());
	pContext->appendObjectToArray(s1->getStation());
	pContext->appendObjectToArray(s2->getStation());

	return 0;
}

void InstructionState::virtMouseMoved(Scyyz12Engine2* pContext, int iX, int iY)
{
	pContext->BaseEngine::virtMouseMoved(iX, iY);
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

void InstructionState::virtMouseWheel(Scyyz12Engine2* pContext, int x, int y, int which, int timestamp)
{
	pContext->BaseEngine::virtMouseWheel(x, y, which, timestamp);
}

void InstructionState::virtMainLoopDoBeforeUpdate(Scyyz12Engine2* pContext)
{
	if (++iFakeInnerTimer == 100) {
		c1->getTrain()->startTrain();
	}
	else if (iFakeInnerTimer >= 105 && 
		(c1->getTrain()->getCarriageList()[0]->getCarriage()->getYExactPos() == 100 ||
			c1->getTrain()->getCarriageList()[0]->getCarriage()->getYExactPos() == 500)) {
		c1->getTrain()->stopTrain();
		iFakeInnerTimer = 0;
	}
	for (CarriageCollection* c : c1->getTrain()->getCarriageList()) {
		if (c->getCarriage()->getYExactPos() == -15) {
			c->getCarriage()->setExactPos(100, 815);
		}
	}
	pContext->redrawDisplay();
}

void InstructionState::copyAllBackgroundBuffer(Scyyz12Engine2* pContext)
{
	pContext->BaseEngine::copyAllBackgroundBuffer();
}

void InstructionState::virtKeyDown(Scyyz12Engine2* pContext, int iKeyCode)
{
	pContext->BaseEngine::virtKeyDown(iKeyCode);
}

void InstructionState::virtCreateSurfaces(Scyyz12Engine2* pContext)
{
	pContext->BaseEngine::virtCreateSurfaces();
}
