#include "header.h"
#include "GameState.h"
#include "FileHandler.h"

void GameState::clickAtSelectionArea(Scyyz12Engine2* pContext, int iMapX)
{
	int type = m_sa->getTileType(iMapX);
	int value = m_sa->getMapValue(iMapX, 0);
	if (m_mouseState == 0) {
		m_propertyIndex = iMapX;

		if (type < 0) { // click at property -> prompt to select a line
			if (value == 0) return;
			else {
				m_sa->setAndRedrawMapValueAt(iMapX, 0, value - 1, pContext, pContext->getBackgroundSurface());
				m_mouseState = 3;
			}
		}
		else { // click at line -> prompt to select two stations
			if (value == 0) {
				m_mouseState = 100;
			}
			else if (value == 1) {
				m_mouseState = 1;
			}
			else {
				m_mouseState = 101;
			}
		}
	}
	else if (m_mouseState == 3) {
		if (value == 2) {
			m_tempLineIndex = type;
			m_mouseState = 4;
		}
		else {
			m_mouseState = 104;
		}
	}
}

void GameState::resetAtSelectionArea(Scyyz12Engine2* pContext, int iMapX)
{
	int type = m_sa->getTileType(iMapX);
	if (type < 0) {
		int value = m_sa->getMapValue(iMapX, 0);
		m_sa->setAndRedrawMapValueAt(iMapX, 0, value + 1, pContext, pContext->getBackgroundSurface());
	}
}

void GameState::clickAtFirstStation(Scyyz12Engine2* pContext, int iX, int iY)
{
	if (m_propertyIndex == 20) { // add a station at head / tail
		if ((m_tempStationIndex = isPointInStation(iX, iY)) != -1) {
			int lineIndex = m_tempLineIndex / 10;
			if (m_lr[lineIndex]->isStationInStationList(m_sm->getStation(m_tempStationIndex))) {
				m_mouseState = 106;
			}
			else {
				if (m_tempLineIndex % 10 == 0) {
					if (m_lr[lineIndex]->isCanAddStation(m_sm->getStation(m_tempStationIndex), m_lr[lineIndex]->getStationList()[0])) {
						m_lr[lineIndex]->addStationHead(m_sm->getStation(m_tempStationIndex), true, m_railCount++);
						m_mouseState = 0;
					}
					else {
						for (int i = 0; i < m_sa->getTileWidth(); i++) {
							if (m_sa->getTileType(i) == -1) {
								if (m_sa->getMapValue(i, 0) > 0) {
									m_sa->setAndRedrawMapValueAt(i, 0, m_sa->getMapValue(i, 0) - 1, pContext, pContext->getBackgroundSurface());
									m_lr[lineIndex]->addStationHead(m_sm->getStation(m_tempStationIndex), true, m_railCount++);
									m_mouseState = 0;
								}
								else {
									m_mouseState = 108;
								}
								break;
							}
						}
					}
				}
				else {
					if (m_lr[lineIndex]->isCanAddStation(m_sm->getStation(m_tempStationIndex), m_lr[lineIndex]->getStationList().back())) {
						m_lr[lineIndex]->addStationTail(m_sm->getStation(m_tempStationIndex), true, m_railCount++);
						m_mouseState = 0;
					}
					else {
						for (int i = 0; i < m_sa->getTileWidth(); i++) {
							if (m_sa->getTileType(i) == -1) {
								if (m_sa->getMapValue(i, 0) > 0) {
									m_sa->setAndRedrawMapValueAt(i, 0, m_sa->getMapValue(i, 0) - 1, pContext, pContext->getBackgroundSurface());
									m_lr[lineIndex]->addStationTail(m_sm->getStation(m_tempStationIndex), true, m_railCount++);
									m_mouseState = 0;
								}
								else {
									m_mouseState = 108;
								}
								break;
							}
						}
					}
				}

			}
		}
		else {
			m_mouseState = 102;
		}
	}
	else if (m_sa->getTileType(m_propertyIndex) >= 0) { // initialise a line -> prompt to add another station
		if ((m_tempStationIndex = isPointInStation(iX, iY)) != -1) {
			m_mouseState = 2;
		}
		else {
			m_mouseState = 102;
		}
	}
	else if (m_sa->getTileType(m_propertyIndex) == -6) { // add a carriage to that train
		if (m_lr[m_tempLineIndex]->isPosATrainInLine(iX, iY) != -1) {
			m_lr[m_tempLineIndex]->addCarriage(m_lr[m_tempLineIndex]->isPosATrainInLine(iX, iY));
			m_mouseState = 0;
		}
		else {
			m_mouseState = 107;
		}
	}
	else { // add a train to that line
		int stationIndex = isPointInStation(iX, iY);
		if (stationIndex != -1) {
			int x = m_sm->getStation(stationIndex)->getStation()->getXCentre();
			int y = m_sm->getStation(stationIndex)->getStation()->getYCentre();
			if (m_lr[m_tempLineIndex]->isPosAStationInLine(x, y)) {
				m_lr[m_tempLineIndex]->addTrain(m_trainCount++, m_sa->getTileType(m_propertyIndex) + 5, x, y + 2);
				m_mouseState = 0;
			}
			else {
				m_mouseState = 105;
			}
		}
		else {
			m_mouseState = 102;
		}
	}

}

void GameState::clickAtSecondStation(Scyyz12Engine2* pContext, int iX, int iY)
{
	int secondStationIndex = isPointInStation(iX, iY);
	if (secondStationIndex != -1) {
		if (secondStationIndex == m_tempStationIndex) {
			m_mouseState = 103;
		}
		else {
			if (m_lr[m_sa->getTileType(m_propertyIndex)]->isCanAddStation(m_sm->getStation(m_tempStationIndex), m_sm->getStation(secondStationIndex))) {
				m_lr[m_sa->getTileType(m_propertyIndex)]->iniAdd2Stations(m_sm->getStation(m_tempStationIndex), m_sm->getStation(secondStationIndex),
					false, m_railCount, m_railCount + 1, m_railCount + 2);
				m_railCount += 3;
				int value = m_sa->getMapValue(m_propertyIndex, 0);
				m_sa->setAndRedrawMapValueAt(m_propertyIndex, 0, value + 1, pContext, pContext->getBackgroundSurface());

				m_mouseState = 0;
			}
			else {
				for (int i = 0; i < m_sa->getTileWidth(); i++) {
					if (m_sa->getTileType(i) == -1) {
						if (m_sa->getMapValue(i, 0) > 0) {
							m_sa->setAndRedrawMapValueAt(i, 0, m_sa->getMapValue(i, 0) - 1, pContext, pContext->getBackgroundSurface());

							m_lr[m_sa->getTileType(m_propertyIndex)]->iniAdd2Stations(m_sm->getStation(m_tempStationIndex), m_sm->getStation(secondStationIndex),
								false, m_railCount, m_railCount + 1, m_railCount + 2);
							m_railCount += 3;
							int value = m_sa->getMapValue(m_propertyIndex, 0);
							m_sa->setAndRedrawMapValueAt(m_propertyIndex, 0, value + 1, pContext, pContext->getBackgroundSurface());

							m_mouseState = 0;
						}
						else {
							m_mouseState = 108;
						}

						break;
					}
				}
			}
		}
	}
	else {
		m_mouseState = 102;
	}
}

