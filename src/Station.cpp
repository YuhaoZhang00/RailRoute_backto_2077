#include "header.h"
#include "Station.h"
#include "BaseEngine.h"
#include "Constant.h"

void Station::virtDoUpdate(int iCurrentTime)
{
	if (m_bIsAngry) {
		++m_iAngryValue;
	}
	else {
		if (m_iAngryValue != 0) --m_iAngryValue;
	}
}

void Station::addPassenger(PassengerCollection* oPassenger)
{
	if (m_iPassengerCount < MAX_PASSENGERS_IN_STATION) {
		oPassenger->getPassenger()->setXCenter(m_iCurrentScreenX + 30 + m_iPassengerCount % PASSENGER_IN_STATION_X * 10);
		oPassenger->getPassenger()->setYCenter(m_iCurrentScreenY - 10 + m_iPassengerCount / PASSENGER_IN_STATION_X * 10);
		m_vecPassenger.emplace_back(oPassenger);
		m_iPassengerCount++;
		if (m_iPassengerCount > MAX_PASSENGERS_IN_STATION_BEFORE_ANGER) {
			//printf("## Debug - Anger!\n");
			m_bIsAngry = true;
		}
	}
	else {
		//printf("## Debug - too many passengers in station, negleting incoming one\n");
	}

}

int Station::findFirstPassengerOfType(short sType)
{
	for (int i = 0; i < m_iPassengerCount; i++) {
		if (m_vecPassenger[i]->getType() == sType) {
			return i;
		}
	}
	return -1;
}

short Station::removeFirstPassenger()
{
	if (isEmpty()) {
		printf("!! Error @ Station.cpp removeFirstPassenger() - invalid remove of passenger from station\n");
		return -1;
	}
	else {
		short sType = m_vecPassenger[0]->getType();
		delete m_vecPassenger[0];
		m_vecPassenger.erase(m_vecPassenger.begin());
		m_iPassengerCount--;
		for (int i = 0; i < m_iPassengerCount; i++) {
			m_vecPassenger[i]->getPassenger()->setXCenter(m_iCurrentScreenX + 30 + i % PASSENGER_IN_STATION_X * 10);
			m_vecPassenger[i]->getPassenger()->setYCenter(m_iCurrentScreenY - 10 + i / PASSENGER_IN_STATION_X * 10);
		}
		if (m_iPassengerCount <= MAX_PASSENGERS_IN_STATION_BEFORE_ANGER) {
			m_bIsAngry = false;
		}
		return sType;
	}
}

std::vector<PassengerCollection*> Station::getPassengerList()
{
	return m_vecPassenger;
}

void Station::removePassenger(int iIndex)
{
	if (iIndex < 0 || iIndex >= m_iPassengerCount) {
		printf("!! Error @ Station.cpp removePassenger() - invalid remove of passenger from station\n");
	}
	else {
		delete m_vecPassenger[iIndex];
		m_vecPassenger.erase(m_vecPassenger.begin() + iIndex);
		m_iPassengerCount--;
		for (int i = iIndex; i < m_iPassengerCount; i++) {
			m_vecPassenger[i]->getPassenger()->setXCenter(m_iCurrentScreenX + 30 + i % PASSENGER_IN_STATION_X * 10);
			m_vecPassenger[i]->getPassenger()->setYCenter(m_iCurrentScreenY - 10 + i / PASSENGER_IN_STATION_X * 10);
		}
	}
	if (m_iPassengerCount <= MAX_PASSENGERS_IN_STATION_BEFORE_ANGER) {
		m_bIsAngry = false;
	}
}

bool Station::isEmpty()
{
	return (m_iPassengerCount == 0);
}

bool Station::getIsAngry()
{
	return m_bIsAngry;
}

int Station::getAngryValue()
{
	return m_iAngryValue;
}

void Station::setIsAngry(bool b)
{
	m_bIsAngry = b;
}

void Station::setAngryValue(int i)
{
	m_iAngryValue = i;
}

