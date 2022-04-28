#include "header.h"
#include "GameState.h"
#include "ImagePixelMapping.h"

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
	else {

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
				if (m_tempLineIndex % 10 == 0) m_lr[lineIndex]->addStationHead(m_sm->getStation(m_tempStationIndex), true, m_railCount++);
				else m_lr[lineIndex]->addStationTail(m_sm->getStation(m_tempStationIndex), true, m_railCount++);
				m_mouseState = 0;
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
			m_lr[m_sa->getTileType(m_propertyIndex)]->iniAdd2Stations(m_sm->getStation(m_tempStationIndex), m_sm->getStation(secondStationIndex),
				false, m_railCount, m_railCount + 1, m_railCount + 2);
			m_railCount += 3;
			int value = m_sa->getMapValue(m_propertyIndex, 0);
			m_sa->setAndRedrawMapValueAt(m_propertyIndex, 0, value + 1, pContext, pContext->getBackgroundSurface());

			m_mouseState = 0;
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
	return pContext->BaseEngine::virtInitialise();
}

void GameState::virtSetupBackgroundBuffer(Scyyz12Engine2* pContext)
{
	m_filterScaling = Scyyz12FilterPointsScaling(0, pContext);
	m_filterTranslation = Scyyz12FilterPointsTranslation(0, 0, &m_filterScaling);
	pContext->getForegroundSurface()->setDrawPointsFilter(&m_filterTranslation); // TODO: 增加拖拽移动的监听

	pContext->fillBackground(0xffffff);

	// Exit btn
	SimpleImage backArrow = ImageManager::loadImage("resources/arrow-right-50-50.png", true);
	ImagePixelMappingRotateAndColour mapping(0, backArrow.getWidth() / 2, backArrow.getHeight() / 2);
	mapping.setTransparencyColour(0xffffff);
	mapping.setRotation(M_PI);
	backArrow.renderImageApplyingMapping(pContext, pContext->getBackgroundSurface(), 30, 30, backArrow.getWidth(), backArrow.getHeight(), &mapping);

	// Pause btn
	SimpleImage pause = ImageManager::loadImage("resources/pause-50-50.png", true);
	mapping.setRotation(0);
	pause.renderImageApplyingMapping(pContext, pContext->getBackgroundSurface(), 100, 30, pause.getWidth(), pause.getHeight(), &mapping);

	// Selection area
	pContext->drawBackgroundRectangle(280, 725, 1020, 800, 0xeeeeee);
	pContext->drawBackgroundThickLine(280, 725, 1020, 725, 0xaaaaaa, 2);

	if (m_sa == nullptr) {
		m_sa = new SelectionArea({ 0x52B69A, 0xF9C74F, 0xF94144 ,0x4361EE ,0xF19C79 ,0x48CAE4,0xFF4D6D }, 0xAAAAAA, true, false, false, true, false, true);
		m_sa->setProperty(-5, 3);
		m_sa->setProperty(-6, 2);
		m_sa->setProperty(-1, 3);
		m_sa->addNewLineState2Discovered();
		m_sa->addNewLineState2Discovered();
		m_sa->addNewLineState2Discovered();
	}
	m_sa->setTopLeftPositionOnScreen(300, 730);
	m_sa->drawAllTiles(pContext, pContext->getBackgroundSurface());
}

