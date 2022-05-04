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

bool LineRoute::exchangePassengers(int index, TrainCollection* t, StationCollection* s, std::vector<LineRoute*>& vecLr)
{
	if (!isCooldown()) {
		// passenger : train -> station (destination)
		int firstPassengerOnTrain = t->getTrain()->findFirstPassengerByType(s->getType());
		if (firstPassengerOnTrain != -1) {
			printf("- Destination\n");
			t->getTrain()->removePassenger(firstPassengerOnTrain);
			resetCooldown();
			return true;
		}
		// passenger : train -> station (transfer)
		if (aiIsExchangeStation(s, this, vecLr)) {
			std::vector<bool> hasStationTypeExchange = aiGetStationTypeAfterExchange(3, s, this, vecLr);
			std::vector<bool> hasStationTypeNonExchange = aiGetStationTypeNonExchange(3, s);
			for (int i = 0; i < 6; i++) {
				hasStationTypeExchange[i] = hasStationTypeExchange[i] && !hasStationTypeNonExchange[i];
			}
			int iIndex = t->getTrain()->findFirstPassengerByTypes(hasStationTypeExchange);
			int sType = t->getTrain()->findFirstPassengerTypeByTypes(hasStationTypeExchange);
			if (iIndex != -1) {
				printf("- Transfer: passenger index in train: %d, passenger type: %d\n", iIndex, sType);
				t->getTrain()->removePassenger(iIndex);
				s->getStation()->addPassenger(new PassengerCollection(sType, m_pEngine));
				resetCooldown();
				return false;
			}
		}
		// passenger : station -> train (board)
		while (!t->getTrain()->isFull() && !s->getStation()->isEmpty()) {
			if (aiRemovePassenger(index, t, s, vecLr)) {}
			else {
				if (rand() % 10 <= 1) {
					short sType = s->getStation()->removeFirstPassenger();
					t->getTrain()->addPassenger(new PassengerCollection(sType, m_pEngine));
					printf("- Boarding: passenger type: %d\n", sType);
				}
			}
			resetCooldown();
			return false;
		}
	}
	return false;
}

bool LineRoute::exchangePassengers(int index, std::vector<LineRoute*>& vecLr)
{
	TrainCollection* t = m_vecTrain[index];
	CarriageCollection* head = t->getTrain()->getCarriageList()[0];
	int headX = head->getCarriage()->getXCentre();
	int headY = head->getCarriage()->getYCentre();
	int speed = head->getCarriage()->getSpeed();
	for (int i = -speed; i < speed; i++) {
		for (int j = -speed; j <= speed; j++) {
			if (m_mapStation.count((headX + i) * 10000 + (headY + j)) > 0) {
				return exchangePassengers(index, t, m_mapStation.at((headX + i) * 10000 + (headY + j)), vecLr);
			}
		}
	}
	return false;
}

bool LineRoute::aiRemovePassenger(int index, TrainCollection* t, StationCollection* s, std::vector<LineRoute*>& vecLr)
{
	aiUpdateThisPrevStationId(index, s);
	std::vector<int> stationIndexAndDirection = aiFindCurrentStationIndexAndDirection(index);
	std::vector<bool> hasStationType = aiFindStationTypeOfNextNStations(5, stationIndexAndDirection[0], stationIndexAndDirection[1], vecLr);

	//printf("circle? %d - square? %d - triangle? %d - inv-triangle? %d - diamond? %d - flower? %d\n",
	//	hasStationType[0] ? 1 : 0, hasStationType[1] ? 1 : 0, hasStationType[2] ? 1 : 0,
	//	hasStationType[3] ? 1 : 0, hasStationType[4] ? 1 : 0, hasStationType[5] ? 1 : 0);

	short sType = s->getStation()->removeFirstPassengerOfTypes(hasStationType);
	if (sType != -1) {
		t->getTrain()->addPassenger(new PassengerCollection(sType, m_pEngine));
		return true;
	}
	return false;
}

