#include "header.h"
#include "Rail.h"
#include "BaseEngine.h"

void RailLine::virtDraw()
{
	if (m_bIsHorizontal) { // horizontal
		getEngine()->drawForegroundThickLine(m_iCurrentScreenX + m_iLineWidth / 2, m_iCurrentScreenY + m_iLineWidth / 2,
			m_iCurrentScreenX + m_iDrawWidth - m_iLineWidth / 2, m_iCurrentScreenY + m_iLineWidth / 2, m_uiColor, m_iLineWidth);
	}
	else { // vertical
		getEngine()->drawForegroundThickLine(m_iCurrentScreenX + m_iLineWidth / 2, m_iCurrentScreenY + m_iLineWidth / 2,
			m_iCurrentScreenX + m_iLineWidth / 2, m_iCurrentScreenY + m_iDrawHeight - m_iLineWidth / 2, m_uiColor, m_iLineWidth);
	}

}

void RailLineDiagonal::virtDraw()
{
	if (m_sDirection % 2 == 0) { // lower left - upper right
		getEngine()->drawForegroundThickLine(m_iCurrentScreenX + m_iLineWidth / 4, m_iCurrentScreenY + m_iDrawHeight - m_iLineWidth / 4,
			m_iCurrentScreenX + m_iDrawWidth - m_iLineWidth / 4, m_iCurrentScreenY + m_iLineWidth / 4, m_uiColor, m_iLineWidth);
	}
	else { // lower right - upper left
		getEngine()->drawForegroundThickLine(m_iCurrentScreenX + m_iDrawWidth - m_iLineWidth / 4, m_iCurrentScreenY + m_iDrawHeight - m_iLineWidth / 4,
			m_iCurrentScreenX + m_iLineWidth / 4, m_iCurrentScreenY + m_iLineWidth / 4, m_uiColor, m_iLineWidth);
	}
}

//void RailLink135::virtDraw()
//{
//	getEngine()->drawForegroundOval(m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY,
//		m_iCurrentScreenX + m_iLineWidth / 2, m_iCurrentScreenY + m_iLineWidth / 2, m_uiColor);
//}