void StationCircle::virtDraw()
{
	if (m_iAngryValue != 0) {
		double percentage = std::min(1.0, m_iAngryValue * 1.0 / 2000);
		//printf("%d %f\n", m_iAngryValue, percentage);
		getEngine()->drawForegroundOval(
			m_iCurrentScreenX - m_iSize / 2 * (1 + percentage), m_iCurrentScreenY - m_iSize / 2 * (1 + percentage),
			m_iCurrentScreenX + m_iSize / 2 * (1 + percentage), m_iCurrentScreenY + m_iSize / 2 * (1 + percentage),
			((0xFF << 16) + ((int)(0xFF * (1 - percentage)) << 8) + (0xFF * (1 - percentage))));
	}

	getEngine()->drawForegroundOval(
		m_iCurrentScreenX - m_iSize / 2, m_iCurrentScreenY - m_iSize / 2,
		m_iCurrentScreenX + m_iSize / 2, m_iCurrentScreenY + m_iSize / 2,
		m_uiColor);
	getEngine()->drawForegroundOval(
		m_iCurrentScreenX - m_iSize / 2 + m_iBorderWidth, m_iCurrentScreenY - m_iSize / 2 + m_iBorderWidth,
		m_iCurrentScreenX + m_iSize / 2 - m_iBorderWidth, m_iCurrentScreenY + m_iSize / 2 - m_iBorderWidth,
		m_uiInnerColor);

	for (PassengerCollection* passenger : m_vecPassenger) {
		passenger->getPassenger()->virtDraw();
	}
}

void StationSquare::virtDraw()
{
	if (m_iAngryValue != 0) {
		double percentage = std::min(1.0, m_iAngryValue * 1.0 / 2000);
		//printf("%d %f\n", m_iAngryValue, percentage);
		getEngine()->drawForegroundOval(
			m_iCurrentScreenX - m_iSize / 2 * (1 + percentage), m_iCurrentScreenY - m_iSize / 2 * (1 + percentage),
			m_iCurrentScreenX + m_iSize / 2 * (1 + percentage), m_iCurrentScreenY + m_iSize / 2 * (1 + percentage),
			((0xFF << 16) + ((int)(0xFF * (1 - percentage)) << 8) + (0xFF * (1 - percentage))));
	}

	getEngine()->drawForegroundRectangle(
		m_iCurrentScreenX - m_iSize * 2 / 5, m_iCurrentScreenY - m_iSize * 2 / 5,
		m_iCurrentScreenX + m_iSize * 2 / 5, m_iCurrentScreenY + m_iSize * 2 / 5,
		m_uiColor);
	getEngine()->drawForegroundRectangle(
		m_iCurrentScreenX - m_iSize * 2 / 5 + m_iBorderWidth, m_iCurrentScreenY - m_iSize * 2 / 5 + m_iBorderWidth,
		m_iCurrentScreenX + m_iSize * 2 / 5 - m_iBorderWidth, m_iCurrentScreenY + m_iSize * 2 / 5 - m_iBorderWidth,
		m_uiInnerColor);

	for (PassengerCollection* passenger : m_vecPassenger) {
		passenger->getPassenger()->virtDraw();
	}
}

//void StationHexagon::virtDraw()
//{
//	getEngine()->drawForegroundPolygon(
//		m_iCurrentScreenX - m_iSize / 4, m_iCurrentScreenY - m_iSize * 0.433, // 0.433 = sqrt(3)/4
//		m_iCurrentScreenX + m_iSize / 4, m_iCurrentScreenY - m_iSize * 0.433,
//		m_iCurrentScreenX + m_iSize / 2, m_iCurrentScreenY,
//		m_iCurrentScreenX + m_iSize / 4, m_iCurrentScreenY + m_iSize * 0.433,
//		m_iCurrentScreenX - m_iSize / 4, m_iCurrentScreenY + m_iSize * 0.433,
//		m_iCurrentScreenX - m_iSize / 2, m_iCurrentScreenY,
//		m_uiColor);
//	getEngine()->drawForegroundPolygon(
//		m_iCurrentScreenX - m_iSize / 4 + m_iBorderWidth / 1.732, m_iCurrentScreenY - m_iSize * 0.433 + m_iBorderWidth, // 0.433 = sqrt(3)/4  1.732 = sqrt(3)
//		m_iCurrentScreenX + m_iSize / 4 - m_iBorderWidth / 1.732, m_iCurrentScreenY - m_iSize * 0.433 + m_iBorderWidth,
//		m_iCurrentScreenX + m_iSize / 2 - m_iBorderWidth * 2 / 1.732, m_iCurrentScreenY,
//		m_iCurrentScreenX + m_iSize / 4 - m_iBorderWidth / 1.732, m_iCurrentScreenY + m_iSize * 0.433 - m_iBorderWidth,
//		m_iCurrentScreenX - m_iSize / 4 + m_iBorderWidth / 1.732, m_iCurrentScreenY + m_iSize * 0.433 - m_iBorderWidth,
//		m_iCurrentScreenX - m_iSize / 2 + m_iBorderWidth * 2 / 1.732, m_iCurrentScreenY,
//		m_uiInnerColor);
//}

