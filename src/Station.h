#pragma once
#include "header.h"
#include "DisplayableObject.h"
#include "Passenger.h"
#include <vector>

class Station :
	public DisplayableObject
{
protected:
	int m_iBorderWidth;
	int m_iSize;
	unsigned int m_uiInnerColor;
	unsigned int m_uiColor;

	int m_iPassengerCount = 0;
	std::vector<PassengerCollection*> m_vecPassenger;

public:
	Station(BaseEngine* pEngine, int iXCenter, int iYCenter,
		unsigned int uiInnerColor = 0xFFFFFF, unsigned int uiColor = 0x000000, int iBorderWidth = 5, int iSize = 40)
		: DisplayableObject(iXCenter, iYCenter, pEngine, iSize, iSize, false),
		m_uiInnerColor(uiInnerColor), m_uiColor(uiColor), m_iBorderWidth(iBorderWidth), m_iSize(iSize)
	{}

	~Station()
	{
		for (int i = 0; i < m_iPassengerCount; i++) {
			delete m_vecPassenger[i];
		}
	}

	virtual void virtDraw() override = 0;
	//virtual void virtDoUpdate(int iCurrentTime) override = 0;

	void addPassenger(PassengerCollection* oPassenger);
	// returns the index of the first passenger of given type; return -1 if not found
	int findFirstPassengerOfType(short sType);
	// returns the type of the first passenger
	short removeFirstPassenger();
	void removePassenger(int iIndex);
	bool isEmpty();
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

//class StationHexagon :
//	public Station
//{
//public:
//	StationHexagon(BaseEngine* pEngine, int iXCenter, int iYCenter,
//		unsigned int uiInnerColor = 0xFFFFFF, unsigned int uiColor = 0x000000, int iBorderWidth = 5, int iSize = 40)
//		: Station(pEngine, iXCenter, iYCenter, uiInnerColor, uiColor, iBorderWidth, iSize)
//	{}
//
//	void virtDraw() override;
//};

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

class StationFlower :
	public Station
{
private:
	int dist(int x1, int y1, int x2, int y2);

public:
	StationFlower(BaseEngine* pEngine, int iXCenter, int iYCenter,
		unsigned int uiInnerColor = 0xFFFFFF, unsigned int uiColor = 0x000000, int iBorderWidth = 5, int iSize = 40)
		: Station(pEngine, iXCenter, iYCenter, uiInnerColor, uiColor, iBorderWidth, iSize)
	{}

	void virtDraw() override;
};

class StationCollection {
private:
	int m_id;
	short m_sType;
	Station* m_oStation;

public:
	/* sType - a short number between [0,5] for different shape of station
	* 0 - circle  1 - square  2 - triangle
	* 3 - invert triangle  4 - diamond  5 - flower
	*/
	StationCollection(int id, short sType, BaseEngine* pEngine, int iXCenter, int iYCenter,
		unsigned int uiInnerColor = 0xFFFFFF, unsigned int uiColor = 0x000000, int iBorderWidth = 5, int iSize = 40)
		: m_id(id), m_sType(0), m_oStation(NULL)
	{
		switch (sType) {
		case 0:
			m_sType = 0;
			m_oStation = new StationCircle(pEngine, iXCenter, iYCenter, uiInnerColor, uiColor, iBorderWidth, iSize);
			break;
		case 1:
			m_sType = 1;
			m_oStation = new StationSquare(pEngine, iXCenter, iYCenter, uiInnerColor, uiColor, iBorderWidth, iSize);
			break;
		case 2:
			m_sType = 2;
			m_oStation = new StationTriangle(pEngine, iXCenter, iYCenter, uiInnerColor, uiColor, iBorderWidth, iSize);
			break;
		case 3:
			m_sType = 3;
			m_oStation = new StationInvTriangle(pEngine, iXCenter, iYCenter, uiInnerColor, uiColor, iBorderWidth, iSize);
			break;
		case 4:
			m_sType = 4;
			m_oStation = new StationDiamond(pEngine, iXCenter, iYCenter, uiInnerColor, uiColor, iBorderWidth, iSize);
			break;
		case 5:
			m_sType = 5;
			m_oStation = new StationFlower(pEngine, iXCenter, iYCenter, uiInnerColor, uiColor, iBorderWidth, iSize);
			break;
		default:
			printf("!! Error @ Station.h StationCollection Constructor - invalid sIndex\n");
			break;
		}
		m_oStation->setShouldDeleteOnRemoval(false);
	}

	~StationCollection() {
		delete m_oStation;
	}

	Station* getStation();
	int getId();
	void setId(int id);
	short getType();
};