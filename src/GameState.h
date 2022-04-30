#pragma once
#include "header.h"
#include "State.h"
#include "SelectionArea.h"
#include "StationMap.h"
#include "LineRoute.h"
#include "Scyyz12FilterPoints.h"
#include "FileHandler.h"
#include "ImagePixelMapping.h"

class GameState :
	public State
{
private:
	SelectionArea* m_sa;

	Scyyz12FilterPointsScaling m_filterScaling;
	Scyyz12FilterPointsTranslation m_filterTranslation;
	Scyyz12FilterPointsRectangularMask m_filterMask;

	StationMap* m_sm;
	std::vector<LineRoute*> m_lr;

	SimpleImage map;
	SimpleImage backArrow;
	SimpleImage pause;
	ImagePixelMappingRotateAndColour mapping;

	int m_trainCount = 0;
	int m_stationCount = 0;
	int m_railCount = 0;

	int m_iniTimeCount = 0;
	int m_timeCount = 0;

	int m_dayCount = 1;
	int m_scoreCount = 0;

	bool m_bIsNewDay = false;
	bool m_bRunToStop = false;
	bool m_bSelectionNotMade = false;

	bool m_bIsNeedsReload = false;
	bool m_bIsContinue = false;
	int m_iLevelId = 0;

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
	* 108 - error - no enough bridges
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

	void doIfNeedsReload() {
		if (m_bIsNeedsReload) {
			delete m_sa;
			delete m_sm;
			for (LineRoute* lr : m_lr) {
				delete lr;
			}

			m_sa = nullptr;
			m_sm = nullptr;
			m_lr.clear();

			m_dayCount = 0;
			m_scoreCount = 0;

			m_bIsNeedsReload = false;
		}
	}

	void writeToContinueFile(bool isWrite) {
		FileWriter fh("resources/level-continue.txt");
		if (!isWrite) {
			fh.write(-1);
		}
		else {
			fh.write(m_iLevelId);
			fh.write(100000);
			for (int i = 0; i < m_sa->getMapWidth(); i++) {
				if (m_sa->getTileType(i) >= 0) {
					fh.write(m_sa->getLineColor(i));
					fh.write(m_sa->getMapValue(i, 0));
				}
			}
			fh.write(100001);
			fh.write(m_sa->getLineColor(-1));
			for (int p = -6; p < 0; p++) {
				int value = -1;
				for (int i = 0; i < m_sa->getMapWidth(); i++) {
					if (m_sa->getTileType(i) == p) {
						value = m_sa->getMapValue(i, 0);
						break;
					}
				}
				fh.write(value);
			}
			fh.write(100002);

			// all the stations with passengers
			for (int i = 0; i < m_sm->getStationList().size(); i++) {
				fh.write(m_sm->getStation(i)->getStation()->getXCentre());
				fh.write(m_sm->getStation(i)->getStation()->getYCentre());
				fh.write(m_sm->getStation(i)->getType());
				fh.write(m_sm->getStation(i)->getId());
				fh.write(m_sm->getStation(i)->getStation()->getIsAngry());
				fh.write(m_sm->getStation(i)->getStation()->getAngryValue());
				fh.write(1000000);
				for (PassengerCollection* passenger : m_sm->getStation(i)->getStation()->getPassengerList()) {
					fh.write(passenger->getType());
				}
				fh.write(1000001);
			}
			fh.write(100003);

			// all the rail lines in lineroute
			for (LineRoute* lr : m_lr) {
				fh.write(1000005);
				for (Rail* rail : lr->getRailList()) {
					for (int i : rail->getInfoForContinue()) {
						fh.write(i);
					}
				}
			}
			fh.write(100004);

			// all the stations in lineroute
			for (LineRoute* lr : m_lr) {
				fh.write(1000005);
				for (StationCollection* station : lr->getStationList()) {
					fh.write(station->getId());
				}
			}
			fh.write(100005);

			// all the carriages with passengers in lineroute
			for (LineRoute* lr : m_lr) {
				fh.write(1000005);
				for (TrainCollection* train : lr->getTrainList()) {
					fh.write(train->getId());
					fh.write(train->getType());
					fh.write(train->getTrain()->getXCenter());
					fh.write(train->getTrain()->getYCenter());
					fh.write(train->getTrain()->getColor());
					fh.write(train->getTrain()->getDirection());
					fh.write(1000000);
					for (CarriageCollection* carriage : train->getTrain()->getCarriageList()) {
						fh.write(carriage->getType());
						fh.write(carriage->getCarriage()->getXExactPos());
						fh.write(carriage->getCarriage()->getYExactPos());
						fh.write(carriage->getCarriage()->getDirection());
						fh.write(carriage->getCarriage()->getSpeed());
						fh.write(1000002);
						for (PassengerCollection* passenger : carriage->getCarriage()->getPassengerList()) {
							if (passenger == nullptr) fh.write(-1);
							else fh.write(passenger->getType());
						}
						fh.write(1000003);
					}
					fh.write(1000001);
				}
			}
			fh.write(100006);

			// map turn points
			for (LineRoute* lr : m_lr) {
				fh.write(1000005);
				for (std::pair<int, short> element : lr->getMapTurnPoints()) {
					fh.write(element.first);
					fh.write(element.second);
				}
			}
			fh.write(100007);

			// map station
			for (LineRoute* lr : m_lr) {
				fh.write(1000005);
				for (std::pair<int, StationCollection*> element : lr->getMapStation()) {
					fh.write(element.first);
					fh.write(element.second->getId());
				}
			}
			fh.write(100008);
			fh.write(m_dayCount);
			fh.write(m_scoreCount);
			fh.write(100009);
		}
	}

public:
	GameState()
		: m_sa(nullptr), m_filterScaling(0, 0, 100, 1300, 700), m_filterTranslation(0, 0),m_filterMask(0, 100, 1300, 700), m_sm(nullptr),mapping(0,0,0)
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

	void virtSetSelfDefinedValue(bool b, bool c, int i) override;
};

