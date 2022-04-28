#pragma once
#include "header.h"
#include <unordered_map>
#include "BaseEngine.h"
#include "State.h"

class State;

class Scyyz12Engine2
	: public BaseEngine
{
private:
	// the current state (page)
	State* m_pState;
	// a map of states with their corresponding name
	std::unordered_map<std::string, State*> m_mAllState;

public:
	Scyyz12Engine2(State* pState, std::unordered_map<std::string, State*> mAllState)
		: m_pState(pState), m_mAllState(mAllState)
	{}

	// gets the current state
	State* getState(); // not used
	// changes to the state of given string, if fail changes to start state
	void changeState(std::string strState);

	void setBackgourndSurface(DrawingSurface* pBackgroundSurface);
	DrawingSurface& getTheDefaultBackgroundSurface();

	int virtInitialise() override;
	void virtSetupBackgroundBuffer() override;
	void virtDrawStringsOnTop() override;
	int virtInitialiseObjects() override;
	void virtMouseDown(int iButton, int iX, int iY) override;
	void virtMouseWheel(int x, int y, int which, int timestamp) override;
	void virtMainLoopDoBeforeUpdate() override;
	void copyAllBackgroundBuffer() override;
	void virtKeyDown(int iKeyCode) override;
	void virtCreateSurfaces() override;
	void virtMouseMoved(int iX, int iY) override;
};

