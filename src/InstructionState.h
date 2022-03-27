#pragma once
#include "header.h"
#include "State.h"
#include "Rail.h"
#include "Station.h"

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

	StationCollection* m_station1;
	//StationCollection* m_station2;
	//StationCollection* m_station3;
	StationCollection* m_station4;
	//StationCollection* m_station5;
	//StationCollection* m_station6;

public:
	void virtSetupBackgroundBuffer(Scyyz12Engine2* pContext) override;
	void virtDrawStringsOnTop(Scyyz12Engine2* pContext) override;
	int virtInitialiseObjects(Scyyz12Engine2* pContext) override;
	void virtMouseDown(Scyyz12Engine2* pContext, int iButton, int iX, int iY) override;
};

