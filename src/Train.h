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

	int getLength();
	int getMaxNumOfPassengers();

	void addPassenger(PassengerCollection* oPassenger);
	std::vector<int> findPassengerByType(short sType);
	void removePassenger(int iIndex);
	bool isFull();
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
	unsigned int m_uiSpecialColor;

public:
	CarriageHeadIntelli(BaseEngine* pEngine, int iXCenter, int iYCenter, unsigned int uiColor = 0xFFD700, unsigned int uiSpecialColor = 0xCD9B1D,
		int iMaxNumOfPassengers = 8, int iWidth = 20, int iLength = 40)
		: Carriage(pEngine, iXCenter, iYCenter, uiColor, iMaxNumOfPassengers, iWidth, iLength), m_uiSpecialColor(uiSpecialColor)
	{}

	void virtDraw() override;
};

class CarriageCollection {
private:
	Carriage* m_oCarriage;

public:
	/* sType - a short number between [0,3] for different type or carriage
	* 0 - head  1 - fast head  2 - intelligent head  3 - main
	* `uiBorderColor` is only useful for type 2 carriage
	* set `iMaxNumOfPassengers` and `iLength` (i.e. default setting) will generate default train
	*/
	CarriageCollection(short sType, BaseEngine* pEngine, int iXCenter, int iYCenter, unsigned int uiColor, unsigned int uiSpecialColor = 0xCD9B1D,
		int iMaxNumOfPassengers = -1, int iWidth = 20, int iLength = -1)
		: m_oCarriage(NULL)
	{
		switch (sType) {
		case 0:
			m_oCarriage = new CarriageHead(pEngine, iXCenter, iYCenter, uiColor, (iMaxNumOfPassengers == -1) ? 6 : iMaxNumOfPassengers, iWidth,
				(iLength == -1) ? 30 : iLength);
			break;
		case 1:
			m_oCarriage = new CarriageHeadFast(pEngine, iXCenter, iYCenter, uiColor, (iMaxNumOfPassengers == -1) ? 4 : iMaxNumOfPassengers, iWidth,
				(iLength == -1) ? 20 : iLength);
			break;
		case 2:
			m_oCarriage = new CarriageHeadIntelli(pEngine, iXCenter, iYCenter, uiColor, uiSpecialColor,
				(iMaxNumOfPassengers == -1) ? 8 : iMaxNumOfPassengers, iWidth, (iLength == -1) ? 40 : iLength);
			break;
		case 3:
			m_oCarriage = new CarriageMain(pEngine, iXCenter, iYCenter, uiColor, (iMaxNumOfPassengers == -1) ? 6 : iMaxNumOfPassengers, iWidth,
				(iLength == -1) ? 30 : iLength);
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
protected:
	BaseEngine* m_pEngine;
	int m_iXCenterHead;
	int m_iYCenterHead;
	unsigned int m_uiColor;
	int m_iDist;

	int m_iCarriageCount = 0;
	std::vector<CarriageCollection*> m_vecCarriage;

	int m_iPassengerCount = 0;
	int m_iMaxNumOfPassengers = 0;

public:
	Train(BaseEngine* pEngine, int iXCenterHead, int iYCenterHead, unsigned int uiColor, int iDist = 5)
		: m_pEngine(pEngine), m_iXCenterHead(iXCenterHead), m_iYCenterHead(iYCenterHead), m_uiColor(uiColor), m_iDist(iDist)
	{}

	~Train()
	{
		for (int i = 0; i < m_iCarriageCount; i++) {
			delete m_vecCarriage[i];
		}
	}

	//virtual void virtDraw() override = 0;
	//virtual void virtDoUpdate(int iCurrentTime) override = 0;

	virtual void addHead(int iMaxNumberOfPassengers = -1, int iLength = -1) = 0;
	void addCarriage(int iMaxNumberOfPassengers = -1, int iLength = -1);
	void removeCarriageAfterN(int iIndex);
	std::vector<CarriageCollection*> getCarriageList();
	void addPassenger(PassengerCollection* oPassenger);
	std::vector<int> findPassengerByType(short sType);
	void removePassenger(int iIndex);
	bool isFull();
};

class TrainNormal :
	public Train
{
public:
	TrainNormal(BaseEngine* pEngine, int iXCenterHead, int iYCenterHead, unsigned int uiColor, int iDist = 5)
		: Train(pEngine, iXCenterHead, iYCenterHead, uiColor, iDist)
	{}

	void addHead(int iMaxNumberOfPassengers = -1, int iLength = -1) override;
};

class TrainFast :
	public Train
{
public:
	TrainFast(BaseEngine* pEngine, int iXCenterHead, int iYCenterHead, unsigned int uiColor, int iDist = 5)
		: Train(pEngine, iXCenterHead, iYCenterHead, uiColor, iDist)
	{}

	void addHead(int iMaxNumberOfPassengers = -1, int iLength = -1) override;
};

class TrainIntelli :
	public Train
{
private:
	unsigned int m_uiSpecialColor;

public:
	TrainIntelli(BaseEngine* pEngine, int iXCenterHead, int iYCenterHead, unsigned int uiColor, int iDist = 5, int uiSpecialColor = 0xCD9B1D)
		: Train(pEngine, iXCenterHead, iYCenterHead, uiColor, iDist), m_uiSpecialColor(uiSpecialColor)
	{}

	void addHead(int iMaxNumberOfPassengers = -1, int iLength = -1) override;
};

class TrainCollection
{
private:
	Train* m_oTrain;

public:
	/* sType - a short number between [0,2] for different type of train
	* 0 - normal train  1 - fast train  2 - intelligent train
	* `uiBorderColor` is only useful for type 2 train
	*/
	TrainCollection(short sType, BaseEngine* pEngine, int iXCenterHead, int iYCenterHead, unsigned int uiColor, int iDist = 5, unsigned int uiSpecialColor = 0xCD9B1D)
		: m_oTrain(NULL)
	{
		switch (sType) {
		case 0:
			m_oTrain = new TrainNormal(pEngine, iXCenterHead, iYCenterHead, uiColor, iDist);
			break;
		case 1:
			m_oTrain = new TrainFast(pEngine, iXCenterHead, iYCenterHead, uiColor, iDist);
			break;
		case 2:
			m_oTrain = new TrainIntelli(pEngine, iXCenterHead, iYCenterHead, uiColor, iDist, uiSpecialColor);
			break;
		default:
			printf("!! Error @ Train.h TrainCollection Constructor - invalid sIndex\n");
			break;
		}
	}

	Train* getTrain();
};