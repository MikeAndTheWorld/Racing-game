#include "Player.h"
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>

#define DEG 57.2958f
#define RAD 0.0174533f
#define PI 3.14159265f

Player::Player(float xPos, float yPos, float xVel, float yVel, float angle)
{
	position.x = xPos;
	position.y = yPos;

	velocity.x = xVel;
	velocity.y = yVel;

	acceleration.x = 0.0f;
	acceleration.y = 0.0f;

	dragForce.x = 0.8f;
	dragForce.y = 0.8f;

	wheelDis = 20;

	carRotation = angle * RAD;
	steeringRotation = angle * RAD;

	bool bSuccess = CarTex.loadFromFile("../../assets/car.png");
	if (bSuccess == false){ exit(-1); } // exit if the sprite doesn't load
	CarSprite.setTexture(CarTex); // set the texture
	CarSprite.setOrigin(18/2,38/2);
	CarSprite.setScale(1, 1);
	CarSprite.setPosition(xPos, yPos); // starting position

}

void Player::setScale(sf::Vector2f scale)
{
	CarSprite.setScale(scale);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(CarSprite, states); // draw the setting
}


sf::FloatRect Player::getBounds(){
	
	return	sf::FloatRect(CarSprite.getPosition().x, CarSprite.getPosition().y, CarTex.getSize().x, CarTex.getSize().y);
}
void Player::playerMovement(sf::Vector2f movement)
{
	CarSprite.setPosition(movement);
}

void Player::update(float deltaT)
{
	if (isLeftReleased)
	{
		steeringRotation += 20* 0.0174533f;
		if (steeringRotation < carRotation + (RAD * 150) && steeringRotation > carRotation - (RAD * 150))
		{
			steeringRotation = carRotation;
			isLeftReleased = false;
		}
	}
	if (isRightReleased)
	{
		steeringRotation -= 20* 0.0174533f;
		if (steeringRotation < carRotation + (RAD * 150) && steeringRotation > carRotation - (RAD * 150))
		{
			steeringRotation = carRotation;
			isRightReleased = false;
		}
	}
	// the speed of the car
	velocity.x = velocity.x + (acceleration.x * deltaT); // the new velocity X
	velocity.y = velocity.y + (acceleration.y * deltaT); // the new velocity y

	//adding drag to the car to slow the car after acceleration
	velocity.x = velocity.x + (-velocity.x * dragForce.x * 0.98f * deltaT); // velocity x force * time step
	velocity.y = velocity.y + (-velocity.y * dragForce.y * 0.98f * deltaT);
	if (velocity.y < 0.1 && velocity.y > -0.1)
	{
		velocity.y = 0;
	}
	if (velocity.x < 0.1 && velocity.x > -0.1)
	{
		velocity.x = 0;
	}
	sf::Vector2f displacement = velocity * deltaT;

	//STEERING
	float steeringAngle = steeringRotation;// -carRotation;

	//the car’s orientation
	orientationC = sf::Vector2f(cos(carRotation) * 0 + -sin(carRotation) * -1, sin(carRotation) * 0 + cos(carRotation) * -1);

	//steering orientation
	orientationS = sf::Vector2f(cos(steeringAngle) * 0 + -sin(steeringAngle) * -1, sin(steeringAngle) * 0 + cos(steeringAngle) * -1);

	//the current positions of the front wheel
	frontW.x = position.x + (orientationC.x * (wheelDis / 2));
	frontW.y = position.y + (orientationC.y * (wheelDis / 2));
	//the current positions of the back wheel
	backW.x = position.x - (orientationC.x * (wheelDis / 2));
	backW.y = position.y - (orientationC.y * (wheelDis / 2));
	
	//steering trajectory
	frontW.x = frontW.x + orientationS.x * displacement.y; // front wheel movement
	frontW.y = frontW.y + orientationS.y * displacement.y; // front wheel movement
	
	//cars trajectory
	backW.x = backW.x + orientationC.x * displacement.y;
	backW.y = backW.y + orientationC.y * displacement.y;
	
	// cars new position
	position.x = (frontW.x + backW.x) / 2; // update pos
	position.y = (frontW.y + backW.y) / 2;
	
	//update the two orientation angles
	float newcarRotation = atan2(frontW.y - backW.y, frontW.x - backW.x);
	newcarRotation = newcarRotation + PI / 2;
	steeringRotation = steeringRotation + (newcarRotation - carRotation);
	carRotation = newcarRotation;
	playerMovement(position); // the player's movement depending on the velocity
}

void Player::updateRotation()
{
	CarSprite.setRotation(carRotation * DEG);
}

OBB Player::asOBB()
{
	return OBB(position, sf::Vector2f(16/2, 38/2), carRotation);
}