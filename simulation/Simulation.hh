//
// Created by robert on 28.10.18.
//

#ifndef SIMULATION_SIMULATION_HH
#define SIMULATION_SIMULATION_HH


#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Light.hh"

class Simulation {
public:
    Simulation();
    explicit Simulation(std::vector<Light> lights);
    bool show();
    bool run();
    unsigned long numLights() const;
    sf::Color getColor(unsigned long idx) const;
    void setColor(unsigned long idx, sf::Color color);
    sf::Uint8 getBrightness(unsigned long idx) const;
    void setBrightness(unsigned long idx, sf::Uint8 brightness);
    void setGridSize(unsigned int x, unsigned int y);
    void setBorderSize(unsigned int x, unsigned int y);
    void setSpacing(unsigned int x, unsigned int y);
    void setOutline(unsigned int thickness, sf::Color color);
private:
    void createShapes();
    /* TODO: Add getters for these values. */
    unsigned int gridX = 120;
    unsigned int gridY = 120;
    unsigned int borderX = 10;
    unsigned int borderY = 10;
    unsigned int spacingX = 2;
    unsigned int spacingY = 2;
    unsigned int outlineThickness = 1;
    sf::Color outlineColor = sf::Color::White;
    std::vector<Light> lights;
    sf::RenderWindow window;
    std::vector<sf::CircleShape> shapes;
};


#endif //SIMULATION_SIMULATION_HH
