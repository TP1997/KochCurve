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
    /*
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }*/
    return 0;
}
