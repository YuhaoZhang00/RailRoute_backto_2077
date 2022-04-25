#include "header.h"
#include "LineRoute.h"
#include "Constant.h"

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

void LineRoute::stopAtStation(TrainCollection* t)
{
	if (!t->isCooldown()) {
		CarriageCollection* head = t->getTrain()->getCarriageList()[0];
		int headX = head->getCarriage()->getXCentre();
		int headY = head->getCarriage()->getYCentre();
		for (int i = -1; i < 1; i++) {
			for (int j = -1; j <= 1; j++) {
				if (m_mapStation.count((headX + i) * 10000 + (headY + j)) > 0) {
					t->getTrain()->stopTrain();
					t->resetStopCooldown();
					return;
				}
			}
		}
	}
}

void LineRoute::setCarriageStateOnTurn(CarriageCollection* c)
{
	int x = c->getCarriage()->getXCentre();
	int y = c->getCarriage()->getYCentre();
	if (!c->isCooldown()) {
		for (int i = -1; i < 1; i++) {
			for (int j = -1; j <= 1; j++) {
				if (m_mapTurnPoints.count((x + i) * 10000 + (y + j)) > 0) {
					//printf("%d %d\n", x, y);
					//printf("%d\n", carriage->getCarriage()->getDirection());
					short d1 = m_mapTurnPoints.at((x + i) * 10000 + (y + j));
					short d2 = d1 % 10;
					d1 = d1 / 10;
					//printf("%d %d\n", d1, d2);
					if (c->getCarriage()->getDirection() == d1)
						c->getCarriage()->setDirection((d2 + 4) % 8);
					else c->getCarriage()->setDirection((d1 + 4) % 8);

					c->getCarriage()->setExactPos(x + i, y + j);

					c->getCarriage()->getPassengerPosition();
					//printf("%f %f\n", carriage->getCarriage()->getXExactPos(), carriage->getCarriage()->getYExactPos());
					//printf("------------\n");
					c->resetCooldown();
					return;
				}
			}
		}
	}
}

void LineRoute::exchangePassengers(TrainCollection* t, StationCollection* s)
{
	if (!isCooldown()) {
		int index = t->getTrain()->findFirstPassengerByType(s->getType());
		if (index != -1) {
			t->getTrain()->removePassenger(index);
			resetCooldown();
			return;
		}
		while (!t->getTrain()->isFull() && !s->getStation()->isEmpty()) {
			short sType = s->getStation()->removeFirstPassenger();
			t->getTrain()->addPassenger(new PassengerCollection(sType, m_pEngine));
			resetCooldown();
			return;
		}
	}
}

void LineRoute::exchangePassengers(TrainCollection* t)
{
	CarriageCollection* head = t->getTrain()->getCarriageList()[0];
	int headX = head->getCarriage()->getXCentre();
	int headY = head->getCarriage()->getYCentre();
	for (int i = -1; i < 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (m_mapStation.count((headX + i) * 10000 + (headY + j)) > 0) {
				exchangePassengers(t, m_mapStation.at((headX + i) * 10000 + (headY + j)));
				return;
			}
		}
	}
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


	m_mapTurnPoints.emplace(xStart * 10000 + yStart, end1Direction * 10 + end1Direction);
	m_mapTurnPoints.emplace(xEnd * 10000 + yEnd, end2Direction * 10 + end2Direction);

	m_mapStation.emplace(xStart * 10000 + yStart, s1);
	m_mapStation.emplace(xEnd * 10000 + yEnd, s2);
}

void LineRoute::addStationHead(StationCollection* s, bool bIs45, int rId)
{
	if (isStationInStationList(s)) return;

	int eId = m_vecRail.front()->getId();
	delete m_vecRail.front();
	m_vecRail.erase(m_vecRail.begin());

	int xStart = s->getStation()->getXCentre();
	int yStart = s->getStation()->getYCentre();
	int xEnd = m_vecStation.front()->getStation()->getXCentre();
	int yEnd = m_vecStation.front()->getStation()->getYCentre();

	m_vecStation.insert(m_vecStation.begin(), s);

	Rail* addRail = new Rail(rId, m_pEngine, xStart, yStart, xEnd, yEnd, bIs45, m_uiColor);
	m_vecRail.insert(m_vecRail.begin(), addRail);
	short end1DirectionO = addRail->getRailStartDirection();
	short end1Direction = (end1DirectionO + 4) % 8;
	m_vecRail.insert(m_vecRail.begin(), new Rail(eId, m_pEngine, xStart, yStart, end1Direction, m_uiColor));

	m_mapTurnPoints.erase(xEnd * 10000 + yEnd);
	m_mapTurnPoints.emplace(xStart * 10000 + yStart, end1Direction * 10 + end1Direction);
	m_mapTurnPoints.emplace(xEnd * 10000 + yEnd,
		(addRail->getRailEndDirection() + 4) % 8 * 10 + (m_vecRail[2]->getRailStartDirection() + 4) % 8);

	m_mapStation.emplace(xStart * 10000 + yStart, s);
}

void LineRoute::addStationTail(StationCollection* s, bool bIs45, int rId)
{
	if (isStationInStationList(s)) return;

	int eId = m_vecRail.back()->getId();
	delete m_vecRail.back();
	m_vecRail.pop_back();

	int xStart = m_vecStation.back()->getStation()->getXCentre();
	int yStart = m_vecStation.back()->getStation()->getYCentre();
	int xEnd = s->getStation()->getXCentre();
	int yEnd = s->getStation()->getYCentre();

	m_vecStation.emplace_back(s);

	Rail* addRail = new Rail(rId, m_pEngine, xStart, yStart, xEnd, yEnd, bIs45, m_uiColor);
	m_vecRail.emplace_back(addRail);
	short end1DirectionO = addRail->getRailEndDirection();
	short end1Direction = (end1DirectionO + 4) % 8;
	m_vecRail.emplace_back(new Rail(eId, m_pEngine, xEnd, yEnd, end1Direction, m_uiColor));

	m_mapTurnPoints.erase(xStart * 10000 + yStart);
	m_mapTurnPoints.emplace(xEnd * 10000 + yEnd, end1Direction * 10 + end1Direction);
	m_mapTurnPoints.emplace(xStart * 10000 + yStart,
		(addRail->getRailStartDirection() + 4) % 8 * 10 + (m_vecRail[m_vecRail.size() - 3]->getRailEndDirection() + 4) % 8);

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

void LineRoute::addTrain(int sId, short sType, int iX, int iY)
{
	// TODO: ����Ӧ�ü�����·��
	TrainCollection* train = new TrainCollection(sId, sType, m_pEngine, iX, iY, m_uiColor);
	addTrain(train);
	train->getTrain()->addHead();
}

std::vector<TrainCollection*> LineRoute::getTrainList()
{
	return m_vecTrain;
}

void LineRoute::addCarriage(int index)
{
	printf("aa");
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

void LineRoute::update()
{
	for (TrainCollection* train : m_vecTrain) {
		if (!train->isStopCooldown()) {
			stopAtStation(train);
			for (CarriageCollection* carriage : train->getTrain()->getCarriageList()) {
				setCarriageStateOnTurn(carriage);
			}
		}
		else {
			exchangePassengers(train);
		}

	}
}