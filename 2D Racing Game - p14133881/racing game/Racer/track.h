#ifndef Track_H
#define Track_H
#include <SFML/Graphics.hpp>
using namespace std;

class Track : public sf::Drawable
{
private:
	sf::Texture TrackTex; // texture for the background
	sf::RectangleShape TrackSPS; // background sprite
public:
	Track();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};
#endif