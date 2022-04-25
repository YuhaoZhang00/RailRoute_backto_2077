#pragma once
#include "header.h"
#include "DisplayableObject.h"
#include "BaseEngine.h"
#include "Passenger.h"
#include "Station.h"
#include <vector>

class StationMap
{
private:
	BaseEngine* m_pEngine;

	std::vector<StationCollection*> m_vecStation;

	long long m_difficultyCount = 50000;
	int m_stationCount = 0;

public:
	StationMap(BaseEngine* pEngine)
		: m_pEngine(pEngine)
	{}

	~StationMap() {
		for (StationCollection* station : m_vecStation) {
			delete station;
		}
	}

	void addStation(StationCollection* s);
	void addStation(int sId, short sType, int iX, int iY);
	void addRandomStation(int sId);
	std::vector<StationCollection*> getStationList();
	StationCollection* getStation(int iIndex);

	void drawInitialise();
	void update();
};

