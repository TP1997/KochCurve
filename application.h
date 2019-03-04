#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "Line.h"
#include <vector>
#define DRAWSPEED 10
class Application{
    sf::RenderWindow &window;
    std::vector<Line*> lines;
    int maxGenerations;
    int growRatio;
public:
    Application(sf::RenderWindow &rw);
    ~Application();
    void mainloop();
    void selectVisualization();
    void animate(std::vector<Line*> &oldGen, int currGen, int gRate=0);
    void handleWinEvents();
};

int castInteger(std::string value);
std::vector<Line*> createNewGeneration(std::vector<Line*> &oldGen, int gen);
int startBit(Line *line, int gen, bool sb);

#endif // APPLICATION_H_INCLUDED