int GameState::isPointInStation(int iX, int iY)
{
	for (int i = 0; i < m_sm->getStationList().size(); i++) {
		Station* station = m_sm->getStation(i)->getStation();
		if (station->getDrawingRegionLeft() <= iX && station->getDrawingRegionRight() >= iX &&
			station->getDrawingRegionTop() <= iY && station->getDrawingRegionBottom() >= iY) {
			return i;
		}
	}
	return -1;
}

int GameState::clickAtRailEnd(int iX, int iY)
{
	for (int i = 0; i < m_lr.size(); i++) {
		std::vector<Rail*> railList = m_lr[i]->getRailList();
		if (railList.size() != 0) {
			if (railList[0]->getDrawingRegionLeft() <= iX && railList[0]->getDrawingRegionRight() >= iX &&
				railList[0]->getDrawingRegionTop() <= iY && railList[0]->getDrawingRegionBottom() >= iY) {
				short direction = railList[0]->getRailStartDirection();
				int stationX = m_lr[i]->getStationList()[0]->getStation()->getXCentre();
				int stationY = m_lr[i]->getStationList()[0]->getStation()->getYCentre();
				short directionStation = directionToStation(iX, iY, stationX, stationY);
				if (direction == directionStation) {
					return i * 10;
				}
			}
			if (railList.back()->getDrawingRegionLeft() <= iX && railList.back()->getDrawingRegionRight() >= iX &&
				railList.back()->getDrawingRegionTop() <= iY && railList.back()->getDrawingRegionBottom() >= iY) {
				short direction = railList.back()->getRailStartDirection();
				int stationX = m_lr[i]->getStationList().back()->getStation()->getXCentre();
				int stationY = m_lr[i]->getStationList().back()->getStation()->getYCentre();
				short directionStation = directionToStation(iX, iY, stationX, stationY);
				if (direction == directionStation) {
					return i * 10 + 1;
				}
			}
		}
	}
	return -1;
}

short GameState::directionToStation(int iX, int iY, int iStationX, int iStationY)
{
	double cosValue = acos((iX - iStationX) / sqrt((iY - iStationY) * (iY - iStationY) + (iX - iStationX) * (iX - iStationX))) * 180 / M_PI;
	double sinValue = asin((iY - iStationY) / sqrt((iY - iStationY) * (iY - iStationY) + (iX - iStationX) * (iX - iStationX))) * 180 / M_PI;
	if (sinValue < -67.5) {
		return 0;
	}
	else if (sinValue > 67.5) {
		return 4;
	}
	else if (cosValue > 157.5) {
		return 6;
	}
	else if (cosValue < 22.5) {
		return 2;
	}
	else if (cosValue >= 22.5 && cosValue <= 67.5) {
		if (sinValue < 0) {
			return 1;
		}
		else {
			return 3;
		}
	}
	else {
		if (sinValue < 0) {
			return 7;
		}
		else {
			return 5;
		}
	}
}

