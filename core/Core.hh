//
// Created by robert on 28.10.18.
//

#ifndef CORE_LIGHTEFFECTDRIVERCORE_HH
#define CORE_LIGHTEFFECTDRIVERCORE_HH


#include <functional>
#include "Effect.hh"
#include "Order.hh"
#include "Direction.hh"
#include "Curve.hh"

namespace LightEffectDriver {
    /**
     * This class provides the core functionality.
     */
    class Core {
    public:
        Core() = delete;

        /**
         * @param number The number of lights to control.
         * @param callback The function that should be called to update the brightness of a light. First param is
         * the index of the light, second param the brightness value.
         */
        Core(unsigned int number, std::function<void(unsigned int, uint8_t)> callback);

        /**
         * Does the animation, should be called as often as possible in the main loop of the program.
         */
        void run();

        /**
         * Calculates the animation parameters, has to be called after a change of number, effect, direction or speed.
         */
        void update();

        /**
         * The number of lights to control.
         */
        unsigned int number;

        /**
         * The function that should be called to update the brightness of a light. First param is the index of the
         * light, second param the brightness value.
         */
        std::function<void(unsigned int, uint8_t)> callback;

        /**
         * The effect type.
         */
        Effect effect = SWITCH;

        /**
         * The effect order.
         */
        Order order = ORDERED;

        /**
         * The effect direction.
         */
        Direction direction = UP;

        /**
         * The brightness curve.
         */
        Curve curve = Curve::Lin;

        /**
         * The effect speed.
         */
        unsigned int speed = 100;
    };
}


#endif //CORE_LIGHTEFFECTDRIVERCORE_HH
