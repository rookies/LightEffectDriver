//
// Created by robert on 28.10.18.
//

#include "Core.hh"

namespace LightEffectDriver {
    Core::Core(unsigned int number, std::function<void(unsigned int, unsigned int)> callback) :
        number{number}, callback{std::move(callback)} {}

    void Core::update() {
        /* TODO */
    }

    void Core::setLightNumber(unsigned int number) {
        this->number = number;
    }

    void Core::setCallback(std::function<void(unsigned int, unsigned int)> callback) {
        this->callback = std::move(callback);
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