#include "header.h"

#include <ctime>

// Needs one of the following #includes, to include the class definition
#include "SimpleDemo.h"
#include "BouncingBallMain.h"
#include "MazeDemoMain.h"

#include "FlashingDemo.h"
#include "StarfieldDemo.h"
#include "ImageMappingDemo.h"
#include "ZoomingDemo.h"
#include "DraggingDemo.h"

#include "MyDemoA.h"
#include "Scyyz12Engine.h"
#include "Scyyz12Engine2.h"

#include "ChooseLevelState.h"
#include "GameOverState.h"
#include "GameState.h"
#include "HighScoreState.h"
#include "InstructionState.h"
#include "StartState.h"
#include "PauseState.h"

// These are passed to initialise to determine the window size
const int BaseScreenWidth = 1300;
const int BaseScreenHeight = 800;


// This was only moved outside of main so that I can do some memory checking once it ends.
// Main calls this then checks for errors before ending.
int doProgram(int argc, char* argv[])
{
	int iResult = 0;

	//MyDemoA oMainDemoObject;
	//Scyyz12Engine oMainDemoObject;

	State* chooseLevelState = new ChooseLevelState();
	State* gameOverState = new GameOverState();
	State* gameState = new GameState();
	State* highScoreState = new HighScoreState();
	State* instructionState = new InstructionState();
	State* startState = new StartState();
	State* pauseState = new PauseState();
	std::unordered_map<std::string, State*> states;
	states.emplace("choose_level", chooseLevelState);
	states.emplace("game_over", gameOverState);
	states.emplace("gaming", gameState);
	states.emplace("high_score", highScoreState);
	states.emplace("instruction", instructionState);
	states.emplace("start", startState);
	states.emplace("pause", pauseState);
	Scyyz12Engine2 oMainDemoObject(startState, states);

	// Uncomment only ONE of the following lines - to choose which object to create - ENSURE ONLY ONE IS CREATED.
	//SimpleDemo oMainDemoObject;
	//BouncingBallMain oMainDemoObject;
	//MazeDemoMain oMainDemoObject;

	// Advanced demos showing one or more facilities...
	//FlashingDemo oMainDemoObject;
	//StarfieldDemo oMainDemoObject;
	//ImageMappingDemo oMainDemoObject;
	//ZoomingDemo oMainDemoObject;
	//DraggingDemo oMainDemoObject;

	// More advanced demos... see folders... not imported yet

	char buf[1024];
	// Screen caption can be set on following line...
	sprintf(buf, "C++ Coursework Framework Program : Size %d x %d", BaseScreenWidth, BaseScreenHeight);
	iResult = oMainDemoObject.initialise(buf, BaseScreenWidth, BaseScreenHeight, "Cornerstone Regular.ttf", 24);

	iResult = oMainDemoObject.mainLoop();
	oMainDemoObject.deinitialise();

	delete chooseLevelState;
	delete gameOverState;
	delete gameState;
	delete highScoreState;
	delete instructionState;
	delete startState;
	delete pauseState;

	return iResult;
} // Main object (created on the stack) gets destroyed at this point, so it will free its memory





/* Separate main function, so we can check for memory leaks after objects are destroyed */
int main(int argc, char* argv[])
{
	// Send random number generator with current time
	::srand((unsigned int)time(0));

	int iResult = doProgram(argc, argv);

	// Free the cached images by destroying the image manager
	// Ensure that you do this AFTER the main object and any other objects have been destroyed
	// The game object is a stack object inside doProgram() so will have been 
	ImageManager::destroyImageManager();

	// Uncomment the following line to introduce a memory leak!
	// new int();
	// _CrtDumpMemoryLeaks() should make Visual studio tell you about memory leaks when it ends. 
	/* e.g.:
	Detected memory leaks!
		Dumping objects ->
	{189} normal block at 0x0358C828, 4 bytes long.
		Data: < > 00 00 00 00
		Object dump complete.
	*/

	// Detect memory leaks on windows if building for debug (not release!)
#if defined(_MSC_VER)
#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif
#endif

	return iResult;
}
