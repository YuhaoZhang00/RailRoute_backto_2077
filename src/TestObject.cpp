#include "header.h"
#include "TestObject.h"
#include "BaseEngine.h"

void TestObject::virtDraw()
{
	getEngine()->drawForegroundOval(m_iCurrentScreenX - m_iDrawWidth / 2, m_iCurrentScreenY - m_iDrawHeight / 2,
		m_iCurrentScreenX + m_iDrawWidth / 2 - 1, m_iCurrentScreenY + m_iDrawHeight / 2 - 1,
		0xffff00);
	getEngine()->drawForegroundThickLine(m_iCurrentScreenX, m_iCurrentScreenY - m_iDrawHeight / 8,
		m_iCurrentScreenX, m_iCurrentScreenY + m_iDrawHeight - m_iDrawHeight * 7 / 8 - 1,
		0xff0000, 2);
	getEngine()->drawForegroundThickLine(m_iCurrentScreenX - m_iDrawWidth / 8, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - m_iDrawWidth * 7 / 8 - 1, m_iCurrentScreenY,
		0xff0000, 2);
}

void TestObject::virtDoUpdate(int iCurrentTime)
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

bool TestObject::getDirection()
{
	return m_bDirection;
}