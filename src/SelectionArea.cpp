#include "header.h"
#include "SelectionArea.h"
#include "ImagePixelMapping.h"
#include "Scyyz12ImagePixelMapping.h"

void SelectionArea::virtDrawTileAt(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY, int iStartPositionScreenX, int iStartPositionScreenY) const
{
	pEngine->redrawRectangle(iStartPositionScreenX, iStartPositionScreenY, iStartPositionScreenX + getTileWidth(), iStartPositionScreenY + getTileHeight());

	//printf("-- %d --\n", getMapValue(iMapX, iMapY));
	int iMapValue = m_vecTile2Type[iMapX];
	//printf("++ %d ++\n", iMapValue);
	if (iMapValue >= 0) { // iMapValue >= 0 : lines
		int state = getMapValue(iMapX, iMapY);
		if (state == 0) {
			pSurface->drawOval(iStartPositionScreenX + getTileWidth() * 0.3, iStartPositionScreenY + getTileHeight() * 0.3,
				iStartPositionScreenX + getTileWidth() * 0.7, iStartPositionScreenY + getTileHeight() * 0.7,
				m_uiUndiscoveredColor);
		}
		else if (state == 1) {
			pSurface->drawOval(iStartPositionScreenX + getTileWidth() * 0.3, iStartPositionScreenY + getTileHeight() * 0.3,
				iStartPositionScreenX + getTileWidth() * 0.7, iStartPositionScreenY + getTileHeight() * 0.7,
				m_vecLineColors[iMapValue]);
		}
		else if (state == 2) {
			pSurface->drawOval(iStartPositionScreenX + getTileWidth() * 0.1, iStartPositionScreenY + getTileHeight() * 0.1,
				iStartPositionScreenX + getTileWidth() * 0.9, iStartPositionScreenY + getTileHeight() * 0.9,
				m_vecLineColors[iMapValue]);
		}
		else {
			printf("!! Error @ SelectionArea.cpp virtDrawTileAt - invalid state\n");
		}

		SimpleImage rail = ImageManager::loadImage("resources/rail-20-20-bg.png", true);
		ImagePixelMappingRotateAndColour mapping(0, 0, 0);
		mapping.setTransparencyColour(0xFF0000);
		rail.renderImageApplyingMapping(pEngine, pSurface,
			iStartPositionScreenX + getTileWidth() - rail.getWidth() * 1.2, iStartPositionScreenY + rail.getHeight() * 0.2,
			rail.getWidth(), rail.getHeight(),
			&mapping);
	}
	else { // iMapValue < 0 : properties
		SimpleImage property;

		if (iMapValue == -5) {
			property = ImageManager::loadImage("resources/train_normal-50-50-w.png", true);
		}
		else if (iMapValue == -4) {
			property = ImageManager::loadImage("resources/train_fast_2-50-50-w.png", true);
		}
		else if (iMapValue == -3) {
			property = ImageManager::loadImage("resources/train_intelli_2-50-50-w-r.png", true);
		}
		else if (iMapValue == -6) {
			property = ImageManager::loadImage("resources/carriage-50-50-w.png", true);
		}
		else if (iMapValue == -2) {
			property = ImageManager::loadImage("resources/tunnel_2-50-50-w.png", true);
		}
		else if (iMapValue == -1) {
			property = ImageManager::loadImage("resources/bridge_3-50-50-w.png", true);
		}
		else {
			printf("!! Error @ SelectionArea.cpp virtDrawTileAt - invalid iMapValue of properties\n");
		}

		if (m_iCurrentMouseAt == -1 || m_vecTile2Type[m_iCurrentMouseAt] == iMapValue) {
			ImagePixelMappingRotateAndColour mapping(0, 0, 0);
			mapping.setTransparencyColour(0xffffff);
			property.renderImageApplyingMapping(pEngine, pSurface,
				iStartPositionScreenX + (getTileWidth() - property.getWidth()) / 2, iStartPositionScreenY + (getTileHeight() - property.getHeight()) / 2,
				property.getWidth(), property.getHeight(),
				&mapping);
		}
		else {
			Scyyz12ImagePixelMapping mapping(0xffffff, 0.7);
			property.renderImageApplyingMapping(pEngine, pSurface,
				iStartPositionScreenX + (getTileWidth() - property.getWidth()) / 2, iStartPositionScreenY + (getTileHeight() - property.getHeight()) / 2,
				property.getWidth(), property.getHeight(),
				&mapping);
		}

		pSurface->drawOval(iStartPositionScreenX + getTileWidth() - 24, iStartPositionScreenY + 4,
			iStartPositionScreenX + getTileWidth() - 4, iStartPositionScreenY + 24,
			0xffffff);
		int iNum = getMapValue(iMapX, iMapY);
		char cStrNum[3]; sprintf(cStrNum, "%d", iNum);
		if (iNum < 10) {
			pSurface->drawFastString(iStartPositionScreenX + getTileWidth() - 17, iStartPositionScreenY + 4,
				cStrNum, 0x000000, pEngine->getFont("Ubuntu-Medium.ttf", 16));
		}
		else {
			pSurface->drawFastString(iStartPositionScreenX + getTileWidth() - 22, iStartPositionScreenY + 4,
				cStrNum, 0x000000, pEngine->getFont("Ubuntu-Medium.ttf", 16));
		}
	}
}

