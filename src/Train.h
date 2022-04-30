#pragma once
#include "header.h"
#include "DisplayableObject.h"
#include "Passenger.h"
#include "Constant.h"
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

	double m_dXExactPos;
	double m_dYExactPos;
	double m_dSpeed;
	short m_sDirection;
	bool m_bIsRun = true;

	int m_iPassengerCount = 0;
	std::vector<PassengerCollection*> m_vecPassenger;
	std::vector<int> m_vecPassengerPos;

	void drawForegroundRectangle0();
	void drawForegroundRectangle90();
	void drawForegroundRectangle45();
	void drawForegroundRectangle135();
	void drawPassenger();

public:
	Carriage(BaseEngine* pEngine, double dXCenter, double dYCenter, unsigned int uiColor,
		double dSpeed, short sDirection, int iMaxNumOfPassengers = 6, int iWidth = 20, int iLength = 30)
		: DisplayableObject(dXCenter, dYCenter, pEngine, iWidth, iLength, false), m_dXExactPos(dXCenter), m_dYExactPos(dYCenter),
		m_uiPassengerColor(0), m_uiColor(uiColor), m_iMaxNumOfPassengers(iMaxNumOfPassengers), m_iWidth(iWidth), m_iLength(iLength),
		m_dSpeed(dSpeed), m_sDirection(sDirection)
	{
		int iR = (0xff & (uiColor >> 16)) * 50 + (0xff & (0xFFFFFF >> 16)) * 50;
		int iG = (0xff & (uiColor >> 8)) * 50 + (0xff & (0xFFFFFF >> 8)) * 50;
		int iB = (0xff & uiColor) * 50 + (0xff & 0xFFFFFF) * 50;
		m_uiPassengerColor = (((iR / 100) & 0xff) << 16) | (((iG / 100) & 0xff) << 8) | ((iB / 100) & 0xff);

		m_vecPassenger.resize(iMaxNumOfPassengers, nullptr);
		setPassengerPosition();
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
	void virtDoUpdate(int iCurrentTime) override;

	int getLength();
	int getMaxNumOfPassengers();

	// please check isFull() before ading passenger to carriage
	void addPassenger(PassengerCollection* oPassenger);
	// returns the index of the first passenger of given type; return -1 if not found
	int findFirstPassengerByType(short sType);
	std::vector<int> findPassengerByType(short sType);
	void removePassenger(int iIndex);
	bool isFull();
	void setPassengerPosition();

	double getXExactPos();
	double getYExactPos();
	void setExactPos(double dX, double dY);
	double getSpeed();
	short getDirection();
	void setDirection(short sDirection);
	void setIsRun(bool bIsRun);
	bool getIsRun();

	std::vector<PassengerCollection*> getPassengerList();
	void setPassengerList(std::vector<PassengerCollection*> p, int i);
	void setSpeed(int i) {
		m_dSpeed = i;
	}
	int getPassengerColor() {
		return m_uiPassengerColor;
	}
	int getPassengerCount() {
		return m_iPassengerCount;
	}
	int getMaxNumberOfPassengers() {
		return m_iMaxNumOfPassengers;
	}
};

class CarriageHead :
	public Carriage
{
public:
	CarriageHead(BaseEngine* pEngine, double dXCenter, double dYCenter, unsigned int uiColor,
		double dSpeed = 1, short sDirection = 0, int iMaxNumOfPassengers = 6, int iWidth = 20, int iLength = 30)
		: Carriage(pEngine, dXCenter, dYCenter, uiColor, dSpeed, sDirection, iMaxNumOfPassengers, iWidth, iLength)
	{}

	void virtDraw() override;
};

class CarriageMain :
	public Carriage
{
public:
	CarriageMain(BaseEngine* pEngine, double dXCenter, double dYCenter, unsigned int uiColor,
		double dSpeed = 1, short sDirection = 0, int iMaxNumOfPassengers = 6, int iWidth = 20, int iLength = 30)
		: Carriage(pEngine, dXCenter, dYCenter, uiColor, dSpeed, sDirection, iMaxNumOfPassengers, iWidth, iLength)
	{}

	void virtDraw() override;
};

class CarriageHeadFast :
	public Carriage
{
public:
	CarriageHeadFast(BaseEngine* pEngine, double dXCenter, double dYCenter, unsigned int uiColor,
		double dSpeed = 2, short sDirection = 0, int iMaxNumOfPassengers = 4, int iWidth = 20, int iLength = 20)
		: Carriage(pEngine, dXCenter, dYCenter, uiColor, dSpeed, sDirection, iMaxNumOfPassengers, iWidth, iLength)
	{}

	void virtDraw() override;
};

