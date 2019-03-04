#include <iostream>
#include <SFML/Graphics.hpp>
#include "application.h"

using namespace std;

int main()
{
    sf::RenderWindow window;
    window.create(sf::VideoMode(800, 900), "SFML works!");
    Application app(window);
    app.mainloop();

    return 0;
}
