#include "../include/VerletString.h"
#include <iostream>

VerletString::VerletString(VerletDot* first, VerletDot* second)
{
	lenght = distance(first->getPosition(),second->getPosition());
	string[0].color = first->getColor();
	string[1].color = second->getColor();
	stiffness = 1;
	indexFirst = first->index;
	indexSecond = second->index;
	
}

VerletString::~VerletString()
{
}

void VerletString::update(bool Mouse, VerletDot* first, VerletDot* second)
{
	
	first->updatePosition(Mouse);
	second->updatePosition(Mouse);
	const float dist = distance(first->getPosition(), second->getPosition());
	const float diff = (lenght - dist) / dist * stiffness;

	const float offsetx = (first->getPosition().x - second->getPosition().x) * diff * 0.5;
	const float offsety = (first->getPosition().y - second->getPosition().y) * diff * 0.5;

	const float m1 = second->getMass() / (first->getMass() + second->getMass());
	const float m2 = first->getMass() / (first->getMass() + second->getMass());

	first->addPosition(sf::Vector2f(offsetx * m1,offsety * m1) );
	second->addPosition(sf::Vector2f(-offsetx * m2, -offsety * m2));

	string[0].position = first->getPosition();
	start = first->getPosition();
	string[1].position = second->getPosition();
	end = second->getPosition();
}

void VerletString::render(sf::RenderWindow* window)
{
	window->draw(string, 2, sf::Lines);
}

float VerletString::distance(sf::Vector2f first, sf::Vector2f second)
{
	return sqrt((first.x - second.x) * (first.x - second.x) + (first.y - second.y) * (first.y - second.y));
}
