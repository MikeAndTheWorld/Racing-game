#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "player.h"
#include "track.h"
#include "Walls.h"
#include "Checkpoint.h"
#include <sstream>

#define DEG 57.2958f
#define RAD 0.0174533f
#define PI 3.14159265f

using namespace std;

void render(sf::RenderWindow& window,Player& player,Track& track, vector<Walls> walls, Checkpoint& checkpoint)
{
	
	// Declare a new font
	sf::Font font;
	// Load it from a file
	if (!font.loadFromFile("../../assets/Font.ttf"))
	{
		// error...
	}
	// Create a text which uses our font
	sf::Text text1;
	text1.setFont(font);
	text1.setCharacterSize(70);
	text1.setStyle(sf::Text::Bold);
	text1.setString("start");
	text1.rotate(-90);
	text1.setColor(sf::Color(255, 255, 255));
	text1.scale(1, 1);
	text1.move(2150, 2305);

	// Create another text using the same font, but with different parameters
	sf::Text time;
	time.setFont(font);
	time.setCharacterSize(50);
	time.setStyle(sf::Text::Italic);
	stringstream buffer;
	buffer.precision(4);
	buffer << "Time:" << (player.RaceTimer / 1000) << endl;
	time.setString(buffer.str());
	time.rotate(-90);
	time.setColor(sf::Color(255, 255, 255));
	time.scale(1, 1);
	time.move(player.position.x - 70, player.position.y - 20);

	sf::Text gear;
	gear.setFont(font);
	gear.setCharacterSize(50);
	gear.setStyle(sf::Text::Italic);
	buffer.precision(1);
	if (player.velocity.y < 0)
	{
		buffer << "gear:" << "reverse" << endl;
	}
	if (player.velocity.y == 0)
	{
		buffer << "gear:" << "neutral" << endl;
	}
	if (player.velocity.y <= 200)
	{
		if (player.velocity.y > 0)
		{
				buffer << "gear:" << "1" << endl;
		}
	}
	if (player.velocity.y <= 300)
	{
		if (player.velocity.y >= 200)
		{
			buffer << "gear:" << "2" << endl;
		}
		
	}
	if (player.velocity.y <= 400)
	{
		if (player.velocity.y >= 300)
		{
			buffer << "gear:" << "3" << endl;
		}
	}
	if (player.velocity.y <= 500)
	{
		if (player.velocity.y >= 400)
		{
			buffer << "gear:" << "4" << endl;
		}
	}
	if (player.velocity.y <= 600)
	{
		if (player.velocity.y >= 500)
		{
			buffer << "gear:" << "5" << endl;
		}
	}
	if (player.velocity.y >= 600)
	{
		buffer << "gear:" << "6" << endl;
	}
	gear.setString(buffer.str());
	gear.rotate(-90);
	gear.setColor(sf::Color(255, 255, 255));
	gear.scale(1, 1);
	gear.move(player.position.x - 70, player.position.y - 20);

	sf::Text text2;
	text2.setFont(font);
	text2.setCharacterSize(50);
	text2.setStyle(sf::Text::Italic);
	buffer.precision(5);
	if (player.velocity.y >= 0)
	{
		buffer << "spd:"<< player.velocity.y << endl;
	}
	else
	{
		buffer << "spd:" << "R" << -player.velocity.y << endl;
	}
	text2.setString(buffer.str());
	text2.rotate(-90);
	text2.setColor(sf::Color(255, 255, 255));
	text2.scale(1, 1);
	text2.move(player.position.x - 70,player.position.y - 20);
	

	window.draw(track); //draw track
	
	window.draw(text1);
	player.setScale(sf::Vector2f(1.0f,1.0f));
	window.draw(player); // draw car
	for (auto i = walls.begin(); i != walls.end(); i++)
	{
		window.draw(*i); //draw wheels
	}
	window.draw(time);
	window.draw(text2);
	window.draw(gear);
	window.draw(checkpoint);
	
}
void render2(sf::RenderWindow& window, Player& player, Track& track, vector<Walls> walls)
{
	player.setScale(sf::Vector2f(10.0f, 10.0f));
	window.draw(track); //draw track
	window.draw(player); // draw car
}
void update(sf::RenderWindow& window, Player& player, Checkpoint& checkpoint, float deltaT)
{
	sf::Event event;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
			player.acceleration.y = 500; //acceleration of the car
	}
	if (sf::Keyboard::isKeyPressed( sf::Keyboard::S))
	{
			player.acceleration.y = -300; //acceleration of the car
		}
	
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close(); //close game
		}

		if (event.type == sf::Event::KeyPressed)
		{
			//menu keys
			if (event.key.code == sf::Keyboard::A) // left
			{
				player.steeringRotation -= 10 * RAD;
				if (player.steeringRotation  < -359 * RAD)
				{
					player.steeringRotation = -359 * RAD;
				}
			}

			if (event.key.code == sf::Keyboard::D) // right
			{
				player.steeringRotation += 10 * RAD;
				if (player.steeringRotation > 359 * RAD)
				{
					player.steeringRotation = 359 * RAD;
				}
			}
		}
		if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::A)
			{
				player.isLeftReleased = true;
			}
			if (event.key.code == sf::Keyboard::D)
			{
				player.isRightReleased = true;
			}
	
		}
	}
	player.update(deltaT);
	player.updateRotation();
	
	if (checkpoint.checkP[0].getGlobalBounds().intersects(player.getBounds()))
	{
		checkpoint.checking[0] = true;
		cout << "0";
	}
	if (checkpoint.checkP[1].getGlobalBounds().intersects(player.getBounds()))
	{
		checkpoint.checking[1] = true;
		cout << "1";
	}
	if (checkpoint.checkP[2].getGlobalBounds().intersects(player.getBounds()))
	{
		checkpoint.checking[2] = true;
		cout << "2";
	}
	if (checkpoint.checkP[3].getGlobalBounds().intersects(player.getBounds()))
	{
		checkpoint.checking[3] = true;
		cout << "3";
	}
	checkpoint.update();
}

