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
