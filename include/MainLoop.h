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
#include "VerletObject.h"
#include "CollisionHandler.h"

class MainLoop
{
public:
	MainLoop();
	virtual ~MainLoop();

	//Called by main every frame
	void update();
	void render();

	// Accessors
	const bool running() const;

private:
	//-Window-//
	sf::RenderWindow* window;

	//-Event-//
	sf::Event event;


	//-initilize-//
	void initVariables();
	void initWindow();
	void initGameObjects();
	void initGUI();


	//-Events-//
	void pollEvents();
	void updateGameObjects();
	void updateGUI();

	std::vector<VerletDot*> Dots;
	std::list<VerletString> Strings;
	std::vector<VerletObject> Objects;

	//--Private Variables --//

	//-inputs-//
	sf::Vector2i MousePosition;
	bool leftMouseButton;

	//-timing-fps-//
	float fps;
	sf::Clock clock;
	sf::Time previousTime;
	sf::Time currentTime;

	std::list<VerletObject*> CollidingObjects;
	CollisionHandler collisionhandler;

	void spawnCube(float OffsetX, float OffsetY);
	void spawnCloth(int Distance, int SizeX, int SizeY, float OffsetX, float OffsetY);

};


