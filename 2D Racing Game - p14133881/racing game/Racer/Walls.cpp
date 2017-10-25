#include "Walls.h"
#include <cstdlib>
#include <SFML/Graphics.hpp>

Walls::Walls(float WallXpos , float WallYpos)
{
	bool bSuccess = WallsTex.loadFromFile("../../assets/Walls.png");// the sprite which contains the wheels
	if (bSuccess == false){ exit(-1); }
	WallsSPS.setRadius(32); // size of the wheel
	WallsSPS.setOrigin(32,32);
	WallRadius = 32;
	WallsSPS.setScale(1, 1); // scale of the wheel
	WallsSPS.setPosition(WallXpos, WallYpos); // the position from the top left
	WallsSPS.setTexture(&WallsTex); // texture of the background
}
void Walls::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(WallsSPS, states); // draw Walls
}
sf::Vector2f Walls::GetPosition()
{
	return WallsSPS.getPosition();
}
