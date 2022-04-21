#include <iostream>
#include "../include/MainLoop.h"
#include <iterator>
#include <list>

MainLoop::MainLoop()
{
    // initialize
    this->initVariables();
    this->initWindow();
    this->initGameObjects();
    this->initGUI();
}

MainLoop::~MainLoop()
{
    delete this->window;
}

// Accessors
const bool MainLoop::running() const
{
    return this->window->isOpen();
}

//------Functions------//
//---Voids---//

//--Events--//
void MainLoop::pollEvents()
{

    while (this->window->pollEvent(this->event))
    {
        switch (this->event.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->event.key.code == sf::Keyboard::Escape)
                this->window->close();
            break;
        case sf::Event::MouseButtonPressed:
            if (this->event.key.code == sf::Mouse::Left)

                leftMouseButton = true;
            break;
        case sf::Event::MouseButtonReleased:
            if (this->event.key.code == sf::Mouse::Left)
                leftMouseButton = false;
            break;
        }
    }

    // update Mouse Position
    MousePosition = sf::Mouse::getPosition(*this->window);

    // calc FPS
    currentTime = clock.getElapsedTime();
    fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds());
    previousTime = currentTime;
}

//--initialize--//
void MainLoop::initVariables()
{

    this->window = nullptr;
    //if (!font.loadFromFile("../assets/font.ttf"))
   // {
   //     sf::err() << "Couldn't load font\n";
   // }

    previousTime = clock.getElapsedTime();
}

void MainLoop::initWindow()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    this->window = new sf::RenderWindow(sf::VideoMode(1600, 900), "Main", sf::Style::Close, settings);
    this->window->setFramerateLimit(165);
}

void MainLoop::initGameObjects()
{

    spawnCube(50, 50);
    spawnCube(250, 250);
    spawnCube(350, 450);
    spawnCube(550, 50);
    spawnCube(750, 250);
    spawnCube(850, 450);
    spawnCloth(20, 10, 10, 500,50);
   
    for (VerletObject& it : Objects)
    {
        if (it.colliding != 0) {
            CollidingObjects.push_back(&it);
        }
    }
}



void MainLoop::initGUI()
{

}

//--Update--//

//-Called by main--//
void MainLoop::update()
{
    // Events
    this->pollEvents();

    this->updateGUI();

    this->updateGameObjects();
}

//-functions-//
void MainLoop::updateGameObjects()
{
    
    
    for (VerletObject& it : Objects)
    {
        it.update(leftMouseButton);
    }
    collisionhandler.solveCollisions(&CollidingObjects);
}

void MainLoop::updateGUI()
{

}

void MainLoop::spawnCube(float OffsetX, float OffsetY)
{
    Dots = {};
    Strings = {};
    VerletDot* dot1s = new VerletDot(0 + OffsetX, 0 + OffsetY, 1);
    VerletDot* dot2s = new VerletDot(100 + OffsetX, 0 + OffsetY, 2);
    VerletDot* dot3s = new VerletDot(0 + OffsetX, 100 + OffsetY, 3);
    VerletDot* dot4s = new VerletDot(100 + OffsetX, 100 + OffsetY, 4);

    Dots.push_back(dot1s);
    Dots.push_back(dot2s);
    Dots.push_back(dot3s);
    Dots.push_back(dot4s);

    VerletString string1s(dot1s, dot2s);
    VerletString string2s(dot3s, dot4s);
    VerletString string3s(dot2s, dot3s);
    VerletString string4s(dot2s, dot4s);
    VerletString string5s(dot1s, dot4s);
    VerletString string6s(dot1s, dot3s);

 
    Strings.push_back(string1s);
    Strings.push_back(string2s);
    Strings.push_back(string3s);
    Strings.push_back(string4s);
    Strings.push_back(string5s);
    Strings.push_back(string6s);

    
    VerletObject obj1s(Dots, Strings, Objects.size() + 1, 1);

    Objects.push_back(obj1s);

    //std::cout << "last:" << &Objects[0] << "\n";
    

}

void MainLoop::spawnCloth(int Distance, int SizeX, int SizeY, float OffsetX, float OffsetY)
{
    Dots = {};
    Strings = {};
    for (int y = 0; y < SizeY; y++) {
        for (int x = 0; x < SizeX; x++) {
            VerletDot* dot;
            if (y == 0) {
                dot = new VerletDot(x * Distance + OffsetX, y * Distance + OffsetY, y * SizeX + x, 1 - pow(-1, x / 1));
            }
            else {
                dot = new VerletDot(x * Distance + OffsetX, y * Distance + OffsetY, y * SizeX + x);
            }
            Dots.push_back(dot);
        }
    }
    for (int y = 0; y < SizeY; y++) {
        for (int x = 0; x < SizeX-1; x++) {
            VerletString string(Dots[y*SizeX+x], Dots[y * SizeX + x+1]);
            Strings.push_back(string);
        }
    }
    for (int x = 0; x < SizeX; x++) {
        for (int y = 0; y < SizeY-1; y++) {
            
            //std::cout << y * SizeY + x << ", " << y * SizeY + x + SizeX << "\n";
            VerletString string(Dots[y * SizeX + x], Dots[y * SizeX + x + SizeX]);
            Strings.push_back(string);
            
        }
    }
    VerletObject obj1s(Dots, Strings, Objects.size() + 1, 0);

    Objects.push_back(obj1s);

}

//--render--// -> Called by main
void MainLoop::render()
{
    //std::cout << fps << "\n";
    // clear screen
    this->window->clear(sf::Color(60, 60, 60, 255));


    for (VerletObject& it : Objects)
    {
        it.render(this->window);
    }

    // display screen
    this->window->display();
}