class CarriageHeadIntelli :
	public Carriage
{
private:
	unsigned int m_uiSpecialColor;

public:
	CarriageHeadIntelli(BaseEngine* pEngine, double dXCenter, double dYCenter, unsigned int uiColor = 0xFFD700, unsigned int uiSpecialColor = 0xCD9B1D,
		double dSpeed = 1, short sDirection = 0, int iMaxNumOfPassengers = 8, int iWidth = 20, int iLength = 40)
		: Carriage(pEngine, dXCenter, dYCenter, uiColor, dSpeed, sDirection, iMaxNumOfPassengers, iWidth, iLength), m_uiSpecialColor(uiSpecialColor)
	{}

	void virtDraw() override;
};

class CarriageCollection {
private:
	Carriage* m_oCarriage;
	int iType = 0;

	int m_cooldown = 3;

public:
	/* sType - a short number between [0,3] for different type or carriage
	* 0 - head  1 - fast head  2 - intelligent head  3 - main
	* `uiBorderColor` is only useful for type 2 carriage
	* set `iMaxNumOfPassengers` and `iLength` (i.e. default setting) will generate default train
	* sDirection - a short number between [0,7] for different direction of movement
	*  7  0  1
	*  6     2
	*  5  4  3
	*/
	CarriageCollection(short sType, BaseEngine* pEngine, double dXCenter, double dYCenter, unsigned int uiColor,
		double dSpeed = -1, short sDirection = 0, unsigned int uiSpecialColor = 0xCD9B1D,
		int iMaxNumOfPassengers = -1, int iWidth = 20, int iLength = -1)
		: m_oCarriage(NULL)
	{
		switch (sType) {
		case 0:
			iType = 0;
			m_oCarriage = new CarriageHead(pEngine, dXCenter, dYCenter, uiColor, (dSpeed == -1) ? 1 : dSpeed, sDirection,
				(iMaxNumOfPassengers == -1) ? 6 : iMaxNumOfPassengers, iWidth, (iLength == -1) ? 30 : iLength);
			break;
		case 1:
			iType = 1;
			m_oCarriage = new CarriageHeadFast(pEngine, dXCenter, dYCenter, uiColor, (dSpeed == -1) ? 2 : dSpeed, sDirection,
				(iMaxNumOfPassengers == -1) ? 4 : iMaxNumOfPassengers, iWidth, (iLength == -1) ? 20 : iLength);
			break;
		case 2:
			iType = 2;
			m_oCarriage = new CarriageHeadIntelli(pEngine, dXCenter, dYCenter, uiColor, uiSpecialColor, (dSpeed == -1) ? 1 : dSpeed, sDirection,
				(iMaxNumOfPassengers == -1) ? 8 : iMaxNumOfPassengers, iWidth, (iLength == -1) ? 40 : iLength);
			break;
		case 3:
			iType = 3;
			m_oCarriage = new CarriageMain(pEngine, dXCenter, dYCenter, uiColor, dSpeed, sDirection,
				(iMaxNumOfPassengers == -1) ? 6 : iMaxNumOfPassengers, iWidth, (iLength == -1) ? 30 : iLength);
			break;
		default:
			printf("!! Error @ Train.h CarriageCollection Constructor - invalid sIndex\n");
			break;
		}
		m_oCarriage->setShouldDeleteOnRemoval(false);
	}

	~CarriageCollection() {
		delete m_oCarriage;
	}

	Carriage* getCarriage();

	void resetCooldown();
	bool isCooldown();

	int getType() {
		return iType;
	}
};


class Train
{
protected:
	BaseEngine* m_pEngine;
	double m_dXCenterHead;
	double m_dYCenterHead;
	unsigned int m_uiColor;
	int m_iDist;

	double m_dSpeed;
	short m_sDirection;
	bool m_bIsRun = true;

	int m_iCarriageCount = 0;
	std::vector<CarriageCollection*> m_vecCarriage;

	int m_iPassengerCount = 0;
	int m_iMaxNumOfPassengers = 0;

public:
	Train(BaseEngine* pEngine, double dXCenterHead, double dYCenterHead, double dSpeed, short sDirection, unsigned int uiColor, int iDist = 5)
		: m_pEngine(pEngine), m_dXCenterHead(dXCenterHead), m_dYCenterHead(dYCenterHead), m_uiColor(uiColor), m_iDist(iDist),
		m_dSpeed(dSpeed), m_sDirection(sDirection)
	{}

	~Train() {
		for (int i = 0; i < m_iCarriageCount; i++) {
			delete m_vecCarriage[i];
		}
	}

	//virtual void virtDraw() override = 0;
	//virtual void virtDoUpdate(int iCurrentTime) override = 0;

