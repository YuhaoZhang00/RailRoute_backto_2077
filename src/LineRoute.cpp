#include "header.h"
#include "LineRoute.h"
#include "Constant.h"

void LineRoute::resetCooldown()
{
	m_cooldown = GET_ON_OFF_TRAIN_TIME;
}

bool LineRoute::isCooldown()
{
	if (m_cooldown == 0) return false;
	m_cooldown -= 1;
	return true;
}

bool LineRoute::stopAtStation(TrainCollection* t)
{
	if (!t->isCooldown()) {
		CarriageCollection* head = t->getTrain()->getCarriageList()[0];
		int headX = head->getCarriage()->getXCentre();
		int headY = head->getCarriage()->getYCentre();
		int speed = head->getCarriage()->getSpeed();
		for (int i = -speed; i < speed; i++) {
			for (int j = -speed; j <= speed; j++) {
				if (m_mapStation.count((headX + i) * 10000 + (headY + j)) > 0) {
					t->getTrain()->stopTrain();
					t->resetStopCooldown();
					return true;
				}
			}
		}
	}
	return false;
}

void LineRoute::setCarriageStateOnTurn(CarriageCollection* c)
{
	if (!c->isCooldown()) {
		int x = c->getCarriage()->getXCentre();
		int y = c->getCarriage()->getYCentre();
		int speed = c->getCarriage()->getSpeed();
		for (int i = -speed; i < speed; i++) {
			for (int j = -speed; j <= speed; j++) {
				if (m_mapTurnPoints.count((x + i) * 10000 + (y + j)) > 0) {
					short d1 = m_mapTurnPoints.at((x + i) * 10000 + (y + j));
					short d2 = d1 % 10;
					d1 = d1 / 10;
					if (c->getCarriage()->getDirection() == d1)
						c->getCarriage()->setDirection((d2 + 4) % 8);
					else c->getCarriage()->setDirection((d1 + 4) % 8);

					c->getCarriage()->setExactPos(x + i, y + j);
					c->getCarriage()->setPassengerPosition();
					//printf("%d %d %d\n", c->getCarriage()->getXCentre(), c->getCarriage()->getYCentre(), c->getCarriage()->getDirection());

					c->resetCooldown();
					return;
				}
			}
		}
	}
}

bool LineRoute::exchangePassengers(TrainCollection* t, StationCollection* s)
{
	if (!isCooldown()) {
		int index = t->getTrain()->findFirstPassengerByType(s->getType());
		if (index != -1) {
			t->getTrain()->removePassenger(index);
			resetCooldown();
			return true;
		}
		while (!t->getTrain()->isFull() && !s->getStation()->isEmpty()) {
			short sType = s->getStation()->removeFirstPassenger();
			t->getTrain()->addPassenger(new PassengerCollection(sType, m_pEngine));
			resetCooldown();
			return false;
		}
	}
	return false;
}

bool LineRoute::exchangePassengers(TrainCollection* t)
{
	CarriageCollection* head = t->getTrain()->getCarriageList()[0];
	int headX = head->getCarriage()->getXCentre();
	int headY = head->getCarriage()->getYCentre();
	int speed = head->getCarriage()->getSpeed();
	for (int i = -speed; i < speed; i++) {
		for (int j = -speed; j <= speed; j++) {
			if (m_mapStation.count((headX + i) * 10000 + (headY + j)) > 0) {
				return exchangePassengers(t, m_mapStation.at((headX + i) * 10000 + (headY + j)));
			}
		}
	}
	return false;
}

bool LineRoute::isCanAddStation(StationCollection* s1, StationCollection* s2)
{
	m_pEngine->getBackgroundSurface()->mySDLLockSurface();
	int xStart = s1->getStation()->getXCentre();
	int yStart = s1->getStation()->getYCentre();
	int xEnd = s2->getStation()->getXCentre();
	int yEnd = s2->getStation()->getYCentre();
	Rail* testRail1 = new Rail(0, m_pEngine, xStart, yStart, xEnd, yEnd, true, 0x777777);
	for (std::vector<int> pixelPoint : testRail1->getImagePixelMap()) {
		if (m_pEngine->getBackgroundSurface()->rawGetPixel(pixelPoint[0], pixelPoint[1]) != -1) return false;
	}
	Rail* testRail2 = new Rail(0, m_pEngine, xStart, yStart, xEnd, yEnd, false, 0x777777);
	for (std::vector<int> pixelPoint : testRail2->getImagePixelMap()) {
		if (m_pEngine->getBackgroundSurface()->rawGetPixel(pixelPoint[0], pixelPoint[1]) != -1) return false;
	}
	m_pEngine->getBackgroundSurface()->mySDLUnlockSurface();
	delete testRail1;
	delete testRail2;
	return true;
}

