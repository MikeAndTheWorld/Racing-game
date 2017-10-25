#ifndef OBB_H
#define OBB_H
#include <SFML/Graphics.hpp>
using namespace std;

class OBB
{
private:

public:
	OBB(sf::Vector2f Centre, sf::Vector2f Extents, float Orientation);

	sf::Vector2f centre;
	sf::Vector2f extents; // half extents
	float orientation;

	sf::Vector2f OBB_Circle(sf::Vector2f circlePos, float circleRad, bool & hasHit);

};
#endif