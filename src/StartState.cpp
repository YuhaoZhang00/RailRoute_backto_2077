#include "header.h"
#include "StartState.h"
#include "ImagePixelMapping.h"

int StartState::virtInitialise(Scyyz12Engine2* pContext)
{
	return pContext->BaseEngine::virtInitialise();
}

void StartState::virtSetupBackgroundBuffer(Scyyz12Engine2* pContext)
{
	pContext->getForegroundSurface()->setDrawPointsFilter(pContext);

	// background
	pContext->fillBackground(0xffffff);
	m_oTheExtraSurface1->fillSurface(0xffffff);
	m_oTheExtraSurface2->fillSurface(0xffffff);
	m_oTheExtraSurface3->fillSurface(0xffffff);
	m_oTheExtraSurface4->fillSurface(0xffffff);
	m_oTheExtraSurface5->fillSurface(0xffffff);

	// ---------------------------------------------------
	m_oTheExtraSurface1->mySDLLockSurface();
	m_oTheExtraSurface2->mySDLLockSurface();
	m_oTheExtraSurface3->mySDLLockSurface();
	m_oTheExtraSurface4->mySDLLockSurface();
	m_oTheExtraSurface5->mySDLLockSurface();
	// ---------------------------------------------------

	// TODO : beautify them

	pContext->drawBackgroundRectangle(200, 200, 300, 400, 0x404040);
	m_oTheExtraSurface1->drawOval(100, 100, 200, 200, 0x400000);
	m_oTheExtraSurface2->drawOval(100, 100, 200, 200, 0x004000);
	m_oTheExtraSurface3->drawOval(100, 100, 200, 200, 0x000040);
	m_oTheExtraSurface4->drawOval(100, 100, 200, 200, 0x004040);
	m_oTheExtraSurface5->drawOval(100, 100, 200, 200, 0x400040);

	//SimpleImage background = ImageManager::loadImage("resources/bg-route-1300-800.png", true);
	//background.renderImageWithMaskAndTransparency(pContext->getBackgroundSurface(), 0, 0, 0, 0, background.getWidth(), background.getHeight(), 0xffffff, 30);

	// ---------------------------------------------------
	m_oTheExtraSurface1->mySDLUnlockSurface();
	m_oTheExtraSurface2->mySDLUnlockSurface();
	m_oTheExtraSurface3->mySDLUnlockSurface();
	m_oTheExtraSurface4->mySDLUnlockSurface();
	m_oTheExtraSurface5->mySDLUnlockSurface();
	// ---------------------------------------------------
}

void StartState::virtDrawStringsOnTop(Scyyz12Engine2* pContext)
{
	// title
	SimpleImage title = ImageManager::loadImage("resources/title-ver1-800-235.png", true);
	//title.renderImageWithMaskAndTransparency(pContext->getBackgroundSurface(), 0, 0, 250, 80, title.getWidth(), title.getHeight(), 0xffffff, 90);
	title.renderImageBlit(pContext, pContext->getForegroundSurface(),
		450, 100, 400, 117,
		0, 0, title.getWidth(), title.getHeight());


	//arrows before btns
	SimpleImage image2 = ImageManager::loadImage("resources/arrow-right-50-50.png", true);
	image2.renderImageWithMask(pContext->getForegroundSurface(), 0, 0, 480, 400, image2.getWidth(), image2.getHeight());

	ImagePixelMappingRotateAndColour mapping2(0, image2.getWidth() / 2, image2.getHeight() / 2);
	mapping2.setTransparencyColour(0xffffff);
	//image2.renderImageApplyingMapping(pContext, pContext->getBackgroundSurface(), 480, 400, image2.getWidth(), image2.getHeight(), &mapping2);

	mapping2.setRotation(M_PI / 4);
	image2.renderImageApplyingMapping(pContext, pContext->getForegroundSurface(), 480, 470, image2.getWidth(), image2.getHeight(), &mapping2);

	mapping2.setRotation(M_PI * 3 / 2);
	image2.renderImageApplyingMapping(pContext, pContext->getForegroundSurface(), 480, 540, image2.getWidth(), image2.getHeight(), &mapping2);

	mapping2.setRotation(M_PI * 7 / 4);
	image2.renderImageApplyingMapping(pContext, pContext->getForegroundSurface(), 480, 610, image2.getWidth(), image2.getHeight(), &mapping2);

	mapping2.setRotation(M_PI);
	image2.renderImageApplyingMapping(pContext, pContext->getForegroundSurface(), 480, 680, image2.getWidth(), image2.getHeight(), &mapping2);


	// buttons
	pContext->drawForegroundRectangle(550, 400, 750, 450, 0xF94144);
	pContext->drawForegroundString(650 - 72, 405, "New Game", 0xFFFFFF, pContext->getFont("Ubuntu-Medium.ttf", 30));

	pContext->drawForegroundRectangle(550, 470, 750, 520, 0xF9C74F);
	pContext->drawForegroundString(650 - 65, 475, "Continue", 0xFFFFFF, pContext->getFont("Ubuntu-Medium.ttf", 30));

	pContext->drawForegroundRectangle(550, 540, 750, 590, 0x4361EE);
	pContext->drawForegroundString(650 - 85, 545, "How to Play", 0xFFFFFF, pContext->getFont("Ubuntu-Medium.ttf", 30));

	pContext->drawForegroundRectangle(550, 610, 750, 660, 0xF19C79);
	pContext->drawForegroundString(650 - 75, 615, "High Score", 0xFFFFFF, pContext->getFont("Ubuntu-Medium.ttf", 30));

	pContext->drawForegroundRectangle(550, 680, 750, 730, 0x52B69A);
	pContext->drawForegroundString(650 - 28, 685, "Exit", 0xFFFFFF, pContext->getFont("Ubuntu-Medium.ttf", 30));
}

