#include "header.h"
#include "Train.h"
#include "BaseEngine.h"
#include "Constant.h"

void Carriage::drawForegroundRectangle0()
{
	getEngine()->drawForegroundRectangle(
		m_iCurrentScreenX - m_iWidth / 2, m_iCurrentScreenY - m_iLength / 2,
		m_iCurrentScreenX + m_iWidth / 2, m_iCurrentScreenY + m_iLength / 2,
		m_uiColor);
}

void Carriage::drawForegroundRectangle90()
{
	getEngine()->drawForegroundRectangle(
		m_iCurrentScreenX - m_iLength / 2, m_iCurrentScreenY - m_iWidth / 2,
		m_iCurrentScreenX + m_iLength / 2, m_iCurrentScreenY + m_iWidth / 2,
		m_uiColor);
}

void Carriage::drawForegroundRectangle45()
{
	for (int i = -m_iLength; i <= m_iLength; i++) {
		for (int j = -m_iLength; j <= m_iLength; j++) {
			if (i + j < m_iWidth * 0.707 && i + j > -m_iWidth * 0.707 && j - i<m_iLength * 0.707 && j - i > -m_iLength * 0.707) {
				getEngine()->setForegroundPixel(m_iCurrentScreenX + i, m_iCurrentScreenY + j, m_uiColor);
			}
		}
	}
}

void Carriage::drawForegroundRectangle135()
{
	for (int i = -m_iLength; i <= m_iLength; i++) {
		for (int j = -m_iLength; j <= m_iLength; j++) {
			if (i + j < m_iLength * 0.707 && i + j > -m_iLength * 0.707 && j - i<m_iWidth * 0.707 && j - i > -m_iWidth * 0.707) {
				getEngine()->setForegroundPixel(m_iCurrentScreenX + i, m_iCurrentScreenY + j, m_uiColor);
			}
		}
	}
}

