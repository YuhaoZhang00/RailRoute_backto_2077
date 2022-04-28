#include "header.h"
#include "StationMap.h"

bool StationMap::isNoStationTooClose(int iX, int iY)
{
	for (StationCollection* station : m_vecStation) {
		int xCenter = station->getStation()->getXCentre();
		int yCenter = station->getStation()->getYCentre();
		if ((iX <= xCenter + 150 && iX >= xCenter - 50) && (iY <= yCenter + 100 && iY >= yCenter - 100)) {
			return false;
		}
	}
	return true;
}

bool StationMap::isInMapBorder(int iX, int iY)
{
	if (iX >= 100 && iX <= 1200 && iY >= 100 && iY <= 600) return true;
	return false;
}

void StationMap::addStation(StationCollection* s)
{
	m_vecStation.emplace_back(s);
}

void StationMap::addStation(int sId, short sType, int iX, int iY)
{
	addStation(new StationCollection(sId, sType, m_pEngine, iX, iY));
}

void StationMap::addRandomStation(int sId)
{
	int x, y;
	do {
		x = rand() % 1100 + 100;
		y = rand() % 500 + 100;
	} while (!isNoStationTooClose(x, y));
	addStation(new StationCollection(sId, rand() % 6, m_pEngine, x, y));
}

void StationMap::addRandomStationInRectangle(int sId, int iX, int iY, int iWidth, int iHeight)
{
	int x, y, count = 0;
	do {
		x = rand() % iWidth + iX;
		y = rand() % iHeight + iY;
		++count;
	} while ((!isNoStationTooClose(x, y) || !isInMapBorder(x, y)) && count < 10);
	if (count == 10) {
		addRandomStation(sId);
		return;
	}
	addStation(new StationCollection(sId, rand() % 6, m_pEngine, x, y));
}

void StationMap::addRandomStationNearCurrent(int sId)
{
	int len = m_vecStation.size();
	for (int i = 0; i < len; i++) {
		int stationId = rand() % len;
		int x, y, count = 0;
		do {
			x = rand() % 400 + m_vecStation[stationId]->getStation()->getXCentre();
			y = rand() % 400 + m_vecStation[stationId]->getStation()->getYCentre();
			++count;
		} while ((!isNoStationTooClose(x, y) || !isInMapBorder(x, y)) && count < 10);
		if (count < 10) {
			addStation(new StationCollection(sId, rand() % 6, m_pEngine, x, y));
			return;
		}
	}
	addRandomStation(sId);
}

std::vector<StationCollection*> StationMap::getStationList()
{
	return m_vecStation;
}

StationCollection* StationMap::getStation(int iIndex)
{
	if (iIndex < 0 || iIndex >= m_vecStation.size()) {
		printf("!! Error @ StationMap.cpp getStation() - invalid index of station\n");
	}
	return m_vecStation[iIndex];
}

void StationMap::drawInitialise()
{
	for (StationCollection* station : m_vecStation) {
		m_pEngine->appendObjectToArray(station->getStation());
	}
}

void StationMap::update()
{
	++m_difficultyCount;

	for (StationCollection* station : m_vecStation) {
		int count = (m_difficultyCount / 50000) / (rand() % 1000 + 1);
		if (count > 5) count = 5;
		for (int i = 0; i < count; i++) {
			short sType = station->getType();
			short sTypePassenger;
			do {
				sTypePassenger = rand() % 6;
			} while (sTypePassenger == sType);
			station->getStation()->addPassenger(new PassengerCollection(sTypePassenger, m_pEngine));
		}
	}

	if (m_difficultyCount / 1000 > m_stationCount) {
		m_stationCount = m_difficultyCount / 1000;
		addRandomStationNearCurrent(m_stationCount);
		m_pEngine->appendObjectToArray(m_vecStation.back()->getStation());
	}
}
