#pragma once
#include "header.h"
#include "DisplayableObject.h"

class Passenger :
	public DisplayableObject
{
protected:
	int m_iSize;
	unsigned int m_uiColor;

public:
	Passenger(BaseEngine* pEngine, int iXCenter, int iYCenter, unsigned int uiColor = 0x000000, int iSize = 8)
		: DisplayableObject(iXCenter, iYCenter, pEngine, iSize, iSize, false), m_uiColor(uiColor), m_iSize(iSize)
	{}

	virtual void virtDraw() override = 0;
};

class PassengerCircle :
	public Passenger
{
public:
	PassengerCircle(BaseEngine* pEngine, int iXCenter, int iYCenter, unsigned int uiColor = 0x000000, int iSize = 8)
		: Passenger(pEngine, iXCenter, iYCenter, uiColor, iSize)
	{}

	void virtDraw() override;
};

class PassengerSquare :
	public Passenger
{
public:
	PassengerSquare(BaseEngine* pEngine, int iXCenter, int iYCenter, unsigned int uiColor = 0x000000, int iSize = 8)
		: Passenger(pEngine, iXCenter, iYCenter, uiColor, iSize)
	{}

	void virtDraw() override;
};

//class PassengerHexagon :
//	public Passenger
//{
//public:
//	PassengerHexagon(BaseEngine* pEngine, int iXCenter, int iYCenter, unsigned int uiColor = 0x000000, int iSize = 8)
//		: Passenger(pEngine, iXCenter, iYCenter, uiColor, iSize)
//	{}
//
//	void virtDraw() override;
//};

class PassengerDiamond :
	public Passenger
{
public:
	PassengerDiamond(BaseEngine* pEngine, int iXCenter, int iYCenter, unsigned int uiColor = 0x000000, int iSize = 8)
		: Passenger(pEngine, iXCenter, iYCenter, uiColor, iSize)
	{}

	void virtDraw() override;
};

class PassengerTriangle :
	public Passenger
{
public:
	PassengerTriangle(BaseEngine* pEngine, int iXCenter, int iYCenter, unsigned int uiColor = 0x000000, int iSize = 8)
		: Passenger(pEngine, iXCenter, iYCenter, uiColor, iSize)
	{}

	void virtDraw() override;
};

class PassengerInvTriangle :
	public Passenger
{
public:
	PassengerInvTriangle(BaseEngine* pEngine, int iXCenter, int iYCenter, unsigned int uiColor = 0x000000, int iSize = 8)
		: Passenger(pEngine, iXCenter, iYCenter, uiColor, iSize)
	{}

	void virtDraw() override;
};

class PassengerFlower :
	public Passenger
{
private:
	int dist(int x1, int y1, int x2, int y2);

public:
	PassengerFlower(BaseEngine* pEngine, int iXCenter, int iYCenter, unsigned int uiColor = 0x000000, int iSize = 8)
		: Passenger(pEngine, iXCenter, iYCenter, uiColor, iSize)
	{}

	void virtDraw() override;
};

class PassengerCollection {
private:
	short m_sType;
	Passenger* m_oPassenger;

public:
	/* sType - a short number between [0,5] for different shape of passenger
	* 0 - circle  1 - square  2 - triangle
	* 3 - invert triangle  4 - diamond  5 - flower
	*/
	PassengerCollection(short sType, BaseEngine* pEngine, int iXCenter = 0, int iYCenter = 0, unsigned int uiColor = 0x000000, int iSize = 8)
		: m_sType(0), m_oPassenger(NULL)
	{
		switch (sType) {
		case 0:
			m_sType = 0;
			m_oPassenger = new PassengerCircle(pEngine, iXCenter, iYCenter, uiColor, iSize);
			break;
		case 1:
			m_sType = 1;
			m_oPassenger = new PassengerSquare(pEngine, iXCenter, iYCenter, uiColor, iSize);
			break;
		case 2:
			m_sType = 2;
			m_oPassenger = new PassengerTriangle(pEngine, iXCenter, iYCenter, uiColor, iSize);
			break;
		case 3:
			m_sType = 3;
			m_oPassenger = new PassengerInvTriangle(pEngine, iXCenter, iYCenter, uiColor, iSize);
			break;
		case 4:
			m_sType = 4;
			m_oPassenger = new PassengerDiamond(pEngine, iXCenter, iYCenter, uiColor, iSize);
			break;
		case 5:
			m_sType = 5;
			m_oPassenger = new PassengerFlower(pEngine, iXCenter, iYCenter, uiColor, iSize);
			break;
		default:
			printf("!! Error @ Passenger.h PassengerCollection Constructor - invalid sIndex\n");
			break;
		}
	}

	Passenger* getPassenger();
	short getType();
};

