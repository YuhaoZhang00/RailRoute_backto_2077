#include "header.h"
#include "Scyyz12TileManager.h"

void Scyyz12TileManager::virtDrawTileAt(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY, int iStartPositionScreenX, int iStartPositionScreenY) const
{
	int iMapValue = getMapValue(iMapX, iMapY);
	unsigned int iColour = (unsigned int)((iMapValue & 0xf00) << 12) // red
		+ (unsigned int)((iMapValue & 0xf0) << 8) // green
		+ (unsigned int)((iMapValue & 0xf) << 4); // blue

	pSurface->drawRectangle(
		iStartPositionScreenX,
		iStartPositionScreenY,
		iStartPositionScreenX + getTileWidth() - 1,
		iStartPositionScreenY + getTileHeight() - 1,
		NULL);

	switch (iMapValue % 5) {
	case 0:
		pSurface->drawOval(
			iStartPositionScreenX,
			iStartPositionScreenY,
			iStartPositionScreenX + getTileWidth() - 1,
			iStartPositionScreenY + getTileHeight() - 1,
			iColour);
		break;
	case 1:
		pSurface->drawTriangle(
			iStartPositionScreenX + getTileWidth() / 2, iStartPositionScreenY,
			iStartPositionScreenX + getTileWidth() - 1, iStartPositionScreenY + getTileHeight() - 1,
			iStartPositionScreenX, iStartPositionScreenY + getTileHeight() - 1,
			iColour);
		break;
	case 2:
		pSurface->drawTriangle(
			iStartPositionScreenX + getTileWidth() / 2, iStartPositionScreenY + getTileHeight() - 1,
			iStartPositionScreenX + getTileWidth() - 1, iStartPositionScreenY,
			iStartPositionScreenX, iStartPositionScreenY,
			iColour);
		break;
	case 3:
		pSurface->drawRectangle(
			iStartPositionScreenX,
			iStartPositionScreenY,
			iStartPositionScreenX + getTileWidth() - 1,
			iStartPositionScreenY + getTileHeight() - 1,
			iColour);
		break;
	case 4:
		pSurface->drawPolygon(6,
			new double[] {double(iStartPositionScreenX) + getTileWidth() / 4, double(iStartPositionScreenX) + getTileWidth() * 3 / 4,
			double(iStartPositionScreenX) + getTileWidth(), double(iStartPositionScreenX) + getTileWidth() * 3 / 4,
			double(iStartPositionScreenX) + getTileWidth() / 4, double(iStartPositionScreenX)},
			new double[] {double(iStartPositionScreenY) + getTileWidth() * 0.3 / 4, double(iStartPositionScreenY) + getTileWidth() * 0.3 / 4,
			double(iStartPositionScreenY) + getTileWidth() / 2, double(iStartPositionScreenY) + getTileWidth() * 3.7 / 4,
			double(iStartPositionScreenY) + getTileWidth() * 3.7 / 4, double(iStartPositionScreenY) + getTileWidth() / 2},
			iColour);
		break;
	}
}
