#pragma once
#include "header.h"
#include "DisplayableObject.h"

class Station :
	public DisplayableObject
{
protected:
	int m_iBorderWidth;
	int m_iSize;
	unsigned int m_uiInnerColor;
	unsigned int m_uiColor;

public:
	Station(BaseEngine* pEngine, int iXCenter, int iYCenter,
		unsigned int uiInnerColor = 0xFFFFFF, unsigned int uiColor = 0x000000, int iBorderWidth = 5, int iSize = 40)
		: DisplayableObject(iXCenter, iYCenter, pEngine, iSize, iSize, false),
		m_uiInnerColor(uiInnerColor), m_uiColor(uiColor), m_iBorderWidth(iBorderWidth), m_iSize(iSize)
	{}

	virtual void virtDraw() override = 0;
};

class StationCircle :
	public Station
{
public:
	StationCircle(BaseEngine* pEngine, int iXCenter, int iYCenter,
		unsigned int uiInnerColor = 0xFFFFFF, unsigned int uiColor = 0x000000, int iBorderWidth = 5, int iSize = 40)
		: Station(pEngine, iXCenter, iYCenter, uiInnerColor, uiColor, iBorderWidth, iSize)
	{}

	void virtDraw() override;
};

class StationSquare :
	public Station
{
public:
	StationSquare(BaseEngine* pEngine, int iXCenter, int iYCenter,
		unsigned int uiInnerColor = 0xFFFFFF, unsigned int uiColor = 0x000000, int iBorderWidth = 5, int iSize = 40)
		: Station(pEngine, iXCenter, iYCenter, uiInnerColor, uiColor, iBorderWidth, iSize)
	{}

	void virtDraw() override;
};

class StationHexagon :
	public Station
{
public:
	StationHexagon(BaseEngine* pEngine, int iXCenter, int iYCenter,
		unsigned int uiInnerColor = 0xFFFFFF, unsigned int uiColor = 0x000000, int iBorderWidth = 5, int iSize = 40)
		: Station(pEngine, iXCenter, iYCenter, uiInnerColor, uiColor, iBorderWidth, iSize)
	{}

	void virtDraw() override;
};

class StationDiamond :
	public Station
{
public:
	StationDiamond(BaseEngine* pEngine, int iXCenter, int iYCenter,
		unsigned int uiInnerColor = 0xFFFFFF, unsigned int uiColor = 0x000000, int iBorderWidth = 5, int iSize = 40)
		: Station(pEngine, iXCenter, iYCenter, uiInnerColor, uiColor, iBorderWidth, iSize)
	{}

	void virtDraw() override;
};

class StationTriangle :
	public Station
{
public:
	StationTriangle(BaseEngine* pEngine, int iXCenter, int iYCenter,
		unsigned int uiInnerColor = 0xFFFFFF, unsigned int uiColor = 0x000000, int iBorderWidth = 5, int iSize = 40)
		: Station(pEngine, iXCenter, iYCenter, uiInnerColor, uiColor, iBorderWidth, iSize)
	{}

	void virtDraw() override;
};

class StationInvTriangle :
	public Station
{
public:
	StationInvTriangle(BaseEngine* pEngine, int iXCenter, int iYCenter,
		unsigned int uiInnerColor = 0xFFFFFF, unsigned int uiColor = 0x000000, int iBorderWidth = 5, int iSize = 40)
		: Station(pEngine, iXCenter, iYCenter, uiInnerColor, uiColor, iBorderWidth, iSize)
	{}

	void virtDraw() override;
};

class StationCollection {
private:
	Station* m_oStation;

public:
	/* sIndex - a short number between [0,5] for different shape of station
	* 0 - circle  1 - square  2 - triangle
	* 3 - invert triangle  4 - hexagon  5 - diamond
	*/
	StationCollection(short sIndex, BaseEngine* pEngine, int iXCenter, int iYCenter,
		unsigned int uiInnerColor = 0xFFFFFF, unsigned int uiColor = 0x000000, int iBorderWidth = 5, int iSize = 40)
		: m_oStation(NULL)
	{
		switch (sIndex) {
		case 0:
			m_oStation = new StationCircle(pEngine, iXCenter, iYCenter, uiInnerColor, uiColor, iBorderWidth, iSize);
			break;
		case 1:
			m_oStation = new StationSquare(pEngine, iXCenter, iYCenter, uiInnerColor, uiColor, iBorderWidth, iSize);
			break;
		case 2:
			m_oStation = new StationTriangle(pEngine, iXCenter, iYCenter, uiInnerColor, uiColor, iBorderWidth, iSize);
			break;
		case 3:
			m_oStation = new StationInvTriangle(pEngine, iXCenter, iYCenter, uiInnerColor, uiColor, iBorderWidth, iSize);
			break;
		case 4:
			m_oStation = new StationHexagon(pEngine, iXCenter, iYCenter, uiInnerColor, uiColor, iBorderWidth, iSize);
			break;
		case 5:
			m_oStation = new StationDiamond(pEngine, iXCenter, iYCenter, uiInnerColor, uiColor, iBorderWidth, iSize);
			break;
		default:
			printf("!! Error @ Station.h StationCollection Constructor - invalid sIndex\n");
			break;
		}
	}

	Station* getStation();
};