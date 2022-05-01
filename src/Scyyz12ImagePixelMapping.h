#pragma once
#include "header.h"
#include "ImagePixelMapping.h"

class Scyyz12ImagePixelMapping :
	public ImagePixelMapping
{
private:
	int m_iTransparencyColour = -1;
	double m_dTransparencyPercentage = 0.5;
	bool m_bIsShrink;

public:
	Scyyz12ImagePixelMapping(int iTransparencyColour, double dTransparencyPercentage, bool bIsShrink = false)
		: m_iTransparencyColour(iTransparencyColour), m_dTransparencyPercentage(dTransparencyPercentage), m_bIsShrink(bIsShrink)
	{}

	virtual bool mapCoordinates(double& x, double& y, const SimpleImage& image) override {
		if (m_bIsShrink) {
			int w = image.getWidth() / 2;
			int h = image.getHeight() / 2;
			x = (x - w) * 1.3 + w;
			y = (y - h) * 1.3 + h;
		}

		return true;
	}

	virtual bool changePixelColour(int x, int y, int& iNewColour, DrawingSurface* pTarget) override {

		if ((m_iTransparencyColour != -1) && (iNewColour == m_iTransparencyColour))
			return false;

		double dR = 0xFF & (iNewColour >> 16);
		double dG = 0xFF & (iNewColour >> 8);
		double dB = 0xFF & iNewColour;

		dR = dR * m_dTransparencyPercentage + 0xFF * (1 - m_dTransparencyPercentage);
		dG = dG * m_dTransparencyPercentage + 0xFF * (1 - m_dTransparencyPercentage);
		dB = dB * m_dTransparencyPercentage + 0xFF * (1 - m_dTransparencyPercentage);

		iNewColour = ((((int)(dR + 0.5)) & 0xFF) << 16)
			+ ((((int)(dG + 0.5)) & 0xFF) << 8)
			+ ((((int)(dB + 0.5)) & 0xFF));

		return true;
	}
};