void StationDiamond::virtDraw()
{
	if (m_iAngryValue != 0) {
		double percentage = std::min(1.0, m_iAngryValue * 1.0 / 2000);
		//printf("%d %f\n", m_iAngryValue, percentage);
		getEngine()->drawForegroundOval(
			m_iCurrentScreenX - m_iSize / 2 * (1 + percentage), m_iCurrentScreenY - m_iSize / 2 * (1 + percentage),
			m_iCurrentScreenX + m_iSize / 2 * (1 + percentage), m_iCurrentScreenY + m_iSize / 2 * (1 + percentage),
			((0xFF << 16) + ((int)(0xFF * (1 - percentage)) << 8) + (0xFF * (1 - percentage))));
	}

	getEngine()->drawForegroundPolygon(
		m_iCurrentScreenX, m_iCurrentScreenY - m_iSize / 2,
		m_iCurrentScreenX + m_iSize / 2, m_iCurrentScreenY,
		m_iCurrentScreenX, m_iCurrentScreenY + m_iSize / 2,
		m_iCurrentScreenX - m_iSize / 2, m_iCurrentScreenY,
		m_uiColor);
	getEngine()->drawForegroundPolygon(
		m_iCurrentScreenX, m_iCurrentScreenY - m_iSize / 2 + m_iBorderWidth * 1.414, // 1.414 = sqrt(2)
		m_iCurrentScreenX + m_iSize / 2 - m_iBorderWidth * 1.414, m_iCurrentScreenY,
		m_iCurrentScreenX, m_iCurrentScreenY + m_iSize / 2 - m_iBorderWidth * 1.414,
		m_iCurrentScreenX - m_iSize / 2 + m_iBorderWidth * 1.414, m_iCurrentScreenY,
		m_uiInnerColor);

	for (PassengerCollection* passenger : m_vecPassenger) {
		passenger->getPassenger()->virtDraw();
	}
}

void StationTriangle::virtDraw()
{
	if (m_iAngryValue != 0) {
		double percentage = std::min(1.0, m_iAngryValue * 1.0 / 2000);
		//printf("%d %f\n", m_iAngryValue, percentage);
		getEngine()->drawForegroundOval(
			m_iCurrentScreenX - m_iSize / 2 * (1 + percentage), m_iCurrentScreenY - m_iSize / 2 * (1 + percentage),
			m_iCurrentScreenX + m_iSize / 2 * (1 + percentage), m_iCurrentScreenY + m_iSize / 2 * (1 + percentage),
			((0xFF << 16) + ((int)(0xFF * (1 - percentage)) << 8) + (0xFF * (1 - percentage))));
	}

	getEngine()->drawForegroundTriangle(
		m_iCurrentScreenX, m_iCurrentScreenY - m_iSize / 2,
		m_iCurrentScreenX + m_iSize / 2, m_iCurrentScreenY + m_iSize * 0.366, // 0.366 = sqrt(3)/2 - 0.5
		m_iCurrentScreenX - m_iSize / 2, m_iCurrentScreenY + m_iSize * 0.366,
		m_uiColor);
	getEngine()->drawForegroundTriangle(
		m_iCurrentScreenX, m_iCurrentScreenY - m_iSize / 2 + m_iBorderWidth * 2,
		m_iCurrentScreenX + m_iSize / 2 - m_iBorderWidth * 1.732, m_iCurrentScreenY + m_iSize * 0.366 - m_iBorderWidth, // 0.866 = sqrt(3)/2  1.732 = sqrt(3)
		m_iCurrentScreenX - m_iSize / 2 + m_iBorderWidth * 1.732, m_iCurrentScreenY + m_iSize * 0.366 - m_iBorderWidth,
		m_uiInnerColor);

	for (PassengerCollection* passenger : m_vecPassenger) {
		passenger->getPassenger()->virtDraw();
	}
}

