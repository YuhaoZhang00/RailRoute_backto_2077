#pragma once
#include "header.h"
#include "FilterPoints.h"
#include "DrawingSurface.h"

class Scyyz12FilterPointsScaling : public FilterPoints
{
private:
	int m_stretch, m_compress;
	FilterPoints* m_pNextFilter;

	void handleDrawing(DrawingSurface* surface, int xVirtual, int yVirtual, unsigned int& uiColour) {
		if (m_stretch > 1) { // Stretch
			xVirtual *= m_stretch;
			yVirtual *= m_stretch;
			for (int i = 0; i < m_stretch; i++) {
				int xTest = xVirtual + i;
				for (int j = 0; j < m_stretch; j++) {
					int yTest = yVirtual + j;
					if ((m_pNextFilter == nullptr) || m_pNextFilter->filter(surface, xTest, yTest, uiColour))
						surface->rawSetPixel(xTest, yTest, uiColour);
				}
			}
		}
		else { // Shrinking
			xVirtual /= m_compress;
			yVirtual /= m_compress;
			if ((m_pNextFilter == nullptr) || m_pNextFilter->filter(surface, xVirtual, yVirtual, uiColour))
				surface->rawSetPixel(xVirtual, yVirtual, uiColour);
		}
	}

public:
	Scyyz12FilterPointsScaling(int factor, FilterPoints* pNextFilter = nullptr)
		: m_stretch(1), m_compress(1), m_pNextFilter(pNextFilter)
	{
		setStretch(factor);
	}

	void compress() {
		if (m_stretch > 1) --m_stretch;
		else ++m_compress;
	}
	void stretch() {
		if (m_compress > 1) --m_compress;
		else ++m_stretch;
	}
	void setStretch(int factor) {
		if (factor == 0) { m_stretch = 1; m_compress = 1; } // zero: leave unscaled
		else if (factor > 0) { m_stretch = 1 + factor; m_compress = 1; } // Positive: Stretch by this factor
		else if (factor < 0) { m_stretch = 1; m_compress = 1 - factor; } // Negative: Compress by this factor
	}
	float getZoom() {
		return (float)m_stretch / (float)m_compress;
	}

	bool filter(DrawingSurface* surface, int& xVirtual, int& yVirtual, unsigned int& uiColour) override
	{
		handleDrawing(surface, xVirtual, yVirtual, uiColour);
		return false; // already coloured the pixel in `handleDrawing` function
	}
	int filterConvertVirtualToRealXPosition(int xVirtual) override {
		if (m_stretch > 1) {
			if (m_pNextFilter) return m_pNextFilter->filterConvertVirtualToRealXPosition(xVirtual * m_stretch);
			else return xVirtual * m_stretch;
		}
		else {
			if (m_pNextFilter) return m_pNextFilter->filterConvertVirtualToRealXPosition(xVirtual / m_compress);
			else return xVirtual / m_compress;
		}
	}
	int filterConvertVirtualToRealYPosition(int yVirtual) override {
		if (m_stretch > 1) {
			if (m_pNextFilter) return m_pNextFilter->filterConvertVirtualToRealYPosition(yVirtual * m_stretch);
			else return yVirtual * m_stretch;
		}
		else {
			if (m_pNextFilter) return m_pNextFilter->filterConvertVirtualToRealYPosition(yVirtual / m_compress);
			else return yVirtual / m_compress;
		}
	}
	int filterConvertRealToVirtualXPosition(int xReal) override {
		if (m_pNextFilter) xReal = m_pNextFilter->filterConvertRealToVirtualXPosition(xReal);
		if (m_stretch > 1) return xReal / m_stretch;
		else return xReal * m_compress;
	}
	int filterConvertRealToVirtualYPosition(int yReal) override {
		if (m_pNextFilter) yReal = m_pNextFilter->filterConvertRealToVirtualYPosition(yReal);
		if (m_stretch > 1) return yReal / m_stretch;
		else return yReal * m_compress;
	}
};

class Scyyz12FilterPointsTranslation : public FilterPoints
{
private:
	int m_xModifier, m_yModifier;
	FilterPoints* m_pNextFilter;

public:
	Scyyz12FilterPointsTranslation(int xModifier, int yModifier, FilterPoints* pNextFilter = nullptr)
		: m_xModifier(xModifier), m_yModifier(yModifier), m_pNextFilter(pNextFilter)
	{}

	int getXOffset() { return m_xModifier; }
	int getYOffset() { return m_yModifier; }
	void setOffset(int offsetX, int offsetY) {
		m_xModifier = offsetX;
		m_yModifier = offsetY;
	}
	void changeOffset(int offsetXIncrement, int offsetYIncrement) {
		m_xModifier += offsetXIncrement;
		m_yModifier += offsetYIncrement;
	}

	bool filter(DrawingSurface* surface, int& xVirtual, int& yVirtual, unsigned int& uiColour) override {
		xVirtual += m_xModifier;
		yVirtual += m_yModifier;
		return (m_pNextFilter == nullptr) || m_pNextFilter->filter(surface, xVirtual, yVirtual, uiColour);
	}
	int filterConvertVirtualToRealXPosition(int xVirtual) override {
		if (m_pNextFilter)
			return m_pNextFilter->filterConvertVirtualToRealXPosition(xVirtual + m_xModifier);
		return xVirtual + m_xModifier;
	}
	int filterConvertVirtualToRealYPosition(int yVirtual) override {
		if (m_pNextFilter)
			return m_pNextFilter->filterConvertVirtualToRealYPosition(yVirtual + m_yModifier);
		return yVirtual + m_yModifier;
	}
	int filterConvertRealToVirtualXPosition(int x) override {
		if (m_pNextFilter)
			x = m_pNextFilter->filterConvertRealToVirtualXPosition(x);
		return x - m_xModifier;
	}
	int filterConvertRealToVirtualYPosition(int y) override {
		if (m_pNextFilter)
			y = m_pNextFilter->filterConvertRealToVirtualYPosition(y);
		return y - m_yModifier;
	}
};