void SelectionArea::incProperty(short index)
{
	for (int i = 0; i < m_iNumOfTiles; i++) {
		if (m_vecTile2Type[i] == index) {
			setMapValue(i, 0, (getMapValue(i, 0) + 1));
			return;
		}
	}
	printf("!! Error @ SelectionArea.cpp incProperty - property not found\n");
}

void SelectionArea::setProperty(short index, int value)
{
	for (int i = 0; i < m_iNumOfTiles; i++) {
		if (m_vecTile2Type[i] == index) {
			setMapValue(i, 0, value);
			return;
		}
	}
	printf("!! Error @ SelectionArea.cpp setProperty - property not found\n");
}

bool SelectionArea::decProperty(short index)
{
	for (int i = 0; i < m_iNumOfTiles; i++) {
		if (m_vecTile2Type[i] == index) {
			setMapValue(i, 0, (getMapValue(i, 0) - 1));
			if (getMapValue(i, 0) == 0) {
				return true;
			}
			else if (getMapValue(i, 0) < 0) {
				printf("!! Error @ SelectionArea.cpp decProperty - property value change to negative\n");
			}
			return false;
		}
	}
	printf("!! Error @ SelectionArea.cpp decProperty - property not found\n");
	return false;
}

bool SelectionArea::isAllLineDiscovered()
{
	return m_iDiscoveredLineCount == size(m_vecLineColors);
}

void SelectionArea::addNewLineState2Discovered()
{
	if (isAllLineDiscovered()) {
		printf("!! Error @ SelectionArea.cpp addNewLineState2Discovered - no new line can be discovered, please check isAllLineDiscovered() before adding passenger to carriage\n");
	}
	else {
		for (int i = 0; i < m_iNumOfTiles; i++) {
			if (m_vecTile2Type[i] == m_iDiscoveredLineCount) {
				if (getMapValue(i, 0) != 0) {
					printf("!! Error @ SelectionArea.cpp addNewLineState2Discovered - error state of line, the line should be undiscovered\n");
				}
				setMapValue(i, 0, 1);
				m_iDiscoveredLineCount++;
				return;
			}
		}
	}
}

void SelectionArea::setLineState2Using(short index)
{
	if (index < 0 || index >= size(m_vecLineColors)) {
		printf("!! Error @ SelectionArea.cpp setLineState2Using - incorrect index\n");
	}
	else {
		for (int i = 0; i < m_iNumOfTiles; i++) {
			if (m_vecTile2Type[i] == index) {
				if (getMapValue(i, 0) != 1) {
					printf("!! Error @ SelectionArea.cpp setLineState2Using - error state of line, the line should be discovered\n");
				}
				setMapValue(i, 0, 2);
				return;
			}
		}
	}
}

void SelectionArea::setLineState2Discovered(short index)
{
	if (index < 0 || index >= size(m_vecLineColors)) {
		printf("!! Error @ SelectionArea.cpp setLineState2Using - incorrect index\n");
	}
	else {
		for (int i = 0; i < m_iNumOfTiles; i++) {
			if (m_vecTile2Type[i] == index) {
				if (getMapValue(i, 0) != 2) {
					printf("!! Error @ SelectionArea.cpp setLineState2Using - error state of line, the line should be using\n");
				}
				setMapValue(i, 0, 1);
				return;
			}
		}
	}
}

void SelectionArea::mouseAt(short iX)
{
	m_iCurrentMouseAt = iX;
}

void SelectionArea::mouseRemoved()
{
	m_iCurrentMouseAt = -1;
}

int SelectionArea::getTileType(int iX)
{
	return m_vecTile2Type[iX];
}
