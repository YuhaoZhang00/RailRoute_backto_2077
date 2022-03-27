#include "header.h"
#include "Station.h"
#include "BaseEngine.h"

void StationCircle::virtDraw()
{
	getEngine()->drawForegroundOval(
		m_iCurrentScreenX - m_iSize / 2, m_iCurrentScreenY - m_iSize / 2,
		m_iCurrentScreenX + m_iSize / 2, m_iCurrentScreenY + m_iSize / 2,
		m_uiColor);
	getEngine()->drawForegroundOval(
		m_iCurrentScreenX - m_iSize / 2 + m_iBorderWidth, m_iCurrentScreenY - m_iSize / 2 + m_iBorderWidth,
		m_iCurrentScreenX + m_iSize / 2 - m_iBorderWidth, m_iCurrentScreenY + m_iSize / 2 - m_iBorderWidth,
		m_uiInnerColor);
}

void StationSquare::virtDraw()
{
	getEngine()->drawForegroundRectangle(
		m_iCurrentScreenX - m_iSize * 2 / 5, m_iCurrentScreenY - m_iSize * 2 / 5,
		m_iCurrentScreenX + m_iSize * 2 / 5, m_iCurrentScreenY + m_iSize * 2 / 5,
		m_uiColor);
	getEngine()->drawForegroundRectangle(
		m_iCurrentScreenX - m_iSize * 2 / 5 + m_iBorderWidth, m_iCurrentScreenY - m_iSize * 2 / 5 + m_iBorderWidth,
		m_iCurrentScreenX + m_iSize * 2 / 5 - m_iBorderWidth, m_iCurrentScreenY + m_iSize * 2 / 5 - m_iBorderWidth,
		m_uiInnerColor);
}

void StationHexagon::virtDraw()
{
	getEngine()->drawForegroundPolygon(
		m_iCurrentScreenX - m_iSize / 4, m_iCurrentScreenY - m_iSize * 0.433, // 0.433 = sqrt(3)/4
		m_iCurrentScreenX + m_iSize / 4, m_iCurrentScreenY - m_iSize * 0.433,
		m_iCurrentScreenX + m_iSize / 2, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iSize / 4, m_iCurrentScreenY + m_iSize * 0.433,
		m_iCurrentScreenX - m_iSize / 4, m_iCurrentScreenY + m_iSize * 0.433,
		m_iCurrentScreenX - m_iSize / 2, m_iCurrentScreenY,
		m_uiColor);
	getEngine()->drawForegroundPolygon(
		m_iCurrentScreenX - m_iSize / 4 + m_iBorderWidth / 1.732, m_iCurrentScreenY - m_iSize * 0.433 + m_iBorderWidth, // 0.433 = sqrt(3)/4  1.732 = sqrt(3)
		m_iCurrentScreenX + m_iSize / 4 - m_iBorderWidth / 1.732, m_iCurrentScreenY - m_iSize * 0.433 + m_iBorderWidth,
		m_iCurrentScreenX + m_iSize / 2 - m_iBorderWidth * 2 / 1.732, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iSize / 4 - m_iBorderWidth / 1.732, m_iCurrentScreenY + m_iSize * 0.433 - m_iBorderWidth,
		m_iCurrentScreenX - m_iSize / 4 + m_iBorderWidth / 1.732, m_iCurrentScreenY + m_iSize * 0.433 - m_iBorderWidth,
		m_iCurrentScreenX - m_iSize / 2 + m_iBorderWidth * 2 / 1.732, m_iCurrentScreenY,
		m_uiInnerColor);
}

void StationDiamond::virtDraw()
{
	getEngine()->drawForegroundPolygon(
		m_iCurrentScreenX, m_iCurrentScreenY - m_iSize / 2,
		m_iCurrentScreenX + m_iSize / 2, m_iCurrentScreenY,
		m_iCurrentScreenX, m_iCurrentScreenY + m_iSize / 2,
		m_iCurrentScreenX - m_iSize / 2, m_iCurrentScreenY,
		m_uiColor);
	getEngine()->drawForegroundPolygon(
		m_iCurrentScreenX, m_iCurrentScreenY - m_iSize / 2 + m_iBorderWidth * 1.414, // 1.414 = sqrt(2)
		m_iCurrentScreenX + m_iSize / 2 - m_iBorderWidth * 1.414, m_iCurrentScreenY,
		m_iCurrentScreenX, m_iCurrentScreenY + m_iSize / 2 - m_iBorderWidth * 1.414,
		m_iCurrentScreenX - m_iSize / 2 + m_iBorderWidth * 1.414, m_iCurrentScreenY,
		m_uiInnerColor);
}

void StationTriangle::virtDraw()
{
	getEngine()->drawForegroundTriangle(
		m_iCurrentScreenX, m_iCurrentScreenY - m_iSize / 2,
		m_iCurrentScreenX + m_iSize / 2, m_iCurrentScreenY + m_iSize * 0.366, // 0.366 = sqrt(3)/2 - 0.5
		m_iCurrentScreenX - m_iSize / 2, m_iCurrentScreenY + m_iSize * 0.366,
		m_uiColor);
	getEngine()->drawForegroundTriangle(
		m_iCurrentScreenX, m_iCurrentScreenY - m_iSize / 2 + m_iBorderWidth * 2,
		m_iCurrentScreenX + m_iSize / 2 - m_iBorderWidth * 1.732, m_iCurrentScreenY + m_iSize * 0.366 - m_iBorderWidth, // 0.866 = sqrt(3)/2  1.732 = sqrt(3)
		m_iCurrentScreenX - m_iSize / 2 + m_iBorderWidth * 1.732, m_iCurrentScreenY + m_iSize * 0.366 - m_iBorderWidth,
		m_uiInnerColor);
}

void StationInvTriangle::virtDraw()
{
	getEngine()->drawForegroundTriangle(
		m_iCurrentScreenX, m_iCurrentScreenY + m_iSize / 2,
		m_iCurrentScreenX - m_iSize / 2, m_iCurrentScreenY - m_iSize * 0.366, // 0.366 = sqrt(3)/2 - 0.5
		m_iCurrentScreenX + m_iSize / 2, m_iCurrentScreenY - m_iSize * 0.366,
		m_uiColor);
	getEngine()->drawForegroundTriangle(
		m_iCurrentScreenX, m_iCurrentScreenY + m_iSize / 2 - m_iBorderWidth * 2,
		m_iCurrentScreenX - m_iSize / 2 + m_iBorderWidth * 1.732, m_iCurrentScreenY - m_iSize * 0.366 + m_iBorderWidth, // 0.366 = sqrt(3)/2 - 0.5  1.732 = sqrt(3)
		m_iCurrentScreenX + m_iSize / 2 - m_iBorderWidth * 1.732, m_iCurrentScreenY - m_iSize * 0.366 + m_iBorderWidth,
		m_uiInnerColor);
}

Station* StationCollection::getStation()
{
	return m_oStation;
}