void GameState::virtDrawStringsOnTop(Scyyz12Engine2* pContext)
{
	char strDay[10]; sprintf(strDay, "Day %d", m_dayCount);
	pContext->drawForegroundString(650 - 350, 33, strDay, 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
	pContext->drawForegroundRectangle(650 - 150, 48, 650 + 350, 52, 0xDDDDDD);
	pContext->drawForegroundRectangle(650 - 150, 40, 650 - 146, 60, 0x777777);
	pContext->drawForegroundRectangle(650 + 346, 40, 650 + 350, 60, 0x777777);
	int x = 500 + m_timeCount;
	pContext->drawForegroundRectangle(x, 40, x + 4, 60, 0x000000);


	pContext->drawForegroundString(650 - 80, 650, "test game over", 0x777777, pContext->getFont("Ubuntu-Medium.ttf", 20)); // TODO: delete

	switch (m_mouseState)
	{
	case 0:
		pContext->drawForegroundString(650 - 450, 100, "Click a asset / line end", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
		break;
	case 1:
		pContext->drawForegroundString(650 - 450, 100, "Click a station (right click to cancel)", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
		break;
	case 2:
		pContext->drawForegroundString(650 - 450, 100, "Click another station (right click to cancel)", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
		break;
	case 3:
		pContext->drawForegroundString(650 - 450, 100, "Click a line (right click to cancel)", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
		break;
	case 4:
		pContext->drawForegroundString(650 - 450, 100, "Click a station /train on that line (right click to cancel)", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
		break;
	case 100:
		pContext->drawForegroundString(650 - 450, 100, "E - line not discovered (right click to cancel)", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
		break;
	case 101:
		pContext->drawForegroundString(650 - 450, 100, "E - line already in use (right click to cancel)", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
		break;
	case 102:
		pContext->drawForegroundString(650 - 450, 100, "E - not click at station (right click to cancel)", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
		break;
	case 103:
		pContext->drawForegroundString(650 - 450, 100, "E - click at the same station twice (right click to cancel)", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
		break;
	case 104:
		pContext->drawForegroundString(650 - 450, 100, "E - line not in use (right click to cancel)", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
		break;
	case 105:
		pContext->drawForegroundString(650 - 450, 100, "E - the station not in given line (right click to cancel)", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
		break;
	case 106:
		pContext->drawForegroundString(650 - 450, 100, "E - the station already in given line (right click to cancel)", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
		break;
	case 107:
		pContext->drawForegroundString(650 - 450, 100, "E - not clicking at a train at given line (right click to cancel)", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
		break;
	case 200:
		pContext->drawForegroundString(650 - 450, 100, "TEST (right click to cancel)", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
		break;
	default:
		break;
	}

	if (m_bRunToStop || m_bSelectionNotMade) {
		m_filterTranslation.setOffset(0, 0);
		m_filterScaling.setStretch(0);

		pContext->drawForegroundRectangle(300, 200, 1000, 600, 0xaaaaaa);
		pContext->drawForegroundRectangle(302, 202, 998, 598, 0xeeeeee);
		pContext->drawForegroundString(650 - 310, 210, "A brand new day!", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
		pContext->drawForegroundString(650 - 310, 260, "Select one update for your railway:", 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));

		if (m_sa->isAllLineDiscovered()) {
			SimpleImage train = ImageManager::loadImage("resources/train_normal-80-80-g.png", true);
			SimpleImage carriage = ImageManager::loadImage("resources/carriage-80-80-g.png", true);
			SimpleImage bridge = ImageManager::loadImage("resources/bridge_3-80-80-g.png", true);
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
			SimpleImage rail = ImageManager::loadImage("resources/rail-80-80-g.png", true);
			SimpleImage train = ImageManager::loadImage("resources/train_normal-80-80-g.png", true);
			SimpleImage carriage = ImageManager::loadImage("resources/carriage-80-80-g.png", true);
			SimpleImage bridge = ImageManager::loadImage("resources/bridge_3-80-80-g.png", true);
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

		char strDay[100]; sprintf(strDay, "And get ready for more passengers in Day %d", m_dayCount);
		pContext->drawForegroundString(650 - 310, 550, strDay, 0x000000, pContext->getFont("Ubuntu-Medium.ttf", 30));
	}
}

int GameState::virtInitialiseObjects(Scyyz12Engine2* pContext)
{
	m_iniTimeCount = pContext->getModifiedTime();

	pContext->destroyOldObjects(true);

	if (m_sm == nullptr) {
		m_sm = new StationMap(pContext);
		m_sm->addRandomStationInRectangle(m_stationCount++, 500, 300, 100, 100);
		m_sm->addRandomStationInRectangle(m_stationCount++, 600, 400, 100, 100);
		m_sm->addRandomStationInRectangle(m_stationCount++, 500, 400, 100, 100);
	}

	if (m_lr.size() == 0) {
		LineRoute* lr = new LineRoute(pContext, 0x52B69A); // TODO : can be better by a vector
		m_lr.emplace_back(lr);
		lr = new LineRoute(pContext, 0xF9C74F);
		m_lr.emplace_back(lr);
		lr = new LineRoute(pContext, 0xF94144);
		m_lr.emplace_back(lr);
		lr = new LineRoute(pContext, 0x4361EE);
		m_lr.emplace_back(lr);
		lr = new LineRoute(pContext, 0xF19C79);
		m_lr.emplace_back(lr);
		lr = new LineRoute(pContext, 0x48CAE4);
		m_lr.emplace_back(lr);
		lr = new LineRoute(pContext, 0xFF4D6D);
		m_lr.emplace_back(lr);
	}

	for (LineRoute* lr : m_lr) {
		lr->drawInitialise();
	}
	m_sm->drawInitialise();

	return 0;
}

void GameState::virtMouseMoved(Scyyz12Engine2* pContext, int iX, int iY)
{
	int iXClicked = pContext->convertVirtualPixelToClickedXPosition(iX), iYClicked = pContext->convertVirtualPixelToClickedYPosition(iY);
	printf("## Debug - move at %d %d (virtual), %d %d (to clicked)\n", iX, iY, iXClicked, iYClicked);
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

	if (iButton == SDL_BUTTON_LEFT) {
		if (m_bIsNewDay && m_bSelectionNotMade) {
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
				if (iX > 550 && iX < 750) {
					if (iY > 640 && iY < 690) {
						pContext->changeState("game_over");
					}
				}
				else if (iXClicked > 30 && iXClicked < 80) {
					if (iYClicked > 30 && iYClicked < 80) {
						pContext->changeState("start");
					}
				}
				else if (iXClicked > 100 && iXClicked < 150) {
					if (iYClicked > 30 && iYClicked < 80) {
						pContext->changeState("pause");
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
			if (m_sa->isValidTilePosition(iX, iY)) {
				int mapX = m_sa->getMapXForScreenX(iX);
				int mapY = m_sa->getMapYForScreenY(iY);
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
	//pContext->redrawDisplay();
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
		m_timeCount = ((pContext->getModifiedTime() - m_iniTimeCount) / 10) % 497;
		if (m_timeCount == 496) {
			++m_dayCount;
			m_bIsNewDay = true;
			m_bRunToStop = true;
			m_bSelectionNotMade = true;
		}

		for (LineRoute* lr : m_lr) {
			lr->update();
		}
		m_sm->update();

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
		//pContext->redrawDisplay();
		break;
	case SDLK_RIGHT:
		m_filterTranslation.changeOffset(20, 0);
		//pContext->redrawDisplay();
		break;
	case SDLK_UP:
		m_filterTranslation.changeOffset(0, -20);
		//pContext->redrawDisplay();
		break;
	case SDLK_DOWN:
		m_filterTranslation.changeOffset(0, 20);
		//pContext->redrawDisplay();
		break;
	case SDLK_SPACE:
		m_filterTranslation.setOffset(0, 0);
		m_filterScaling.setStretch(0);
		//pContext->redrawDisplay();
		break;
	}
}

void GameState::virtCreateSurfaces(Scyyz12Engine2* pContext)
{
	pContext->BaseEngine::virtCreateSurfaces();
}
