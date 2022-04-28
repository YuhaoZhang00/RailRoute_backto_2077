#pragma once
#include "header.h"
#include "State.h"
#include "Rail.h"
#include "Station.h"
#include "Passenger.h"
#include "Train.h"
#include "LineRoute.h"
#include "StationMap.h"

class InstructionState :
	public State
{
private:
	StationMap* m_sm1;
	LineRoute* m_lr1;

public:
	InstructionState()
		: m_lr1(nullptr), m_sm1(nullptr)
	{}

	~InstructionState() {
		delete m_sm1;
		delete m_lr1;
	}

	int virtInitialise(Scyyz12Engine2* pContext) override;
	void virtSetupBackgroundBuffer(Scyyz12Engine2* pContext) override;
	void virtDrawStringsOnTop(Scyyz12Engine2* pContext) override;
	int virtInitialiseObjects(Scyyz12Engine2* pContext) override;
	void virtMouseMoved(Scyyz12Engine2* pContext, int iX, int iY) override;
	void virtMouseDown(Scyyz12Engine2* pContext, int iButton, int iX, int iY) override;
	void virtMouseWheel(Scyyz12Engine2* pContext, int x, int y, int which, int timestamp) override;
	void virtMainLoopDoBeforeUpdate(Scyyz12Engine2* pContext) override;
	void copyAllBackgroundBuffer(Scyyz12Engine2* pContext) override;
	void virtKeyDown(Scyyz12Engine2* pContext, int iKeyCode) override;
	void virtCreateSurfaces(Scyyz12Engine2* pContext) override;
};