void LineRoute::aiUpdateThisPrevStationId(int index, StationCollection* s)
{
	if (m_vecTrainThisStation[index] == 10000) {
		m_vecTrainThisStation[index] = s->getId();
	}
	else {
		if (m_vecTrainThisStation[index] == s->getId()) return;
		else {
			m_vecTrainPrevStation[index] = m_vecTrainThisStation[index];
			m_vecTrainThisStation[index] = s->getId();
		}
	}
}

std::vector<int> LineRoute::aiFindCurrentStationIndexAndDirection(int index)
{
	std::vector<int> ans(2);
	int stationIndex = -1;
	int prevStationIndex = -1;
	for (int i = 0; i < m_vecStation.size(); i++) {
		if (m_vecTrainThisStation[index] == m_vecStation[i]->getId()) {
			stationIndex = i;
		}
		if (m_vecTrainPrevStation[index] == m_vecStation[i]->getId()) {
			prevStationIndex = i;
		}
	}
	ans[0] = stationIndex;
	if (m_vecTrainPrevStation[index] == 10000) ans[1] = 0;
	else if (stationIndex == -1 || prevStationIndex == -1) {
		printf("!! Error @ LineRoute::aiFindCurrentStationIndexAndDirection(int index) - 1\n");
	}
	else if (stationIndex > prevStationIndex || stationIndex == 0) ans[1] = 0;
	else ans[1] = 1;

	return ans;
}

std::vector<bool> LineRoute::aiFindStationTypeOfNextNStations(int n, int stationIndex, short direction, std::vector<LineRoute*>& vecLr)
{
	std::vector<bool> hasStationType(6, false);
	if (direction == 0) {
		n = std::min(n, ((int)m_vecStation.size() - stationIndex - 1));
		for (int i = stationIndex + 1; i < stationIndex + 1 + n; i++) {
			if (aiIsExchangeStation(m_vecStation[i], this, vecLr)) {
				std::vector<bool> hasStationTypeExchange = aiGetStationTypeAfterExchange(n - (i - stationIndex), m_vecStation[i], this, vecLr);
				for (int i = 0; i < 6; i++) {
					hasStationType[i] = hasStationType[i] || hasStationTypeExchange[i];
				}
			}
			hasStationType[m_vecStation[i]->getType()] = true;
		}
	}
	else {
		n = std::min(n, stationIndex);
		for (int i = stationIndex - n; i < stationIndex; i++) {
			if (aiIsExchangeStation(m_vecStation[i], this, vecLr)) {
				std::vector<bool> hasStationTypeExchange = aiGetStationTypeAfterExchange(n - (stationIndex - i), m_vecStation[i], this, vecLr);
				for (int i = 0; i < 6; i++) {
					hasStationType[i] = hasStationType[i] || hasStationTypeExchange[i];
				}
			}
			hasStationType[m_vecStation[i]->getType()] = true;
		}
	}
	return hasStationType;
}

std::vector<bool> LineRoute::aiFindStationTypeOfNextNStationsInBothDirection(int n, StationCollection* s, std::vector<LineRoute*>& vecLr)
{
	int stationIndex = -1;
	for (int i = 0; i < m_vecStation.size(); i++) {
		if (m_vecStation[i] == s) {
			stationIndex = i;
			break;
		}
	}
	std::vector<bool> hasStationType(6, false);
	int a = std::min(n, ((int)m_vecStation.size() - stationIndex - 1));
	for (int i = stationIndex + 1; i < stationIndex + 1 + a; i++) {
		hasStationType[m_vecStation[i]->getType()] = true;
	}
	int b = std::min(n, stationIndex);
	for (int i = stationIndex - b; i < stationIndex; i++) {
		hasStationType[m_vecStation[i]->getType()] = true;
	}

	return hasStationType;
}

bool LineRoute::aiIsExchangeStation(StationCollection* s, LineRoute* thisLr, std::vector<LineRoute*>& vecLr)
{
	for (LineRoute* lr : vecLr) {
		if (lr == thisLr) continue;
		for (StationCollection* station : lr->getStationList()) {
			if (s == station) {
				return true;
			}
		}
	}
	return false;
}