int GameState::virtInitialise(Scyyz12Engine2* pContext)
{
	m_filterScaling = Scyyz12FilterPointsScaling(1, 1, 80, 1299, 720, pContext);
	m_filterTranslation = Scyyz12FilterPointsTranslation(0, 0, &m_filterScaling);
	m_filterMask = Scyyz12FilterPointsRectangularMask(1, 80, 1299, 720, &m_filterTranslation);
	pContext->getForegroundSurface()->setDrawPointsFilter(&m_filterMask);
	pContext->getBackgroundSurface()->setDrawPointsFilter(&m_filterMask);

	backArrow = ImageManager::loadImage("resources/arrow-right-50-50.png", true);
	pause = ImageManager::loadImage("resources/pause-50-50.png", true);
	mapping = ImagePixelMappingRotateAndColour(0, backArrow.getWidth() / 2, backArrow.getHeight() / 2);

	doIfNeedsReload();

	m_iniTimeCount = pContext->getModifiedTime();

	if (m_sa == nullptr) { // m_sa == nullptr && m_sm == nullptr && m_lr.size() == 0

		if (m_bIsContinue) {
			FileReader frContinue("resources/level-continue.txt");
			m_iLevelId = frContinue.readNumber();

			// ----- map -----
			std::string mapText("resources/map-");
			mapText.append(std::to_string(m_iLevelId));
			mapText.append(".png");
			map = ImageManager::loadImage(mapText, true);
			pContext->getBackgroundSurface()->mySDLLockSurface();
			map.renderImage(pContext->getBackgroundSurface(), 0, 0, 0, 0, 1300, 800);
			pContext->getBackgroundSurface()->mySDLUnlockSurface();
			// ---------------

			int temp = frContinue.readNumber();
			if (temp != 100000) printf("E-1  %d\n", temp);

			// selection area
			// -----------------
			std::vector<unsigned int> vecLineColors;
			std::vector<int> vecLineState;
			unsigned int iUndiscoveredColor;
			std::vector<int> vecProperty;
			while (true) {
				temp = frContinue.readNumber();
				if (temp == 100001) break;
				vecLineColors.emplace_back(temp);
				temp = frContinue.readNumber();
				vecLineState.emplace_back(temp);
			}
			iUndiscoveredColor = frContinue.readNumber();
			for (int i = 0; i < 6; i++) {
				temp = frContinue.readNumber();
				vecProperty.emplace_back(temp);
			}
			temp = frContinue.readNumber();
			if (temp != 100002) printf("E-2\n");
			// -----------------
			m_sa = new SelectionArea(vecLineColors, iUndiscoveredColor,
				(vecProperty[1] != -1), (vecProperty[2] != -1), (vecProperty[3] != -1),
				(vecProperty[0] != -1), (vecProperty[4] != -1), (vecProperty[5] != -1));
			for (int i = 0; i < 6; i++) {
				if (vecProperty[i] != -1) {
					m_sa->setProperty(i - 6, vecProperty[i]);
				}
			}
			for (int i = 0; i < vecLineState.size(); i++) {
				if (vecLineState[i] == 1) {
					m_sa->addNewLineState2Discovered();
				}
				else if (vecLineState[i] == 2) {
					m_sa->addNewLineState2Discovered();
					m_sa->setLineState2Using(i);
				}
			}
			// -----------------

			// station map
			// -----------------
			m_sm = new StationMap(pContext);
			while (true) {
				int iX = frContinue.readNumber();
				if (iX == 100003) break;
				int iY = frContinue.readNumber();
				int iType = frContinue.readNumber();
				int iId = frContinue.readNumber();
				StationCollection* station = new StationCollection(-iId, iType, pContext, iX, iY);
				int iIsAngry = frContinue.readNumber();
				int iAngryValue = frContinue.readNumber();
				station->getStation()->setIsAngry(iIsAngry);
				station->getStation()->setAngryValue(iAngryValue);
				temp = frContinue.readNumber();
				if (temp != 1000000) printf("E-sm\n");
				while (true) {
					temp = frContinue.readNumber();
					if (temp == 1000001) break;
					station->getStation()->addPassenger(new PassengerCollection(temp, pContext));
				}
				m_sm->addStation(station);
			}
			// -----------------

			// line route
			// -----------------
			for (unsigned int color : vecLineColors) {
				LineRoute* lr = new LineRoute(pContext, color);
				m_lr.emplace_back(lr);
			}
			// -----------------
			temp = frContinue.readNumber();
			if (temp != 1000005) printf("E-lr-1\n");
			for (int i = 0; i < m_lr.size(); i++) {
				while (true) {
					int iId = frContinue.readNumber();
					if (iId == 1000005 || iId == 100004) break;
					int iIsEnd = frContinue.readNumber();
					int iXS = frContinue.readNumber();
					int iYS = frContinue.readNumber();
					int iXE = frContinue.readNumber();
					int iYE = frContinue.readNumber();
					int iIs45 = frContinue.readNumber();
					int iDirection = frContinue.readNumber();
					int iColor = frContinue.readNumber();
					if (iIsEnd) {
						m_lr[i]->addRail(new Rail(-iId, pContext, iXS, iYS, iDirection, iColor));
					}
					else {
						m_lr[i]->addRail(new Rail(-iId, pContext, iXS, iYS, iXE, iYE, iIs45, iColor));
					}

				}
			}
			// -----------------
			temp = frContinue.readNumber();
			if (temp != 1000005) printf("E-lr-2\n");
			for (int i = 0; i < m_lr.size(); i++) {
				while (true) {
					temp = frContinue.readNumber();
					if (temp == 1000005 || temp == 100005) break;
					for (StationCollection* station : m_sm->getStationList()) {
						if (station->getId() == (-temp)) {
							m_lr[i]->addStation(station);
							break;
						}
					}
				}
			}
			// -----------------
			if (temp != 100005) printf("E-lr-3-p\n");
			temp = frContinue.readNumber();
			if (temp != 1000005) printf("E-lr-3\n");
			for (int i = 0; i < m_lr.size(); i++) {
				while (true) {
					int iId = frContinue.readNumber();
					if (iId == 1000005 || iId == 100006) break;
					int iType = frContinue.readNumber();
					int iX = frContinue.readNumber();
					int iY = frContinue.readNumber();
					int iColor = frContinue.readNumber();
					int iDirection = frContinue.readNumber();
					TrainCollection* train = new TrainCollection(-iId, iType, pContext, iX, iY, iColor);
					train->getTrain()->setDirection(iDirection);
					temp = frContinue.readNumber();
					if (temp != 1000000) printf("E-lr-3-1\n");
					while (true) {
						int iType = frContinue.readNumber();
						if (iType == 1000001) break;
						int iX = frContinue.readNumber();
						int iY = frContinue.readNumber();
						int iDirection = frContinue.readNumber();
						int iSpeed = frContinue.readNumber();
						CarriageCollection* carriage = new CarriageCollection(iType, pContext, iX, iY, iColor, iSpeed);
						carriage->getCarriage()->setDirection(iDirection);
						temp = frContinue.readNumber();
						if (temp != 1000002) printf("E-lr-3-2\n");
						std::vector<PassengerCollection*> vecPassenger;
						int iPassengerCount = 0;
						while (true) {
							int iType = frContinue.readNumber();
							if (iType == 1000003) break;
							if (iType == -1) vecPassenger.emplace_back(nullptr);
							else {
								PassengerCollection* passenger = new PassengerCollection(iType, pContext);
								passenger->getPassenger()->setColor(carriage->getCarriage()->getPassengerColor());
								vecPassenger.emplace_back(passenger);
								iPassengerCount++;
							}
						}
						carriage->getCarriage()->setPassengerList(vecPassenger, iPassengerCount);
						carriage->getCarriage()->setPassengerPosition();
						train->getTrain()->addCarriage(carriage);
					}
					train->getTrain()->recalculatePassengerCount();
					m_lr[i]->addTrain(train);
				}
			}
			// -----------------
			temp = frContinue.readNumber();
			if (temp != 1000005) printf("E-lr-4\n");
			for (int i = 0; i < m_lr.size(); i++) {
				while (true) {
					int iFirst = frContinue.readNumber();
					if (iFirst == 1000005 || iFirst == 100007) break;
					int iSecond = frContinue.readNumber();
					m_lr[i]->addTurnPoints(iFirst, iSecond);
				}
			}
			// -----------------
			temp = frContinue.readNumber();
			if (temp != 1000005) printf("E-lr-5\n");
			for (int i = 0; i < m_lr.size(); i++) {
				while (true) {
					int iFirst = frContinue.readNumber();
					if (iFirst == 1000005 || iFirst == 100008) break;
					int iSecond = frContinue.readNumber();
					for (StationCollection* station : m_sm->getStationList()) {
						if (station->getId() == (-iSecond)) {
							m_lr[i]->addStation(iFirst, station);
							break;
						}
					}
				}
			}
			// -----------------

			// score information
			m_dayCount = frContinue.readNumber();
			m_scoreCount = frContinue.readNumber();
			temp = frContinue.readNumber();
			if (temp != 100009) printf("E-final\n");

			for (LineRoute* lr : m_lr) {
				lr->update(m_lr);
			}
		}
		else {
			std::string fileName("resources/level-");
			fileName.append(std::to_string(m_iLevelId));
			fileName.append(".txt");
			FileReader frLevel((char*)(fileName.c_str()));

			// ----- map -----
			std::string mapText("resources/map-");
			mapText.append(std::to_string(m_iLevelId));
			mapText.append(".png");
			map = ImageManager::loadImage(mapText, true);
			pContext->getBackgroundSurface()->mySDLLockSurface();
			map.renderImage(pContext->getBackgroundSurface(), 0, 0, 0, 0, 1300, 800);
			pContext->getBackgroundSurface()->mySDLUnlockSurface();
			// ---------------

			int temp = frLevel.readNumber();
			if (temp != 100000) printf("E-1  %d\n", temp);

			// selection area
			// -----------------
			std::vector<unsigned int> vecLineColors;
			std::vector<int> vecLineState;
			unsigned int iUndiscoveredColor;
			std::vector<int> vecProperty;
			while (true) {
				temp = frLevel.readNumber();
				if (temp == 100001) break;
				vecLineColors.emplace_back(temp);
				temp = frLevel.readNumber();
				vecLineState.emplace_back(temp);
			}
			iUndiscoveredColor = frLevel.readNumber();
			for (int i = 0; i < 6; i++) {
				temp = frLevel.readNumber();
				vecProperty.emplace_back(temp);
			}
			temp = frLevel.readNumber();
			if (temp != 100002) printf("E-2\n");
			// -----------------
			m_sa = new SelectionArea(vecLineColors, iUndiscoveredColor,
				(vecProperty[1] != -1), (vecProperty[2] != -1), (vecProperty[3] != -1),
				(vecProperty[0] != -1), (vecProperty[4] != -1), (vecProperty[5] != -1));
			for (int i = 0; i < 6; i++) {
				if (vecProperty[i] != -1) {
					m_sa->setProperty(i - 6, vecProperty[i]);
				}
			}
			for (int i = 0; i < vecLineState.size(); i++) {
				if (vecLineState[i] == 1) {
					m_sa->addNewLineState2Discovered();
				}
				else if (vecLineState[i] == 2) {
					m_sa->addNewLineState2Discovered();
					m_sa->setLineState2Using(i);
				}
			}
			// -----------------

			// station map
			// -----------------
			int iX = frLevel.readNumber();
			int iY = frLevel.readNumber();
			std::vector<short> vecStationType;
			while (true) {
				temp = frLevel.readNumber();
				if (temp == 100003) break;
				vecStationType.emplace_back(temp);
			}
			// -----------------
			m_sm = new StationMap(pContext);
			m_sm->addStationInRectangle(m_stationCount++, vecStationType[0], iX, iY, 100, 100);
			for (int i = 1; i < vecStationType.size(); i++) {
				m_sm->addStationNearCurrent(m_stationCount++, vecStationType[i]);
			}
			// -----------------

			// line route
			// -----------------
			// -----------------
			for (unsigned int color : vecLineColors) {
				LineRoute* lr = new LineRoute(pContext, color);
				m_lr.emplace_back(lr);
			}
			// -----------------
		}
	}

	return pContext->BaseEngine::virtInitialise();


}

