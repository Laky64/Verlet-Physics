#pragma once
#include <iostream>
#include <list>
#include "VerletObject.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class CollisionHandler
{
public:
	CollisionHandler();
	virtual ~CollisionHandler();
	void solveCollisions(std::list<VerletObject*>* Objects);
private:
	struct line
	{
		sf::Vector2f start;
		sf::Vector2f end;
		line(sf::Vector2f start, sf::Vector2f end) {
			this->start = start;
			this->end = end;
		};
		

	};	
	bool getIntersection(line first, line second);

};