void LineRoute::iniAdd2Stations(StationCollection* s1, StationCollection* s2, bool bIs45, int e1Id, int rId, int e2Id)
{
	if (!m_vecTrain.empty() || !m_vecStation.empty() || !m_vecRail.empty()) {
		printf("!! Error @ LineRoute.cpp iniAdd2Stations() - should not call initialisation method on non-empty line\n");
	}
	if (s1->getId() == s2->getId()) {
		printf("!! Error @ LineRoute.cpp iniAdd2Stations() - two stations cannot be the same\n");
	}

	m_vecStation.emplace_back(s1);
	m_vecStation.emplace_back(s2);

	int xStart = s1->getStation()->getXCentre();
	int yStart = s1->getStation()->getYCentre();
	int xEnd = s2->getStation()->getXCentre();
	int yEnd = s2->getStation()->getYCentre();
	Rail* firstRail = new Rail(rId, m_pEngine, xStart, yStart, xEnd, yEnd, bIs45, m_uiColor);
	m_vecRail.emplace_back(firstRail);
	short end1DirectionO = firstRail->getRailStartDirection();
	short end1Direction = (end1DirectionO + 4) % 8;
	m_vecRail.insert(m_vecRail.begin(), (new Rail(e1Id, m_pEngine, xStart, yStart, end1Direction, m_uiColor)));
	short end2DirectionO = firstRail->getRailEndDirection();
	short end2Direction = (end2DirectionO + 4) % 8;
	m_vecRail.emplace_back(new Rail(e2Id, m_pEngine, xEnd, yEnd, end2Direction, m_uiColor));
	m_pEngine->appendObjectToArray(m_vecRail[0]);
	m_pEngine->appendObjectToArray(m_vecRail[1]);
	m_pEngine->appendObjectToArray(m_vecRail[2]);

	m_mapTurnPoints.emplace(xStart * 10000 + yStart, end1Direction * 10 + end1Direction);
	m_mapTurnPoints.emplace(xEnd * 10000 + yEnd, end2Direction * 10 + end2Direction);
	if (firstRail->getTurnDirection() != 0)
		m_mapTurnPoints.emplace(firstRail->getTurnX() * 10000 + firstRail->getTurnY(), firstRail->getTurnDirection());

	m_mapStation.emplace(xStart * 10000 + yStart, s1);
	m_mapStation.emplace(xEnd * 10000 + yEnd, s2);
}

void LineRoute::addStationHead(StationCollection* s, bool bIs45, int rId)
{
	int eId = m_vecRail.front()->getId();
	m_pEngine->drawableObjectsChanged();
	bool returnValue = m_pEngine->removeDisplayableObject(m_vecRail.front());
	delete m_vecRail.front();
	m_vecRail.erase(m_vecRail.begin());

	int xStart = s->getStation()->getXCentre();
	int yStart = s->getStation()->getYCentre();
	int xEnd = m_vecStation.front()->getStation()->getXCentre();
	int yEnd = m_vecStation.front()->getStation()->getYCentre();
	short direction = m_vecRail.front()->getRailStartDirection();

	m_vecStation.insert(m_vecStation.begin(), s);

	Rail* addRail = new Rail(rId, m_pEngine, xStart, yStart, xEnd, yEnd, (direction % 2 == 0) ? true : false, m_uiColor);
	m_vecRail.insert(m_vecRail.begin(), addRail);
	m_pEngine->appendObjectToArray(m_vecRail[0]);
	short end1DirectionO = addRail->getRailStartDirection();
	short end1Direction = (end1DirectionO + 4) % 8;
	m_vecRail.insert(m_vecRail.begin(), new Rail(eId, m_pEngine, xStart, yStart, end1Direction, m_uiColor));
	m_pEngine->appendObjectToArray(m_vecRail[0]);

	m_mapTurnPoints.erase(xEnd * 10000 + yEnd);
	m_mapTurnPoints.emplace(xStart * 10000 + yStart, end1Direction * 10 + end1Direction);
	m_mapTurnPoints.emplace(xEnd * 10000 + yEnd,
		(addRail->getRailEndDirection() + 4) % 8 * 10 + (m_vecRail[2]->getRailStartDirection() + 4) % 8);
	if (addRail->getTurnDirection() != 0)
		m_mapTurnPoints.emplace(addRail->getTurnX() * 10000 + addRail->getTurnY(), addRail->getTurnDirection());

	m_mapStation.emplace(xStart * 10000 + yStart, s);
}

