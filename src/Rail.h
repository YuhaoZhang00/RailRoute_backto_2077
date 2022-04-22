#pragma once
#include "header.h"
#include "DisplayableObject.h"

class RailLine :
	public DisplayableObject
{
private:
	bool m_bIsHorizontal;
	int m_iLineWidth;
	unsigned int m_uiColor;

public:
	RailLine(BaseEngine* pEngine, int iXStart, int iYStart, bool bIsHorizontal, unsigned int uiColor, int iLen, int iLineWidth = 10)
		: DisplayableObject(iXStart, iYStart, pEngine, 0, 0), m_bIsHorizontal(bIsHorizontal), m_uiColor(uiColor), m_iLineWidth(iLineWidth)
	{
		if (bIsHorizontal) {
			m_iDrawWidth = iLen;
			m_iDrawHeight = iLineWidth;
			m_iCurrentScreenY = iYStart - iLineWidth / 2;
		}
		else {
			m_iDrawWidth = iLineWidth;
			m_iDrawHeight = iLen;
			m_iCurrentScreenX = iXStart - iLineWidth / 2;
		}
	}

	void virtDraw() override;
};

class RailLineDiagonal :
	public DisplayableObject
{
private:
	/* a number between [0,3] showing the direction of the rail
	* 0: to upper-right
	* 1: to lower-right
	* 2: to lower-left
	* 3: to upper-left */
	short m_sDirection;
	int m_iLineWidth;
	unsigned int m_uiColor;

public:
	RailLineDiagonal(BaseEngine* pEngine, int iXStart, int iYStart, short sDirection, unsigned int uiColor, int iLenInXOrY, int iLineWidth = 10)
		: DisplayableObject(iXStart, iYStart, pEngine, iLenInXOrY, iLenInXOrY), m_sDirection(sDirection), m_uiColor(uiColor), m_iLineWidth(iLineWidth)
	{
		if (sDirection == 0) {
			m_iCurrentScreenY -= iLenInXOrY;
		}
		else if (sDirection == 1) {
		}
		else if (sDirection == 2) {
			m_iCurrentScreenX -= iLenInXOrY;
		}
		else if (sDirection == 3) {
			m_iCurrentScreenX -= iLenInXOrY;
			m_iCurrentScreenY -= iLenInXOrY;
		}
		else {
			printf("!! Error @ Rail.h RailLineDiagonal Constructor - invalid sDirection\n");
		}
	}

	void virtDraw() override;
};

//class RailLink135 :
//	public DisplayableObject
//{
//private:
//	int m_iLineWidth;
//	unsigned int m_uiColor;
//
//public:
//	RailLink135(BaseEngine* pEngine, int iXCenter, int iYCenter, unsigned int uiColor, int iLineWidth = 10)
//		: DisplayableObject(iXCenter, iYCenter, pEngine, iLineWidth, iLineWidth, false), m_uiColor(uiColor), m_iLineWidth(iLineWidth)
//	{
//	}
//
//	void virtDraw() override;
//};

class RailLink90 :
	public DisplayableObject
{
private:
	/* a number between [0,3] showing the center point of the arc
	* 0: center at upper-right
	* 1: center at lower-right
	* 2: center at lower-left
	* 3: center at upper-left */
	short m_sDirection;
	int m_iRadius;
	int m_iLineWidth;
	unsigned int m_uiColor;

	int dist(int x1, int y1, int x2, int y2);

public:
	RailLink90(BaseEngine* pEngine, int iXStart, int iYStart, short sDirection, unsigned int uiColor, int iRadius = 20, int iLineWidth = 10)
		: DisplayableObject(iXStart, iYStart, pEngine, iRadius, iRadius), m_sDirection(sDirection), m_uiColor(uiColor), m_iRadius(iRadius), m_iLineWidth(iLineWidth)
	{
		if (sDirection != 0 && sDirection != 1 && sDirection != 2 && sDirection != 3) {
			printf("!! Error @ Rail.h RailLink90 Constructor - invalid sDirection\n");
		}
	}

	void virtDraw() override;
};

