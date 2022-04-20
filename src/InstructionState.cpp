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

	/*m_stationls.clear();
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
		temp->getStation()->removePassenger(1);
		m_stationls.emplace_back(temp);
		pContext->appendObjectToArray(m_stationls[i]->getStation());
	}*/

	//CarriageCollection* temp = new CarriageCollection(0, pContext, 500, 600, 0x52B69A);
	////CarriageCollection* temp = new CarriageCollection(1, pContext, 500, 600, 0x52B69A);
	////CarriageCollection* temp = new CarriageCollection(2, pContext, 500, 600, 0xFFD700);
	////CarriageCollection* temp = new CarriageCollection(3, pContext, 500, 600, 0x52B69A);
	//temp->getCarriage()->addPassenger(new PassengerCollection(0, pContext));
	//temp->getCarriage()->addPassenger(new PassengerCollection(1, pContext));
	//temp->getCarriage()->addPassenger(new PassengerCollection(2, pContext));
	//temp->getCarriage()->addPassenger(new PassengerCollection(3, pContext));
	//temp->getCarriage()->addPassenger(new PassengerCollection(3, pContext));
	//temp->getCarriage()->addPassenger(new PassengerCollection(4, pContext));
	//for (int idx : temp->getCarriage()->findPassengerByType(3)) {
	//	temp->getCarriage()->removePassenger(idx);
	//}
	//temp->getCarriage()->addPassenger(new PassengerCollection(5, pContext));
	//pContext->appendObjectToArray(temp->getCarriage());

	//TrainCollection* temp = new TrainCollection(0, pContext, 500, 500, 0x52B69A);
	TrainCollection* temp = new TrainCollection(1, pContext, 500, 500, 0x52B69A);
	//TrainCollection* temp = new TrainCollection(2, pContext, 500, 500, 0x52B69A);
	temp->getTrain()->addHead();
	temp->getTrain()->addCarriage();
	temp->getTrain()->addCarriage();
	temp->getTrain()->addCarriage();
	temp->getTrain()->addCarriage();
	temp->getTrain()->removeCarriageAfterN(2);
	temp->getTrain()->addCarriage();
	temp->getTrain()->addCarriage();
	temp->getTrain()->removeCarriageAfterN(2);
	temp->getTrain()->addPassenger(new PassengerCollection(0, pContext));
	temp->getTrain()->addPassenger(new PassengerCollection(1, pContext));
	temp->getTrain()->addPassenger(new PassengerCollection(2, pContext));
	temp->getTrain()->addPassenger(new PassengerCollection(3, pContext));
	temp->getTrain()->addPassenger(new PassengerCollection(4, pContext));
	temp->getTrain()->addPassenger(new PassengerCollection(0, pContext));
	temp->getTrain()->addPassenger(new PassengerCollection(1, pContext));
	temp->getTrain()->addPassenger(new PassengerCollection(2, pContext));
	temp->getTrain()->addPassenger(new PassengerCollection(3, pContext));
	temp->getTrain()->addPassenger(new PassengerCollection(4, pContext));
	temp->getTrain()->addPassenger(new PassengerCollection(0, pContext));
	temp->getTrain()->addPassenger(new PassengerCollection(1, pContext));
	temp->getTrain()->addPassenger(new PassengerCollection(2, pContext));
	temp->getTrain()->addPassenger(new PassengerCollection(3, pContext));
	temp->getTrain()->addPassenger(new PassengerCollection(4, pContext));
	for (int passengerIdx : (temp->getTrain()->findPassengerByType(1))) {
		temp->getTrain()->removePassenger(passengerIdx);
	}
	temp->getTrain()->addPassenger(new PassengerCollection(5, pContext));
	temp->getTrain()->addPassenger(new PassengerCollection(5, pContext));
	for (CarriageCollection* carriage : temp->getTrain()->getCarriageList()) {
		pContext->appendObjectToArray(carriage->getCarriage());
	}

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

void InstructionState::virtMainLoopDoBeforeUpdate(Scyyz12Engine2* pContext)
{
	pContext->BaseEngine::virtMainLoopDoBeforeUpdate();
}

void InstructionState::copyAllBackgroundBuffer(Scyyz12Engine2* pContext)
{
	pContext->BaseEngine::copyAllBackgroundBuffer();
}

void InstructionState::virtKeyDown(Scyyz12Engine2* pContext, int iKeyCode)
{
	pContext->BaseEngine::virtKeyDown(iKeyCode);
}
