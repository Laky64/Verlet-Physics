#include "VerletObject.h"


VerletObject::VerletObject(std::vector<VerletDot*> Dots, std::list<VerletString> Strings, int index, int colliding)
{
	this->Strings = Strings;
	this->Dots = Dots;
	this->index = index;
	for (VerletDot* it : Dots)
	{
		this->mass += it->getMass();
	}
	this->colliding = colliding;
}

VerletObject::~VerletObject()
{
}

void VerletObject::update(bool Mouse)
{

	for (VerletString& it : Strings)
	{
		VerletDot* dot1 = nullptr;
		VerletDot* dot2 = nullptr;

		for (VerletDot* it2 : Dots)
		{
			if (it.indexFirst == it2->index) {
				dot1 = it2;
				
			}
			if (it.indexSecond == it2->index) {
				dot2 = it2;
				
			}
			
		}

		it.update(Mouse, dot1, dot2);

	}
}

void VerletObject::render(sf::RenderWindow* window)
{
	for (VerletString& it : Strings)
	{
		it.render(window);
	}
	for (VerletDot* it : Dots)
	{
		it->render(window);
	}
}

sf::Vector2f VerletObject::getVelocity()
{
	int ind = 0;
	sf::Vector2f vel;
	for (VerletDot* it : Dots) {
		vel += it->velocity;
		ind++;
	}
	return sf::Vector2f(vel.x / ind,vel.y / ind);
}

void VerletObject::setVelocity(sf::Vector2f vel)
{
	for (VerletDot* it : Dots) {
		it->velSet = true;
		it->velocity = vel;
	}
}

sf::Vector2f VerletObject::getPosition()
{
	int ind = 0;
	sf::Vector2f vel;
	for (VerletDot* it : Dots) {
		vel += it->currentPosition;
		ind++;
	}
	return sf::Vector2f(vel.x / ind, vel.y / ind);
}

void VerletObject::addPostion(sf::Vector2f add)
{
	for (VerletDot* it : Dots) {
		it->currentPosition += add;
	}
}

