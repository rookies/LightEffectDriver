//
// Created by robert on 28.10.18.
//

#include "Core.hh"

namespace LightEffectDriver {
    Core::Core(unsigned int number, std::function<void(unsigned int, uint8_t)> callback) :
        number{number}, callback{std::move(callback)} {}

    void Core::run() {
        if (number == 0) return;
        /* TODO: Check change interval. */
        switch (effect) {
            case SWITCH:
                /* TODO */
                break;
            case FADE:
                /* TODO */
                break;
            case FADEOVER:
                /* TODO */
                break;
            default:
                break;
        }
        /* TODO: Update last change. */
    }

    void Core::update() {
        /* TODO */
    }
}