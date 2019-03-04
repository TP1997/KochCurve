#include "Line.h"
#include <math.h>
#include <chrono>
#include <thread>
#include <iostream>

#define PI 3.14159265358979323846

Line::Line(float sx, float sy, float ex, float ey){
    sp[0]=sx;
    sp[1]=sy;
    ep[0]=ex;
    ep[1]=ey;
    length=sqrt(pow((sp[0]-ep[0]), 2) + pow((sp[1]-ep[1]), 2));
}
Line::~Line(){

}
void Line::draw(sf::RenderWindow &window, sf::Color color){
    sf::Vertex line[]={sf::Vertex(sf::Vector2f(sp[0], sp[1]), color),
                        sf::Vertex(sf::Vector2f(ep[0], ep[1]), color) };
    window.draw(line, 2, sf::Lines);
}
void Line::drawPart(sf::RenderWindow &window, float amount, sf::Color color){
    float ratio=amount/length;
    if(ratio<1){
        float tEndx=(1-ratio)*sp[0]+ratio*ep[0];
        float tEndy=(1-ratio)*sp[1]+ratio*ep[1];
        sf::Vertex subLine[]={sf::Vertex(sf::Vector2f(sp[0], sp[1]), color),
                            sf::Vertex(sf::Vector2f(tEndx, tEndy), color)};
        window.draw(subLine, 2, sf::Lines);
    }
    else{
        //std::cout << ratio << std::endl;
        draw(window, color);
    }
}

/****************** KOCH *************************************/
kochLine::kochLine(float sx, float sy, float ex, float ey): Line(sx, sy, ex, ey){

}
kochLine::~kochLine(){

};
std::vector<Line*> kochLine::generate(bool opposite){
    std::vector<Line*> newLines;
    float b[2];float c[2];float d[2];
    float ratio=1.0/3.0;

    b[0]=(1-ratio)*sp[0]+ratio*ep[0];
    b[1]=(1-ratio)*sp[1]+ratio*ep[1];

    ratio=2.0/3.0;
    d[0]=(1-ratio)*sp[0]+ratio*ep[0];
    d[1]=(1-ratio)*sp[1]+ratio*ep[1];

    c[0]=(d[0]-b[0])*cos(-PI/3)-(d[1]-b[1])*sin(-PI/3)+b[0];
    c[1]=(d[1]-b[1])*cos(-PI/3)+(d[0]-b[0])*sin(-PI/3)+b[1];

    newLines.push_back(new kochLine(sp[0], sp[1], b[0], b[1]));
    newLines.push_back(new kochLine(b[0], b[1], c[0], c[1]));
    newLines.push_back(new kochLine(c[0], c[1], d[0], d[1]));
    newLines.push_back(new kochLine(d[0], d[1], ep[0], ep[1]));

    return newLines;

}
/************** SIERPINSKI ************************************/
sierpinskiLine::sierpinskiLine(float sx, float sy, float ex, float ey): Line(sx, sy, ex, ey){

}
sierpinskiLine::~sierpinskiLine(){

}
std::vector<Line*> sierpinskiLine::generate(bool opposite){
    std::vector<Line*> newLines;
    float b[2];float c[2];float temp[2];
    float ratio=1.0/2.0;
    float angle=(opposite)? PI/3 : -PI/3;
    temp[0]=(1-ratio)*sp[0]+ratio*ep[0];
    temp[1]=(1-ratio)*sp[1]+ratio*ep[1];

    b[0]=(temp[0]-sp[0])*cos(angle)-(temp[1]-sp[1])*sin(angle)+sp[0];
    b[1]=(temp[1]-sp[1])*cos(angle)+(temp[0]-sp[0])*sin(angle)+sp[1];

    c[0]=(ep[0]-temp[0])*cos(angle)-(ep[1]-temp[1])*sin(angle)+temp[0];
    c[1]=(ep[1]-temp[1])*cos(angle)+(ep[0]-temp[0])*sin(angle)+temp[1];

    newLines.push_back(new sierpinskiLine(sp[0], sp[1], b[0], b[1]));
    newLines.push_back(new sierpinskiLine(b[0], b[1], c[0], c[1]));
    newLines.push_back(new sierpinskiLine(c[0], c[1], ep[0], ep[1]));


    return newLines;
}

/************** DRAGON ******************************************/
dragonLine::dragonLine(float sx, float sy, float ex, float ey): Line(sx, sy, ex, ey){

}
dragonLine::~dragonLine(){

}
std::vector<Line*> dragonLine::generate(bool opposite){
    std::vector<Line*> newLines;
    float b[2]; float temp[2];
    float angle=(opposite)? -PI/4 : PI/4;
    float ratio=sqrt(2)/2;

    temp[0]=(1-ratio)*sp[0]+ratio*ep[0];
    temp[1]=(1-ratio)*sp[1]+ratio*ep[1];

    b[0]=(temp[0]-sp[0])*cos(angle)-(temp[1]-sp[1])*sin(angle)+sp[0];
    b[1]=(temp[1]-sp[1])*cos(angle)+(temp[0]-sp[0])*sin(angle)+sp[1];


    newLines.push_back(new dragonLine(sp[0], sp[1], b[0], b[1]));
    newLines.push_back(new dragonLine(b[0], b[1], ep[0], ep[1]));

    return newLines;

}