class RailLink90Diagonal :
	public DisplayableObject
{
private:
	/* a number between [0,3] showing the center point of the arc
	* 0: center at right
	* 1: center at bottom
	* 2: center at left
	* 3: center at top */
	short m_sDirection;
	int m_iRadius;
	int m_iLineWidth;
	unsigned int m_uiColor;

	int dist(int x1, int y1, int x2, int y2);

public:
	RailLink90Diagonal(BaseEngine* pEngine, int iXStart, int iYStart, short sDirection, unsigned int uiColor, int iRadius = 20, int iLineWidth = 10)
		: DisplayableObject(iXStart, iYStart, pEngine, static_cast<int>(iRadius * 1.414), static_cast<int>(iRadius * 1.414)),
		m_sDirection(sDirection), m_uiColor(uiColor), m_iRadius(iRadius), m_iLineWidth(iLineWidth)
	{
		if (sDirection != 0 && sDirection != 1 && sDirection != 2 && sDirection != 3) {
			printf("!! Error @ Rail.h RailLink90Diagonal Constructor - invalid sDirection\n");
		}
	}

	void virtDraw() override;
};

//class RailEnd :
//	public DisplayableObject
//{
//private:
//	short m_sDirection;
//	double m_dSpeed;
//
//public:
//	RailEnd(BaseEngine* pEngine, int iSize = 50,
//		int iX = 500, int iY = 500, double dSpeed = 2, short sDirection = 0)
//		: DisplayableObject(iX, iY, pEngine, iSize, iSize), m_sDirection(sDirection)
//	{
//	}
//
//	void virtDraw() override;
//};

class Rail
{
private:
	int m_id;

	BaseEngine* m_pEngine;

	/* a number between [0,15] showing the starting direction of the rail
	*  7 (15) 0 (8)  1
	* (14)          (9)
	*  6             2
	* (13)          (10)
	*  5 (12) 4 (11) 3 */
	short m_sDirection;
	// only used when m_sDirection in [8,15]
	bool m_bIs45;

	int m_iXStart;
	int m_iYStart;
	int m_iXEnd;
	int m_iYEnd;

	unsigned int m_uiColor;
	int m_iRadius;
	int m_iLineWidth;

public:
	Rail(int id, BaseEngine* pEngine, int iXStart, int iYStart, int iXEnd, int iYEnd,
		bool bIs45, unsigned int uiColor, int iRadius = 20, int iLineWidth = 10)
		: m_id(id), m_pEngine(pEngine), m_iXStart(iXStart), m_iYStart(iYStart), m_iXEnd(iXEnd), m_iYEnd(iYEnd),
		m_bIs45(bIs45), m_sDirection(0), m_uiColor(uiColor), m_iRadius(iRadius), m_iLineWidth(iLineWidth)
	{
		if (iXStart == iXEnd) {
			if (iYStart > iYEnd) m_sDirection = 0;
			else if (iYStart < iYEnd) m_sDirection = 4;
			else printf("!! Error @ Rail.h Rail Constructor - start point and end point are same\n");
		}
		else if (iYStart == iYEnd) {
			if (iXStart > iXEnd) m_sDirection = 6;
			else if (iXStart < iXEnd) m_sDirection = 2;
		}
		else if (iXStart > iXEnd) {
			if (iYStart > iYEnd) {
				if (abs(iXEnd - iXStart) == abs(iYEnd - iYStart)) m_sDirection = 7;
				else if (abs(iXEnd - iXStart) > abs(iYEnd - iYStart)) m_sDirection = 14;
				else m_sDirection = 15; // abs(iXEnd - iXStart)  abs(iYEnd - iYStart)
			}
			else { // iYStart < iYEnd
				if (abs(iXEnd - iXStart) == abs(iYEnd - iYStart)) m_sDirection = 5;
				else if (abs(iXEnd - iXStart) > abs(iYEnd - iYStart)) m_sDirection = 13;
				else m_sDirection = 12; // abs(iXEnd - iXStart)  abs(iYEnd - iYStart)
			}
		}
		else { // iXStart < iXEnd
			if (iYStart > iYEnd) {
				if (abs(iXEnd - iXStart) == abs(iYEnd - iYStart)) m_sDirection = 1;
				else if (abs(iXEnd - iXStart) > abs(iYEnd - iYStart)) m_sDirection = 9;
				else m_sDirection = 8; // abs(iXEnd - iXStart)  abs(iYEnd - iYStart)
			}
			else { // iYStart < iYEnd
				if (abs(iXEnd - iXStart) == abs(iYEnd - iYStart)) m_sDirection = 3;
				else if (abs(iXEnd - iXStart) > abs(iYEnd - iYStart)) m_sDirection = 10;
				else m_sDirection = 11; // abs(iXEnd - iXStart)  abs(iYEnd - iYStart)
			}
		}
	}

	//void virtDraw() override;
};