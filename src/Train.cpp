#include "header.h"
#include "Train.h"
#include "BaseEngine.h"
#include "Constant.h"

int Carriage::getLength()
{
	return m_iLength;
}

int Carriage::getMaxNumOfPassengers()
{
	return m_iMaxNumOfPassengers;
}

void Carriage::addPassenger(PassengerCollection* oPassenger)
{
	if (isFull()) {
		printf("!! Error @ Train.cpp Carriage::addPassenger - carriage is full, please check isFull() before adding passenger to carriage\n");
	}
	else {
		for (int i = 0; i < m_iMaxNumOfPassengers; i++) {
			if (m_vecPassenger[i] == nullptr) {
				oPassenger->getPassenger()->setXCenter(m_iCurrentScreenX - m_iWidth / 2 + m_iWidth / 2 * (i % 2) + m_iWidth / 4);
				oPassenger->getPassenger()->setYCenter(m_iCurrentScreenY - m_iLength / 2 + m_iLength / (m_iMaxNumOfPassengers / 2) * (i / 2) + m_iLength / (m_iMaxNumOfPassengers / 2) / 2);
				oPassenger->getPassenger()->setColor(m_uiPassengerColor);
				m_vecPassenger[i] = oPassenger;
				m_iPassengerCount++;
				return;
			}
		}
		printf("!! Error @ Train.cpp Carriage::addPassenger() - m_iPassengerCount said there are still places, but failed to put the passenger into the carriage\n");
	}

}

std::vector<int> Carriage::findPassengerByType(short sType)
{
	std::vector<int> vecPassenger;
	for (int i = 0; i < m_iMaxNumOfPassengers; i++) {
		if (m_vecPassenger[i] != nullptr && m_vecPassenger[i]->getType() == sType) {
			vecPassenger.emplace_back(i);
		}
	}
	return vecPassenger;
}

void Carriage::removePassenger(int iIndex)
{
	if (iIndex < 0 || iIndex >= m_iMaxNumOfPassengers || m_vecPassenger[iIndex] == nullptr) {
		printf("!! Error @ Train.cpp Carriage::removePassenger() - invalid remove of passenger from train\n");
	}
	else {
		delete m_vecPassenger[iIndex];
		m_vecPassenger[iIndex] = nullptr;
		m_iPassengerCount--;
	}
}

bool Carriage::isFull()
{
	return (m_iPassengerCount >= m_iMaxNumOfPassengers);
}

void CarriageHead::virtDraw()
{
	getEngine()->drawForegroundRectangle(
		m_iCurrentScreenX - m_iWidth / 2, m_iCurrentScreenY - m_iLength / 2,
		m_iCurrentScreenX + m_iWidth / 2, m_iCurrentScreenY + m_iLength / 2,
		m_uiColor);
	getEngine()->drawForegroundOval(
		m_iCurrentScreenX - m_iWidth / 2, m_iCurrentScreenY - m_iLength / 2 - m_iLength / 5,
		m_iCurrentScreenX + m_iWidth / 2, m_iCurrentScreenY - m_iLength / 2 + m_iLength / 5,
		m_uiColor);

	for (PassengerCollection* passenger : m_vecPassenger) {
		if (passenger != nullptr)
			passenger->getPassenger()->virtDraw();
	}
}

void CarriageMain::virtDraw()
{
	getEngine()->drawForegroundRectangle(
		m_iCurrentScreenX - m_iWidth / 2, m_iCurrentScreenY - m_iLength / 2,
		m_iCurrentScreenX + m_iWidth / 2, m_iCurrentScreenY + m_iLength / 2,
		m_uiColor);

	for (PassengerCollection* passenger : m_vecPassenger) {
		if (passenger != nullptr)
			passenger->getPassenger()->virtDraw();
	}
}

