#include "../include/VerletDot.h"
#include <iostream>

bool VerletDot::holdPoint = 0;

VerletDot::VerletDot(float x, float y, int index, int type)
{
	
	currentPosition = sf::Vector2f(x,y);
	oldPosition = sf::Vector2f(x, y);

	normalFriction = 0.99f;
	groundFriction = 0.7f;
	gravity = sf::Vector2f(0, 0.1);
	radius = 7;
	dot.setRadius(radius);
	dot.setPosition(currentPosition.x - radius, currentPosition.y - radius);
	color = sf::Color(255,255,255,255);
	dot.setFillColor(color);

	mass = 1;

	followMouse = false;
	this->index = index;
	this->type = type;

}

VerletDot::~VerletDot()
{
}

void VerletDot::updatePosition(bool Mouse)
{
	
	if (type != 0) {
		
		if (!velSet) {
			velocity = sf::Vector2f((currentPosition.x - oldPosition.x), (currentPosition.y - oldPosition.y));
		}
		else {
			velSet = false;
		}
		velocity *= normalFriction;
		oldPosition = currentPosition;
		currentPosition.x += gravity.x;
		currentPosition.y += gravity.y;
		const bool a = constrain();
		
		if (a) {
			currentPosition.x += velocity.x * groundFriction;
			currentPosition.y += velocity.y * groundFriction;
		}
		else {
			currentPosition.x += velocity.x;
			currentPosition.y += velocity.y;
		}




		dot.setPosition(currentPosition - sf::Vector2f(radius, radius));


		if (MousePosition.x > currentPosition.x - radius && MousePosition.x < currentPosition.x + radius && MousePosition.y > currentPosition.y - radius && MousePosition.y < currentPosition.y + radius)
		{
			dot.setFillColor(sf::Color::Blue);
			if (Mouse) {
				if (!VerletDot::holdPoint)
				{
					followMouse = true;
				}
			}
			else {
				followMouse = false;
				VerletDot::holdPoint = followMouse;
			}
		}
		else {
			dot.setFillColor(color);
			if (!Mouse) {
				followMouse = false;
				VerletDot::holdPoint = followMouse;
			}
		}
		if (followMouse) {
			currentPosition = sf::Vector2f(MousePosition);
			dot.setPosition(sf::Vector2f(MousePosition));
			VerletDot::holdPoint = followMouse;
		}
		
	}

}

void VerletDot::render(sf::RenderWindow* window)
{
	
	//window->draw(this->dot);

	//update Mouse Position
	MousePosition = sf::Mouse::getPosition(*window);
}

sf::Vector2f VerletDot::getPosition()
{
	return currentPosition;
}

sf::Color VerletDot::getColor()
{
	return dot.getFillColor();
}

float VerletDot::getMass()
{
	return this->mass;
}

void VerletDot::addPosition(sf::Vector2f add)
{
	if (type != 0) {
		this->currentPosition.x += add.x;
		this->currentPosition.y += add.y;
		dot.setPosition(currentPosition - sf::Vector2f(radius, radius));
	}
}

bool VerletDot::constrain()
{
	
	if (currentPosition.y >= 900) {
		
		currentPosition.y = 900;
		return true;
	}
	return false;
	
}
