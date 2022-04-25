#include "header.h"
#include "StationMap.h"

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
	// TODO: 不应该安排距离过近的车站
	addStation(new StationCollection(sId, rand()%6, m_pEngine, rand()%1100+100, rand() % 500 + 100));
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
		int count = (m_difficultyCount / 50000) / (rand() % 1000+1);
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
		addRandomStation(m_stationCount);
		m_pEngine->appendObjectToArray(m_vecStation.back()->getStation());
	}
}
