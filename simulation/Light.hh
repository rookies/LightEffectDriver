//
// Created by robert on 28.10.18.
//

#ifndef SIMULATION_LIGHT_HH
#define SIMULATION_LIGHT_HH

#include <SFML/Graphics/Color.hpp>

/**
 * Represents a simulated light.
 */
struct Light {
    Light(unsigned int x, unsigned int y, sf::Color color);
    /**
     * Position coordinates.
     */
    unsigned int x;
    unsigned int y;
    sf::Color color;
};


#endif //SIMULATION_LIGHT_HH
