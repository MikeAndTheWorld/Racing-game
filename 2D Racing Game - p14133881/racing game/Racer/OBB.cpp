#include "OBB.h"
#include <cstdlib>
#include <SFML/Graphics.hpp>


sf::Vector2f OBB::OBB_Circle(sf::Vector2f circlePos, float circleRad, bool & hasHit)
{
	sf::Vector2f Clamp;
	sf::Vector2f originalDist = circlePos - centre;
	sf::Vector2f dist;
	sf::Vector2f diff;

	dist.x = cos(-orientation) * originalDist.x - sin(-orientation) * originalDist.y;
	dist.y = sin(-orientation) * originalDist.x + cos(-orientation) * originalDist.y;

	if (dist.x >= 0) Clamp.x = min(dist.x, extents.x);
	if (dist.x < 0) Clamp.x = max(dist.x, -extents.x);
	if (dist.y >= 0) Clamp.y = min(dist.y, extents.y);
	if (dist.y < 0) Clamp.y = max(dist.y, -extents.y);

	diff = dist - Clamp;
	float diff_magnitude = sqrt((diff.x*diff.x) + (diff.y * diff.y));

	float distance = diff_magnitude - circleRad;

	if (distance <= 0)
	{
		hasHit = true;
	}
	else
	{
		hasHit = false;
	}

	if (diff_magnitude == 0)
	{
		return sf::Vector2f(-circleRad, 0);
	}

	return diff * (distance / diff_magnitude);
}

OBB::OBB(sf::Vector2f Centre, sf::Vector2f Extents, float Orientation)
{
	centre = Centre;
	extents = Extents;
	orientation = Orientation;
}