#pragma once
#include "header.h"
#include "DisplayableObject.h"

class Passenger :
	public DisplayableObject
{
protected:
	int m_iSize;
	unsigned int m_uiColor;

	double m_dXExactPos;
	double m_dYExactPos;

public:
	Passenger(BaseEngine* pEngine, double dXCenter, double dYCenter, unsigned int uiColor = 0x000000, int iSize = 8)
		: DisplayableObject(dXCenter, dYCenter, pEngine, iSize, iSize, false), m_uiColor(uiColor), m_iSize(iSize),
		m_dXExactPos(dXCenter), m_dYExactPos(dYCenter)
	{}

	virtual void virtDraw() override = 0;
	void setColor(unsigned int uiColor);
	double getXCenter();
	void setXCenter(double iXCenter);
	void incXCenter(double incrementX);
	double getYCenter();
	void setYCenter(double iYCenter);
	void incYCenter(double incrementY);
};

class PassengerCircle :
	public Passenger
{
public:
	PassengerCircle(BaseEngine* pEngine, double dXCenter, double dYCenter, unsigned int uiColor = 0x000000, int iSize = 8)
		: Passenger(pEngine, dXCenter, dYCenter, uiColor, iSize)
	{}

	void virtDraw() override;
};

class PassengerSquare :
	public Passenger
{
public:
	PassengerSquare(BaseEngine* pEngine, double dXCenter, double dYCenter, unsigned int uiColor = 0x000000, int iSize = 8)
		: Passenger(pEngine, dXCenter, dYCenter, uiColor, iSize)
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
	PassengerDiamond(BaseEngine* pEngine, double dXCenter, double dYCenter, unsigned int uiColor = 0x000000, int iSize = 8)
		: Passenger(pEngine, dXCenter, dYCenter, uiColor, iSize)
	{}

	void virtDraw() override;
};

class PassengerTriangle :
	public Passenger
{
public:
	PassengerTriangle(BaseEngine* pEngine, double dXCenter, double dYCenter, unsigned int uiColor = 0x000000, int iSize = 8)
		: Passenger(pEngine, dXCenter, dYCenter, uiColor, iSize)
	{}

	void virtDraw() override;
};

class PassengerInvTriangle :
	public Passenger
{
public:
	PassengerInvTriangle(BaseEngine* pEngine, double dXCenter, double dYCenter, unsigned int uiColor = 0x000000, int iSize = 8)
		: Passenger(pEngine, dXCenter, dYCenter, uiColor, iSize)
	{}

	void virtDraw() override;
};

class PassengerFlower :
	public Passenger
{
private:
	int dist(int x1, int y1, int x2, int y2);

public:
	PassengerFlower(BaseEngine* pEngine, double dXCenter, double dYCenter, unsigned int uiColor = 0x000000, int iSize = 8)
		: Passenger(pEngine, dXCenter, dYCenter, uiColor, iSize)
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
	PassengerCollection(short sType, BaseEngine* pEngine, double dXCenter = 0, double dYCenter = 0, unsigned int uiColor = 0x000000, int iSize = 8)
		: m_sType(0), m_oPassenger(NULL)
	{
		switch (sType) {
		case 0:
			m_sType = 0;
			m_oPassenger = new PassengerCircle(pEngine, dXCenter, dYCenter, uiColor, iSize);
			break;
		case 1:
			m_sType = 1;
			m_oPassenger = new PassengerSquare(pEngine, dXCenter, dYCenter, uiColor, iSize);
			break;
		case 2:
			m_sType = 2;
			m_oPassenger = new PassengerTriangle(pEngine, dXCenter, dYCenter, uiColor, iSize);
			break;
		case 3:
			m_sType = 3;
			m_oPassenger = new PassengerInvTriangle(pEngine, dXCenter, dYCenter, uiColor, iSize);
			break;
		case 4:
			m_sType = 4;
			m_oPassenger = new PassengerDiamond(pEngine, dXCenter, dYCenter, uiColor, iSize);
			break;
		case 5:
			m_sType = 5;
			m_oPassenger = new PassengerFlower(pEngine, dXCenter, dYCenter, uiColor, iSize);
			break;
		default:
			printf("!! Error @ Passenger.h PassengerCollection Constructor - invalid sIndex\n");
			break;
		}
	}

	~PassengerCollection() {
		delete m_oPassenger;
	}

	Passenger* getPassenger();
	short getType();
};