std::vector<bool> LineRoute::aiGetStationTypeAfterExchange(int n, StationCollection* s, LineRoute* thisLr, std::vector<LineRoute*>& vecLr)
{
	if (n <= 0) return std::vector<bool>(6, false);
	else {
		std::vector<bool> hasStationType(6, false);
		for (LineRoute* lr : vecLr) {
			if (lr == thisLr) continue;
			for (StationCollection* station : lr->getStationList()) {
				if (s == station) {
					std::vector<bool> hasStationTypeThisLine = lr->aiFindStationTypeOfNextNStationsInBothDirection(n, station, vecLr);
					for (int i = 0; i < 6; i++) {
						hasStationType[i] = hasStationType[i] || hasStationTypeThisLine[i];
					}
					break;
				}
			}
		}
		return hasStationType;
	}
}

std::vector<bool> LineRoute::aiGetStationTypeNonExchange(int n, StationCollection* s)
{
	if (n <= 0) return std::vector<bool>(6, false);
	else {
		return aiFindStationTypeOfNextNStationsInBothDirection(n, s, std::vector<LineRoute*>{});
	}
}

bool LineRoute::isCanAddStation(StationCollection* s1, StationCollection* s2) // pixel-perfect
{
	m_pEngine->getBackgroundSurface()->mySDLLockSurface();
	int xStart = s1->getStation()->getXCentre();
	int yStart = s1->getStation()->getYCentre();
	int xEnd = s2->getStation()->getXCentre();
	int yEnd = s2->getStation()->getYCentre();
	Rail* testRail1 = new Rail(0, m_pEngine, xStart, yStart, xEnd, yEnd, true, 0x777777);
	for (std::vector<int> pixelPoint : testRail1->getImagePixelMap()) {
		if (m_pEngine->getBackgroundSurface()->rawGetPixel(pixelPoint[0], pixelPoint[1]) != -1) {
			delete testRail1;
			return false;
		}
	}
	delete testRail1;
	Rail* testRail2 = new Rail(0, m_pEngine, xStart, yStart, xEnd, yEnd, false, 0x777777);
	for (std::vector<int> pixelPoint : testRail2->getImagePixelMap()) {
		if (m_pEngine->getBackgroundSurface()->rawGetPixel(pixelPoint[0], pixelPoint[1]) != -1) {
			delete testRail2;
			return false;
		}
	}
	delete testRail2;
	m_pEngine->getBackgroundSurface()->mySDLUnlockSurface();

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
	m_vecTrainThisStation.emplace_back(10000);
	m_vecTrainPrevStation.emplace_back(10000);
}

void LineRoute::addTrain(int tId, short sType, int iX, int iY)
{
	TrainCollection* train = new TrainCollection(tId, sType, m_pEngine, iX, iY + 2, m_uiColor);
	addTrain(train);
	train->getTrain()->addHead();
	m_pEngine->appendObjectToArray(train->getTrain()->getCarriageList()[0]->getCarriage());
}

void LineRoute::removeTrain(TrainCollection* t)
{
	for (int i = 0; i < m_vecTrain.size(); i++) {
		if (m_vecTrain[i] == t) {
			for (CarriageCollection* c : m_vecTrain[i]->getTrain()->getCarriageList()) {
				m_pEngine->removeDisplayableObject(c->getCarriage());
			}
			delete m_vecTrain[i];
			m_vecTrain.erase(m_vecTrain.begin() + i);
			m_vecTrainThisStation.erase(m_vecTrainThisStation.begin() + i);
			m_vecTrainPrevStation.erase(m_vecTrainPrevStation.begin() + i);
			break;
		}
	}
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

int LineRoute::update(std::vector<LineRoute*>& vecLr)
{
	int passengerCount = 0;
	for (int i = 0; i < m_vecTrain.size(); i++) {
		if (!m_vecTrain[i]->isStopCooldown()) {
			if (!stopAtStation(m_vecTrain[i])) {
				for (CarriageCollection* carriage : m_vecTrain[i]->getTrain()->getCarriageList()) {
					setCarriageStateOnTurn(carriage);
				}
			}
		}
		else {
			if (exchangePassengers(i, vecLr)) passengerCount++;
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