void Carriage::setPassengerPosition()
{
	m_vecPassengerPos.clear();
	if (m_sDirection == 0) {
		for (int i = 0; i < m_iMaxNumOfPassengers; i++) {
			m_vecPassengerPos.emplace_back(
				-m_iWidth / 2 + m_iWidth / 2 * (i % 2) + m_iWidth / 4);
			m_vecPassengerPos.emplace_back(
				-m_iLength / 2 + m_iLength / (m_iMaxNumOfPassengers / 2) * (i / 2) + m_iLength / (m_iMaxNumOfPassengers / 2) / 2);
		}
	}
	else if (m_sDirection == 4) {
		for (int i = m_iMaxNumOfPassengers - 1; i >= 0; i--) {
			m_vecPassengerPos.emplace_back(
				-m_iWidth / 2 + m_iWidth / 2 * (i % 2) + m_iWidth / 4);
			m_vecPassengerPos.emplace_back(
				-m_iLength / 2 + m_iLength / (m_iMaxNumOfPassengers / 2) * (i / 2) + m_iLength / (m_iMaxNumOfPassengers / 2) / 2);
		}
	}
	else if (m_sDirection == 2) {
		for (int i = 0; i < m_iMaxNumOfPassengers; i++) {
			m_vecPassengerPos.emplace_back(
				-m_iLength / 2 + m_iLength / (m_iMaxNumOfPassengers / 2) * (i / 2) + m_iLength / (m_iMaxNumOfPassengers / 2) / 2);
			m_vecPassengerPos.emplace_back(
				-m_iWidth / 2 + m_iWidth / 2 * (i % 2) + m_iWidth / 4);

		}
	}
	else if (m_sDirection == 6) {
		for (int i = m_iMaxNumOfPassengers - 1; i >= 0; i--) {
			m_vecPassengerPos.emplace_back(
				-m_iLength / 2 + m_iLength / (m_iMaxNumOfPassengers / 2) * (i / 2) + m_iLength / (m_iMaxNumOfPassengers / 2) / 2);
			m_vecPassengerPos.emplace_back(
				-m_iWidth / 2 + m_iWidth / 2 * (i % 2) + m_iWidth / 4);

		}
	}
	else if (m_sDirection == 1) {
		for (int i = 0; i < m_iMaxNumOfPassengers; i++) {
			m_vecPassengerPos.emplace_back(
				+1 + 0.707 * (m_iWidth * (-0.25 + i % 2 * 1.0 / 2) - m_iLength * (-0.5 + (i / 2 * 2 + 1) * 1.0 / m_iMaxNumOfPassengers)));
			m_vecPassengerPos.emplace_back(
				+0.707 * (m_iWidth * (-0.25 + i % 2 * 1.0 / 2) + m_iLength * (-0.5 + (i / 2 * 2 + 1) * 1.0 / m_iMaxNumOfPassengers)));
		}
	}
	else if (m_sDirection == 5) {
		for (int i = 0; i < m_iMaxNumOfPassengers; i++) {
			m_vecPassengerPos.emplace_back(
				+1 - 0.707 * (m_iWidth * (-0.25 + i % 2 * 1.0 / 2) - m_iLength * (-0.5 + (i / 2 * 2 + 1) * 1.0 / m_iMaxNumOfPassengers)));
			m_vecPassengerPos.emplace_back(
				-0.707 * (m_iWidth * (-0.25 + i % 2 * 1.0 / 2) + m_iLength * (-0.5 + (i / 2 * 2 + 1) * 1.0 / m_iMaxNumOfPassengers)));
		}
	}
	else if (m_sDirection == 3) {
		for (int i = 0; i < m_iMaxNumOfPassengers; i++) {
			m_vecPassengerPos.emplace_back(
				-0.707 * (m_iWidth * (-0.25 + i % 2 * 1.0 / 2) - m_iLength * (-0.5 + (i / 2 * 2 + 1) * 1.0 / m_iMaxNumOfPassengers)));
			m_vecPassengerPos.emplace_back(
				+0.707 * (m_iWidth * (-0.25 + i % 2 * 1.0 / 2) + m_iLength * (-0.5 + (i / 2 * 2 + 1) * 1.0 / m_iMaxNumOfPassengers)));
		}
	}
	else if (m_sDirection == 7) {
		for (int i = 0; i < m_iMaxNumOfPassengers; i++) {
			m_vecPassengerPos.emplace_back(
				+0.707 * (m_iWidth * (-0.25 + i % 2 * 1.0 / 2) - m_iLength * (-0.5 + (i / 2 * 2 + 1) * 1.0 / m_iMaxNumOfPassengers)));
			m_vecPassengerPos.emplace_back(
				-0.707 * (m_iWidth * (-0.25 + i % 2 * 1.0 / 2) + m_iLength * (-0.5 + (i / 2 * 2 + 1) * 1.0 / m_iMaxNumOfPassengers)));
		}
	}
	for (int i = 0; i < m_iMaxNumOfPassengers; i++) {
		if (m_vecPassenger[i] != nullptr) {
			m_vecPassenger[i]->getPassenger()->setXCenter(m_iCurrentScreenX + m_vecPassengerPos[i * 2]);
			m_vecPassenger[i]->getPassenger()->setYCenter(m_iCurrentScreenY + m_vecPassengerPos[i * 2 + 1]);
		}
	}
}

void Carriage::drawPassenger()
{
	for (int i = 0; i < m_iMaxNumOfPassengers; i++) {
		if (m_vecPassenger[i] != nullptr) {
			m_vecPassenger[i]->getPassenger()->virtDraw();
		}
	}
}

