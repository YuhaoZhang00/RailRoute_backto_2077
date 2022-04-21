#pragma once
#include "header.h"
#include "State.h"
#include "Rail.h"
#include "Station.h"
#include "Passenger.h"
#include "Train.h"

class InstructionState :
    public State
{
private:
	RailLine* m_line1;
	RailLineDiagonal* m_line2;
	//RailLine* m_line3_1;
	//RailLineDiagonal* m_line3_2;
	//RailLineDiagonal* m_line4_1;
	//RailLineDiagonal* m_line4_2;
	//RailLink90Diagonal* m_linelink4;

	std::vector<StationCollection*> m_vecStations;

	TrainCollection* m_train1;

public:
	InstructionState()
		: m_line1(nullptr), m_line2(nullptr), m_train1(nullptr)
	{}

	~InstructionState() {
		for (StationCollection* station : m_vecStations) {
			delete station;
		}
		delete m_train1;
	}

	int virtInitialise(Scyyz12Engine2* pContext) override;
	void virtSetupBackgroundBuffer(Scyyz12Engine2* pContext) override;
	void virtDrawStringsOnTop(Scyyz12Engine2* pContext) override;
	int virtInitialiseObjects(Scyyz12Engine2* pContext) override;
	void virtMouseDown(Scyyz12Engine2* pContext, int iButton, int iX, int iY) override;
	void virtMainLoopDoBeforeUpdate(Scyyz12Engine2* pContext) override;
	void copyAllBackgroundBuffer(Scyyz12Engine2* pContext) override;
	void virtKeyDown(Scyyz12Engine2* pContext, int iKeyCode) override;
};