int StartState::virtInitialiseObjects(Scyyz12Engine2* pContext)
{
	return pContext->BaseEngine::virtInitialiseObjects();
}

void StartState::virtMouseMoved(Scyyz12Engine2* pContext, int iX, int iY)
{
	pContext->BaseEngine::virtMouseMoved(iX, iY);
}

void StartState::virtMouseDown(Scyyz12Engine2* pContext, int iButton, int iX, int iY)
{
	printf("## Debug - click at %d %d\n", iX, iY);
	if (iButton == SDL_BUTTON_LEFT)
	{
		if (iX > 550 && iX < 750) {
			if (iY > 400 && iY < 450) {
				pContext->changeState("choose_level");
			}
			else if (iY > 470 && iY < 520) {
				pContext->changeState("gaming");
			}
			else if (iY > 540 && iY < 590) {
				pContext->changeState("instruction");
			}
			else if (iY > 610 && iY < 660) {
				pContext->changeState("high_score");
			}
			else if (iY > 680 && iY < 730) {
				pContext->setExitWithCode(0);
			}
		}
	}
}

void StartState::virtMouseWheel(Scyyz12Engine2* pContext, int x, int y, int which, int timestamp)
{
	pContext->BaseEngine::virtMouseWheel(x, y, which, timestamp);
}

void StartState::virtMainLoopDoBeforeUpdate(Scyyz12Engine2* pContext)
{
	m_iCurrentSurfaceNumber = (m_iCurrentSurfaceNumber + 1) % 600;
	switch (m_iCurrentSurfaceNumber / 100)
	{
	case 0: pContext->setBackgourndSurface(&(pContext->getTheDefaultBackgroundSurface())); break;
	case 1: pContext->setBackgourndSurface(m_oTheExtraSurface1); break;
	case 2: pContext->setBackgourndSurface(m_oTheExtraSurface2); break;
	case 3: pContext->setBackgourndSurface(m_oTheExtraSurface3); break;
	case 4: pContext->setBackgourndSurface(m_oTheExtraSurface4); break;
	case 5: pContext->setBackgourndSurface(m_oTheExtraSurface5); break;
	}
	pContext->redrawDisplay();
}

void StartState::copyAllBackgroundBuffer(Scyyz12Engine2* pContext)
{
	pContext->BaseEngine::copyAllBackgroundBuffer();
}

void StartState::virtKeyDown(Scyyz12Engine2* pContext, int iKeyCode)
{
	pContext->BaseEngine::virtKeyDown(iKeyCode);
}

void StartState::virtCreateSurfaces(Scyyz12Engine2* pContext)
{
	pContext->BaseEngine::virtCreateSurfaces();

	m_oTheExtraSurface1 = new DrawingSurface(pContext);
	m_oTheExtraSurface2 = new DrawingSurface(pContext);
	m_oTheExtraSurface3 = new DrawingSurface(pContext);
	m_oTheExtraSurface4 = new DrawingSurface(pContext);
	m_oTheExtraSurface5 = new DrawingSurface(pContext);
	m_oTheExtraSurface1->createSurface(pContext->getWindowWidth(), pContext->getWindowHeight());
	m_oTheExtraSurface2->createSurface(pContext->getWindowWidth(), pContext->getWindowHeight());
	m_oTheExtraSurface3->createSurface(pContext->getWindowWidth(), pContext->getWindowHeight());
	m_oTheExtraSurface4->createSurface(pContext->getWindowWidth(), pContext->getWindowHeight());
	m_oTheExtraSurface5->createSurface(pContext->getWindowWidth(), pContext->getWindowHeight());
}
