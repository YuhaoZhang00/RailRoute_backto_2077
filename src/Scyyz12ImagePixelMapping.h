#pragma once
#include "header.h"
#include "ImagePixelMapping.h"

class Scyyz12ImagePixelMapping :
	public ImagePixelMapping
{
private:
	int m_iTransparencyColour = -1;
	double m_dTransparencyPercentage = 0.5;

public:
	Scyyz12ImagePixelMapping(int iTransparencyColour, double dTransparencyPercentage)
		: m_iTransparencyColour(iTransparencyColour), m_dTransparencyPercentage(dTransparencyPercentage)
	{}

	virtual bool mapCoordinates(double& x, double& y, const SimpleImage& image) override {
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

