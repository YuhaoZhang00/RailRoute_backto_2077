#pragma once
#include "header.h"
#include "DisplayableObject.h"
#include "Passenger.h"
#include "Rail.h"
#include "Station.h"
#include "Train.h"
#include <vector>

class LineRoute
{
protected:
	BaseEngine* m_pEngine;
	unsigned int m_uiColor;

	std::vector<TrainCollection*> m_vecTrain;
	std::vector<StationCollection*> m_vecStation;
	std::vector<Rail*> m_vecRail;

public:
	LineRoute(BaseEngine* pEngine, unsigned int uiColor)
		:m_pEngine(pEngine), m_uiColor(uiColor)
	{}

	void addStationHead();
	void addStationTail();
	void addStation(int index);
	void addTrain();
	void removeTrain(int index);
};

