#ifndef Checkpoint_H
#define Checkpoint_H
#include <SFML/Graphics.hpp>
using namespace std;

class Checkpoint : public sf::Drawable
{
private:
	float finish;
	int counter;
	sf::Vector2f position1;
	sf::Vector2f size1;
	sf::Vector2f position2;
	sf::Vector2f size2;
	sf::Vector2f position3;
	sf::Vector2f size3;
	sf::Vector2f position4;
	sf::Vector2f size4;
public:

	
	sf::RectangleShape block1;

	sf::RectangleShape  checkP[4];
	bool checking[4];
	
	Checkpoint();
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif