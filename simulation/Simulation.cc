//
// Created by robert on 28.10.18.
//

#include <iostream>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/Event.hpp>
#include "Simulation.hh"

Simulation::Simulation() :
    lights{std::vector<Light>()}, shapes{std::vector<sf::CircleShape>()} {}

Simulation::Simulation(std::vector<Light> lights) :
    lights{std::move(lights)}, shapes{std::vector<sf::CircleShape>()} {}

bool Simulation::show() {
    /* Calculate number of lights in X & Y direction: */
    unsigned int numX = 0;
    unsigned int numY = 0;
    for (const auto& l : lights) {
        if (l.x >= numX) {
            numX = l.x + 1;
        }
        if (l.y >= numY) {
            numY = l.y + 1;
        }
    }
    std::cout << "Grid size: " << numX << "x" << numY << std::endl;
    /* Calculate window width & height: */
    unsigned int width = numX * gridX + 2 * borderX + ((numX > 1)?((numX - 1) * spacingX):0);
    unsigned int height = numY * gridY + 2 * borderY  + ((numY > 1)?((numY - 1) * spacingY):0);
    std::cout << "Creating window with size " << width << "x" << height << "..." << std::endl;
    window.create(sf::VideoMode(width, height), "FLOAT");
    if (!window.isOpen()) return false;
    /* Create shapes: */
    createShapes();
    return true;
}

bool Simulation::run() {
    /* Check for events: */
    sf::Event event = sf::Event();
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
    /* Check if window is still open: */
    if (!window.isOpen()) return false;
    /* Draw the window content: */
    window.clear();
    for (const auto& s : shapes) {
        window.draw(s);
    }
    window.display();
    return true;
}

unsigned long Simulation::numLights() const {
    return lights.size();
}

sf::Color Simulation::getColor(unsigned long idx) const {
    return lights.at(idx).color;
}

void Simulation::setColor(unsigned long idx, sf::Color color) {
    lights.at(idx).color = color;
    createShapes();
}

sf::Uint8 Simulation::getBrightness(unsigned long idx) const {
    return lights.at(idx).color.a;
}

void Simulation::setBrightness(unsigned long idx, sf::Uint8 brightness) {
    lights.at(idx).color.a = brightness;
    createShapes();
}

void Simulation::setGridSize(unsigned int x, unsigned int y) {
    if (x == 0) throw std::invalid_argument("x grid size has to be greater than zero.");
    if (y == 0) throw std::invalid_argument("y grid size has to be greater than zero.");
    gridX = x;
    gridY = y;
}

void Simulation::setBorderSize(unsigned int x, unsigned int y) {
    borderX = x;
    borderY = y;
}

void Simulation::setSpacing(unsigned int x, unsigned int y) {
    spacingX = x;
    spacingY = y;
}

void Simulation::setOutline(unsigned int thickness, sf::Color color) {
    outlineThickness = thickness;
    outlineColor = color;
}

void Simulation::createShapes() {
    shapes.clear();
    for (const auto& l : lights) {
        /* Create a new shape: */
        sf::CircleShape shape((float)gridX / 2);
        /* Scale it to the right size: */
        shape.setScale(1, (float)gridY / (float)gridX);
        /* Set the position: */
        unsigned int x = l.x * gridX + borderX + ((l.x > 0)?(l.x * spacingX):0);
        unsigned int y = l.y * gridY + borderY + ((l.y > 0)?(l.y * spacingY):0);
        shape.setPosition(x, y);
        /* Set the color: */
        shape.setFillColor(l.color);
        /* Set the outline thickness & color: */
        shape.setOutlineThickness(outlineThickness);
        shape.setOutlineColor(outlineColor);
        /* Add it to our shape vector: */
        shapes.push_back(std::move(shape));
    }
}