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
    class Core {
    public:
        Core() = delete;
        explicit Core(unsigned int number, std::function<void(unsigned int, unsigned int)> callback);
        void update();
        void setLightNumber(unsigned int number);
        void setCallback(std::function<void(unsigned int, unsigned int)> callback);
        void setEffect(Effect effect);
        void setEffectOrder(Order order);
        void setEffectDirection(Direction direction);
        void setEffectCurve(Curve curve);
    private:
        unsigned int number;
        std::function<void(unsigned int, unsigned int)> callback;
        Effect effect = SWITCH;
        Order order = ORDERED;
        Direction direction = UP;
        Curve curve = Curve::Lin;
    };
}


#endif //CORE_LIGHTEFFECTDRIVERCORE_HH
