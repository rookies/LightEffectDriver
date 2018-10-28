#include <cstddef>
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Core.hh>
#include "Light.hh"
#include "Simulation.hh"

/**
 * A traffic light fading through.
 */
int example1() {
    Simulation simulation({
        Light(0, 0, sf::Color(255,0,0,0)),
        Light(0, 1, sf::Color(255,255,0,0)),
        Light(0, 2, sf::Color(0,255,0,0))
    });
    if (!simulation.show()) {
        std::cerr << "Showing the simulation failed!" << std::endl;
        return 1;
    }
    sf::Clock clock;
    bool fadingDown = false;
    unsigned long currentLight = 0;
    while (simulation.run()) {
        if (clock.getElapsedTime().asMilliseconds() > 2) {
            auto brightness = simulation.getBrightness(currentLight);
            if (fadingDown) {
                simulation.setBrightness(currentLight, brightness - (sf::Uint8)1);
                if (brightness == 1) {
                    fadingDown = false;
                    currentLight = (currentLight + 1) % simulation.numLights();
                }
            } else {
                simulation.setBrightness(currentLight, brightness + (sf::Uint8)1);
                if (brightness == 254) fadingDown = true;
            }
            clock.restart();
        }
    }
    return 0;
}

/**
 * A 5x7 dot-matrix display showing "HELLO WORLD" letter by letter.
 */
int example2() {
    sf::Color c(0,200,0);
    std::vector<Light> lights;
    for (unsigned int y=0; y < 7; ++y) {
        for (unsigned int x=0; x < 5; ++x) {
            lights.emplace_back(Light(x,y,c));
        }
    }
    char data[][5*7] = {
            {
                1,0,0,0,1,
                1,0,0,0,1,
                1,0,0,0,1,
                1,1,1,1,1,
                1,0,0,0,1,
                1,0,0,0,1,
                1,0,0,0,1
            },
            {
                1,1,1,1,1,
                1,0,0,0,0,
                1,0,0,0,0,
                1,1,1,1,0,
                1,0,0,0,0,
                1,0,0,0,0,
                1,1,1,1,1
            },
            {
                1,0,0,0,0,
                1,0,0,0,0,
                1,0,0,0,0,
                1,0,0,0,0,
                1,0,0,0,0,
                1,0,0,0,0,
                1,1,1,1,1
            },
            {
                1,0,0,0,0,
                1,0,0,0,0,
                1,0,0,0,0,
                1,0,0,0,0,
                1,0,0,0,0,
                1,0,0,0,0,
                1,1,1,1,1
            },
            {
                0,1,1,1,0,
                1,0,0,0,1,
                1,0,0,0,1,
                1,0,0,0,1,
                1,0,0,0,1,
                1,0,0,0,1,
                0,1,1,1,0
            },
            {
                0,0,0,0,0,
                0,0,0,0,0,
                0,0,0,0,0,
                0,0,0,0,0,
                0,0,0,0,0,
                0,0,0,0,0,
                0,0,0,0,0
            },
            {
                1,0,0,0,1,
                1,0,0,0,1,
                1,0,0,0,1,
                1,0,0,0,1,
                1,0,1,0,1,
                1,1,0,1,1,
                1,0,0,0,1
            },
            {
                0,1,1,1,0,
                1,0,0,0,1,
                1,0,0,0,1,
                1,0,0,0,1,
                1,0,0,0,1,
                1,0,0,0,1,
                0,1,1,1,0
            },
            {
                1,1,1,1,0,
                1,0,0,0,1,
                1,0,0,0,1,
                1,0,0,0,1,
                1,1,1,1,0,
                1,0,0,0,1,
                1,0,0,0,1
            },
            {
                1,0,0,0,0,
                1,0,0,0,0,
                1,0,0,0,0,
                1,0,0,0,0,
                1,0,0,0,0,
                1,0,0,0,0,
                1,1,1,1,1
            },
            {
                1,1,1,1,0,
                1,0,0,0,1,
                1,0,0,0,1,
                1,0,0,0,1,
                1,0,0,0,1,
                1,0,0,0,1,
                1,1,1,1,0
            },
            {
                0,0,0,0,0,
                0,0,0,0,0,
                0,0,0,0,0,
                0,0,0,0,0,
                0,0,0,0,0,
                0,0,0,0,0,
                0,0,0,0,0
            }
    };
    Simulation simulation(lights);
    simulation.setGridSize(20, 20);
    simulation.setOutline(0, sf::Color::White);
    simulation.setSpacing(0, 0);
    if (!simulation.show()) {
        std::cerr << "Showing the simulation failed!" << std::endl;
        return 1;
    }
    sf::Clock clock;
    unsigned int position = 0;
    while (simulation.run()) {
        if (clock.getElapsedTime().asMilliseconds() > 1000) {
            for (unsigned long i = 0; i < simulation.numLights(); ++i) {
                if (data[position][i] == 0) {
                    simulation.setBrightness(i, 0);
                } else {
                    simulation.setBrightness(i, 255);
                }
            }
            position = (position + 1) % (sizeof(data)/sizeof(*data));
            clock.restart();
        }
    }
    return 0;
}

/**
 * A traffic light using the LightEffectDriverCore.
 */
int example3() {
    /* Set up simulation: */
    Simulation simulation({
        Light(0, 0, sf::Color(255,0,0,0)),
        Light(0, 1, sf::Color(255,255,0,0)),
        Light(0, 2, sf::Color(0,255,0,0))
    });
    /* Set up driver: */
    LightEffectDriver::Core driver(3, [&simulation](unsigned int idx, uint8_t val) {
        simulation.setBrightness(idx, val);
    });
    /* Show the simulation window: */
    if (!simulation.show()) {
        std::cerr << "Showing the simulation failed!" << std::endl;
        return 1;
    }
    /* Main loop: */
    sf::Clock clock;
    while (simulation.run()) {
        if (clock.getElapsedTime().asMilliseconds() > 2) {
            driver.run();
            clock.restart();
        }
    }
    return 0;
}

int usage(char **argv) {
    std::cerr << "Usage: " << argv[0] << " exampleId" << std::endl;
    std::cerr << "  1) Traffic light" << std::endl;
    std::cerr << "  2) Dot-matrix display" << std::endl;
    std::cerr << "  3) Traffic light with LightEffectDriverCore" << std::endl;
    return 1;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        return usage(argv);
    }
    switch (strtol(argv[1], nullptr, 10)) {
        case 1:
            return example1();
        case 2:
            return example2();
        case 3:
            return example3();
        default:
            return usage(argv);
    }
}