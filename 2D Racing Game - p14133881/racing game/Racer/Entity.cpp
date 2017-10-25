#include <SFML/Graphics.hpp>
#include "Entity.h"

bool Entity::ImgLoader(sf::Texture& texture, sf::Sprite& sprite, std::string fileName, sf::Vector2f& size){

	if (texture.loadFromFile("../../assets/" + fileName)) // load the texture from my assets folder
	{
		sprite.setScale(size.x / texture.getSize().x, size.y / texture.getSize().y); // to scqale with the size
		sprite.setOrigin(size.x / texture.getSize().x / 2.0f, size.y / texture.getSize().y / 2.0f); //set origin to be in the center of the sprite
		sprite.setTexture(texture); // setting the texture
		return true;// return true to loading the images
	}
	return false;
}
void Entity::setXpos(float x)
{
	fXpos = x; // setting the position
}
void Entity::setYpos(float y)
{
	fYpos = y; // setting the position
}
float Entity::getXpos()
{
	return fXpos; // return x position
}
float Entity::getYpos()
{
	return fYpos; // return y position
}