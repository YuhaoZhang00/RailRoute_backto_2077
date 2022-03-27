#include "header.h"
#include "Passenger.h"
#include "BaseEngine.h"

void PassengerCircle::virtDraw()
{
	getEngine()->drawForegroundOval(
		m_iCurrentScreenX - m_iSize / 2, m_iCurrentScreenY - m_iSize / 2,
		m_iCurrentScreenX + m_iSize / 2, m_iCurrentScreenY + m_iSize / 2,
		m_uiColor);
}

void PassengerSquare::virtDraw()
{
	getEngine()->drawForegroundRectangle(
		m_iCurrentScreenX - m_iSize * 2 / 5, m_iCurrentScreenY - m_iSize * 2 / 5,
		m_iCurrentScreenX + m_iSize * 2 / 5, m_iCurrentScreenY + m_iSize * 2 / 5,
		m_uiColor);
}

//void PassengerHexagon::virtDraw()
//{
//	getEngine()->drawForegroundPolygon(
//		m_iCurrentScreenX - m_iSize / 4, m_iCurrentScreenY - m_iSize * 0.433, // 0.433 = sqrt(3)/4
//		m_iCurrentScreenX + m_iSize / 4, m_iCurrentScreenY - m_iSize * 0.433,
//		m_iCurrentScreenX + m_iSize / 2, m_iCurrentScreenY,
//		m_iCurrentScreenX + m_iSize / 4, m_iCurrentScreenY + m_iSize * 0.433,
//		m_iCurrentScreenX - m_iSize / 4, m_iCurrentScreenY + m_iSize * 0.433,
//		m_iCurrentScreenX - m_iSize / 2, m_iCurrentScreenY,
//		m_uiColor);
//}

void PassengerDiamond::virtDraw()
{
	getEngine()->drawForegroundPolygon(
		m_iCurrentScreenX, m_iCurrentScreenY - m_iSize / 2,
		m_iCurrentScreenX + m_iSize / 2, m_iCurrentScreenY,
		m_iCurrentScreenX, m_iCurrentScreenY + m_iSize / 2,
		m_iCurrentScreenX - m_iSize / 2, m_iCurrentScreenY,
		m_uiColor);
}

void PassengerTriangle::virtDraw()
{
	getEngine()->drawForegroundTriangle(
		m_iCurrentScreenX, m_iCurrentScreenY - m_iSize / 2,
		m_iCurrentScreenX + m_iSize / 2, m_iCurrentScreenY + m_iSize * 0.366+1, // 0.366 = sqrt(3)/2 - 0.5
		m_iCurrentScreenX - m_iSize / 2, m_iCurrentScreenY + m_iSize * 0.366+1,
		m_uiColor);
}

void PassengerInvTriangle::virtDraw()
{
	getEngine()->drawForegroundTriangle(
		m_iCurrentScreenX, m_iCurrentScreenY + m_iSize / 2-1,
		m_iCurrentScreenX - m_iSize / 2, m_iCurrentScreenY - m_iSize * 0.366-1, // 0.366 = sqrt(3)/2 - 0.5
		m_iCurrentScreenX + m_iSize / 2, m_iCurrentScreenY - m_iSize * 0.366-1,
		m_uiColor);
}

int PassengerFlower::dist(int x1, int y1, int x2, int y2)
{
	return static_cast<int>(sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
}

void PassengerFlower::virtDraw()
{
	for (int i = m_iCurrentScreenX-m_iSize/2; i <= m_iCurrentScreenX + m_iSize / 2; i++) {
		for (int j = m_iCurrentScreenY- m_iSize / 2; j <= m_iCurrentScreenY + m_iSize / 2; j++) {
			if ((dist(i, j, m_iCurrentScreenX- m_iSize / 2, m_iCurrentScreenY + m_iSize / 2) < m_iSize &&
				dist(i, j, m_iCurrentScreenX + m_iSize / 2, m_iCurrentScreenY- m_iSize / 2) < m_iSize) ||
				(dist(i, j, m_iCurrentScreenX- m_iSize / 2, m_iCurrentScreenY- m_iSize / 2) < m_iSize &&
					dist(i, j, m_iCurrentScreenX + m_iSize / 2, m_iCurrentScreenY + m_iSize / 2) < m_iSize)) {
				getEngine()->setForegroundPixel(i, j, m_uiColor);
			}
		}
	}
}

Passenger* PassengerCollection::getPassenger()
{
	return m_oPassenger;
}

short PassengerCollection::getType()
{
	return m_sType;
}