void Carriage::virtDoUpdate(int iCurrentTime)
{
	if (m_bIsRun) {
		double dSpeedXY;
		switch (m_sDirection) {
		case 0:
			m_dYExactPos -= m_dSpeed;
			for (PassengerCollection* passenger : m_vecPassenger) {
				if (passenger != nullptr) {
					passenger->getPassenger()->incYCenter(-m_dSpeed);
				}
			}
			break;
		case 1:
			dSpeedXY = m_dSpeed * 0.71;
			m_dXExactPos += dSpeedXY;
			m_dYExactPos -= dSpeedXY;
			for (PassengerCollection* passenger : m_vecPassenger) {
				if (passenger != nullptr) {
					passenger->getPassenger()->incXCenter(dSpeedXY);
					passenger->getPassenger()->incYCenter(-dSpeedXY);
				}
			}
			break;
		case 2:
			m_dXExactPos += m_dSpeed;
			for (PassengerCollection* passenger : m_vecPassenger) {
				if (passenger != nullptr) {
					passenger->getPassenger()->incXCenter(m_dSpeed);
				}
			}
			break;
		case 3:
			dSpeedXY = m_dSpeed * 0.71;
			m_dXExactPos += dSpeedXY;
			m_dYExactPos += dSpeedXY;
			for (PassengerCollection* passenger : m_vecPassenger) {
				if (passenger != nullptr) {
					passenger->getPassenger()->incXCenter(dSpeedXY);
					passenger->getPassenger()->incYCenter(dSpeedXY);
				}
			}
			break;
		case 4:
			m_dYExactPos += m_dSpeed;
			for (PassengerCollection* passenger : m_vecPassenger) {
				if (passenger != nullptr) {
					passenger->getPassenger()->incYCenter(m_dSpeed);
				}
			}
			break;
		case 5:
			dSpeedXY = m_dSpeed * 0.71;
			m_dXExactPos -= dSpeedXY;
			m_dYExactPos += dSpeedXY;
			for (PassengerCollection* passenger : m_vecPassenger) {
				if (passenger != nullptr) {
					passenger->getPassenger()->incXCenter(-dSpeedXY);
					passenger->getPassenger()->incYCenter(dSpeedXY);
				}
			}
			break;
		case 6:
			m_dXExactPos -= m_dSpeed;
			for (PassengerCollection* passenger : m_vecPassenger) {
				if (passenger != nullptr) {
					passenger->getPassenger()->incXCenter(-m_dSpeed);
				}
			}
			break;
		case 7:
			dSpeedXY = m_dSpeed * 0.71;
			m_dXExactPos -= dSpeedXY;
			m_dYExactPos -= dSpeedXY;
			for (PassengerCollection* passenger : m_vecPassenger) {
				if (passenger != nullptr) {
					passenger->getPassenger()->incXCenter(-dSpeedXY);
					passenger->getPassenger()->incYCenter(-dSpeedXY);
				}
			}
			break;
		default:
			printf("!! Error @ Train.cpp virtDoUpdate() - invalid direction\n");
			break;
		}
	}

	m_iCurrentScreenX = m_dXExactPos;
	m_iCurrentScreenY = m_dYExactPos;
}

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
				oPassenger->getPassenger()->setColor(m_uiPassengerColor);
				oPassenger->getPassenger()->setXCenter(m_iCurrentScreenX + m_vecPassengerPos[i * 2]);
				oPassenger->getPassenger()->setYCenter(m_iCurrentScreenY + m_vecPassengerPos[i * 2 + 1]);
				m_vecPassenger[i] = oPassenger;
				m_iPassengerCount++;
				return;
			}
		}
		printf("!! Error @ Train.cpp Carriage::addPassenger() - m_iPassengerCount said there are still places, but failed to put the passenger into the carriage\n");
	}

}

