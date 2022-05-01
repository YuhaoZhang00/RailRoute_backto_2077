#include "header.h"
#include "StartState.h"
#include "ImagePixelMapping.h"
#include "FileHandler.h"

int StartState::virtInitialise(Scyyz12Engine2* pContext)
{
	FileReader fh("resources/level-continue.txt");
	if (fh.readNumber() == -1) m_bIsContinue = false;
	else m_bIsContinue = true;
	return pContext->BaseEngine::virtInitialise();
}

void StartState::virtSetupBackgroundBuffer(Scyyz12Engine2* pContext)
{
	pContext->getForegroundSurface()->setDrawPointsFilter(pContext);

	// background
	pContext->fillBackground(0xffffff);
	m_oTheExtraSurface11->fillSurface(0xffffff);
	m_oTheExtraSurface12->fillSurface(0xffffff);
	m_oTheExtraSurface13->fillSurface(0xffffff);
	m_oTheExtraSurface21->fillSurface(0xffffff);
	m_oTheExtraSurface22->fillSurface(0xffffff);
	m_oTheExtraSurface23->fillSurface(0xffffff);
	m_oTheExtraSurface31->fillSurface(0xffffff);
	m_oTheExtraSurface32->fillSurface(0xffffff);
	m_oTheExtraSurface33->fillSurface(0xffffff);

	// ---------------------------------------------------
	m_oTheExtraSurface11->mySDLLockSurface();
	m_oTheExtraSurface12->mySDLLockSurface();
	m_oTheExtraSurface13->mySDLLockSurface();
	m_oTheExtraSurface21->mySDLLockSurface();
	m_oTheExtraSurface22->mySDLLockSurface();
	m_oTheExtraSurface23->mySDLLockSurface();
	m_oTheExtraSurface31->mySDLLockSurface();
	m_oTheExtraSurface32->mySDLLockSurface();
	m_oTheExtraSurface33->mySDLLockSurface();
	// ---------------------------------------------------

	// TODO : beautify them

	SimpleImage bg1 = ImageManager::loadImage("resources/bg-1-y.png", true);
	bg1.renderImage(m_oTheExtraSurface11, 0, 0, 70, 100, bg1.getWidth(), bg1.getHeight());
	bg1.renderImageWithMaskAndTransparency(m_oTheExtraSurface12, 0, 0, 70, 100, bg1.getWidth(), bg1.getHeight(), -1, 66);
	bg1.renderImageWithMaskAndTransparency(m_oTheExtraSurface13, 0, 0, 70, 100, bg1.getWidth(), bg1.getHeight(), -1, 33);
	SimpleImage bg2 = ImageManager::loadImage("resources/bg-2-y.png", true);
	bg2.renderImage(m_oTheExtraSurface21, 0, 0, 800, 200, bg2.getWidth(), bg2.getHeight());
	bg2.renderImageWithMaskAndTransparency(m_oTheExtraSurface22, 0, 0, 800, 200, bg2.getWidth(), bg2.getHeight(), -1, 66);
	bg2.renderImageWithMaskAndTransparency(m_oTheExtraSurface23, 0, 0, 800, 200, bg2.getWidth(), bg2.getHeight(), -1, 33);
	SimpleImage bg3 = ImageManager::loadImage("resources/bg-3-y.png", true);
	bg3.renderImage(m_oTheExtraSurface31, 0, 0, 20, 400, bg3.getWidth(), bg3.getHeight());
	bg3.renderImageWithMaskAndTransparency(m_oTheExtraSurface32, 0, 0, 20, 400, bg3.getWidth(), bg3.getHeight(), -1, 66);
	bg3.renderImageWithMaskAndTransparency(m_oTheExtraSurface33, 0, 0, 20, 400, bg3.getWidth(), bg3.getHeight(), -1, 33);

	// ---------------------------------------------------
	m_oTheExtraSurface11->mySDLUnlockSurface();
	m_oTheExtraSurface12->mySDLUnlockSurface();
	m_oTheExtraSurface13->mySDLUnlockSurface();
	m_oTheExtraSurface21->mySDLUnlockSurface();
	m_oTheExtraSurface22->mySDLUnlockSurface();
	m_oTheExtraSurface23->mySDLUnlockSurface();
	m_oTheExtraSurface31->mySDLUnlockSurface();
	m_oTheExtraSurface32->mySDLUnlockSurface();
	m_oTheExtraSurface33->mySDLUnlockSurface();
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

	if (!m_bIsContinue) {
		pContext->drawForegroundRectangle(550, 470, 750, 520, 0xeeeeee);
		pContext->drawForegroundString(650 - 65, 475, "Continue", 0xaaaaaa, pContext->getFont("Ubuntu-Medium.ttf", 30));
	}
	else {
		pContext->drawForegroundRectangle(550, 470, 750, 520, 0xF9C74F);
		pContext->drawForegroundString(650 - 65, 475, "Continue", 0xFFFFFF, pContext->getFont("Ubuntu-Medium.ttf", 30));
	}

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
	//printf("## Debug - click at %d %d\n", iX, iY);
	if (iButton == SDL_BUTTON_LEFT)
	{
		if (iX > 550 && iX < 750) {
			if (iY > 400 && iY < 450) {
				pContext->changeState("choose_level");
			}
			else if (iY > 470 && iY < 520 && m_bIsContinue) {
				pContext->changeState("gaming", true, true, 0);
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
	m_iCurrentSurfaceNumber = (++m_iCurrentSurfaceNumber) % 1950;
	if (m_iCurrentSurfaceNumber == 50) pContext->setBackgourndSurface(m_oTheExtraSurface13);
	else if (m_iCurrentSurfaceNumber == 54) pContext->setBackgourndSurface(m_oTheExtraSurface12);
	else if (m_iCurrentSurfaceNumber == 58) pContext->setBackgourndSurface(m_oTheExtraSurface11);
	else if (m_iCurrentSurfaceNumber == 600) pContext->setBackgourndSurface(m_oTheExtraSurface12);
	else if (m_iCurrentSurfaceNumber == 604) pContext->setBackgourndSurface(m_oTheExtraSurface13);
	else if (m_iCurrentSurfaceNumber == 608) pContext->setBackgourndSurface(&(pContext->getTheDefaultBackgroundSurface()));
	else if (m_iCurrentSurfaceNumber == 50 + 650) pContext->setBackgourndSurface(m_oTheExtraSurface23);
	else if (m_iCurrentSurfaceNumber == 54 + 650) pContext->setBackgourndSurface(m_oTheExtraSurface22);
	else if (m_iCurrentSurfaceNumber == 58 + 650) pContext->setBackgourndSurface(m_oTheExtraSurface21);
	else if (m_iCurrentSurfaceNumber == 600 + 650) pContext->setBackgourndSurface(m_oTheExtraSurface22);
	else if (m_iCurrentSurfaceNumber == 604 + 650) pContext->setBackgourndSurface(m_oTheExtraSurface23);
	else if (m_iCurrentSurfaceNumber == 608 + 650) pContext->setBackgourndSurface(&(pContext->getTheDefaultBackgroundSurface()));
	else if (m_iCurrentSurfaceNumber == 50 + 1300) pContext->setBackgourndSurface(m_oTheExtraSurface33);
	else if (m_iCurrentSurfaceNumber == 54 + 1300) pContext->setBackgourndSurface(m_oTheExtraSurface32);
	else if (m_iCurrentSurfaceNumber == 58 + 1300) pContext->setBackgourndSurface(m_oTheExtraSurface31);
	else if (m_iCurrentSurfaceNumber == 600 + 1300) pContext->setBackgourndSurface(m_oTheExtraSurface32);
	else if (m_iCurrentSurfaceNumber == 604 + 1300) pContext->setBackgourndSurface(m_oTheExtraSurface33);
	else if (m_iCurrentSurfaceNumber == 608 + 1300) pContext->setBackgourndSurface(&(pContext->getTheDefaultBackgroundSurface()));
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

	m_oTheExtraSurface11 = new DrawingSurface(pContext);
	m_oTheExtraSurface12 = new DrawingSurface(pContext);
	m_oTheExtraSurface13 = new DrawingSurface(pContext);
	m_oTheExtraSurface21 = new DrawingSurface(pContext);
	m_oTheExtraSurface22 = new DrawingSurface(pContext);
	m_oTheExtraSurface23 = new DrawingSurface(pContext);
	m_oTheExtraSurface31 = new DrawingSurface(pContext);
	m_oTheExtraSurface32 = new DrawingSurface(pContext);
	m_oTheExtraSurface33 = new DrawingSurface(pContext);
	m_oTheExtraSurface11->createSurface(pContext->getWindowWidth(), pContext->getWindowHeight());
	m_oTheExtraSurface12->createSurface(pContext->getWindowWidth(), pContext->getWindowHeight());
	m_oTheExtraSurface13->createSurface(pContext->getWindowWidth(), pContext->getWindowHeight());
	m_oTheExtraSurface21->createSurface(pContext->getWindowWidth(), pContext->getWindowHeight());
	m_oTheExtraSurface22->createSurface(pContext->getWindowWidth(), pContext->getWindowHeight());
	m_oTheExtraSurface23->createSurface(pContext->getWindowWidth(), pContext->getWindowHeight());
	m_oTheExtraSurface31->createSurface(pContext->getWindowWidth(), pContext->getWindowHeight());
	m_oTheExtraSurface32->createSurface(pContext->getWindowWidth(), pContext->getWindowHeight());
	m_oTheExtraSurface33->createSurface(pContext->getWindowWidth(), pContext->getWindowHeight());
}
