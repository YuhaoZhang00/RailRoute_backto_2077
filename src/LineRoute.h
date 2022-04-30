#pragma once
#include "header.h"
#include "BaseEngine.h"
#include "Passenger.h"
#include "Rail.h"
#include "Station.h"
#include "Train.h"
#include <vector>
#include <unordered_map>

class LineRoute
{
private:
	BaseEngine* m_pEngine;
	unsigned int m_uiColor;

	std::vector<TrainCollection*> m_vecTrain;
	std::vector<StationCollection*> m_vecStation;
	std::vector<Rail*> m_vecRail;
	std::unordered_map<int, short> m_mapTurnPoints;
	std::unordered_map<int, StationCollection*> m_mapStation;

	int m_cooldown = 0;



	void resetCooldown();
	bool isCooldown();

	bool stopAtStation(TrainCollection* t);
	void setCarriageStateOnTurn(CarriageCollection* c);
	bool exchangePassengers(TrainCollection* t, StationCollection* s);
	bool exchangePassengers(TrainCollection* t);

public:
	LineRoute(BaseEngine* pEngine, unsigned int uiColor)
		: m_pEngine(pEngine), m_uiColor(uiColor)
	{}

	~LineRoute() {
		for (TrainCollection* train : m_vecTrain) {
			delete train;
		}
		for (Rail* rail : m_vecRail) {
			delete rail;
		}
		// delete of station handled by StationMap
	}

	bool isCanAddStation(StationCollection* s1, StationCollection* s2); // collision detection
	void iniAdd2Stations(StationCollection* s1, StationCollection* s2, bool bIs45, int e1Id, int rId, int e2Id);
	void addStationHead(StationCollection* s, bool bIs45, int rId);
	void addStationTail(StationCollection* s, bool bIs45, int rId);
	void addStation(int index, StationCollection* s, bool bIs45_1, bool bIs45_2, int r2Id);
	void removeStation(); // TODO: NOTE: no delete of station
	std::vector<StationCollection*> getStationList();
	std::vector<Rail*> getRailList();

	void addTrain(TrainCollection* t);
	void addTrain(int sId, short sType, int iX, int iY);
	void removeTrain();
	std::vector<TrainCollection*> getTrainList();

	void addCarriage(int index);

	void drawInitialise();
	int update();

	bool isPosAStationInLine(int iX, int iY);
	int isPosATrainInLine(int iX, int iY);
	bool isStationInStationList(StationCollection* s);


	void addRail(Rail* r) {
		m_vecRail.emplace_back(r);
	}
	void addStation(StationCollection* s) {
		m_vecStation.emplace_back(s);
	}
	std::unordered_map<int, short>& getMapTurnPoints() {
		return m_mapTurnPoints;
	}
	std::unordered_map<int, StationCollection*>& getMapStation() {
		return m_mapStation;
	}
	void addTurnPoints(int i, short s) {
		m_mapTurnPoints.emplace(i, s);
	}
	void addStation(int i, StationCollection* s) {
		m_mapStation.emplace(i, s);
	}
};