int RailLink90::dist(int x1, int y1, int x2, int y2)
{
	return static_cast<int>(sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
}

void RailLink90::virtDraw()
{
	int c1 = 0, c2 = 0;
	if (m_sDirection == 0) {
		c1 = m_iCurrentScreenX + m_iDrawWidth;
		c2 = m_iCurrentScreenY;
	}
	else if (m_sDirection == 1) {
		c1 = m_iCurrentScreenX + m_iDrawWidth;
		c2 = m_iCurrentScreenY + m_iDrawHeight;
	}
	else if (m_sDirection == 2) {
		c1 = m_iCurrentScreenX;
		c2 = m_iCurrentScreenY + m_iDrawHeight;
	}
	else if (m_sDirection == 3) {
		c1 = m_iCurrentScreenX;
		c2 = m_iCurrentScreenY;
	}

	for (int i = m_iCurrentScreenX; i <= m_iCurrentScreenX + m_iDrawWidth; i++) {
		for (int j = m_iCurrentScreenY; j <= m_iCurrentScreenY + m_iDrawHeight; j++) {
			int d = dist(i, j, c1, c2);
			if (d > m_iRadius - m_iLineWidth && d < m_iRadius) {
				getEngine()->setForegroundPixel(i, j, m_uiColor);
			}
		}
	}
}

int RailLink90Diagonal::dist(int x1, int y1, int x2, int y2)
{
	return static_cast<int>(sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
}

void RailLink90Diagonal::virtDraw()
{
	int c1 = 0, c2 = 0;
	int constraint1 = 0, constraint2 = 0;
	if (m_sDirection == 0) {
		c1 = m_iCurrentScreenX + m_iDrawWidth;
		c2 = m_iCurrentScreenY + m_iDrawHeight / 2;
		constraint1 = m_iCurrentScreenX + m_iCurrentScreenY + m_iDrawHeight * 3 / 2; // x + y < X + Y + 3H/2
		constraint2 = -m_iCurrentScreenX + m_iCurrentScreenY - m_iDrawHeight / 2; // y - x > -X + Y - H/2
		for (int i = m_iCurrentScreenX; i <= m_iCurrentScreenX + m_iDrawWidth; i++) {
			for (int j = m_iCurrentScreenY; j <= m_iCurrentScreenY + m_iDrawHeight; j++) {
				int d = dist(i, j, c1, c2);
				if (d > m_iRadius - m_iLineWidth && d < m_iRadius && i + j < constraint1 && j - i > constraint2) {
					getEngine()->setForegroundPixel(i, j, m_uiColor);
				}
			}
		}
	}
	else if (m_sDirection == 1) {
		c1 = m_iCurrentScreenX + m_iDrawWidth / 2;
		c2 = m_iCurrentScreenY + m_iDrawHeight;
		constraint1 = m_iCurrentScreenX + m_iCurrentScreenY + m_iDrawHeight * 3 / 2; // x + y < X + Y + 3H/2
		constraint2 = -m_iCurrentScreenX + m_iCurrentScreenY + m_iDrawHeight / 2; // y - x < -X + Y + H/2
		for (int i = m_iCurrentScreenX; i <= m_iCurrentScreenX + m_iDrawWidth; i++) {
			for (int j = m_iCurrentScreenY; j <= m_iCurrentScreenY + m_iDrawHeight; j++) {
				int d = dist(i, j, c1, c2);
				if (d > m_iRadius - m_iLineWidth && d < m_iRadius && i + j < constraint1 && j - i < constraint2) {
					getEngine()->setForegroundPixel(i, j, m_uiColor);
				}
			}
		}
	}
	else if (m_sDirection == 2) {
		c1 = m_iCurrentScreenX;
		c2 = m_iCurrentScreenY + m_iDrawHeight / 2;
		constraint1 = m_iCurrentScreenX + m_iCurrentScreenY + m_iDrawHeight / 2; // x + y > X + Y + H/2
		constraint2 = -m_iCurrentScreenX + m_iCurrentScreenY + m_iDrawHeight / 2; // y - x < -X + Y + H/2
		for (int i = m_iCurrentScreenX; i <= m_iCurrentScreenX + m_iDrawWidth; i++) {
			for (int j = m_iCurrentScreenY; j <= m_iCurrentScreenY + m_iDrawHeight; j++) {
				int d = dist(i, j, c1, c2);
				if (d > m_iRadius - m_iLineWidth && d < m_iRadius && i + j > constraint1 && j - i < constraint2) {
					getEngine()->setForegroundPixel(i, j, m_uiColor);
				}
			}
		}
	}
	else if (m_sDirection == 3) {
		c1 = m_iCurrentScreenX + m_iDrawWidth / 2;
		c2 = m_iCurrentScreenY;
		constraint1 = m_iCurrentScreenX + m_iCurrentScreenY + m_iDrawHeight / 2; // x + y > X + Y + H/2
		constraint2 = -m_iCurrentScreenX + m_iCurrentScreenY - m_iDrawHeight / 2; // y - x > -X + Y - H/2
		for (int i = m_iCurrentScreenX; i <= m_iCurrentScreenX + m_iDrawWidth; i++) {
			for (int j = m_iCurrentScreenY; j <= m_iCurrentScreenY + m_iDrawHeight; j++) {
				int d = dist(i, j, c1, c2);
				if (d > m_iRadius - m_iLineWidth && d < m_iRadius && i + j > constraint1 && j - i > constraint2) {
					getEngine()->setForegroundPixel(i, j, m_uiColor);
				}
			}
		}
	}
}

void RailEnd::virtDraw()
{
	if (m_sDirection == 0) {
		getEngine()->drawForegroundThickLine(
			getXCentre(), getYCentre() - m_iLineLength + m_iLineWidth / 2,
			getXCentre(), getYCentre() - m_iLineWidth / 2,
			m_uiColor, m_iLineWidth);
		getEngine()->drawForegroundThickLine(
			getXCentre() - m_iLineEndLength / 2 + m_iLineWidth / 2, getYCentre() - m_iLineLength + m_iLineWidth / 2,
			getXCentre() + m_iLineEndLength / 2 - m_iLineWidth / 2, getYCentre() - m_iLineLength + m_iLineWidth / 2,
			m_uiColor, m_iLineWidth);
	}
	else if (m_sDirection == 2) {
		getEngine()->drawForegroundThickLine(
			getXCentre() + m_iLineWidth / 2, getYCentre(),
			getXCentre() + m_iLineLength - m_iLineWidth / 2, getYCentre(),
			m_uiColor, m_iLineWidth);
		getEngine()->drawForegroundThickLine(
			getXCentre() + m_iLineLength - m_iLineWidth / 2, getYCentre() - m_iLineEndLength / 2 + m_iLineWidth / 2,
			getXCentre() + m_iLineLength - m_iLineWidth / 2, getYCentre() + m_iLineEndLength / 2 - m_iLineWidth / 2,
			m_uiColor, m_iLineWidth);
	}
	else if (m_sDirection == 4) {
		getEngine()->drawForegroundThickLine(
			getXCentre(), getYCentre() + m_iLineWidth / 2,
			getXCentre(), getYCentre() + m_iLineLength - m_iLineWidth / 2,
			m_uiColor, m_iLineWidth);
		getEngine()->drawForegroundThickLine(
			getXCentre() - m_iLineEndLength / 2 + m_iLineWidth / 2, getYCentre() + m_iLineLength - m_iLineWidth / 2,
			getXCentre() + m_iLineEndLength / 2 - m_iLineWidth / 2, getYCentre() + m_iLineLength - m_iLineWidth / 2,
			m_uiColor, m_iLineWidth);
	}
	else if (m_sDirection == 6) {
		getEngine()->drawForegroundThickLine(
			getXCentre() - m_iLineLength + m_iLineWidth / 2, getYCentre(),
			getXCentre() - m_iLineWidth / 2, getYCentre(),
			m_uiColor, m_iLineWidth);
		getEngine()->drawForegroundThickLine(
			getXCentre() - m_iLineLength + m_iLineWidth / 2, getYCentre() - m_iLineEndLength / 2 + m_iLineWidth / 2,
			getXCentre() - m_iLineLength + m_iLineWidth / 2, getYCentre() + m_iLineEndLength / 2 - m_iLineWidth / 2,
			m_uiColor, m_iLineWidth);
	}
	else if (m_sDirection == 1) {
		getEngine()->drawForegroundThickLine(
			getXCentre() + m_iLineWidth / 4, getYCentre() - m_iLineWidth / 4,
			getXCentre() + static_cast<int>(m_iLineLength * 0.707) - m_iLineWidth / 4, getYCentre() - static_cast<int>(m_iLineLength * 0.707) + m_iLineWidth / 4,
			m_uiColor, m_iLineWidth);
		getEngine()->drawForegroundThickLine(
			getXCentre() + static_cast<int>((m_iLineLength + m_iLineEndLength / 2 - m_iLineWidth / 2) * 0.707),
			getYCentre() - static_cast<int>((m_iLineLength - m_iLineEndLength / 2) * 0.707),
			getXCentre() + static_cast<int>((m_iLineLength - m_iLineEndLength / 2) * 0.707),
			getYCentre() - static_cast<int>((m_iLineLength + m_iLineEndLength / 2 - m_iLineWidth / 2) * 0.707),
			m_uiColor, m_iLineWidth);
	}
	else if (m_sDirection == 3) {
		getEngine()->drawForegroundThickLine(
			getXCentre() + m_iLineWidth / 4, getYCentre() + m_iLineWidth / 4,
			getXCentre() + static_cast<int>(m_iLineLength * 0.707) - m_iLineWidth / 4, getYCentre() + static_cast<int>(m_iLineLength * 0.707) - m_iLineWidth / 4,
			m_uiColor, m_iLineWidth);
		getEngine()->drawForegroundThickLine(
			getXCentre() + static_cast<int>((m_iLineLength + m_iLineEndLength / 2 - m_iLineWidth / 2) * 0.707),
			getYCentre() + static_cast<int>((m_iLineLength - m_iLineEndLength / 2) * 0.707),
			getXCentre() + static_cast<int>((m_iLineLength - m_iLineEndLength / 2) * 0.707),
			getYCentre() + static_cast<int>((m_iLineLength + m_iLineEndLength / 2 - m_iLineWidth / 2) * 0.707),
			m_uiColor, m_iLineWidth);
	}
	else if (m_sDirection == 5) {
		getEngine()->drawForegroundThickLine(
			getXCentre() - m_iLineWidth / 4, getYCentre() + m_iLineWidth / 4,
			getXCentre() - static_cast<int>(m_iLineLength * 0.707) + m_iLineWidth / 4, getYCentre() + static_cast<int>(m_iLineLength * 0.707) - m_iLineWidth / 4,
			m_uiColor, m_iLineWidth);
		getEngine()->drawForegroundThickLine(
			getXCentre() - static_cast<int>((m_iLineLength + m_iLineEndLength / 2 - m_iLineWidth / 2) * 0.707),
			getYCentre() + static_cast<int>((m_iLineLength - m_iLineEndLength / 2) * 0.707),
			getXCentre() - static_cast<int>((m_iLineLength - m_iLineEndLength / 2) * 0.707),
			getYCentre() + static_cast<int>((m_iLineLength + m_iLineEndLength / 2 - m_iLineWidth / 2) * 0.707),
			m_uiColor, m_iLineWidth);
	}
	else if (m_sDirection == 7) {
		getEngine()->drawForegroundThickLine(
			getXCentre() - m_iLineWidth / 4, getYCentre() - m_iLineWidth / 4,
			getXCentre() - static_cast<int>(m_iLineLength * 0.707) + m_iLineWidth / 4, getYCentre() - static_cast<int>(m_iLineLength * 0.707) + m_iLineWidth / 4,
			m_uiColor, m_iLineWidth);
		getEngine()->drawForegroundThickLine(
			getXCentre() - static_cast<int>((m_iLineLength + m_iLineEndLength / 2 - m_iLineWidth / 2) * 0.707),
			getYCentre() - static_cast<int>((m_iLineLength - m_iLineEndLength / 2) * 0.707),
			getXCentre() - static_cast<int>((m_iLineLength - m_iLineEndLength / 2) * 0.707),
			getYCentre() - static_cast<int>((m_iLineLength + m_iLineEndLength / 2 - m_iLineWidth / 2) * 0.707),
			m_uiColor, m_iLineWidth);
	}
}

int Rail::getId()
{
	return m_id;
}

void Rail::setId(int id)
{
	m_id = id;
}

short Rail::getRailStartDirection()
{
	if (m_sDirection <= 7 || m_bIsEnd) return m_sDirection;
	else if (m_sDirection == 8) {
		if (m_bIs45) return 1;
		else return 0;
	}
	else if (m_sDirection == 9) {
		if (m_bIs45) return 1;
		else return 2;
	}
	else if (m_sDirection == 10) {
		if (m_bIs45) return 3;
		else return 2;
	}
	else if (m_sDirection == 11) {
		if (m_bIs45) return 3;
		else return 4;
	}
	else if (m_sDirection == 12) {
		if (m_bIs45) return 5;
		else return 4;
	}
	else if (m_sDirection == 13) {
		if (m_bIs45) return 5;
		else return 6;
	}
	else if (m_sDirection == 14) {
		if (m_bIs45) return 7;
		else return 6;
	}
	else { // m_sDirection == 15
		if (m_bIs45) return 7;
		else return 0;
	}
}

short Rail::getRailEndDirection()
{
	if (m_bIsEnd) printf("!! Error @ Rail.cpp getRailEndDirection() - for direction of RailEnd please call getRailStartDirection() function\n");
	else if (m_sDirection <= 7) return (m_sDirection + 4) % 8;
	else if (m_sDirection == 8) {
		if (m_bIs45) return 4;
		else return 5;
	}
	else if (m_sDirection == 9) {
		if (m_bIs45) return 6;
		else return 5;
	}
	else if (m_sDirection == 10) {
		if (m_bIs45) return 6;
		else return 7;
	}
	else if (m_sDirection == 11) {
		if (m_bIs45) return 0;
		else return 7;
	}
	else if (m_sDirection == 12) {
		if (m_bIs45) return 0;
		else return 1;
	}
	else if (m_sDirection == 13) {
		if (m_bIs45) return 2;
		else return 1;
	}
	else if (m_sDirection == 14) {
		if (m_bIs45) return 2;
		else return 3;
	}
	else { // m_sDirection == 15
		if (m_bIs45) return 4;
		else return 3;
	}
}

void Rail::virtDraw()
{
	if (m_bIsEnd) {
		if (m_re == nullptr) {
			m_re = new RailEnd(m_pEngine, m_iXStart, m_iYStart, m_sDirection, m_uiColor);
		}
		m_re->virtDraw();
	}
	else {
		switch (m_sDirection)
		{
		case 0:
			if (m_rl == nullptr) {
				m_rl = new RailLine(m_pEngine, m_iXStart, m_iYEnd, false, m_uiColor, m_iYStart - m_iYEnd);
			}
			m_rl->virtDraw();
			break;
		case 1:
			if (m_rld == nullptr) {
				m_rld = new RailLineDiagonal(m_pEngine, m_iXStart, m_iYStart, 0, m_uiColor, m_iXEnd - m_iXStart);
			}
			m_rld->virtDraw();
			break;
		case 2:
			if (m_rl == nullptr) {
				m_rl = new RailLine(m_pEngine, m_iXStart, m_iYStart, true, m_uiColor, m_iXEnd - m_iXStart);
			}
			m_rl->virtDraw();
			break;
		case 3:
			if (m_rld == nullptr) {
				m_rld = new RailLineDiagonal(m_pEngine, m_iXStart, m_iYStart, 1, m_uiColor, m_iXEnd - m_iXStart);
			}
			m_rld->virtDraw();
			break;
		case 4:
			if (m_rl == nullptr) {
				m_rl = new RailLine(m_pEngine, m_iXStart, m_iYStart, false, m_uiColor, m_iYEnd - m_iYStart);
			}
			m_rl->virtDraw();
			break;
		case 5:
			if (m_rld == nullptr) {
				m_rld = new RailLineDiagonal(m_pEngine, m_iXStart, m_iYStart, 2, m_uiColor, m_iXStart - m_iXEnd);
			}
			m_rld->virtDraw();
			break;
		case 6:
			if (m_rl == nullptr) {
				m_rl = new RailLine(m_pEngine, m_iXEnd, m_iYStart, true, m_uiColor, m_iXStart - m_iXEnd);
			}
			m_rl->virtDraw();
			break;
		case 7:
			if (m_rld == nullptr) {
				m_rld = new RailLineDiagonal(m_pEngine, m_iXStart, m_iYStart, 3, m_uiColor, m_iXStart - m_iXEnd);
			}
			m_rld->virtDraw();
			break;
		case 8:
			break;
		case 9:
			break;
		case 10:
			break;
		case 11:
			break;
		case 12:
			break;
		case 13:
			break;
		case 14:
			break;
		case 15:
			break;
		default:
			printf("!! Error @ Rail.cpp virtDraw() - invalid sDirection\n");
			break;
		}
	}
}