void LineRoute::addStationTail(StationCollection* s, bool bIs45, int rId)
{
	int eId = m_vecRail.back()->getId();
	m_pEngine->drawableObjectsChanged();
	bool returnValue = m_pEngine->removeDisplayableObject(m_vecRail.back());
	delete m_vecRail.back();
	m_vecRail.pop_back();

	int xStart = m_vecStation.back()->getStation()->getXCentre();
	int yStart = m_vecStation.back()->getStation()->getYCentre();
	int xEnd = s->getStation()->getXCentre();
	int yEnd = s->getStation()->getYCentre();
	short direction = m_vecRail.back()->getRailEndDirection();

	m_vecStation.emplace_back(s);

	Rail* addRail = new Rail(rId, m_pEngine, xStart, yStart, xEnd, yEnd, (direction % 2 == 0) ? false : true, m_uiColor);
	m_vecRail.emplace_back(addRail);
	m_pEngine->appendObjectToArray(m_vecRail.back());
	short end1DirectionO = addRail->getRailEndDirection();
	short end1Direction = (end1DirectionO + 4) % 8;
	m_vecRail.emplace_back(new Rail(eId, m_pEngine, xEnd, yEnd, end1Direction, m_uiColor));
	m_pEngine->appendObjectToArray(m_vecRail.back());

	m_mapTurnPoints.erase(xStart * 10000 + yStart);
	m_mapTurnPoints.emplace(xEnd * 10000 + yEnd, end1Direction * 10 + end1Direction);
	m_mapTurnPoints.emplace(xStart * 10000 + yStart,
		(addRail->getRailStartDirection() + 4) % 8 * 10 + (m_vecRail[m_vecRail.size() - 3]->getRailEndDirection() + 4) % 8);
	if (addRail->getTurnDirection() != 0)
		m_mapTurnPoints.emplace(addRail->getTurnX() * 10000 + addRail->getTurnY(), addRail->getTurnDirection());

	m_mapStation.emplace(xEnd * 10000 + yEnd, s);
}

void LineRoute::addStation(int index, StationCollection* s, bool bIs45_1, bool bIs45_2, int r2Id)
{
	if (isStationInStationList(s)) return;
	if (index < 0 || index >= m_vecStation.size() - 1) {
		printf("!! Error @ LineRoute.cpp addStation() - invalid index, consider to use addStationTail / addStationHead (?)\n");
		return;
	}

	int r1Id = m_vecRail[index + 1]->getId();
	m_pEngine->removeDisplayableObject(m_vecRail[index + 1]);
	delete m_vecRail[index + 1];
	m_vecRail.erase(m_vecRail.begin() + index + 1);

	int xStart = m_vecStation[index]->getStation()->getXCentre();
	int yStart = m_vecStation[index]->getStation()->getYCentre();
	int xEnd1 = s->getStation()->getXCentre();
	int yEnd1 = s->getStation()->getYCentre();
	int xEnd2 = m_vecStation[index + 1]->getStation()->getXCentre();
	int yEnd2 = m_vecStation[index + 1]->getStation()->getYCentre();

	m_vecStation.insert(m_vecStation.begin() + index + 1, s);

	Rail* addRail1 = new Rail(r1Id, m_pEngine, xStart, yStart, xEnd1, yEnd1, bIs45_1, m_uiColor);
	Rail* addRail2 = new Rail(r2Id, m_pEngine, xEnd1, yEnd1, xEnd2, yEnd2, bIs45_2, m_uiColor);
	m_vecRail.insert(m_vecRail.begin() + index + 1, addRail2);
	m_vecRail.insert(m_vecRail.begin() + index + 1, addRail1);

	m_mapTurnPoints.erase(xStart * 10000 + yStart);
	m_mapTurnPoints.erase(xEnd2 * 10000 + yEnd2);
	m_mapTurnPoints.emplace(xEnd1 * 10000 + yEnd1, (addRail1->getRailEndDirection() + 4) % 8 * 10 + (addRail2->getRailStartDirection() + 4) % 8);
	if (addRail1->getTurnDirection() != 0)
		m_mapTurnPoints.emplace(addRail1->getTurnX() * 10000 + addRail1->getTurnY(), addRail1->getTurnDirection());
	if (addRail2->getTurnDirection() != 0)
		m_mapTurnPoints.emplace(addRail2->getTurnX() * 10000 + addRail2->getTurnY(), addRail2->getTurnDirection());

	if (index == 0) {
		int eId = m_vecRail.front()->getId();
		delete m_vecRail.front();
		m_vecRail.erase(m_vecRail.begin());
		short endDirection = (addRail1->getRailStartDirection() + 4) % 8;
		m_vecRail.insert(m_vecRail.begin(), new Rail(eId, m_pEngine, xStart, yStart, endDirection, m_uiColor));

		m_mapTurnPoints.emplace(xStart * 10000 + yStart, endDirection * 10 + endDirection);
	}
	else {
		m_mapTurnPoints.emplace(xStart * 10000 + yStart, (addRail1->getRailStartDirection() + 4) % 8 * 10 + (m_vecRail[index]->getRailEndDirection() + 4) % 8);
	}
	if (index == m_vecStation.size() - 3) {
		int eId = m_vecRail.back()->getId();
		delete m_vecRail.back();
		m_vecRail.pop_back();
		short endDirection = (addRail2->getRailEndDirection() + 4) % 8;
		m_vecRail.emplace_back(new Rail(eId, m_pEngine, xEnd2, yEnd2, endDirection, m_uiColor));

		m_mapTurnPoints.emplace(xEnd2 * 10000 + yEnd2, endDirection * 10 + endDirection);
	}
	else {
		m_mapTurnPoints.emplace(xEnd2 * 10000 + yEnd2, (addRail2->getRailEndDirection() + 4) % 8 * 10 + (m_vecRail[index + 3]->getRailStartDirection() + 4) % 8);
	}

	m_mapStation.emplace(xEnd1 * 10000 + yEnd1, s);
}

