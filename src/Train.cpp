#include "header.h"
#include "Train.h"
#include "BaseEngine.h"
#include "Constant.h"

void Carriage::addPassenger(PassengerCollection* oPassenger)
{
	if (m_iPassengerCount == m_iMaxNumOfPassengers) {
		printf("## Debug - carriage is full\n");
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
		printf("!! Error @ Train.cpp addPassenger() - m_iPassengerCount said there are still places, but failed to put the passenger into the carriage\n");
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
		printf("!! Error @ Train.cpp removePassenger() - invalid remove of passenger from train\n");
	}
	else {
		delete m_vecPassenger[iIndex];
		m_vecPassenger[iIndex] = nullptr;
		m_iPassengerCount--;
	}
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
		m_uiBorderColor);

	for (PassengerCollection* passenger : m_vecPassenger) {
		if (passenger != nullptr)
			passenger->getPassenger()->virtDraw();
	}
}

Carriage* CarriageCollection::getCarriage() {
	return m_oCarriage;
}