	virtual void addHead(int iMaxNumberOfPassengers = -1, int iLength = -1) = 0;
	// returns false if already reaches max number of carriages and the current carriage not added
	bool addCarriage(int iMaxNumberOfPassengers = -1, int iLength = -1);
	void removeCarriageAfterN(int iIndex);
	std::vector<CarriageCollection*> getCarriageList();
	// please check isFull() before ading passenger to train
	void addPassenger(PassengerCollection* oPassenger);
	// returns the index of the first passenger of given type; return -1 if not found
	int findFirstPassengerByType(short sType);
	std::vector<int> findPassengerByType(short sType);
	void removePassenger(int iIndex);
	bool isFull();

	bool getIsRun();
	void startTrain();
	void stopTrain();

	int getXCenter() {
		return m_dXCenterHead;
	}
	int getYCenter() {
		return m_dYCenterHead;
	}
	int getColor() {
		return m_uiColor;
	}
	void addCarriage(CarriageCollection* c) {
		m_vecCarriage.emplace_back(c);
		m_iCarriageCount++;
	}
	int getDirection() {
		return m_sDirection;
	}
	void setDirection(short d) {
		m_sDirection = d;
	}
	void recalculatePassengerCount() {
		for (CarriageCollection* c : m_vecCarriage) {
			m_iPassengerCount += c->getCarriage()->getPassengerCount();
		}
		for (CarriageCollection* c : m_vecCarriage) {
			m_iMaxNumOfPassengers += c->getCarriage()->getMaxNumberOfPassengers();
		}
	}
};

class TrainNormal :
	public Train
{
public:
	TrainNormal(BaseEngine* pEngine, double dXCenterHead, double dYCenterHead, double dSpeed, short sDirection, unsigned int uiColor, int iDist = 5)
		: Train(pEngine, dXCenterHead, dYCenterHead, dSpeed, sDirection, uiColor, iDist)
	{}

	void addHead(int iMaxNumberOfPassengers = -1, int iLength = -1) override;
};

class TrainFast :
	public Train
{
public:
	TrainFast(BaseEngine* pEngine, double dXCenterHead, double dYCenterHead, double dSpeed, short sDirection, unsigned int uiColor, int iDist = 5)
		: Train(pEngine, dXCenterHead, dYCenterHead, dSpeed, sDirection, uiColor, iDist)
	{}

	void addHead(int iMaxNumberOfPassengers = -1, int iLength = -1) override;
};

class TrainIntelli :
	public Train
{
private:
	unsigned int m_uiSpecialColor;

public:
	TrainIntelli(BaseEngine* pEngine, double dXCenterHead, double dYCenterHead, double dSpeed, short sDirection,
		unsigned int uiColor, int iDist = 5, unsigned int uiSpecialColor = 0xCD9B1D)
		: Train(pEngine, dXCenterHead, dYCenterHead, dSpeed, sDirection, uiColor, iDist), m_uiSpecialColor(uiSpecialColor)
	{}

	void addHead(int iMaxNumberOfPassengers = -1, int iLength = -1) override;
};

class TrainCollection
{
private:
	int m_id;
	int m_type;
	Train* m_oTrain;

	int m_StopCooldown = 0;
	int m_cooldown = 3;

public:
	/* sType - a short number between [0,2] for different type of train
	* 0 - normal train  1 - fast train  2 - intelligent train
	* `uiBorderColor` is only useful for type 2 train
	*/
	TrainCollection(int id, short sType, BaseEngine* pEngine, double dXCenterHead, double dYCenterHead, unsigned int uiColor,
		double dSpeed = -1, short sDirection = 0, int iDist = 5, unsigned int uiSpecialColor = 0xCD9B1D)
		: m_id(id), m_oTrain(NULL), m_type(0)
	{
		switch (sType) {
		case 0:
			m_type = 0;
			m_oTrain = new TrainNormal(pEngine, dXCenterHead, dYCenterHead, (dSpeed == -1) ? 1 : dSpeed, sDirection, uiColor, iDist);
			break;
		case 1:
			m_type = 1;
			m_oTrain = new TrainFast(pEngine, dXCenterHead, dYCenterHead, (dSpeed == -1) ? 2 : dSpeed, sDirection, uiColor, iDist);
			break;
		case 2:
			m_type = 2;
			m_oTrain = new TrainIntelli(pEngine, dXCenterHead, dYCenterHead, (dSpeed == -1) ? 1 : dSpeed, sDirection, uiColor, iDist, uiSpecialColor);
			break;
		default:
			printf("!! Error @ Train.h TrainCollection Constructor - invalid sIndex\n");
			break;
		}
	}

	~TrainCollection() {
		delete m_oTrain;
	}

	Train* getTrain();
	int getType();
	int getId();
	void setId(int id);
	void resetStopCooldown();
	bool isStopCooldown();
	void resetCooldown();
	bool isCooldown();
};