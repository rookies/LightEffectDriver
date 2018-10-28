//
// Created by robert on 28.10.18.
//

#ifndef CORE_LIGHTEFFECT_HH
#define CORE_LIGHTEFFECT_HH


namespace LightEffectDriver {
    /**
     * Available light effects.
     */
    enum Effect {
        /** Switches through the lights. */
        SWITCH,
        /** Fades the light on, then off, then switches to the next one. */
        FADE,
        /** Fades the next light on while the current one is still fading off. */
        FADEOVER
    };
}


#endif //CORE_LIGHTEFFECT_HH