std::vector<StationCollection*> LineRoute::getStationList()
{
	return m_vecStation;
}

std::vector<Rail*> LineRoute::getRailList()
{
	return m_vecRail;
}

void LineRoute::addTrain(TrainCollection* t)
{
	m_vecTrain.emplace_back(t);
}

void LineRoute::addTrain(int tId, short sType, int iX, int iY)
{
	TrainCollection* train = new TrainCollection(tId, sType, m_pEngine, iX, iY, m_uiColor);
	addTrain(train);
	train->getTrain()->addHead(); // next: add a ³µÏá
	m_pEngine->appendObjectToArray(train->getTrain()->getCarriageList()[0]->getCarriage());
}

std::vector<TrainCollection*> LineRoute::getTrainList()
{
	return m_vecTrain;
}

void LineRoute::addCarriage(int index)
{
	m_vecTrain[index]->getTrain()->addCarriage();
}

void LineRoute::drawInitialise()
{
	for (Rail* rail : m_vecRail) {
		m_pEngine->appendObjectToArray(rail);
	}
	for (TrainCollection* train : m_vecTrain) {
		for (CarriageCollection* carriage : train->getTrain()->getCarriageList()) {
			m_pEngine->appendObjectToArray(carriage->getCarriage());
		}
	}
}

int LineRoute::update()
{
	int passengerCount = 0;
	for (TrainCollection* train : m_vecTrain) {
		if (!train->isStopCooldown()) {
			if (!stopAtStation(train)) {
				for (CarriageCollection* carriage : train->getTrain()->getCarriageList()) {
					setCarriageStateOnTurn(carriage);
				}
			}
		}
		else {
			if (exchangePassengers(train)) passengerCount++;
		}
	}
	return passengerCount;
}

bool LineRoute::isPosAStationInLine(int iX, int iY)
{
	return (m_mapStation.count(iX * 10000 + iY) == 1);
}

int LineRoute::isPosATrainInLine(int iX, int iY)
{
	for (int i = 0; i < m_vecTrain.size(); i++) {
		for (CarriageCollection* carriage : m_vecTrain[i]->getTrain()->getCarriageList()) {
			if (carriage->getCarriage()->getDrawingRegionLeft() <= iX && carriage->getCarriage()->getDrawingRegionRight() >= iX &&
				carriage->getCarriage()->getDrawingRegionTop() <= iY && carriage->getCarriage()->getDrawingRegionBottom() >= iY) {
				return i;
			}
		}

	}
	return -1;
}

bool LineRoute::isStationInStationList(StationCollection* s)
{
	for (StationCollection* station : m_vecStation) {
		if (station->getId() == s->getId()) {
			printf("## debug - cannot add a existing station / station with same id to the line\n");
			return true;
		}
	}
	return false;
}