int main()

{
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "2D Racer!"); // window size
	sf::View camera(sf::Vector2f(0,0),sf::Vector2f(1000,1000));
	sf::View miniMap(sf::Vector2f(0, 0), sf::Vector2f(100, 100));
	miniMap.setViewport(sf::FloatRect(0.75, 0.75, 0.25, 0.25));
	miniMap.zoom(27);
	camera.zoom(1.0f);
	camera.rotate(-90);

	Player player = Player(2330.0, 2145.0, 0.0, 0.0, -90.0);
	Track track = Track();
	vector<Walls> walls;
	Checkpoint checkpoint;

	//outer walls
	//turn 1
	for (int i = 0; i < 26; i++)
	{
		walls.push_back(Walls
			(1402 - 500 * cosf((-43 + 190/26 * i) * RAD),
			1090 - 500 * sinf(RAD*(-43 + 190 / 26 * i))));
	}
	//turn 2
	for (int i = 0; i < 32; i++)
	{
		walls.push_back(Walls
			(3105 - 497 * cosf((43.5f + 234 / 32 * i) * RAD),
			1830 - 510 * sinf(RAD*(43.5f + 234 / 32 * i))));
	}
	//turn 3
	for (int i = 0; i < 4; i++)
	{
		walls.push_back(Walls
			(2620 - 165 * cosf((242 + 90 / 4 * i) * RAD),
			1372 - 160 * sinf(RAD*(242 + 90 / 4 * i))));
	}
	//turn 4
	for (int i = 0; i < 5; i++)
	{
		walls.push_back(Walls
			(2075 - 435 * cosf((272.5f + 44 / 5 * i) * RAD),
			1928 - 400 * sinf(RAD*(272.5f + 44 / 5 * i))));
	}
	//turn 5
	for (int i = 0; i < 4; i++)
	{
		walls.push_back(Walls
			(1405 - 182 * cosf((65 + 80 / 4 * i) * RAD),
			1430 - 182 * sinf(RAD*(65 + 80 / 4 * i))));
	}
	//turn 6
	for (int i = 0; i < 6; i++)
	{
		walls.push_back(Walls
			(1850 - 140 * cosf((130 + 110 / 6 * i) * RAD),
			1855 - 200 * sinf(RAD*(130 + 110 / 6 * i))));
	}
	//strights
	for (int i = 0; i < 17; i++)
	{
		walls.push_back(Walls(1780 + (i* 43), 765 + (i* 44)));
	}
	for (int i = 0; i < 18; i++)
	{
		walls.push_back(Walls(1075 + (i* 42), 1480 + (i* 43)));
	}
	for (int i = 0; i < 17; i++)
	{
		walls.push_back(Walls(2117 +(i* 63), 2340));
	}
	for (int i = 0; i < 9; i++)
	{
		walls.push_back(Walls(1567 + (i * 42), 1305 + (i * 43)));
	}

	//inner walls
	//turn 1
	for (int i = 0; i < 10; i++)
	{
		walls.push_back(Walls(
		/*X*/ 1402 - 201 /*rad*/ * cosf((-50 /*angle*/ + 180 /*size*/ / 10 /*amount*/ * i /*times to draw it*/) * RAD),
		/*Y*/ 1090 - 201 * sinf(RAD*(-50 + 180 / 10 * i))));
	}
	//turn 2
	for (int i = 0; i < 14; i++)
	{
		walls.push_back(Walls
			(3105 - 201 * cosf((42 + 250 / 14 * i) * RAD),
			1830 - 201 * sinf(RAD*(42 + 250 / 14 * i))));
	}
	//turn 3
	for (int i = 0; i < 12; i++)
	{
		walls.push_back(Walls
			(2620 - 471 * cosf((232 + 87 / 12 * i) * RAD),
			1372 - 471 * sinf(RAD*(232 + 87 / 12 * i))));
	}
	//strights
	for (int i = 0; i < 20; i++)
	{
		walls.push_back(Walls(1525 + (i * 40), 940 + (i * 40)));
	}
	for (int i = 0; i < 16; i++)
	{
		walls.push_back(Walls(2122 + (i * 63), 2033));
	}
	for (int i = 0; i < 9; i++)
	{
		walls.push_back(Walls(1463 + (i * 42), 1452 + (i * 43)));
	}
	for (int i = 0; i < 8; i++)
	{
		walls.push_back(Walls(1515 + (i * 42), 1430 + (i * 43)));
	}
	for (int i = 0; i < 2; i++)
	{
		walls.push_back(Walls(2059 - (i * 57), 2030 - (i * 15)));
	}

	//sf::Event event;
	sf::Clock Ctimer; //clock timer
	window.setVerticalSyncEnabled(true); // Vsync locks to the refresh rate of the screen
	float T = Ctimer.getElapsedTime().asMilliseconds(); // the start time after the window has been made
	float deltaT = 0.0; // the time step
	float RaceStartTime = T;
	
	while (window.isOpen())
	{

		deltaT = (Ctimer.getElapsedTime().asMilliseconds() - T) / 1000; // the clock time - the the timer's time / 1000. the time step, the change in time since the last frame
		T = Ctimer.getElapsedTime().asMilliseconds(); // time in microsecounds the current time
		camera.setCenter(player.position.x, player.position.y);
		window.setView(camera);
		miniMap.setCenter(4500/2, 3000/2);


		player.acceleration = sf::Vector2f(0.0, 0.0); // the starting acceleration
		player.RaceTimer = Ctimer.getElapsedTime().asMilliseconds() - RaceStartTime;
		update(window, player,checkpoint ,deltaT); // updating the shapes
		
		bool hasHit = false;

		for (int i = 0; i < walls.size(); i++)
		{
			sf::Vector2f Intersection = player.asOBB().OBB_Circle(walls.at(i).GetPosition(), walls.at(0).WallRadius, hasHit);
			sf::Vector2f normalise = Intersection / sqrt((Intersection.x*Intersection.x) + (Intersection.y * Intersection.y));

			const float restitutionCoefficient = 1.0f;
			float VdotNormalise = player.velocity.x * normalise.x + player.velocity.y * normalise.y;

			if (hasHit == true)
			{
				sf::err() << "\nHas hit: " << Intersection.x << ", " << Intersection.y << '\n';
				player.setPosition(player.getPosition() - Intersection);
				player.velocity = player.velocity - ((1.0f + restitutionCoefficient)* normalise * VdotNormalise);
			}
		}
		window.clear(); // clear the screen
		render(window,player,track,walls,checkpoint);
		window.setView(miniMap);
		render2(window, player, track, walls);
		window.display(); //display the renders

	sf::err() << player.velocity.y << "   |   " << player.velocity.x << "   |   " << player.position.x << "   |   " << player.position.y<< endl;
	}
	return 0;
}