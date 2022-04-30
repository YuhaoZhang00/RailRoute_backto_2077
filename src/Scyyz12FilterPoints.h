#pragma once
#include "header.h"
#include "FilterPoints.h"
#include "DrawingSurface.h"

class Scyyz12FilterPointsScaling : public FilterPoints
{
private:
	double m_stretch;
	int x1, y1, x2, y2;
	FilterPoints* m_pNextFilter;

	void handleDrawing(DrawingSurface* surface, int xVirtual, int yVirtual, unsigned int& uiColour) {
		xVirtual *= m_stretch;
		yVirtual *= m_stretch;
		for (int i = 0; i < m_stretch; i++) {
			int xTest = xVirtual + i;
			for (int j = 0; j < m_stretch; j++) {
				int yTest = yVirtual + j;
				if ((m_pNextFilter == nullptr) || m_pNextFilter->filter(surface, xTest, yTest, uiColour)) {
					if (xTest >= x1 && xTest <= x2 && yTest >= y1 && yTest <= y2) {
						surface->rawSetPixel(xTest, yTest, uiColour);
					}
				}
			}
		}
	}

public:
	Scyyz12FilterPointsScaling(int factor, int x1, int y1, int x2, int y2, FilterPoints* pNextFilter = nullptr)
		: m_stretch(1.0), m_pNextFilter(pNextFilter), x1(x1), x2(x2), y1(y1), y2(y2)
	{
		setStretch(factor);
	}

	void compress() {
		if (m_stretch > 1) m_stretch -= 0.1;
	}
	void stretch() {
		m_stretch += 0.1;
	}
	void setStretch(double factor) {
		m_stretch = factor;
	}

	bool filter(DrawingSurface* surface, int& xVirtual, int& yVirtual, unsigned int& uiColour) override
	{
		handleDrawing(surface, xVirtual, yVirtual, uiColour);
		return false; // already coloured the pixel in `handleDrawing` function
	}
	int filterConvertVirtualToRealXPosition(int xVirtual) override {
		if (m_pNextFilter) return m_pNextFilter->filterConvertVirtualToRealXPosition(xVirtual * m_stretch);
		return xVirtual * m_stretch;
	}
	int filterConvertVirtualToRealYPosition(int yVirtual) override {
		if (m_pNextFilter) return m_pNextFilter->filterConvertVirtualToRealYPosition(yVirtual * m_stretch);
		return yVirtual * m_stretch;
	}
	int filterConvertRealToVirtualXPosition(int xReal) override {
		if (m_pNextFilter) xReal = m_pNextFilter->filterConvertRealToVirtualXPosition(xReal);
		return xReal / m_stretch;
	}
	int filterConvertRealToVirtualYPosition(int yReal) override {
		if (m_pNextFilter) yReal = m_pNextFilter->filterConvertRealToVirtualYPosition(yReal);
		return yReal / m_stretch;
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

class Scyyz12FilterPointsRectangularMask : public FilterPoints
{
private:
	int x1, y1, x2, y2;
	FilterPoints* m_pNextFilter;

public:
	Scyyz12FilterPointsRectangularMask(int x1, int y1, int x2, int y2, FilterPoints* pNextFilter = nullptr)
		: x1(x1), y1(y1), x2(x2), y2(y2), m_pNextFilter(pNextFilter)
	{}

	bool filter(DrawingSurface* surface, int& x, int& y, unsigned int& uiColour) override {
		if (x < 0 || y < 0 || x >= 1300 || y >= 800)
			return false;
		if (x < x1 || y < y1 || x > x2 || y > y2)
			return true;
		return (m_pNextFilter == nullptr) || m_pNextFilter->filter(surface, x, y, uiColour);
	}
	int filterConvertVirtualToRealXPosition(int xVirtual) override {
		if (xVirtual < x1 || xVirtual > x2) return xVirtual;
		if (m_pNextFilter)
			return m_pNextFilter->filterConvertVirtualToRealXPosition(xVirtual);
		return xVirtual;
	}
	int filterConvertVirtualToRealYPosition(int yVirtual) override {
		if (yVirtual < y1 || yVirtual > y2) return yVirtual;
		if (m_pNextFilter)
			return m_pNextFilter->filterConvertVirtualToRealYPosition(yVirtual);
		return yVirtual;
	}
	int filterConvertRealToVirtualXPosition(int x) override {
		if (x < x1 || x > x2) return x;
		if (m_pNextFilter)
			x = m_pNextFilter->filterConvertRealToVirtualXPosition(x);
		return x;
	}
	int filterConvertRealToVirtualYPosition(int y) override {
		if (y < y1 || y > y2) return y;
		if (m_pNextFilter)
			y = m_pNextFilter->filterConvertRealToVirtualYPosition(y);
		return y;
	}
};