void StationInvTriangle::virtDraw()
{
	if (m_iAngryValue != 0) {
		double percentage = std::min(1.0, m_iAngryValue * 1.0 / 2000);
		//printf("%d %f\n", m_iAngryValue, percentage);
		getEngine()->drawForegroundOval(
			m_iCurrentScreenX - m_iSize / 2 * (1 + percentage), m_iCurrentScreenY - m_iSize / 2 * (1 + percentage),
			m_iCurrentScreenX + m_iSize / 2 * (1 + percentage), m_iCurrentScreenY + m_iSize / 2 * (1 + percentage),
			((0xFF << 16) + ((int)(0xFF * (1 - percentage)) << 8) + (0xFF * (1 - percentage))));
	}

	getEngine()->drawForegroundTriangle(
		m_iCurrentScreenX, m_iCurrentScreenY + m_iSize / 2,
		m_iCurrentScreenX - m_iSize / 2, m_iCurrentScreenY - m_iSize * 0.366, // 0.366 = sqrt(3)/2 - 0.5
		m_iCurrentScreenX + m_iSize / 2, m_iCurrentScreenY - m_iSize * 0.366,
		m_uiColor);
	getEngine()->drawForegroundTriangle(
		m_iCurrentScreenX, m_iCurrentScreenY + m_iSize / 2 - m_iBorderWidth * 2,
		m_iCurrentScreenX - m_iSize / 2 + m_iBorderWidth * 1.732, m_iCurrentScreenY - m_iSize * 0.366 + m_iBorderWidth, // 0.366 = sqrt(3)/2 - 0.5  1.732 = sqrt(3)
		m_iCurrentScreenX + m_iSize / 2 - m_iBorderWidth * 1.732, m_iCurrentScreenY - m_iSize * 0.366 + m_iBorderWidth,
		m_uiInnerColor);

	for (PassengerCollection* passenger : m_vecPassenger) {
		passenger->getPassenger()->virtDraw();
	}
}

int StationFlower::dist(int x1, int y1, int x2, int y2)
{
	return static_cast<int>(sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
}

void StationFlower::virtDraw()
{
	if (m_iAngryValue != 0) {
		double percentage = std::min(1.0, m_iAngryValue * 1.0 / 2000);
		//printf("%d %f\n", m_iAngryValue, percentage);
		getEngine()->drawForegroundOval(
			m_iCurrentScreenX - m_iSize / 2 * (1 + percentage), m_iCurrentScreenY - m_iSize / 2 * (1 + percentage),
			m_iCurrentScreenX + m_iSize / 2 * (1 + percentage), m_iCurrentScreenY + m_iSize / 2 * (1 + percentage),
			((0xFF << 16) + ((int)(0xFF * (1 - percentage)) << 8) + (0xFF * (1 - percentage))));
	}

	for (int i = m_iCurrentScreenX - m_iSize / 2; i <= m_iCurrentScreenX + m_iSize / 2; i++) {
		for (int j = m_iCurrentScreenY - m_iSize / 2; j <= m_iCurrentScreenY + m_iSize / 2; j++) {
			if ((dist(i, j, m_iCurrentScreenX - m_iSize / 2, m_iCurrentScreenY + m_iSize / 2) < m_iSize * 0.95 &&
				dist(i, j, m_iCurrentScreenX + m_iSize / 2, m_iCurrentScreenY - m_iSize / 2) < m_iSize * 0.95) ||
				(dist(i, j, m_iCurrentScreenX - m_iSize / 2, m_iCurrentScreenY - m_iSize / 2) < m_iSize * 0.95 &&
					dist(i, j, m_iCurrentScreenX + m_iSize / 2, m_iCurrentScreenY + m_iSize / 2) < m_iSize * 0.95)) {
				getEngine()->setForegroundPixel(i, j, m_uiColor);
			}
		}
	}
	for (int i = m_iCurrentScreenX - m_iSize / 2; i <= m_iCurrentScreenX + m_iSize / 2; i++) {
		for (int j = m_iCurrentScreenY - m_iSize / 2; j <= m_iCurrentScreenY + m_iSize / 2; j++) {
			if ((dist(i, j, m_iCurrentScreenX - m_iSize / 2, m_iCurrentScreenY + m_iSize / 2) < m_iSize * 0.95 - m_iBorderWidth &&
				dist(i, j, m_iCurrentScreenX + m_iSize / 2, m_iCurrentScreenY - m_iSize / 2) < m_iSize * 0.95 - m_iBorderWidth) ||
				(dist(i, j, m_iCurrentScreenX - m_iSize / 2, m_iCurrentScreenY - m_iSize / 2) < m_iSize * 0.95 - m_iBorderWidth &&
					dist(i, j, m_iCurrentScreenX + m_iSize / 2, m_iCurrentScreenY + m_iSize / 2) < m_iSize * 0.95 - m_iBorderWidth)) {
				getEngine()->setForegroundPixel(i, j, m_uiInnerColor);
			}
		}
	}

	for (PassengerCollection* passenger : m_vecPassenger) {
		passenger->getPassenger()->virtDraw();
	}
}

Station* StationCollection::getStation()
{
	return m_oStation;
}

int StationCollection::getId()
{
	return m_id;
}

void StationCollection::setId(int id)
{
	m_id = id;
}

short StationCollection::getType()
{
	return m_sType;
}
