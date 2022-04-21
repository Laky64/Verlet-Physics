#include <iostream>
#include "../include/MainLoop.h"

int main()
{
    // init GameEngine
    MainLoop mainLoop;

    // Game loop
    while (mainLoop.running())
    {
        // Update
        mainLoop.update();

        // Render
        mainLoop.render();
    }

    return 0;
}