void GameState::virtSetupBackgroundBuffer(Scyyz12Engine2* pContext)
{
	pContext->fillBackground(0xffffff);

	// map
	map.renderImage(pContext->getBackgroundSurface(), 0, 0, 0, 0, 1300, 800);

	// Exit btn
	mapping.setTransparencyColour(0xffffff);
	mapping.setRotation(M_PI);
	backArrow.renderImageApplyingMapping(pContext, pContext->getBackgroundSurface(), 30, 30, backArrow.getWidth(), backArrow.getHeight(), &mapping);

	// Pause btn
	mapping.setRotation(0);
	pause.renderImageApplyingMapping(pContext, pContext->getBackgroundSurface(), 100, 30, pause.getWidth(), pause.getHeight(), &mapping);

	// Selection area
	pContext->drawBackgroundRectangle(280, 725, 1020, 799, 0xeeeeee);
	pContext->drawBackgroundThickLine(280, 725, 1020, 725, 0xaaaaaa, 2);

	m_sa->setTopLeftPositionOnScreen(300, 730);
	m_sa->drawAllTiles(pContext, pContext->getBackgroundSurface());
}

void GameState::virtDrawStringsOnTop(Scyyz12Engine2* pContext)
{
	pContext->drawForegroundString(650 - 300, 38, "Day", 0x777777, pContext->getFont("Ubuntu-Medium.ttf", 20));
	char strDay[10]; sprintf(strDay, "%d", m_dayCount);
	pContext->drawForegroundString(650 - 250, 33, strDay, 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));

	pContext->drawForegroundRectangle(650 - 150, 38, 650 + 350, 42, 0xDDDDDD);
	pContext->drawForegroundRectangle(650 - 150, 30, 650 - 146, 50, 0x777777);
	pContext->drawForegroundRectangle(650 + 346, 30, 650 + 350, 50, 0x777777);
	int x = 500 + m_timeCount;
	pContext->drawForegroundRectangle(x, 30, x + 4, 50, 0x000000);

	pContext->drawForegroundString(650 + 400, 38, "Passenger", 0x777777, pContext->getFont("Ubuntu-Medium.ttf", 20));
	char strPassenger[20]; sprintf(strPassenger, "%d", m_scoreCount);
	pContext->drawForegroundString(650 + 505, 33, strPassenger, 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));

	char strPrompt[1000];
	switch (m_mouseState)
	{
	case 0:
		sprintf(strPrompt, "Add a line / Extend a line / Add a train / Add a carriage");
		//pContext->drawForegroundString(650 - 450, 100, "Click a asset / line end", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
		break;
	case 1:
		sprintf(strPrompt, "Click a station (right click to cancel)");
		//pContext->drawForegroundString(650 - 150, 100, "Click a station (right click to cancel)", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
		break;
	case 2:
		sprintf(strPrompt, "Click another station (right click to cancel)");
		//pContext->drawForegroundString(650 - 150, 100, "Click another station (right click to cancel)", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
		break;
	case 3:
		sprintf(strPrompt, "Click a line (right click to cancel)");
		//pContext->drawForegroundString(650 - 450, 100, "Click a line (right click to cancel)", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
		break;
	case 4:
		sprintf(strPrompt, "Click a station /train on that line (right click to cancel)");
		//pContext->drawForegroundString(650 - 450, 100, "Click a station /train on that line (right click to cancel)", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
		break;
	case 100:
		sprintf(strPrompt, "E - line not discovered (right click to cancel)");
		//pContext->drawForegroundString(650 - 450, 100, "E - line not discovered (right click to cancel)", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
		break;
	case 101:
		sprintf(strPrompt, "E - line already in use (right click to cancel)");
		//pContext->drawForegroundString(650 - 450, 100, "E - line already in use (right click to cancel)", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
		break;
	case 102:
		sprintf(strPrompt, "E - not click at station (right click to cancel)");
		//pContext->drawForegroundString(650 - 450, 100, "E - not click at station (right click to cancel)", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
		break;
	case 103:
		sprintf(strPrompt, "E - click at the same station twice (right click to cancel)");
		//pContext->drawForegroundString(650 - 450, 100, "E - click at the same station twice (right click to cancel)", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
		break;
	case 104:
		sprintf(strPrompt, "E - line not in use (right click to cancel)");
		//pContext->drawForegroundString(650 - 450, 100, "E - line not in use (right click to cancel)", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
		break;
	case 105:
		sprintf(strPrompt, "E - the station not in given line (right click to cancel)");
		//pContext->drawForegroundString(650 - 450, 100, "E - the station not in given line (right click to cancel)", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
		break;
	case 106:
		sprintf(strPrompt, "E - the station already in given line (right click to cancel)");
		//pContext->drawForegroundString(650 - 450, 100, "E - the station already in given line (right click to cancel)", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
		break;
	case 107:
		sprintf(strPrompt, "E - not clicking at a train at given line (right click to cancel)");
		//pContext->drawForegroundString(650 - 450, 100, "E - not clicking at a train at given line (right click to cancel)", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
		break;
	case 108:
		sprintf(strPrompt, "E - no enough bridges (right click to cancel)");
		//pContext->drawForegroundString(650 - 450, 100, "E - no enough bridges (right click to cancel)", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
		break;
	case 200:
		sprintf(strPrompt, "TEST (right click to cancel)");
		//pContext->drawForegroundString(650 - 450, 100, "TEST (right click to cancel)", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
		break;
	default:
		sprintf(strPrompt, "");
		break;
	}
	pContext->drawForegroundString(650 - 150, 60, strPrompt, 0x777777, pContext->getFont("Ubuntu-Medium.ttf", 20));

	if (m_bRunToStop || m_bSelectionNotMade) {
		m_filterTranslation.setOffset(0, 0);
		m_filterScaling.setStretch(1);

		// -----
		pContext->redrawDisplay();
		pContext->getBackgroundSurface()->mySDLLockSurface();
		virtSetupBackgroundBuffer(pContext);
		pContext->getBackgroundSurface()->mySDLUnlockSurface();
		// -----

		pContext->drawForegroundRectangle(300, 200, 1000, 600, 0xaaaaaa);
		pContext->drawForegroundRectangle(302, 202, 998, 598, 0xeeeeee);
		pContext->drawForegroundString(650 - 310, 210, "A brand new day!", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
		pContext->drawForegroundString(650 - 310, 260, "Select one update for your railway:", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));

		SimpleImage rail = ImageManager::loadImage("resources/rail-80-80-g.png", true);
		SimpleImage train = ImageManager::loadImage("resources/train_normal-80-80-g.png", true);
		SimpleImage trainFast = ImageManager::loadImage("resources/train_fast_2-80-80-g.png", true);
		SimpleImage trainIntelligent = ImageManager::loadImage("resources/train_intelli_2-80-80-g.png", true);
		SimpleImage carriage = ImageManager::loadImage("resources/carriage-80-80-g.png", true);
		SimpleImage bridge = ImageManager::loadImage("resources/bridge_3-80-80-g.png", true);
		if (m_iLevelId == 0) {
			if (m_sa->isAllLineDiscovered()) {
				train.renderImage(pContext->getForegroundSurface(), 0, 0, 430, 390, 80, 80);
				carriage.renderImage(pContext->getForegroundSurface(), 0, 0, 610, 390, 80, 80);
				bridge.renderImage(pContext->getForegroundSurface(), 0, 0, 790, 390, 80, 80);

				pContext->drawForegroundOval(495, 385, 525, 415, 0xffffff);
				pContext->drawForegroundOval(675, 385, 705, 415, 0xffffff);
				pContext->drawForegroundOval(855, 385, 885, 415, 0xffffff);
				pContext->drawForegroundString(503, 385, "2", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 25));
				pContext->drawForegroundString(683, 385, "2", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 25));
				pContext->drawForegroundString(863, 385, "3", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 25));
			}
			else {
				rail.renderImage(pContext->getForegroundSurface(), 0, 0, 430, 390, 80, 80);
				train.renderImage(pContext->getForegroundSurface(), 0, 0, 550, 390, 80, 80);
				carriage.renderImage(pContext->getForegroundSurface(), 0, 0, 670, 390, 80, 80);
				bridge.renderImage(pContext->getForegroundSurface(), 0, 0, 790, 390, 80, 80);

				pContext->drawForegroundOval(493 - 20, 385, 513 - 20, 415, 0xffffff);
				pContext->drawForegroundRectangle(503 - 20, 385, 533 - 20, 415, 0xffffff);
				pContext->drawForegroundOval(523 - 20, 385, 543 - 20, 415, 0xffffff);
				pContext->drawForegroundOval(615 - 12, 385, 645 - 12, 415, 0xffffff);
				pContext->drawForegroundOval(735 - 12, 385, 765 - 12, 415, 0xffffff);
				pContext->drawForegroundOval(855 - 12, 385, 885 - 12, 415, 0xffffff);
				pContext->drawForegroundString(499 - 20, 387, "new", 0x666666, pContext->getFont("Ubuntu-Medium.ttf", 20));
				pContext->drawForegroundString(623 - 12, 385, "2", 0x666666, pContext->getFont("Ubuntu-Medium.ttf", 25));
				pContext->drawForegroundString(743 - 12, 385, "2", 0x666666, pContext->getFont("Ubuntu-Medium.ttf", 25));
				pContext->drawForegroundString(863 - 12, 385, "3", 0x666666, pContext->getFont("Ubuntu-Medium.ttf", 25));
			}
		}
		else if (m_iLevelId == 1) {
			if (m_sa->isAllLineDiscovered()) {
				train.renderImage(pContext->getForegroundSurface(), 0, 0, 430, 390, 80, 80);
				trainFast.renderImage(pContext->getForegroundSurface(), 0, 0, 610, 390, 80, 80);
				bridge.renderImage(pContext->getForegroundSurface(), 0, 0, 790, 390, 80, 80);

				pContext->drawForegroundOval(495, 385, 525, 415, 0xffffff);
				pContext->drawForegroundOval(675, 385, 705, 415, 0xffffff);
				pContext->drawForegroundOval(855, 385, 885, 415, 0xffffff);
				pContext->drawForegroundString(503, 385, "2", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 25));
				pContext->drawForegroundString(683, 385, "1", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 25));
				pContext->drawForegroundString(863, 385, "3", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 25));
			}
			else {
				rail.renderImage(pContext->getForegroundSurface(), 0, 0, 430, 390, 80, 80);
				train.renderImage(pContext->getForegroundSurface(), 0, 0, 550, 390, 80, 80);
				trainFast.renderImage(pContext->getForegroundSurface(), 0, 0, 670, 390, 80, 80);
				bridge.renderImage(pContext->getForegroundSurface(), 0, 0, 790, 390, 80, 80);

				pContext->drawForegroundOval(493 - 20, 385, 513 - 20, 415, 0xffffff);
				pContext->drawForegroundRectangle(503 - 20, 385, 533 - 20, 415, 0xffffff);
				pContext->drawForegroundOval(523 - 20, 385, 543 - 20, 415, 0xffffff);
				pContext->drawForegroundOval(615 - 12, 385, 645 - 12, 415, 0xffffff);
				pContext->drawForegroundOval(735 - 12, 385, 765 - 12, 415, 0xffffff);
				pContext->drawForegroundOval(855 - 12, 385, 885 - 12, 415, 0xffffff);
				pContext->drawForegroundString(499 - 20, 387, "new", 0x666666, pContext->getFont("Ubuntu-Medium.ttf", 20));
				pContext->drawForegroundString(623 - 12, 385, "2", 0x666666, pContext->getFont("Ubuntu-Medium.ttf", 25));
				pContext->drawForegroundString(743 - 12, 385, "1", 0x666666, pContext->getFont("Ubuntu-Medium.ttf", 25));
				pContext->drawForegroundString(863 - 12, 385, "3", 0x666666, pContext->getFont("Ubuntu-Medium.ttf", 25));
			}
		}
		else if (m_iLevelId == 2) {
			if (m_sa->isAllLineDiscovered()) {
				train.renderImage(pContext->getForegroundSurface(), 0, 0, 430, 390, 80, 80);
				trainIntelligent.renderImage(pContext->getForegroundSurface(), 0, 0, 550, 390, 80, 80);
				carriage.renderImage(pContext->getForegroundSurface(), 0, 0, 670, 390, 80, 80);
				bridge.renderImage(pContext->getForegroundSurface(), 0, 0, 790, 390, 80, 80);

				pContext->drawForegroundOval(495 - 12, 385, 525 - 12, 415, 0xffffff);
				pContext->drawForegroundOval(615 - 12, 385, 645 - 12, 415, 0xffffff);
				pContext->drawForegroundOval(735 - 12, 385, 765 - 12, 415, 0xffffff);
				pContext->drawForegroundOval(855 - 12, 385, 885 - 12, 415, 0xffffff);
				pContext->drawForegroundString(503 - 12, 385, "2", 0x666666, pContext->getFont("Ubuntu-Medium.ttf", 25));
				pContext->drawForegroundString(623 - 12, 385, "1", 0x666666, pContext->getFont("Ubuntu-Medium.ttf", 25));
				pContext->drawForegroundString(743 - 12, 385, "2", 0x666666, pContext->getFont("Ubuntu-Medium.ttf", 25));
				pContext->drawForegroundString(863 - 12, 385, "3", 0x666666, pContext->getFont("Ubuntu-Medium.ttf", 25));
			}
			else {
				rail.renderImage(pContext->getForegroundSurface(), 0, 0, 370, 390, 80, 80);
				train.renderImage(pContext->getForegroundSurface(), 0, 0, 490, 390, 80, 80);
				trainIntelligent.renderImage(pContext->getForegroundSurface(), 0, 0, 610, 390, 80, 80);
				carriage.renderImage(pContext->getForegroundSurface(), 0, 0, 730, 390, 80, 80);
				bridge.renderImage(pContext->getForegroundSurface(), 0, 0, 850, 390, 80, 80);

				pContext->drawForegroundOval(433 - 20, 385, 453 - 20, 415, 0xffffff);
				pContext->drawForegroundRectangle(443 - 20, 385, 473 - 20, 415, 0xffffff);
				pContext->drawForegroundOval(463 - 20, 385, 483 - 20, 415, 0xffffff);
				pContext->drawForegroundOval(555 - 12, 385, 585 - 12, 415, 0xffffff);
				pContext->drawForegroundOval(675 - 12, 385, 705 - 12, 415, 0xffffff);
				pContext->drawForegroundOval(795 - 12, 385, 825 - 12, 415, 0xffffff);
				pContext->drawForegroundOval(915 - 12, 385, 945 - 12, 415, 0xffffff);
				pContext->drawForegroundString(439 - 20, 387, "new", 0x666666, pContext->getFont("Ubuntu-Medium.ttf", 20));
				pContext->drawForegroundString(563 - 12, 385, "2", 0x666666, pContext->getFont("Ubuntu-Medium.ttf", 25));
				pContext->drawForegroundString(683 - 12, 385, "1", 0x666666, pContext->getFont("Ubuntu-Medium.ttf", 25));
				pContext->drawForegroundString(803 - 12, 385, "2", 0x666666, pContext->getFont("Ubuntu-Medium.ttf", 25));
				pContext->drawForegroundString(923 - 12, 385, "3", 0x666666, pContext->getFont("Ubuntu-Medium.ttf", 25));
			}
		}
		else if (m_iLevelId == 3) {
			if (m_sa->isAllLineDiscovered()) {
				train.renderImage(pContext->getForegroundSurface(), 0, 0, 430, 390, 80, 80);
				trainFast.renderImage(pContext->getForegroundSurface(), 0, 0, 550, 390, 80, 80);
				trainIntelligent.renderImage(pContext->getForegroundSurface(), 0, 0, 670, 390, 80, 80);
				carriage.renderImage(pContext->getForegroundSurface(), 0, 0, 790, 390, 80, 80);

				pContext->drawForegroundOval(495 - 12, 385, 525 - 12, 415, 0xffffff);
				pContext->drawForegroundOval(615 - 12, 385, 645 - 12, 415, 0xffffff);
				pContext->drawForegroundOval(735 - 12, 385, 765 - 12, 415, 0xffffff);
				pContext->drawForegroundOval(855 - 12, 385, 885 - 12, 415, 0xffffff);
				pContext->drawForegroundString(503 - 12, 385, "3", 0x666666, pContext->getFont("Ubuntu-Medium.ttf", 25));
				pContext->drawForegroundString(623 - 12, 385, "2", 0x666666, pContext->getFont("Ubuntu-Medium.ttf", 25));
				pContext->drawForegroundString(743 - 12, 385, "1", 0x666666, pContext->getFont("Ubuntu-Medium.ttf", 25));
				pContext->drawForegroundString(863 - 12, 385, "2", 0x666666, pContext->getFont("Ubuntu-Medium.ttf", 25));
			}
			else {
				rail.renderImage(pContext->getForegroundSurface(), 0, 0, 370, 390, 80, 80);
				train.renderImage(pContext->getForegroundSurface(), 0, 0, 490, 390, 80, 80);
				trainFast.renderImage(pContext->getForegroundSurface(), 0, 0, 610, 390, 80, 80);
				trainIntelligent.renderImage(pContext->getForegroundSurface(), 0, 0, 730, 390, 80, 80);
				carriage.renderImage(pContext->getForegroundSurface(), 0, 0, 850, 390, 80, 80);

				pContext->drawForegroundOval(433 - 20, 385, 453 - 20, 415, 0xffffff);
				pContext->drawForegroundRectangle(443 - 20, 385, 473 - 20, 415, 0xffffff);
				pContext->drawForegroundOval(463 - 20, 385, 483 - 20, 415, 0xffffff);
				pContext->drawForegroundOval(555 - 12, 385, 585 - 12, 415, 0xffffff);
				pContext->drawForegroundOval(675 - 12, 385, 705 - 12, 415, 0xffffff);
				pContext->drawForegroundOval(795 - 12, 385, 825 - 12, 415, 0xffffff);
				pContext->drawForegroundOval(915 - 12, 385, 945 - 12, 415, 0xffffff);
				pContext->drawForegroundString(439 - 20, 387, "new", 0x666666, pContext->getFont("Ubuntu-Medium.ttf", 20));
				pContext->drawForegroundString(563 - 12, 385, "3", 0x666666, pContext->getFont("Ubuntu-Medium.ttf", 25));
				pContext->drawForegroundString(683 - 12, 385, "2", 0x666666, pContext->getFont("Ubuntu-Medium.ttf", 25));
				pContext->drawForegroundString(803 - 12, 385, "1", 0x666666, pContext->getFont("Ubuntu-Medium.ttf", 25));
				pContext->drawForegroundString(923 - 12, 385, "2", 0x666666, pContext->getFont("Ubuntu-Medium.ttf", 25));
			}
		}

		char strDay[100]; sprintf(strDay, "And get ready for more passengers in Day %d", m_dayCount);
		pContext->drawForegroundString(650 - 310, 550, strDay, 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
	}
}

