//
// Created by robert on 28.10.18.
//

#ifndef CORE_LIGHTEFFECTDRIVERCORE_HH
#define CORE_LIGHTEFFECTDRIVERCORE_HH


#include "Effect.hh"
#include "Order.hh"
#include "Direction.hh"
#include "Curve.hh"

namespace LightEffectDriver {
    class Core {
    public:
        Core() = default;
        void update();
        void setEffect(Effect effect);
        void setEffectOrder(Order order);
        void setEffectDirection(Direction direction);
        void setEffectCurve(Curve curve);
    private:
        Effect effect;
        Order order;
        Direction direction;
        Curve curve = Curve::Lin;
    };
}


#endif //CORE_LIGHTEFFECTDRIVERCORE_HH
