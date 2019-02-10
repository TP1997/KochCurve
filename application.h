#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "Line.h"
#include <vector>
class Application{
    sf::RenderWindow &window;
    std::vector<Line*> lines;
    int maxGenerations;
public:
    Application(sf::RenderWindow &rw);
    ~Application();
    void mainloop();
    int readCommand();
    int readInteger()throw(const char*);
    int castInteger(std::string value);
    void selectVisualization();
    void animate(std::vector<Line*> &lines, int currGen);
    void handleWinEvents();
};

std::vector<Line*> createNewGeneration(std::vector<Line*> &oldGen, int gen);

#endif // APPLICATION_H_INCLUDED
