#include "Checkpoint.h"
#include "player.h"
#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

Checkpoint::Checkpoint()
{
	finish = 0;
	counter = 0;
	position1.x = 2010; size1.x = 50;
	position1.y = 2025; size1.y = 300;

	position2.x = 1330; size2.x = 50;
	position2.y = 600; size2.y = 300;

	position3.x = 2600; size3.x = 50;
	position3.y = 1540; size3.y = 300;

	position4.x = 2080; size4.x = 50;
	position4.y = 2045; size4.y = 300;

	checkP[0].setPosition(position1);
	checkP[0].setSize(size1);
	checkP[1].setPosition(position2);
	checkP[1].setSize(size2);
	checkP[2].setPosition(position3);
	checkP[2].setSize(size3);
	checkP[3].setPosition(position4);
	checkP[3].setSize(size4);


	checkP[0].setFillColor(sf::Color(0, 0, 255, 255));

}
void Checkpoint::update()
{
	
		if (checking[0] == true)
		{
			checking[3] = false;
			finish = 1;
		}
		if (checking[1] == true && checking[0] == true)
		{
			if (finish == 1)
			{
				checking[0] = false;
				finish = 2;
			}
		}
		if (checking[2] == true && checking[1] == true)
		{
			if (finish == 2)
			{
				checking[1] = false;
				finish = 3;
			}
		}
		if (checking[3] == true && checking[2] == true)
		{
			if (finish == 3)
			{
				checking[2] = false;
				finish = 4;
			}
		}
		if (finish == 4)
		{
			//you wins
			finish = 0;
			counter + 1;
		}
		if (counter == 1)
		{
			cout << "00000000000000000000000000000000000000000000000000000000000000000000000000000000\n\n\n\n\n";
		}
		if (counter == 2)
		{
			cout << "111111111111111111111111111111111111111111111111111111111111111111111111111111111Y\n\n\n\n\n";
		}
		if (counter == 3)
		{
			cout << "2222222222222222222222222222222222222222222222222222222222222222222222222222222222Y\n\n\n\n\n";
		}
}

void Checkpoint::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(checkP[0]);
}