#ifndef Walls_H
#define Walls_H
#include <SFML/Graphics.hpp>

using namespace std;

class Walls : public sf::Drawable
{
private:
	sf::Texture WallsTex; // texture for the background
	sf::CircleShape WallsSPS; // background sprite
public:
	Walls(float WallXpos, float WallYpos);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	float WallRadius;
	sf::Vector2f GetPosition();
};
#endif