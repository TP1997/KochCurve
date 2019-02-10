#include "application.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <stdlib.h>

Application::Application(sf::RenderWindow &rw): window(rw), maxGenerations(6){

}
Application::~Application(){

}
void Application::mainloop(){
    window.setFramerateLimit(60);
    window.clear();
    window.setVisible(false);
    bool exit=false;
    while(!exit){
        std::cout << "Commands:" << std::endl;
        std::cout << "1 -> [exit]" << std::endl;
        std::cout << "2 -> [run]" << std::endl;

        std::string command;
        std::cin >> command;
        switch(castInteger(command)){
            case(1):
                exit=true;
                break;
            case(2):
                selectVisualization();
                break;
            default:
               std::cout << "Undefined command" << std::endl;
               std::cin.clear();
               std::cin.ignore(INT_MAX, '\n');
        }
    }

}
int Application::readCommand(){
    try{
        int value=readInteger();
        return value;
    }
    catch(const char* msg){
        std::cout << msg << std::endl;
        return 0;
    }
}
int Application::readInteger()throw(const char*){
    int value;
    if(!(std::cin >> value)){
        std::cin.clear();
        std::cin.ignore();
        throw "Type integer commands!";
    }
    return value;
}
int Application::castInteger(std::string value){
    return atoi(value.c_str());
}
void Application::selectVisualization(){
    std::cout << "Select visualization:" << std::endl;
    std::cout << "1 -> [Koch curve]" << std::endl;
    std::cout << "2 -> [Sierpinski triangle]" << std::endl;

    std::string command;
    std::cin >> command;
    switch(castInteger(command)){
        case(1):
            maxGenerations=6;
            lines.push_back(new kochLine(50.0, 250.0, 750.0, 250.0));
            lines.push_back(new kochLine(750.0, 250.0, 400.0, 856.0));
            lines.push_back(new kochLine(400.0, 856.0, 50.0, 250.0));
            window.setVisible(true);
            animate(lines, 0);
            break;
        case(2):
            maxGenerations=10;
            lines.push_back(new sierpinskiLine(50.0, 850.0, 750.0, 850.0));
            window.setVisible(true);
            animate(lines, 0);
            break;
        default:
            std::cout << "Undefined command" << std::endl;
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
    }
    window.setVisible(false);
}
void Application::animate(std::vector<Line*> &oldGen, int currGen){
    handleWinEvents();
    window.clear();
    window.display();
    std::cout << "generation: " << currGen+1 << " maxGeneretion: " << maxGenerations << std::endl;
    if(currGen<maxGenerations){
        std::vector<Line*> newGen=createNewGeneration(oldGen, currGen);
        for(unsigned int plottedLines=0; plottedLines<newGen.size(); plottedLines++){
            float currLength=newGen[plottedLines]->length;
            float currSubLength=DRAWSPEED;
            do{
                handleWinEvents();
                window.clear();
                for(Line *line : oldGen){
                    line->draw(window, sf::Color::Blue);
                }
                for(unsigned int n=0; n<plottedLines; n++){
                    newGen[n]->draw(window);
                }
                newGen[plottedLines]->drawPart(window, currSubLength);
                currSubLength+=DRAWSPEED;
                if((currSubLength/currLength)<1){
                    window.display();
                }

            }while((currSubLength/currLength)<1);

            int intRatio=(int)(currSubLength/currLength);
            for(int n=0; n<intRatio && (plottedLines+n)<newGen.size(); n++){
                newGen[plottedLines+n]->draw(window);
            }
            window.display();
            plottedLines+=intRatio-1;
        }

        for(Line *line : oldGen){
            delete line;
        }
        oldGen.clear();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        animate(newGen, currGen+1);
    }

}
void Application::handleWinEvents(){
    sf::Event event;
    while(window.pollEvent(event)){
        if(event.type==sf::Event::Closed){
            window.close();
            exit(0);
        }

    }
}

//*************************************************
std::vector<Line*> createNewGeneration(std::vector<Line*> &oldGen, int gen){
    std::vector<Line*> newGen;
    int n=(0==(gen&1));;
    for(Line *line : oldGen){
        bool opposite=(0==(n&1));
        std::vector<Line*> temp=line->generate(opposite);
        newGen.insert(newGen.end(), temp.begin(), temp.end());
        n++;
    }
    return newGen;
}
