#ifndef Player_H
#define Player_H

#include <SFML/Graphics.hpp>
#include "OBB.h"
#include "Walls.h"
#include "Entity.h"
using namespace std;

class Player : public sf::Drawable, public Entity
{
private:
	
	sf::Texture CarTex; //texture
	sf::Sprite CarSprite; // player car sprite

public:

	sf::Vector2f position; //!< Position
	sf::Vector2f velocity; //!< Velocity
	sf::Vector2f acceleration; //!< Acceleration
	sf::Vector2f dragForce;
	sf::Vector2f orientationC; // heading
	sf::Vector2f orientationS; // steering
	
	sf::FloatRect getBounds();

	float carRotation;
	float steeringRotation;
	float wheelDis;
	float RaceTimer;

	sf::Vector2f frontW;
	sf::Vector2f backW;
	OBB asOBB();
	bool isLeftReleased;
	bool isRightReleased;

	Player(float xPos, float yPos, float xVel, float yVel, float angle);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void playerMovement(sf::Vector2f movement);

	void updateRotation();

	void update(float deltaT);

	void keypress();

	void setScale(sf::Vector2f scale);
};

#endif