int GameState::virtInitialiseObjects(Scyyz12Engine2* pContext)
{
	pContext->destroyOldObjects(true);

	for (LineRoute* lr : m_lr) {
		lr->drawInitialise();
	}
	m_sm->drawInitialise();

	return 0;
}

void GameState::virtMouseMoved(Scyyz12Engine2* pContext, int iX, int iY)
{
	int iXClicked = pContext->convertVirtualPixelToClickedXPosition(iX), iYClicked = pContext->convertVirtualPixelToClickedYPosition(iY);
	//printf("## Debug - move at %d %d (virtual), %d %d (to clicked)\n", iX, iY, iXClicked, iYClicked);
	//printf("%d\n", m_sa->isValidTilePosition(iXClicked, iYClicked) ? 1 : 0);
	if (m_sa->isValidTilePosition(iXClicked, iYClicked)) {
		int mapX = m_sa->getMapXForScreenX(iXClicked);
		m_sa->mouseAt(mapX);
	}
	else {
		m_sa->mouseRemoved();
	}
	m_sa->drawAllTiles(pContext, pContext->getBackgroundSurface());
}

void GameState::virtMouseDown(Scyyz12Engine2* pContext, int iButton, int iX, int iY)
{
	int iXClicked = pContext->convertVirtualPixelToClickedXPosition(iX), iYClicked = pContext->convertVirtualPixelToClickedYPosition(iY);
	//printf("## Debug - click at %d %d (virtual), %d %d (to clicked)\n", iX, iY, iXClicked, iYClicked);
	//printf("## Debug - mouse state %d\n", m_mouseState);

	//if (iButton == SDL_BUTTON_RIGHT) {
	//	printf("## Debug - click at %d %d (virtual), %d\n", iX, iY, pContext->getBackgroundSurface()->getPixel(iX, iY));
	//}

	if (iButton == SDL_BUTTON_LEFT) {
		if (m_bIsNewDay && m_bSelectionNotMade) {
			if (m_iLevelId == 0) {
				if (m_sa->isAllLineDiscovered()) {
					if (iXClicked >= 430 && iXClicked <= 510 && iYClicked >= 390 && iYClicked <= 470) {
						m_sa->incProperty(-5);
						m_sa->incProperty(-5);
						m_bSelectionNotMade = false;
					}
					else if (iXClicked >= 610 && iXClicked <= 690 && iYClicked >= 390 && iYClicked <= 470) {
						m_sa->incProperty(-6);
						m_sa->incProperty(-6);
						m_bSelectionNotMade = false;
					}
					else if (iXClicked >= 790 && iXClicked <= 870 && iYClicked >= 390 && iYClicked <= 470) {
						m_sa->incProperty(-1);
						m_sa->incProperty(-1);
						m_sa->incProperty(-1);
						m_bSelectionNotMade = false;
					}
				}
				else {
					if (iXClicked >= 430 && iXClicked <= 510 && iYClicked >= 390 && iYClicked <= 470) {
						m_sa->addNewLineState2Discovered();
						m_bSelectionNotMade = false;
					}
					if (iXClicked >= 550 && iXClicked <= 630 && iYClicked >= 390 && iYClicked <= 470) {
						m_sa->incProperty(-5);
						m_sa->incProperty(-5);
						m_bSelectionNotMade = false;
					}
					else if (iXClicked >= 670 && iXClicked <= 750 && iYClicked >= 390 && iYClicked <= 470) {
						m_sa->incProperty(-6);
						m_sa->incProperty(-6);
						m_bSelectionNotMade = false;
					}
					else if (iXClicked >= 790 && iXClicked <= 870 && iYClicked >= 390 && iYClicked <= 470) {
						m_sa->incProperty(-1);
						m_sa->incProperty(-1);
						m_sa->incProperty(-1);
						m_bSelectionNotMade = false;
					}
				}
			}
			else if (m_iLevelId == 1) {
				if (m_sa->isAllLineDiscovered()) {
					if (iXClicked >= 430 && iXClicked <= 510 && iYClicked >= 390 && iYClicked <= 470) {
						m_sa->incProperty(-5);
						m_sa->incProperty(-5);
						m_bSelectionNotMade = false;
					}
					else if (iXClicked >= 610 && iXClicked <= 690 && iYClicked >= 390 && iYClicked <= 470) {
						m_sa->incProperty(-4);
						m_bSelectionNotMade = false;
					}
					else if (iXClicked >= 790 && iXClicked <= 870 && iYClicked >= 390 && iYClicked <= 470) {
						m_sa->incProperty(-1);
						m_sa->incProperty(-1);
						m_sa->incProperty(-1);
						m_bSelectionNotMade = false;
					}
				}
				else {
					if (iXClicked >= 430 && iXClicked <= 510 && iYClicked >= 390 && iYClicked <= 470) {
						m_sa->addNewLineState2Discovered();
						m_bSelectionNotMade = false;
					}
					if (iXClicked >= 550 && iXClicked <= 630 && iYClicked >= 390 && iYClicked <= 470) {
						m_sa->incProperty(-5);
						m_sa->incProperty(-5);
						m_bSelectionNotMade = false;
					}
					else if (iXClicked >= 670 && iXClicked <= 750 && iYClicked >= 390 && iYClicked <= 470) {
						m_sa->incProperty(-4);
						m_bSelectionNotMade = false;
					}
					else if (iXClicked >= 790 && iXClicked <= 870 && iYClicked >= 390 && iYClicked <= 470) {
						m_sa->incProperty(-1);
						m_sa->incProperty(-1);
						m_sa->incProperty(-1);
						m_bSelectionNotMade = false;
					}
				}
			}
			else if (m_iLevelId == 2) {
				if (m_sa->isAllLineDiscovered()) {
					if (iXClicked >= 430 && iXClicked <= 510 && iYClicked >= 390 && iYClicked <= 470) {
						m_sa->incProperty(-5);
						m_sa->incProperty(-5);
						m_bSelectionNotMade = false;
					}
					else if (iXClicked >= 550 && iXClicked <= 630 && iYClicked >= 390 && iYClicked <= 470) {
						m_sa->incProperty(-3);
						m_bSelectionNotMade = false;
					}
					else if (iXClicked >= 670 && iXClicked <= 750 && iYClicked >= 390 && iYClicked <= 470) {
						m_sa->incProperty(-6);
						m_sa->incProperty(-6);
						m_bSelectionNotMade = false;
					}
					else if (iXClicked >= 790 && iXClicked <= 870 && iYClicked >= 390 && iYClicked <= 470) {
						m_sa->incProperty(-1);
						m_sa->incProperty(-1);
						m_sa->incProperty(-1);
						m_bSelectionNotMade = false;
					}
				}
				else {
					if (iXClicked >= 370 && iXClicked <= 450 && iYClicked >= 390 && iYClicked <= 470) {
						m_sa->addNewLineState2Discovered();
						m_bSelectionNotMade = false;
					}
					else if (iXClicked >= 490 && iXClicked <= 570 && iYClicked >= 390 && iYClicked <= 470) {
						m_sa->incProperty(-5);
						m_sa->incProperty(-5);
						m_bSelectionNotMade = false;
					}
					else if (iXClicked >= 610 && iXClicked <= 690 && iYClicked >= 390 && iYClicked <= 470) {
						m_sa->incProperty(-3);
						m_bSelectionNotMade = false;
					}
					else if (iXClicked >= 730 && iXClicked <= 810 && iYClicked >= 390 && iYClicked <= 470) {
						m_sa->incProperty(-6);
						m_sa->incProperty(-6);
						m_bSelectionNotMade = false;
					}
					else if (iXClicked >= 850 && iXClicked <= 930 && iYClicked >= 390 && iYClicked <= 470) {
						m_sa->incProperty(-1);
						m_sa->incProperty(-1);
						m_sa->incProperty(-1);
						m_bSelectionNotMade = false;
					}
				}
			}
			else if (m_iLevelId == 3) {
				if (m_sa->isAllLineDiscovered()) {
					if (iXClicked >= 430 && iXClicked <= 510 && iYClicked >= 390 && iYClicked <= 470) {
						m_sa->incProperty(-5);
						m_sa->incProperty(-5);
						m_sa->incProperty(-5);
						m_bSelectionNotMade = false;
					}
					else if (iXClicked >= 550 && iXClicked <= 630 && iYClicked >= 390 && iYClicked <= 470) {
						m_sa->incProperty(-4);
						m_sa->incProperty(-4);
						m_bSelectionNotMade = false;
					}
					else if (iXClicked >= 670 && iXClicked <= 750 && iYClicked >= 390 && iYClicked <= 470) {
						m_sa->incProperty(-3);
						m_bSelectionNotMade = false;
					}
					else if (iXClicked >= 790 && iXClicked <= 870 && iYClicked >= 390 && iYClicked <= 470) {
						m_sa->incProperty(-6);
						m_sa->incProperty(-6);
						m_bSelectionNotMade = false;
					}
				}
				else {
					if (iXClicked >= 370 && iXClicked <= 450 && iYClicked >= 390 && iYClicked <= 470) {
						m_sa->addNewLineState2Discovered();
						m_bSelectionNotMade = false;
					}
					else if (iXClicked >= 490 && iXClicked <= 570 && iYClicked >= 390 && iYClicked <= 470) {
						m_sa->incProperty(-5);
						m_sa->incProperty(-5);
						m_sa->incProperty(-5);
						m_bSelectionNotMade = false;
					}
					else if (iXClicked >= 610 && iXClicked <= 690 && iYClicked >= 390 && iYClicked <= 470) {
						m_sa->incProperty(-4);
						m_sa->incProperty(-4);
						m_bSelectionNotMade = false;
					}
					else if (iXClicked >= 730 && iXClicked <= 810 && iYClicked >= 390 && iYClicked <= 470) {
						m_sa->incProperty(-3);
						m_bSelectionNotMade = false;
					}
					else if (iXClicked >= 850 && iXClicked <= 930 && iYClicked >= 390 && iYClicked <= 470) {
						m_sa->incProperty(-6);
						m_sa->incProperty(-6);
						m_bSelectionNotMade = false;
					}
				}
			}

		}
		else if (m_mouseState == 0) {
			if (m_sa->isValidTilePosition(iXClicked, iYClicked)) {
				int mapX = m_sa->getMapXForScreenX(iXClicked);
				clickAtSelectionArea(pContext, mapX);
			}
			else if ((m_tempLineIndex = clickAtRailEnd(iX, iY)) != -1) {
				m_mouseState = 1;
				m_propertyIndex = 20;
			}
			else {
				if (iXClicked > 30 && iXClicked < 80) {
					if (iYClicked > 30 && iYClicked < 80) {
						writeToContinueFile(true);
						pContext->changeState("start");
					}
				}
				else if (iXClicked > 100 && iXClicked < 150) {
					if (iYClicked > 30 && iYClicked < 80) {
						pContext->changeState("pause", 0, m_iLevelId);
					}
				}
			}
		}
		else if (m_mouseState == 1) {
			clickAtFirstStation(pContext, iX, iY);
		}
		else if (m_mouseState == 2) {
			//if (m_sa->getTileType(m_propertyIndex) >= 0) {
			clickAtSecondStation(pContext, iX, iY);
			//}
		}
		else if (m_mouseState == 3) {
			if (m_sa->isValidTilePosition(iXClicked, iYClicked)) {
				int mapX = m_sa->getMapXForScreenX(iXClicked);
				int mapY = m_sa->getMapYForScreenY(iYClicked);
				clickAtSelectionArea(pContext, mapX);
			}
		}
		else if (m_mouseState == 4) {
			clickAtFirstStation(pContext, iX, iY);
		}
	}
	//else if (iButton == SDL_BUTTON_MIDDLE) {
	//	m_filterScaling.compress();
	//	pContext->redrawDisplay();
	//}
	else if (iButton == SDL_BUTTON_RIGHT) {
		if (m_mouseState != 0) {
			m_mouseState = 0;
			if (m_propertyIndex < 20 && m_sa->getTileType(m_propertyIndex) < 0) {
				resetAtSelectionArea(pContext, m_propertyIndex);
			}
		}
	}
}

void GameState::virtMouseWheel(Scyyz12Engine2* pContext, int x, int y, int which, int timestamp)
{
	int iOldCentreX = pContext->convertClickedToVirtualPixelXPosition(pContext->getWindowWidth() / 2);
	int iOldCentreY = pContext->convertClickedToVirtualPixelYPosition(pContext->getWindowHeight() / 2);

	if (y < 0) m_filterScaling.compress();
	else if (y > 0) m_filterScaling.stretch();

	int iNewCentreX = pContext->convertClickedToVirtualPixelXPosition(pContext->getWindowWidth() / 2);
	int iNewCentreY = pContext->convertClickedToVirtualPixelYPosition(pContext->getWindowHeight() / 2);

	m_filterTranslation.changeOffset(iNewCentreX - iOldCentreX, iNewCentreY - iOldCentreY);

	// -----
	pContext->redrawDisplay();
	pContext->getBackgroundSurface()->mySDLLockSurface();
	virtSetupBackgroundBuffer(pContext);
	pContext->getBackgroundSurface()->mySDLUnlockSurface();
	// -----
}

void GameState::virtMainLoopDoBeforeUpdate(Scyyz12Engine2* pContext)
{
	if (m_bIsNewDay) {
		if (m_bRunToStop) {
			for (LineRoute* lr : m_lr) {
				for (TrainCollection* train : lr->getTrainList()) {
					train->getTrain()->stopTrain();
				}
			}
			pContext->redrawDisplay();
			m_bRunToStop = false;

		}
		if (!m_bSelectionNotMade) {
			m_bIsNewDay = false;
			for (LineRoute* lr : m_lr) {
				for (TrainCollection* train : lr->getTrainList()) {
					if (!train->isStopCooldown()) {
						train->getTrain()->startTrain();
					}
				}
			}
			m_iniTimeCount = pContext->getModifiedTime();
		}
	}
	else {
		m_timeCount = ((pContext->getModifiedTime() - m_iniTimeCount) / 50) % 497;
		if (m_timeCount == 496) {
			++m_dayCount;
			m_bIsNewDay = true;
			m_bRunToStop = true;
			m_bSelectionNotMade = true;
		}

		for (LineRoute* lr : m_lr) {
			m_scoreCount += lr->update(m_lr);
		}
		if (m_sm->update()) {
			writeToContinueFile(false);
			pContext->changeState("game_over", m_dayCount, m_scoreCount);
		}

		for (LineRoute* lr : m_lr) {
			for (TrainCollection* train : lr->getTrainList()) {
				for (CarriageCollection* carriage : train->getTrain()->getCarriageList()) {
					pContext->moveToLast(carriage->getCarriage());
				}
			}
		}
		for (StationCollection* station : m_sm->getStationList()) {
			pContext->moveToLast(station->getStation());
		}
		pContext->redrawDisplay();
	}
}

