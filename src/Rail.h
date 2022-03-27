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

//class Rail
//{
//private:
//	short m_sDirection;
//	double m_dSpeed;
//
//public:
//	//Rail(BaseEngine* pEngine, int iSize = 50,
//	//    int iX = 500, int iY = 500, double dSpeed = 2, short sDirection = 0)
//	//    : DisplayableObject(iX, iY, pEngine, iSize, iSize), m_sDirection(sDirection)
//	//{
//	//}
//
//	//void virtDraw() override;
//};