#include "stdafx.h"

#include "GridUtils.h"
#include <cmath>

namespace MyEngine
{
    uint GridUtils::LocatePoint(Vec2 point, Vec2 extent)
	{
		unsigned int theX = (unsigned int)floor(point.x / extent.x);
		unsigned int theY = (unsigned int)floor(point.y / extent.y);

		// Shift the numbers into the columns we want:
		// xxx,yyy
		unsigned int theIndex = (theX * 1000) +
								(theY);

		return theIndex;
	}

	Vec2 GridUtils::LocatePosition(uint theIndex, Vec2 extent)
	{
		unsigned int theY = theIndex % 1000;
		unsigned int theX = (theIndex / 1000) % 1000;

		Vec2 minPoint;
		minPoint.x = (float)theX * extent.x;
		minPoint.y = (float)theY * extent.y;

		return minPoint;
	}
}
