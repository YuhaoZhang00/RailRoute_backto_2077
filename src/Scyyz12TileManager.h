#pragma once
#include "header.h"
#include "TileManager.h"
class Scyyz12TileManager :
    public TileManager
{
public:
	Scyyz12TileManager(int iTileHeight = 90, int iTileWidth = 90, int iMapWidth = 4, int iMapHeight = 4)
		: TileManager(iTileHeight, iTileWidth, iMapWidth, iMapHeight)
	{}

	virtual void virtDrawTileAt(
		BaseEngine* pEngine,
		DrawingSurface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY) const override;
};

