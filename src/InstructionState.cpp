#include "header.h"
#include "InstructionState.h"

void InstructionState::virtSetupBackgroundBuffer(Scyyz12Engine2* pContext)
{
	pContext->fillBackground(0xffffff);

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
	pContext->drawableObjectsChanged();
	pContext->destroyOldObjects(true);
	pContext->createObjectArray(1);
	m_line1 = new RailLine(pContext, 100, 0, false, 0x52B69A, 800);
	pContext->storeObjectInArray(0, m_line1);
	m_line2 = new RailLineDiagonal(pContext, 0, 200, 0, 0xF9C74F, 200);
	pContext->appendObjectToArray(m_line2);
	/*m_line3_1 = new RailLine(pContext, 0, 100, true, 0xF94144, 1100);
	pContext->appendObjectToArray(m_line3_1);
	m_line3_2 = new RailLineDiagonal(pContext, 1100, 100, 1, 0xF94144, 200);
	pContext->appendObjectToArray(m_line3_2);*/
	/*m_line4_1 = new RailLineDiagonal(pContext, 220, 200, true, 0xF94144, 100);
	pContext->appendObjectToArray(m_line4_1);
	m_line4_2 = new RailLineDiagonal(pContext, 205, 215, false, 0xF94144, 85);
	pContext->appendObjectToArray(m_line4_2);
	m_linelink4 = new RailLink90Diagonal(pContext, 200, 195, 3, 0xF94144);
	pContext->appendObjectToArray(m_linelink4);*/

	for (int i = 0; i < 6; i++) {
		StationCollection* temp = new StationCollection(i, pContext, 100, 100 + 100 * i);
		temp->getStation()->addPassenger(new PassengerCollection(0, pContext));
		temp->getStation()->addPassenger(new PassengerCollection(1, pContext));
		temp->getStation()->addPassenger(new PassengerCollection(2, pContext));
		temp->getStation()->addPassenger(new PassengerCollection(3, pContext));
		temp->getStation()->addPassenger(new PassengerCollection(4, pContext));
		temp->getStation()->addPassenger(new PassengerCollection(5, pContext));
		temp->getStation()->addPassenger(new PassengerCollection(4, pContext));
		temp->getStation()->addPassenger(new PassengerCollection(2, pContext));
		temp->getStation()->addPassenger(new PassengerCollection(0, pContext));
		m_stationls.emplace_back(temp);
		pContext->appendObjectToArray(m_stationls[i]->getStation());
	}

	//for (int i = 0; i < 6; i++) {
	//	m_passengerls.emplace_back(new PassengerCollection(i, pContext, 300 + 20 * i, 300));
	//	pContext->appendObjectToArray(m_passengerls[i]->getPassenger());
	//}

	return 0;
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
