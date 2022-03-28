#pragma once
#include "header.h"
#include "DisplayableObject.h"
#include "Passenger.h"
#include <vector>

class Carriage :
	public DisplayableObject
{
protected:
	int m_iMaxNumOfPassengers;
	int m_iWidth;
	int m_iLength;
	unsigned int m_uiPassengerColor;
	unsigned int m_uiColor;

	int m_iPassengerCount = 0;
	std::vector<PassengerCollection*> m_vecPassenger;

public:
	Carriage(BaseEngine* pEngine, int iXCenter, int iYCenter, unsigned int uiColor, int iMaxNumOfPassengers = 6, int iWidth = 20, int iLength = 30)
		: DisplayableObject(iXCenter, iYCenter, pEngine, iWidth, iLength, false),
		m_uiPassengerColor(0), m_uiColor(uiColor), m_iMaxNumOfPassengers(iMaxNumOfPassengers), m_iWidth(iWidth), m_iLength(iLength)
	{
		int iR = (0xff & (uiColor >> 16)) * 50 + (0xff & (0xFFFFFF >> 16)) * 50;
		int iG = (0xff & (uiColor >> 8)) * 50 + (0xff & (0xFFFFFF >> 8)) * 50;
		int iB = (0xff & uiColor) * 50 + (0xff & 0xFFFFFF) * 50;
		m_uiPassengerColor = (((iR / 100) & 0xff) << 16) | (((iG / 100) & 0xff) << 8) | ((iB / 100) & 0xff);

		m_vecPassenger.resize(iMaxNumOfPassengers, nullptr);
	}

	~Carriage()
	{
		for (int i = 0; i < m_iMaxNumOfPassengers; i++) {
			if (m_vecPassenger[i] != nullptr) {
				delete m_vecPassenger[i];
			}
		}
	}

	virtual void virtDraw() override = 0;
	//virtual void virtDoUpdate(int iCurrentTime) override = 0;

	void addPassenger(PassengerCollection* oPassenger);
	std::vector<int> findPassengerByType(short sType);
	void removePassenger(int iIndex);
};

class CarriageHead :
	public Carriage
{
public:
	CarriageHead(BaseEngine* pEngine, int iXCenter, int iYCenter, unsigned int uiColor, int iMaxNumOfPassengers = 6, int iWidth = 20, int iLength = 30)
		: Carriage(pEngine, iXCenter, iYCenter, uiColor, iMaxNumOfPassengers, iWidth, iLength)
	{}

	void virtDraw() override;
};

class CarriageMain :
	public Carriage
{
public:
	CarriageMain(BaseEngine* pEngine, int iXCenter, int iYCenter, unsigned int uiColor, int iMaxNumOfPassengers = 6, int iWidth = 20, int iLength = 30)
		: Carriage(pEngine, iXCenter, iYCenter, uiColor, iMaxNumOfPassengers, iWidth, iLength)
	{}

	void virtDraw() override;
};

class CarriageHeadFast :
	public Carriage
{
public:
	CarriageHeadFast(BaseEngine* pEngine, int iXCenter, int iYCenter, unsigned int uiColor, int iMaxNumOfPassengers = 4, int iWidth = 20, int iLength = 20)
		: Carriage(pEngine, iXCenter, iYCenter, uiColor, iMaxNumOfPassengers, iWidth, iLength)
	{}

	void virtDraw() override;
};

class CarriageHeadIntelli :
	public Carriage
{
private:
	unsigned int m_uiBorderColor;

public:
	CarriageHeadIntelli(BaseEngine* pEngine, int iXCenter, int iYCenter, unsigned int uiColor = 0xFFD700, unsigned int uiBorderColor = 0xCD9B1D,
		int iMaxNumOfPassengers = 8, int iWidth = 20, int iLength = 40)
		: Carriage(pEngine, iXCenter, iYCenter, uiColor, iMaxNumOfPassengers, iWidth, iLength), m_uiBorderColor(uiBorderColor)
	{}

	void virtDraw() override;
};

class CarriageCollection {
private:
	Carriage* m_oCarriage;

public:
	/* sType - a short number between [0,3] for different shape of station
	* 0 - head  1 - fast head  2 - intelligent head  3 - main
	* `uiBorderColor` is only useful for 2
	* for 1, `iMaxNumOfPassengers` should be 4, `iLength` should be 20
	* for 2, `iMaxNumOfPassengers` should be 8, `iLength` should be 40
	*/
	CarriageCollection(short sType, BaseEngine* pEngine, int iXCenter, int iYCenter, unsigned int uiColor,
		int iMaxNumOfPassengers = 6, int iWidth = 20, int iLength = 30, unsigned int uiBorderColor = 0xCD9B1D)
		: m_oCarriage(NULL)
	{
		switch (sType) {
		case 0:
			m_oCarriage = new CarriageHead(pEngine, iXCenter, iYCenter, uiColor, iMaxNumOfPassengers, iWidth, iLength);
			break;
		case 1:
			m_oCarriage = new CarriageHeadFast(pEngine, iXCenter, iYCenter, uiColor, iMaxNumOfPassengers, iWidth, iLength);
			break;
		case 2:
			m_oCarriage = new CarriageHeadIntelli(pEngine, iXCenter, iYCenter, uiColor, uiBorderColor, iMaxNumOfPassengers, iWidth, iLength);
			break;
		case 3:
			m_oCarriage = new CarriageMain(pEngine, iXCenter, iYCenter, uiColor, iMaxNumOfPassengers, iWidth, iLength);
			break;
		default:
			printf("!! Error @ Train.h CarriageCollection Constructor - invalid sIndex\n");
			break;
		}
	}

	Carriage* getCarriage();
};


class Train
{

};