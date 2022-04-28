#pragma once
#include "header.h"
#include "State.h"
#include "SelectionArea.h"
#include "StationMap.h"
#include "LineRoute.h"
#include "Scyyz12FilterPoints.h"

class GameState :
	public State
{
private:
	SelectionArea* m_sa;

	Scyyz12FilterPointsScaling m_filterScaling;
	Scyyz12FilterPointsTranslation m_filterTranslation;

	StationMap* m_sm;
	std::vector<LineRoute*> m_lr;

	int m_trainCount = 0;
	int m_stationCount = 0;
	int m_railCount = 0;

	int m_timeCount = 0;

	/*
	* 0 - no action
	* 1 - prompt user to select a station
	* 2 - prompt user to select another station
	* 3 - prompt user to select a line
	* 4 - prompt user to select a station on that line
	* 100 - error - line not discovered
	* 101 - error - line already in use
	* 102 - error - not click at station
	* 103 - error - click the same station twice
	* 104 - error - line not in use
	* 105 - error - station not in line
	* 106 - error - station already in line
	* 107 - error - not click at a train at give line
	* 200 - test
	*/
	short m_mouseState = 0;
	short m_propertyIndex = 0;
	int m_tempStationIndex = 0;
	int m_tempLineIndex = 0;

	void clickAtSelectionArea(Scyyz12Engine2* pContext, int iMapX);
	void resetAtSelectionArea(Scyyz12Engine2* pContext, int iMapX);
	void clickAtFirstStation(Scyyz12Engine2* pContext, int iX, int iY);
	void clickAtSecondStation(Scyyz12Engine2* pContext, int iX, int iY);
	// returns the index of station in StationMap if the point in that station, -1 if point not in any station
	int isPointInStation(int iX, int iY);
	// returns (line_id * 10 + 0(head) or 1(tail)), -1 otherwise
	int clickAtRailEnd(int iX, int iY);

	short directionToStation(int iX, int iY, int iStationX, int iStationY);

public:
	GameState()
		: m_sa(nullptr), m_filterScaling(0, nullptr), m_filterTranslation(0, 0, nullptr), m_sm(nullptr)
	{}

	~GameState() {
		delete m_sa;
		delete m_sm;
		for (LineRoute* lr : m_lr) {
			delete lr;
		}
	}

	int virtInitialise(Scyyz12Engine2* pContext) override;
	void virtSetupBackgroundBuffer(Scyyz12Engine2* pContext) override;
	void virtDrawStringsOnTop(Scyyz12Engine2* pContext) override;
	int virtInitialiseObjects(Scyyz12Engine2* pContext) override;
	void virtMouseMoved(Scyyz12Engine2* pContext, int iX, int iY) override;
	void virtMouseDown(Scyyz12Engine2* pContext, int iButton, int iX, int iY) override;
	void virtMouseWheel(Scyyz12Engine2* pContext, int x, int y, int which, int timestamp) override;
	void virtMainLoopDoBeforeUpdate(Scyyz12Engine2* pContext) override;
	void copyAllBackgroundBuffer(Scyyz12Engine2* pContext) override;
	void virtKeyDown(Scyyz12Engine2* pContext, int iKeyCode) override;
	void virtCreateSurfaces(Scyyz12Engine2* pContext) override;
};

