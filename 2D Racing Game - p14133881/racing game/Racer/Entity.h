#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class Entity : public sf::Transformable{

private:
	int m_scale; // the scale
	float fXpos; // x position
	float fYpos; // y position

protected:
	bool ImgLoader(sf::Texture& texture, sf::Sprite& sprite, std::string fileName, sf::Vector2f& size);
	//entity position
	//void setScale(int scale); // set the scale
	void setXpos(float x); // set the x position
	void setYpos(float y); // set the y position
	//entity move
	void movement(float x, float y); //movement for things such as cars

public:
	float getXpos(); // get the x position
	float getYpos(); // get the y position
	int getScale(); // get the scale
};
#endif