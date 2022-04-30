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
	int m_stationSize = 40;

	bool isNoStationTooClose(int iX, int iY);
	bool isInMapBorder(int iX, int iY);
	bool isNothingInBackground(int iX, int iY); // collision detection

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
	void addRandomStationInRectangle(int sId, int iX, int iY, int iWidth, int iHeight);
	void addRandomStationNearCurrent(int sId);
	void addRandomStationCertainType(int sId, short sType);
	void addStationInRectangle(int sId, short sType, int iX, int iY, int iWidth, int iHeight);
	void addStationNearCurrent(int sId, short sType);
	std::vector<StationCollection*> getStationList();
	StationCollection* getStation(int iIndex);

	void drawInitialise();
	bool update();
};

