#include "header.h"
#include "Part1Object.h"
#include "BaseEngine.h"
#include "UtilCollisionDetection.h"

void Part1Object::virtDraw()
{
	getEngine()->drawForegroundOval(m_iCurrentScreenX - m_iDrawWidth / 2, m_iCurrentScreenY - m_iDrawHeight / 2,
		m_iCurrentScreenX + m_iDrawWidth / 2 - 1,m_iCurrentScreenY + m_iDrawHeight / 2 - 1,
		0x00dd00);
}

void Part1Object::virtDoUpdate(int iCurrentTime)
{
	DisplayableObject* pObject = getEngine()->getDisplayableObject(1);

	//printf("%d %d %d %d\n", pObject->getXCentre(), pObject->getYCentre(), m_iCurrentScreenX, m_iCurrentScreenY);
	if (CollisionDetection::checkCircles(
		pObject->getXCentre(), pObject->getYCentre(),
		m_iCurrentScreenX, m_iCurrentScreenY,
		(getDrawWidth() + pObject->getDrawWidth())/2)
		) {
		printf("Collide!\n");
		if (iCurrentTime > m_iLastUpdatedTime + 100) {
			m_iLastUpdatedTime = iCurrentTime;
			m_dSpeedX = 0 - m_dSpeedX;
			m_dSpeedY = 0 - m_dSpeedY;
			if (m_dSpeedX == 0 && m_dSpeedY == 0) {
				m_dSpeedX = 10;
				m_dSpeedY = 10;
			}
		}
	}

	if (getEngine()->isKeyPressed(SDLK_UP))
		m_dSpeedY -= 0.1;
	if (getEngine()->isKeyPressed(SDLK_DOWN))
		m_dSpeedY += 0.1;
	if (getEngine()->isKeyPressed(SDLK_LEFT))
		m_dSpeedX -= 0.1;
	if (getEngine()->isKeyPressed(SDLK_RIGHT))
		m_dSpeedX += 0.1;
	if (getEngine()->isKeyPressed(SDLK_SPACE))
		m_dSpeedX = m_dSpeedY = 0;

	m_iCurrentScreenX += static_cast<int>(m_dSpeedX);
	m_iCurrentScreenY += static_cast<int>(m_dSpeedY);

	if (m_iCurrentScreenX + m_iStartDrawPosX < 0) {
		m_iCurrentScreenX = 0 - m_iStartDrawPosX;
		m_dSpeedX = 0 - m_dSpeedX;
	}
	if (m_iCurrentScreenX + m_iStartDrawPosX >= getEngine()->getWindowWidth() - m_iDrawWidth) {
		m_iCurrentScreenX = getEngine()->getWindowWidth() - m_iDrawWidth - m_iStartDrawPosX;
		m_dSpeedX = 0 - m_dSpeedX;
	}
	if (m_iCurrentScreenY + m_iStartDrawPosY < 0) {
		m_iCurrentScreenY = 0 - m_iStartDrawPosY;
		m_dSpeedY = 0 - m_dSpeedY;
	}
	if (m_iCurrentScreenY + m_iStartDrawPosY >= getEngine()->getWindowHeight() - m_iDrawHeight) {
		m_iCurrentScreenY = getEngine()->getWindowHeight() - m_iDrawHeight - m_iStartDrawPosY;
		m_dSpeedY = 0 - m_dSpeedY;
	}
		
	//redrawDisplay();

	if (m_pTileManager->isValidTilePosition(m_iCurrentScreenX, m_iCurrentScreenY))
	{
		if (iCurrentTime > m_iLastUpdatedTime + 100)
		{
			m_iLastUpdatedTime = iCurrentTime;
			int iTileX = m_pTileManager->getMapXForScreenX(m_iCurrentScreenX);
			int iTileY = m_pTileManager->getMapYForScreenY(m_iCurrentScreenY);
			int iCurrentTile = m_pTileManager->getMapValue(iTileX, iTileY);
			m_pTileManager->setAndRedrawMapValueAt(iTileX, iTileY, rand(), getEngine(), getEngine()->getBackgroundSurface());
		}
	}
}

void Part1Object::setPosition(int x, int y)
{
	m_iCurrentScreenX = x;
	m_iCurrentScreenY = y;
}

double Part1Object::getSpeedX()
{
	return m_dSpeedX;
}

double Part1Object::getSpeedY()
{
	return m_dSpeedY;
}



void Part1Object2::virtDraw()
{
	getEngine()->drawForegroundOval(m_iCurrentScreenX - m_iDrawWidth / 2, m_iCurrentScreenY - m_iDrawHeight / 2,
		m_iCurrentScreenX + m_iDrawWidth / 2 - 1, m_iCurrentScreenY + m_iDrawHeight / 2 - 1,
		0xffff00);
	getEngine()->drawForegroundThickLine(m_iCurrentScreenX, m_iCurrentScreenY - m_iDrawHeight / 8,
		m_iCurrentScreenX, m_iCurrentScreenY + m_iDrawHeight - m_iDrawHeight *7/8 - 1,
		0xff0000, 2);
	getEngine()->drawForegroundThickLine(m_iCurrentScreenX - m_iDrawWidth / 8, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - m_iDrawWidth *7/8 - 1, m_iCurrentScreenY,
		0xff0000, 2);
}

void Part1Object2::virtDoUpdate(int iCurrentTime)
{
	if (m_pEngine->getModifiedTime() / 1000 != m_iCounter) {
		m_bDirection = !m_bDirection;
		m_iCounter++;
		if (rand() > rand()) {
			m_dSpeed = 0 - m_dSpeed;
		}
	}
	
	if (m_bDirection) {
		m_iCurrentScreenX += static_cast<int>(m_dSpeed);
	}
	else {
		m_iCurrentScreenY += static_cast<int>(m_dSpeed);
	}

	if (m_iCurrentScreenX + m_iStartDrawPosX < 0) {
		m_iCurrentScreenX = 0 - m_iStartDrawPosX;
		m_dSpeed = 0 - m_dSpeed;
	}
	if (m_iCurrentScreenX + m_iStartDrawPosX >= getEngine()->getWindowWidth() - m_iDrawWidth) {
		m_iCurrentScreenX = getEngine()->getWindowWidth() - m_iDrawWidth - m_iStartDrawPosX;
		m_dSpeed = 0 - m_dSpeed;
	}
	if (m_iCurrentScreenY + m_iStartDrawPosY < 0) {
		m_iCurrentScreenY = 0 - m_iStartDrawPosY;
		m_dSpeed = 0 - m_dSpeed;
	}
	if (m_iCurrentScreenY + m_iStartDrawPosY >= getEngine()->getWindowHeight() - m_iDrawHeight) {
		m_iCurrentScreenY = getEngine()->getWindowHeight() - m_iDrawHeight - m_iStartDrawPosY;
		m_dSpeed = 0 - m_dSpeed;
	}

	redrawDisplay();
}

bool Part1Object2::getDirection()
{
	return m_bDirection;
}

