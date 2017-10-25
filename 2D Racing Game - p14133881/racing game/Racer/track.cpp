#include "Track.h"
#include <cstdlib>
#include <SFML/Graphics.hpp>

Track::Track()
{
	bool bSuccess = TrackTex.loadFromFile("../../assets/Track.png");// the background sprite which contains all the Track
	if (bSuccess == false){ exit(-1); } // exit game is texture is not found
	TrackSPS.setSize(sf::Vector2f(4500, 3000)); // size of the background
	TrackSPS.setScale(1, 1); // scale of the background
	TrackSPS.setPosition(0, 0); // the position from the top left
	TrackSPS.setTexture(&TrackTex); // texture of the background
}
void Track::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(TrackSPS,states); // draw Track
}