int Carriage::findFirstPassengerByType(short sType)
{
	for (int i = 0; i < m_iMaxNumOfPassengers; i++) {
		if (m_vecPassenger[i] != nullptr && m_vecPassenger[i]->getType() == sType) {
			return i;
		}
	}
	return -1;
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

double Carriage::getXExactPos()
{
	return m_dXExactPos;
}

double Carriage::getYExactPos()
{
	return m_dYExactPos;
}

void Carriage::setExactPos(double dX, double dY)
{
	for (PassengerCollection* passenger : m_vecPassenger) {
		if (passenger != nullptr) {
			passenger->getPassenger()->incXCenter(dX - m_dXExactPos);
			passenger->getPassenger()->incYCenter(dY - m_dYExactPos);
		}
	}
	m_dXExactPos = dX;
	m_dYExactPos = dY;
	m_iCurrentScreenX = dX;
	m_iCurrentScreenY = dY;
}

double Carriage::getSpeed()
{
	return m_dSpeed;
}

short Carriage::getDirection()
{
	return m_sDirection;
}

void Carriage::setDirection(short sDirection)
{
	m_sDirection = sDirection;
}

void Carriage::setIsRun(bool bIsRun)
{
	m_bIsRun = bIsRun;
}

bool Carriage::getIsRun()
{
	return m_bIsRun;
}

std::vector<PassengerCollection*> Carriage::getPassengerList()
{
	return m_vecPassenger;
}

void Carriage::setPassengerList(std::vector<PassengerCollection*> p, int i)
{
	m_vecPassenger = p;
	m_iPassengerCount = i;
}

void CarriageHead::virtDraw()
{
	if (m_sDirection == 0 || m_sDirection == 4) {
		drawForegroundRectangle0();
		if (m_sDirection == 0) {
			getEngine()->drawForegroundOval(
				m_iCurrentScreenX - m_iWidth / 2, m_iCurrentScreenY - m_iLength / 2 - m_iLength / 5,
				m_iCurrentScreenX + m_iWidth / 2, m_iCurrentScreenY - m_iLength / 2 + m_iLength / 5,
				m_uiColor);
		}
		else {
			getEngine()->drawForegroundOval(
				m_iCurrentScreenX - m_iWidth / 2, m_iCurrentScreenY + m_iLength / 2 - m_iLength / 5,
				m_iCurrentScreenX + m_iWidth / 2, m_iCurrentScreenY + m_iLength / 2 + m_iLength / 5,
				m_uiColor);
		}
	}
	else if (m_sDirection == 2 || m_sDirection == 6) {
		drawForegroundRectangle90();
		if (m_sDirection == 2) {
			getEngine()->drawForegroundOval(
				m_iCurrentScreenX + m_iLength / 2 - m_iWidth / 2, m_iCurrentScreenY - m_iWidth / 2,
				m_iCurrentScreenX + m_iLength / 2 + m_iWidth / 2, m_iCurrentScreenY + m_iWidth / 2,
				m_uiColor);
		}
		else {
			getEngine()->drawForegroundOval(
				m_iCurrentScreenX - m_iLength / 2 - m_iWidth / 2, m_iCurrentScreenY - m_iWidth / 2,
				m_iCurrentScreenX - m_iLength / 2 + m_iWidth / 2, m_iCurrentScreenY + m_iWidth / 2,
				m_uiColor);
		}
	}
	else if (m_sDirection == 1 || m_sDirection == 5) {
		drawForegroundRectangle45();
		if (m_sDirection == 1) {
			getEngine()->drawForegroundOval(
				m_iCurrentScreenX + m_iLength / 2 * 0.707 - m_iWidth / 2 + 1, m_iCurrentScreenY - m_iLength / 2 * 0.707 - m_iWidth / 2,
				m_iCurrentScreenX + m_iLength / 2 * 0.707 + m_iWidth / 2, m_iCurrentScreenY - m_iLength / 2 * 0.707 + m_iWidth / 2,
				m_uiColor);
		}
		else {
			getEngine()->drawForegroundOval(
				m_iCurrentScreenX - m_iLength / 2 * 0.707 - m_iWidth / 2 + 1, m_iCurrentScreenY + m_iLength / 2 * 0.707 - m_iWidth / 2,
				m_iCurrentScreenX - m_iLength / 2 * 0.707 + m_iWidth / 2, m_iCurrentScreenY + m_iLength / 2 * 0.707 + m_iWidth / 2,
				m_uiColor);
		}
	}
	else {
		drawForegroundRectangle135();
		if (m_sDirection == 3) {
			getEngine()->drawForegroundOval(
				m_iCurrentScreenX + m_iLength / 2 * 0.707 - m_iWidth / 2, m_iCurrentScreenY + m_iLength / 2 * 0.707 - m_iWidth / 2,
				m_iCurrentScreenX + m_iLength / 2 * 0.707 + m_iWidth / 2, m_iCurrentScreenY + m_iLength / 2 * 0.707 + m_iWidth / 2,
				m_uiColor);
		}
		else {
			getEngine()->drawForegroundOval(
				m_iCurrentScreenX - m_iLength / 2 * 0.707 - m_iWidth / 2, m_iCurrentScreenY - m_iLength / 2 * 0.707 - m_iWidth / 2,
				m_iCurrentScreenX - m_iLength / 2 * 0.707 + m_iWidth / 2, m_iCurrentScreenY - m_iLength / 2 * 0.707 + m_iWidth / 2,
				m_uiColor);
		}
	}

	drawPassenger();
}

void CarriageMain::virtDraw()
{
	if (m_sDirection == 0 || m_sDirection == 4) drawForegroundRectangle0();
	else if (m_sDirection == 2 || m_sDirection == 6) drawForegroundRectangle90();
	else if (m_sDirection == 1 || m_sDirection == 5) drawForegroundRectangle45();
	else drawForegroundRectangle135();

	drawPassenger();
}

void CarriageHeadFast::virtDraw()
{
	if (m_sDirection == 0 || m_sDirection == 4) {
		drawForegroundRectangle0();
		if (m_sDirection == 0) {
			getEngine()->drawForegroundTriangle(
				m_iCurrentScreenX, m_iCurrentScreenY - m_iLength / 2 - m_iLength / 4,
				m_iCurrentScreenX + m_iWidth / 2, m_iCurrentScreenY - m_iLength / 2,
				m_iCurrentScreenX - m_iWidth / 2, m_iCurrentScreenY - m_iLength / 2,
				m_uiColor);
		}
		else {
			getEngine()->drawForegroundTriangle(
				m_iCurrentScreenX, m_iCurrentScreenY + m_iLength / 2 + m_iLength / 4,
				m_iCurrentScreenX - m_iWidth / 2, m_iCurrentScreenY + m_iLength / 2,
				m_iCurrentScreenX + m_iWidth / 2, m_iCurrentScreenY + m_iLength / 2,
				m_uiColor);
		}
	}
	else if (m_sDirection == 2 || m_sDirection == 6) {
		drawForegroundRectangle90();
		if (m_sDirection == 2) {
			getEngine()->drawForegroundTriangle(
				m_iCurrentScreenX + m_iLength / 2 + m_iLength / 4, m_iCurrentScreenY,
				m_iCurrentScreenX + m_iLength / 2, m_iCurrentScreenY + m_iWidth / 2,
				m_iCurrentScreenX + m_iLength / 2, m_iCurrentScreenY - m_iWidth / 2,
				m_uiColor);
		}
		else {
			getEngine()->drawForegroundTriangle(
				m_iCurrentScreenX - m_iLength / 2 - m_iLength / 4, m_iCurrentScreenY,
				m_iCurrentScreenX - m_iLength / 2, m_iCurrentScreenY - m_iWidth / 2,
				m_iCurrentScreenX - m_iLength / 2, m_iCurrentScreenY + m_iWidth / 2,
				m_uiColor);
		}
	}
	else if (m_sDirection == 1 || m_sDirection == 5) {
		drawForegroundRectangle45();
		if (m_sDirection == 1) {
			getEngine()->drawForegroundTriangle(
				m_iCurrentScreenX + m_iLength * 3 / 4 * 0.707, m_iCurrentScreenY - m_iLength * 3 / 4 * 0.707,
				m_iCurrentScreenX + (m_iLength - m_iWidth) / 2 * 0.707, m_iCurrentScreenY - (m_iLength + m_iWidth) / 2 * 0.707,
				m_iCurrentScreenX + (m_iLength + m_iWidth) / 2 * 0.707, m_iCurrentScreenY - (m_iLength - m_iWidth) / 2 * 0.707,
				m_uiColor);
		}
		else {
			getEngine()->drawForegroundTriangle(
				m_iCurrentScreenX - m_iLength * 3 / 4 * 0.707, m_iCurrentScreenY + m_iLength * 3 / 4 * 0.707,
				m_iCurrentScreenX - (m_iLength - m_iWidth) / 2 * 0.707, m_iCurrentScreenY + (m_iLength + m_iWidth) / 2 * 0.707,
				m_iCurrentScreenX - (m_iLength + m_iWidth) / 2 * 0.707, m_iCurrentScreenY + (m_iLength - m_iWidth) / 2 * 0.707,
				m_uiColor);
		}
	}
	else {
		drawForegroundRectangle135();
		if (m_sDirection == 3) {
			getEngine()->drawForegroundTriangle(
				m_iCurrentScreenX + m_iLength * 3 / 4 * 0.707, m_iCurrentScreenY + m_iLength * 3 / 4 * 0.707,
				m_iCurrentScreenX + (m_iLength + m_iWidth) / 2 * 0.707, m_iCurrentScreenY + (m_iLength - m_iWidth) / 2 * 0.707,
				m_iCurrentScreenX + (m_iLength - m_iWidth) / 2 * 0.707, m_iCurrentScreenY + (m_iLength + m_iWidth) / 2 * 0.707,
				m_uiColor);
		}
		else {
			getEngine()->drawForegroundTriangle(
				m_iCurrentScreenX - m_iLength * 3 / 4 * 0.707, m_iCurrentScreenY - m_iLength * 3 / 4 * 0.707,
				m_iCurrentScreenX - (m_iLength + m_iWidth) / 2 * 0.707, m_iCurrentScreenY - (m_iLength - m_iWidth) / 2 * 0.707,
				m_iCurrentScreenX - (m_iLength - m_iWidth) / 2 * 0.707, m_iCurrentScreenY - (m_iLength + m_iWidth) / 2 * 0.707,
				m_uiColor);
		}
	}

	drawPassenger();
}

void CarriageHeadIntelli::virtDraw()
{
	if (m_sDirection == 0 || m_sDirection == 4) {
		drawForegroundRectangle0();
		if (m_sDirection == 0) {
			getEngine()->drawForegroundTriangle(
				m_iCurrentScreenX, m_iCurrentScreenY - m_iLength / 2 - m_iLength / 4,
				m_iCurrentScreenX + m_iWidth / 2, m_iCurrentScreenY - m_iLength / 2,
				m_iCurrentScreenX - m_iWidth / 2, m_iCurrentScreenY - m_iLength / 2,
				m_uiSpecialColor);
		}
		else {
			getEngine()->drawForegroundTriangle(
				m_iCurrentScreenX, m_iCurrentScreenY + m_iLength / 2 + m_iLength / 4,
				m_iCurrentScreenX - m_iWidth / 2, m_iCurrentScreenY + m_iLength / 2,
				m_iCurrentScreenX + m_iWidth / 2, m_iCurrentScreenY + m_iLength / 2,
				m_uiSpecialColor);
		}
	}
	else if (m_sDirection == 2 || m_sDirection == 6) {
		drawForegroundRectangle90();
		if (m_sDirection == 2) {
			getEngine()->drawForegroundTriangle(
				m_iCurrentScreenX + m_iLength / 2 + m_iLength / 4, m_iCurrentScreenY,
				m_iCurrentScreenX + m_iLength / 2, m_iCurrentScreenY + m_iWidth / 2,
				m_iCurrentScreenX + m_iLength / 2, m_iCurrentScreenY - m_iWidth / 2,
				m_uiSpecialColor);
		}
		else {
			getEngine()->drawForegroundTriangle(
				m_iCurrentScreenX - m_iLength / 2 - m_iLength / 4, m_iCurrentScreenY,
				m_iCurrentScreenX - m_iLength / 2, m_iCurrentScreenY - m_iWidth / 2,
				m_iCurrentScreenX - m_iLength / 2, m_iCurrentScreenY + m_iWidth / 2,
				m_uiSpecialColor);
		}
	}
	else if (m_sDirection == 1 || m_sDirection == 5) {
		drawForegroundRectangle45();
		if (m_sDirection == 1) {
			getEngine()->drawForegroundTriangle(
				m_iCurrentScreenX + m_iLength * 3 / 4 * 0.707, m_iCurrentScreenY - m_iLength * 3 / 4 * 0.707,
				m_iCurrentScreenX + (m_iLength - m_iWidth) / 2 * 0.707, m_iCurrentScreenY - (m_iLength + m_iWidth) / 2 * 0.707,
				m_iCurrentScreenX + (m_iLength + m_iWidth) / 2 * 0.707, m_iCurrentScreenY - (m_iLength - m_iWidth) / 2 * 0.707,
				m_uiSpecialColor);
		}
		else {
			getEngine()->drawForegroundTriangle(
				m_iCurrentScreenX - m_iLength * 3 / 4 * 0.707, m_iCurrentScreenY + m_iLength * 3 / 4 * 0.707,
				m_iCurrentScreenX - (m_iLength - m_iWidth) / 2 * 0.707, m_iCurrentScreenY + (m_iLength + m_iWidth) / 2 * 0.707,
				m_iCurrentScreenX - (m_iLength + m_iWidth) / 2 * 0.707, m_iCurrentScreenY + (m_iLength - m_iWidth) / 2 * 0.707,
				m_uiSpecialColor);
		}
	}
	else {
		drawForegroundRectangle135();
		if (m_sDirection == 3) {
			getEngine()->drawForegroundTriangle(
				m_iCurrentScreenX + m_iLength * 3 / 4 * 0.707, m_iCurrentScreenY + m_iLength * 3 / 4 * 0.707,
				m_iCurrentScreenX + (m_iLength + m_iWidth) / 2 * 0.707, m_iCurrentScreenY + (m_iLength - m_iWidth) / 2 * 0.707,
				m_iCurrentScreenX + (m_iLength - m_iWidth) / 2 * 0.707, m_iCurrentScreenY + (m_iLength + m_iWidth) / 2 * 0.707,
				m_uiSpecialColor);
		}
		else {
			getEngine()->drawForegroundTriangle(
				m_iCurrentScreenX - m_iLength * 3 / 4 * 0.707, m_iCurrentScreenY - m_iLength * 3 / 4 * 0.707,
				m_iCurrentScreenX - (m_iLength + m_iWidth) / 2 * 0.707, m_iCurrentScreenY - (m_iLength - m_iWidth) / 2 * 0.707,
				m_iCurrentScreenX - (m_iLength - m_iWidth) / 2 * 0.707, m_iCurrentScreenY - (m_iLength + m_iWidth) / 2 * 0.707,
				m_uiSpecialColor);
		}
	}

	drawPassenger();
}

Carriage* CarriageCollection::getCarriage() {
	return m_oCarriage;
}

void CarriageCollection::resetCooldown()
{
	m_cooldown = 3;
}

bool CarriageCollection::isCooldown()
{
	if (m_cooldown == 0) return false;
	m_cooldown -= 1;
	return true;
}

bool Train::addCarriage(int iMaxNumberOfPassengers, int iLength)
{
	if (m_iCarriageCount >= MAX_CARRIAGES_IN_TRAIN) {
		printf("## Debug - a train can only have %d carriages in max\n", MAX_CARRIAGES_IN_TRAIN);
		return false;
	}
	else {
		short direction = m_vecCarriage[0]->getCarriage()->getDirection();
		double dXCenter = m_vecCarriage[0]->getCarriage()->getXExactPos();
		double dYCenter = m_vecCarriage[0]->getCarriage()->getYExactPos();
		double distance = m_iCarriageCount * m_iDist + m_vecCarriage[0]->getCarriage()->getLength() / 2
			+ (m_iCarriageCount - 1) * ((iLength == -1) ? 30 : iLength) + ((iLength == -1) ? 30 : iLength) / 2;
		switch (direction)
		{
		case 0:
			dYCenter += distance;
			break;
		case 4:
			dYCenter -= distance;
			break;
		case 2:
			dXCenter -= distance;
			break;
		case 6:
			dXCenter += distance;
			break;
		case 1:
			dXCenter -= distance * 0.707;
			dYCenter += distance * 0.707;
			break;
		case 3:
			dXCenter -= distance * 0.707;
			dYCenter -= distance * 0.707;
			break;
		case 5:
			dXCenter += distance * 0.707;
			dYCenter -= distance * 0.707;
			break;
		case 7:
			dXCenter += distance * 0.707;
			dYCenter += distance * 0.707;
			break;
		default:
			break;
		}
		CarriageCollection* oCarriage = new CarriageCollection(3, m_pEngine, dXCenter, dYCenter, m_uiColor, m_dSpeed, direction,
			0, iMaxNumberOfPassengers, 20, iLength);
		oCarriage->getCarriage()->setIsRun(m_vecCarriage[0]->getCarriage()->getIsRun());
		m_pEngine->appendObjectToArray(oCarriage->getCarriage());
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

int Train::findFirstPassengerByType(short sType)
{
	int iNumOfPassengersInPrevCarriages = 0;
	for (int i = 0; i < size(m_vecCarriage); i++) {
		int iPassengerInCarriage = m_vecCarriage[i]->getCarriage()->findFirstPassengerByType(sType);
		if (iPassengerInCarriage != -1) return iPassengerInCarriage + iNumOfPassengersInPrevCarriages;
		iNumOfPassengersInPrevCarriages += m_vecCarriage[i]->getCarriage()->getMaxNumOfPassengers();
	}
	return -1;
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

bool Train::getIsRun()
{
	return m_bIsRun;
}

void Train::startTrain()
{
	m_bIsRun = true;
	for (CarriageCollection* carriage : m_vecCarriage) {
		carriage->getCarriage()->setIsRun(true);
	}
}

void Train::stopTrain()
{
	m_bIsRun = false;
	for (CarriageCollection* carriage : m_vecCarriage) {
		carriage->getCarriage()->setIsRun(false);
	}
}

void TrainNormal::addHead(int iMaxNumberOfPassengers, int iLength)
{
	if (m_iCarriageCount >= MAX_CARRIAGES_IN_TRAIN) {
		printf("!! Error @ Train.cpp TrainNormal::addHead() - add a head will not result in max carriage count\n");
	}
	else {
		CarriageCollection* oCarriage = new CarriageCollection(0, m_pEngine, m_dXCenterHead, m_dYCenterHead, m_uiColor, m_dSpeed, m_sDirection,
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
		CarriageCollection* oCarriage = new CarriageCollection(1, m_pEngine, m_dXCenterHead, m_dYCenterHead, m_uiColor, m_dSpeed, m_sDirection,
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
		CarriageCollection* oCarriage = new CarriageCollection(2, m_pEngine, m_dXCenterHead, m_dYCenterHead, m_uiColor, m_dSpeed, m_sDirection,
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

int TrainCollection::getType()
{
	return m_type;
}

int TrainCollection::getId()
{
	return m_id;
}

void TrainCollection::setId(int id)
{
	m_id = id;
}

void TrainCollection::resetStopCooldown()
{
	m_StopCooldown = STOP_TIME;
}

bool TrainCollection::isStopCooldown()
{
	if (m_StopCooldown <= 0) {
		if (m_StopCooldown == 0) {
			m_StopCooldown -= 1;
			m_oTrain->startTrain();
			resetCooldown();
		}
		return false;
	}
	m_StopCooldown -= 1;
	return true;
}

void TrainCollection::resetCooldown()
{
	m_cooldown = 3;
}

bool TrainCollection::isCooldown()
{
	if (m_cooldown == 0) return false;
	m_cooldown -= 1;
	return true;
}
