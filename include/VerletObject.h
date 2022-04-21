#pragma once
#include <iostream>
#include <list>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "VerletDot.h"
#include "VerletString.h"

class VerletObject
{
public:
	
	VerletObject(std::vector<VerletDot*> Dots, std::list<VerletString> Strings, int index, int colliding);
	virtual ~VerletObject();
	void update(bool Mouse);
	void render(sf::RenderWindow* window);
	std::list<VerletString> Strings;
	int index;
	sf::Vector2f getVelocity();
	void setVelocity(sf::Vector2f vel);
	sf::Vector2f getPosition();
	void addPostion(sf::Vector2f add);
	float mass = 0;
	int colliding;
private:
	std::vector<VerletDot*> Dots;

};

