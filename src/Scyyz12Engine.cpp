#include "header.h"

#include "Scyyz12Engine.h"
#include "Part1Object.h"

void Scyyz12Engine::virtSetupBackgroundBuffer()
{
	fillBackground(0x000000);

	for (int iX = 0; iX < getWindowWidth(); iX++)
		for (int iY = 0; iY < getWindowHeight(); iY++)
			setBackgroundPixel(iX, iY, iX/6%256 | 0x888800);

	drawBackgroundPolygon(100,100, 200,100, 250,186, 200,272, 100,272, 50,186, 0x0000dd);

	SimpleImage image = ImageManager::loadImage("resources/sign.png", true);
	image.renderImage(getBackgroundSurface(), 0,0, 50,300, image.getWidth(), image.getHeight());

	drawBackgroundString(50,500, "COMP2006 Coursework Part 1 By Yuhao (background)", 0x0000dd, getFont("Cornerstone Regular.ttf", 28));
	drawBackgroundString(50,540, "[up/down/left/right] - change speed of the ball, [space] - stop the ball", 0x0000dd, getFont("Cornerstone Regular.ttf", 18));
	drawBackgroundString(50,560, "[mouse click (left button)] - reset position of the ball", 0x0000dd, getFont("Cornerstone Regular.ttf", 18));

	for (int i = 0; i < tm.getMapHeight(); i++)
		for (int j = 0; j < tm.getMapWidth(); j++)
			tm.setMapValue(i, j, rand());
	tm.setTopLeftPositionOnScreen(800, 100);
	tm.drawAllTiles(this, getBackgroundSurface());
}

void Scyyz12Engine::virtDrawStringsOnTop()
{
	char buf[128];
	sprintf(buf, "Incrememt per 1000 ticks: %d (foreground & before moving object)", getModifiedTime() / 1000);
	drawForegroundString(50,600, buf, 0xffffff, getFont("Cornerstone Regular.ttf", 28));
	sprintf(buf, "Green ball speed: x - %.2f ; y - %.2f", m_oBall->getSpeedX(), m_oBall->getSpeedY());
	drawForegroundString(50,660, buf, 0xffffff, getFont("Cornerstone Regular.ttf", 18));
	if (m_oSquare->getDirection()) {
		drawForegroundString(50, 640, "Yellow ball direction: x", 0xffffff, getFont("Cornerstone Regular.ttf", 18));
	}
	else {
		drawForegroundString(50, 640, "Yellow ball direction: y", 0xffffff, getFont("Cornerstone Regular.ttf", 18));
	}
	
}

int Scyyz12Engine::virtInitialiseObjects()
{
	drawableObjectsChanged();
	destroyOldObjects(true);
	createObjectArray(1);
	m_oBall = new Part1Object(this, &tm);
	storeObjectInArray(0, m_oBall);
	m_oSquare = new Part1Object2(this, 150);
	appendObjectToArray(m_oSquare);
	return 0;
}

void Scyyz12Engine::virtMouseDown(int iButton, int iX, int iY)
{
	printf("click at %d %d\n", iX, iY);
	if (iButton == SDL_BUTTON_LEFT)
	{
		m_oBall->setPosition(iX, iY);
	}
}
