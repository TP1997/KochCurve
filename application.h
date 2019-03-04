#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "circle.h"
#include "curve.h"
#include <vector>
class Application{
    sf::RenderWindow window;
    int scrW;
    int scrH;
    int rows; int cols;
    float angle;
    int frameRate;
    std::vector<Circle*> circleRow;
    std::vector<Circle*> circleCol;
    Curve ***curves2;

public:
    Application(int rows, int cols);
    ~Application();
    void mainloop();
    void draw();
    void update();

};

#endif // APPLICATION_H_INCLUDED