void CarriageHeadFast::virtDraw()
{
	getEngine()->drawForegroundRectangle(
		m_iCurrentScreenX - m_iWidth / 2, m_iCurrentScreenY - m_iLength / 2,
		m_iCurrentScreenX + m_iWidth / 2, m_iCurrentScreenY + m_iLength / 2,
		m_uiColor);
	getEngine()->drawForegroundTriangle(
		m_iCurrentScreenX, m_iCurrentScreenY - m_iLength / 2 - m_iLength / 4,
		m_iCurrentScreenX + m_iWidth / 2, m_iCurrentScreenY - m_iLength / 2,
		m_iCurrentScreenX - m_iWidth / 2, m_iCurrentScreenY - m_iLength / 2,
		m_uiColor);

	for (PassengerCollection* passenger : m_vecPassenger) {
		if (passenger != nullptr)
			passenger->getPassenger()->virtDraw();
	}
}

void CarriageHeadIntelli::virtDraw()
{
	getEngine()->drawForegroundRectangle(
		m_iCurrentScreenX - m_iWidth / 2, m_iCurrentScreenY - m_iLength / 2,
		m_iCurrentScreenX + m_iWidth / 2, m_iCurrentScreenY + m_iLength / 2,
		m_uiColor);
	getEngine()->drawForegroundTriangle(
		m_iCurrentScreenX, m_iCurrentScreenY - m_iLength / 2 - m_iLength / 4,
		m_iCurrentScreenX + m_iWidth / 2, m_iCurrentScreenY - m_iLength / 2,
		m_iCurrentScreenX - m_iWidth / 2, m_iCurrentScreenY - m_iLength / 2,
		m_uiSpecialColor);

	for (PassengerCollection* passenger : m_vecPassenger) {
		if (passenger != nullptr)
			passenger->getPassenger()->virtDraw();
	}
}

Carriage* CarriageCollection::getCarriage() {
	return m_oCarriage;
}

bool Train::addCarriage(int iMaxNumberOfPassengers, int iLength)
{
	if (m_iCarriageCount >= MAX_CARRIAGES_IN_TRAIN) {
		printf("## Debug - a train can only have %d carriages in max\n", MAX_CARRIAGES_IN_TRAIN);
		return false;
	}
	else {
		int iXCenter = m_iXCenterHead;
		int iYCenter = m_iYCenterHead + m_iCarriageCount * m_iDist + m_vecCarriage[0]->getCarriage()->getLength() / 2
			+ (m_iCarriageCount - 1) * ((iLength == -1) ? 30 : iLength) + ((iLength == -1) ? 30 : iLength) / 2;
		CarriageCollection* oCarriage = new CarriageCollection(3, m_pEngine, iXCenter, iYCenter, m_uiColor, 0, iMaxNumberOfPassengers, 20, iLength);
		m_vecCarriage.emplace_back(oCarriage);
		m_iCarriageCount++;
		m_iMaxNumOfPassengers += oCarriage->getCarriage()->getMaxNumOfPassengers();
		return true;
	}
}

void Train::removeCarriageAfterN(int iIndex)
{
	if (iIndex < 0 || iIndex >= m_iCarriageCount) {
		printf("!! Error @ Train.cpp removeLastNCarriage() - invalid remove of carriage from train\n");
	}
	else {
		while (m_iCarriageCount > iIndex) {
			m_iMaxNumOfPassengers -= m_vecCarriage[m_iCarriageCount - 1]->getCarriage()->getMaxNumOfPassengers();
			if (m_iMaxNumOfPassengers < 0) {
				printf("!! Error @ Train.cpp removeLastNCarriage() - number of passengers in the train becomes negative");
			}
			delete m_vecCarriage[m_iCarriageCount - 1];
			m_vecCarriage.pop_back();
			m_iCarriageCount--;
		}
	}
}

std::vector<CarriageCollection*> Train::getCarriageList()
{
	return m_vecCarriage;
}

void Train::addPassenger(PassengerCollection* oPassenger)
{
	if (isFull()) {
		delete oPassenger;
		printf("!! Error @ Train.cpp Train::addPassenger - all carriages are full, please check isFull() before adding passenger to train\n");
	}
	else {
		for (CarriageCollection* oCarriage : m_vecCarriage) {
			if (!oCarriage->getCarriage()->isFull()) {
				oCarriage->getCarriage()->addPassenger(oPassenger);
				m_iPassengerCount++;
				return;
			}
		}
		printf("!! Error @ Train.cpp Train::addPassenger() - m_iPassengerCount said there are still places, but failed to put the passenger into the train\n");
	}
}

