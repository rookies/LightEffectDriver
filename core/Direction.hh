//
// Created by robert on 28.10.18.
//

#ifndef CORE_LIGHTEFFECTDIRECTION_HH
#define CORE_LIGHTEFFECTDIRECTION_HH


namespace LightEffectDriver {
    /**
     * Available directions for ordered selection.
     */
    enum Direction {
        /** Counting light index up. */
        UP,
        /** Counting light index down. */
        DOWN,
        /** Alternate between counting up and down. */
        UPDOWN
    };
}


#endif //CORE_LIGHTEFFECTDIRECTION_HH
