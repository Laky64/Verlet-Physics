#pragma once


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class VerletDot
{
public:
	int index;
	VerletDot(float x, float y, int index, int type = 1);
	virtual ~VerletDot();
	void updatePosition(bool Mouse);
	void render(sf::RenderWindow* window);
	sf::Vector2f getPosition();
	sf::Color getColor();
	float getMass();
	void addPosition(sf::Vector2f add);
	sf::Vector2f velocity;
	bool velSet = false;
	sf::Vector2f currentPosition;

	
private:
	sf::CircleShape dot;
	sf::Vector2f oldPosition;
	float normalFriction;
	float groundFriction;
	sf::Vector2f gravity;
	float radius;
	sf::Color color;
	float mass;
	bool constrain();
	sf::Vector2i MousePosition;
	bool followMouse;
	int type;
	static bool holdPoint;


};

