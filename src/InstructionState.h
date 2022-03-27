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

	std::vector<StationCollection*> m_stationls; // TODO: delete for such a syntax???

public:
	void virtSetupBackgroundBuffer(Scyyz12Engine2* pContext) override;
	void virtDrawStringsOnTop(Scyyz12Engine2* pContext) override;
	int virtInitialiseObjects(Scyyz12Engine2* pContext) override;
	void virtMouseDown(Scyyz12Engine2* pContext, int iButton, int iX, int iY) override;
};

