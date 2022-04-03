#pragma once
#include "header.h"
#include "TileManager.h"

/* Map Tile2Type
* -6 : Carriage
* -5 : NormalTrain
* -4 : FastTrain
* -3 : IntelliTrain
* -2 : Tunnel
* -1 : Bridge
* 0~ : vecLineColors[i]
*
* for properties (i.e. Tile2Type value < 0), MapValue is the number of that property
* for lines (i.e. Tile2Type value >= 0), Map Value 0 : undiscovered; 1 : discovered but not used; 2 : the line is in using
*/
class SelectionArea :
	public TileManager
{
private:
	int m_iNumOfTiles;

	bool m_bIsNormalTrain;
	bool m_bIsFastTrain;
	bool m_bIsIntelliTrain;
	bool m_bIsCarriage;

	bool m_bIsTunnel;
	bool m_bIsBridge;

	std::vector<unsigned int> m_vecLineColors;
	unsigned int m_uiUndiscoveredColor;

	std::vector<int> m_vecTile2Type;

	int m_iDiscoveredLineCount = 0;

public:
	SelectionArea(std::vector<unsigned int> vecLineColors = { 0xFF0000, 0x00FF00, 0x0000FF }, unsigned int uiUndiscoveredColor = 0xAAAAAA,
		bool bIsNormalTrain = true, bool bIsFastTrain = true, bool bIsIntelliTrain = false, bool bIsCarriage = true,
		bool bIsTunnel = true, bool bIsBridge = false, int iTileHeight = 70, int iTileWidth = 70)
		: TileManager(iTileHeight, iTileWidth, 0, 1), m_iNumOfTiles(0),
		m_bIsNormalTrain(bIsNormalTrain), m_bIsFastTrain(bIsFastTrain), m_bIsIntelliTrain(bIsIntelliTrain), m_bIsCarriage(bIsCarriage),
		m_bIsTunnel(bIsTunnel), m_bIsBridge(bIsBridge),
		m_vecLineColors(vecLineColors), m_uiUndiscoveredColor(uiUndiscoveredColor)
	{
		// calculate number of tiles
		m_iNumOfTiles = size(vecLineColors)
			+ ((bIsNormalTrain) ? 1 : 0) + ((bIsFastTrain) ? 1 : 0) + ((bIsIntelliTrain) ? 1 : 0) + ((bIsCarriage) ? 1 : 0)
			+ ((bIsTunnel) ? 1 : 0) + ((bIsBridge) ? 1 : 0);
		setMapSize(m_iNumOfTiles, 1);

		// set tile values
		int i = 0;
		if (bIsNormalTrain) {
			m_vecTile2Type.emplace_back(-5);
			i++;
		}
		if (bIsFastTrain) {
			m_vecTile2Type.emplace_back(-4);
			i++;
		}
		if (bIsIntelliTrain) {
			m_vecTile2Type.emplace_back(-3);
			i++;
		}
		if (bIsCarriage) {
			m_vecTile2Type.emplace_back(-6);
			i++;
		}
		for (int j = 0; j < size(m_vecLineColors); i++, j++) {
			m_vecTile2Type.emplace_back(j);
		}
		if (bIsTunnel) {
			m_vecTile2Type.emplace_back(-2);
			i++;
		}
		if (bIsBridge) {
			m_vecTile2Type.emplace_back(-1);
			i++;
		}
		if (i != m_iNumOfTiles || i != size(m_vecTile2Type)) {
			printf("!! Error @ SelectionArea.h SelectionArea Constructor - number of tiles drawn not equal to number of tiles given\n");
		}
	}

	virtual void virtDrawTileAt(
		BaseEngine* pEngine,
		DrawingSurface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY) const override;

	/* index value
	* -6 : Carriage  -5 : NormalTrain  -4 : FastTrain  -3 : IntelliTrain  -2 : Tunnel  -1 : Bridge
	*/
	void incProperty(short index);
	/* index value
	* -6 : Carriage  -5 : NormalTrain  -4 : FastTrain  -3 : IntelliTrain  -2 : Tunnel  -1 : Bridge
	*/
	void setProperty(short index, int value);
	/* return true if there is no property after decrement (i.e. property number 1 -> 0)
	* index value
	* -6 : Carriage  -5 : NormalTrain  -4 : FastTrain  -3 : IntelliTrain  -2 : Tunnel  -1 : Bridge
	*/
	bool decProperty(short index);

	bool isAllLineDiscovered();
	/* undiscovered -> discovered
	* check isAllLineDiscovered() first
	*/
	void addNewLineState2Discovered();
	/* discovered -> using
	* index value: index in vector m_vecLineColors
	*/
	void setLineState2Using(short index);
	/* using -> discovered
	* index value: index in vector m_vecLineColors
	*/
	void setLineState2Discovered(short index);
};