std::vector<int> Train::findPassengerByType(short sType)
{
	std::vector<int> vecPassenger;
	int iNumOfPassengersInPrevCarriages = 0;
	for (int i = 0; i < size(m_vecCarriage); i++) {
		std::vector<int> vecPassengerInCarriage = m_vecCarriage[i]->getCarriage()->findPassengerByType(sType);
		std::for_each(vecPassengerInCarriage.begin(), vecPassengerInCarriage.end(),
			[iNumOfPassengersInPrevCarriages](int& num) { num += iNumOfPassengersInPrevCarriages; });
		vecPassenger.insert(vecPassenger.end(), vecPassengerInCarriage.begin(), vecPassengerInCarriage.end());
		iNumOfPassengersInPrevCarriages += m_vecCarriage[i]->getCarriage()->getMaxNumOfPassengers();
	}
	return vecPassenger;
}

void Train::removePassenger(int iIndex)
{
	if (iIndex < 0 || iIndex >= m_iMaxNumOfPassengers) {
		printf("!! Error @ Train.cpp Train::removePassenger() - invalid remove of passenger from train\n");
	}
	else {
		for (CarriageCollection* oCarriage : m_vecCarriage) {
			if (iIndex >= oCarriage->getCarriage()->getMaxNumOfPassengers()) {
				iIndex -= oCarriage->getCarriage()->getMaxNumOfPassengers();
			}
			else {
				oCarriage->getCarriage()->removePassenger(iIndex);
				m_iPassengerCount--;
				return;
			}
		}
	}

}

bool Train::isFull()
{
	return (m_iPassengerCount >= m_iMaxNumOfPassengers);
}

void TrainNormal::addHead(int iMaxNumberOfPassengers, int iLength)
{
	if (m_iCarriageCount >= MAX_CARRIAGES_IN_TRAIN) {
		printf("!! Error @ Train.cpp TrainNormal::addHead() - add a head will not result in max carriage count\n");
	}
	else {
		CarriageCollection* oCarriage = new CarriageCollection(0, m_pEngine, m_iXCenterHead, m_iYCenterHead, m_uiColor,
			0, iMaxNumberOfPassengers, 20, iLength);
		m_vecCarriage.emplace_back(oCarriage);
		m_iCarriageCount++;
		m_iMaxNumOfPassengers += oCarriage->getCarriage()->getMaxNumOfPassengers();
	}
}

void TrainFast::addHead(int iMaxNumberOfPassengers, int iLength)
{
	if (m_iCarriageCount >= MAX_CARRIAGES_IN_TRAIN) {
		printf("!! Error @ Train.cpp TrainFast::addHead() - add a head will not result in max carriage count\n");
	}
	else {
		CarriageCollection* oCarriage = new CarriageCollection(1, m_pEngine, m_iXCenterHead, m_iYCenterHead, m_uiColor,
			0, iMaxNumberOfPassengers, 20, iLength);
		m_vecCarriage.emplace_back(oCarriage);
		m_iCarriageCount++;
		m_iMaxNumOfPassengers += oCarriage->getCarriage()->getMaxNumOfPassengers();
	}
}

void TrainIntelli::addHead(int iMaxNumberOfPassengers, int iLength)
{
	if (m_iCarriageCount >= MAX_CARRIAGES_IN_TRAIN) {
		printf("!! Error @ Train.cpp TrainIntelli::addHead() - add a head will not result in max carriage count\n");
	}
	else {
		CarriageCollection* oCarriage = new CarriageCollection(2, m_pEngine, m_iXCenterHead, m_iYCenterHead, m_uiColor,
			m_uiSpecialColor, iMaxNumberOfPassengers, 20, iLength);
		m_vecCarriage.emplace_back(oCarriage);
		m_iCarriageCount++;
		m_iMaxNumOfPassengers += oCarriage->getCarriage()->getMaxNumOfPassengers();
	}
}

Train* TrainCollection::getTrain()
{
	return m_oTrain;
}
