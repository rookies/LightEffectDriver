//
// Created by robert on 28.10.18.
//

#include "Core.hh"

namespace LightEffectDriver {
    void Core::update() {

    }

    void Core::setEffect(Effect effect) {
        this->effect = effect;
    }

    void Core::setEffectOrder(Order order) {
        this->order = order;
    }

    void Core::setEffectDirection(Direction direction) {
        this->direction = direction;
    }

    void Core::setEffectCurve(Curve curve) {
        this->curve = curve;
    }
}