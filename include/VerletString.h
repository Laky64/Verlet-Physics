#pragma once
#include <iostream>
#include <list>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "VerletDot.h"

class VerletString
{
public:
	VerletString(VerletDot* first, VerletDot* second);
	virtual ~VerletString();
	void update(bool Mouse, VerletDot* first, VerletDot* second);
	void render(sf::RenderWindow* window);
	int indexFirst;
	int indexSecond;
	sf::Vector2f start;
	sf::Vector2f end;
private:
	float lenght;
	float distance(sf::Vector2f first, sf::Vector2f second);
	sf::Vertex string[2];
	float stiffness;

};