void GameState::copyAllBackgroundBuffer(Scyyz12Engine2* pContext)
{
	pContext->BaseEngine::copyAllBackgroundBuffer();
}

void GameState::virtKeyDown(Scyyz12Engine2* pContext, int iKeyCode)
{
	switch (iKeyCode)
	{
	case SDLK_LEFT:
		m_filterTranslation.changeOffset(-20, 0);
		break;
	case SDLK_RIGHT:
		m_filterTranslation.changeOffset(20, 0);
		break;
	case SDLK_UP:
		m_filterTranslation.changeOffset(0, -20);
		break;
	case SDLK_DOWN:
		m_filterTranslation.changeOffset(0, 20);
		break;
	case SDLK_SPACE:
		m_filterTranslation.setOffset(0, 0);
		m_filterScaling.setStretch(1);
		break;
	}
	// -----
	pContext->redrawDisplay();
	pContext->getBackgroundSurface()->mySDLLockSurface();
	virtSetupBackgroundBuffer(pContext);
	pContext->getBackgroundSurface()->mySDLUnlockSurface();
	// -----
}

void GameState::virtCreateSurfaces(Scyyz12Engine2* pContext)
{
	pContext->BaseEngine::virtCreateSurfaces();
}

void GameState::virtSetSelfDefinedValue(bool b, bool c, int i)
{
	m_bIsNeedsReload = b;
	m_bIsContinue = c;
	m_iLevelId = i;

	printf("## Debug - Reload?(%d) Continue?(%d) LevelId(%d)\n", b ? 1 : 0, c ? 1 : 0, i);
}
