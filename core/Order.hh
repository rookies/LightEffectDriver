//
// Created by robert on 28.10.18.
//

#ifndef CORE_LIGHTEFFECTORDER_HH
#define CORE_LIGHTEFFECTORDER_HH


namespace LightEffectDriver {
    /**
     * Available orders in which the next light is selected.
     */
    enum Order {
        /** Ordered, needs an effect direction. */
        ORDERED,
        /** Randomly, ignores effect direction. */
        RANDOM,
        /** Randomly avoiding the same light getting selected multiple times in a row, ignores effect direction. */
        RANDOM_NOMULT
    };
}


#endif //CORE_LIGHTEFFECTORDER_HH
