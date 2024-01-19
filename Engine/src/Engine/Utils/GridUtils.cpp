#include "pch.h"

#include "GridUtils.h"
#include <cmath>

namespace MyEngine
{
    uint GridUtils::LocatePoint(glm::vec3 point, glm::vec3 extent)
	{
		unsigned int theX = (unsigned int)floor(point.x / extent.x);
		unsigned int theY = (unsigned int)floor(point.y / extent.y);
		unsigned int theZ = (unsigned int)floor(point.z / extent.z);

		// Shift the numbers into the columns we want:
		// xxx,yyy,zzz
		// For 32 bits, we'll multiply by 1000
		unsigned int theIndex = (theX * 1000 * 1000) +
									   (theY * 1000) +
											  (theZ);

		return theIndex;
	}

	glm::vec3 GridUtils::LocatePosition(uint theIndex, glm::vec3 extent)
	{
		unsigned int theZ = theIndex % 1000;
		unsigned int theY = (theIndex / 1000) % 1000;
		unsigned int theX = theIndex / (1000 * 1000);

		glm::vec3 minPoint;
		minPoint.x = (float)theX * extent.x;
		minPoint.y = (float)theY * extent.y;
		minPoint.z = (float)theZ * extent.z;

		return minPoint;
	}
}
