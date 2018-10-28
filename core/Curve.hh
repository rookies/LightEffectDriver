//
// Created by robert on 28.10.18.
//

#ifndef CORE_LIGHTEFFECTCURVE_HH
#define CORE_LIGHTEFFECTCURVE_HH


#include <cstdint>

namespace LightEffectDriver {
    /**
     * Available brightness modifier curves.
    */
    class Curve {
    public:
        /**
         * Maps a value according to the selected curve.
         *
         * @param v The input value.
         * @return The mapped value.
         */
        inline uint8_t map(uint8_t v) const {
            switch (type) {
                case LIN:
                    return v;
                case LIN_INV:
                    return (uint8_t)255 - v;
                case EXP:
                    return expTable[v];
                case EXP_INV:
                    return expTable[(uint8_t)255 - v];
                default:
                    return 0;
            }
        }

        /** No modification, fading from dark to bright linearly. */
        static const Curve Lin;
        /** Fading from bright to dark linearly. */
        static const Curve LinInv;
        /** Fading from dark to bright exponentially. */
        static const Curve Exp;
        /** Fading from bright to dark exponentially. */
        static const Curve ExpInv;

    private:
        /**
         * The curve type.
         */
        enum Type {
            /** No modification, fading from dark to bright linearly. */
            LIN,
            /** Fading from bright to dark linearly. */
            LIN_INV,
            /** Fading from dark to bright exponentially. */
            EXP,
            /** Fading from bright to dark exponentially. */
            EXP_INV
        };
        Type type;

        explicit Curve(Type type) noexcept : type{type} {}

        /**
         * A pre-computed table of function values for
         *   f(x) = a * e^(x/b) with a = f(0) and b = 255/ln(255/a)
         *
         * Generated with python:
         *   import math
         *   for i in range(256):
         *     print("%3d" % int(0.99*math.exp(i/255*math.log(255/0.99))), end=", ")
        */
        static constexpr uint8_t expTable[256] = {
              0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
              1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
              1,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,
              2,   2,   2,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,
              3,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   5,   5,   5,   5,   5,
              5,   5,   5,   6,   6,   6,   6,   6,   6,   6,   7,   7,   7,   7,   7,   7,
              8,   8,   8,   8,   8,   8,   9,   9,   9,   9,   9,  10,  10,  10,  10,  11,
             11,  11,  11,  12,  12,  12,  12,  13,  13,  13,  14,  14,  14,  15,  15,  15,
             16,  16,  16,  17,  17,  17,  18,  18,  19,  19,  19,  20,  20,  21,  21,  22,
             22,  23,  23,  24,  24,  25,  25,  26,  27,  27,  28,  28,  29,  30,  30,  31,
             32,  32,  33,  34,  35,  35,  36,  37,  38,  39,  40,  40,  41,  42,  43,  44,
             45,  46,  47,  48,  49,  50,  52,  53,  54,  55,  56,  58,  59,  60,  61,  63,
             64,  66,  67,  69,  70,  72,  73,  75,  77,  78,  80,  82,  84,  85,  87,  89,
             91,  93,  95,  97,  99, 102, 104, 106, 109, 111, 113, 116, 119, 121, 124, 127,
            129, 132, 135, 138, 141, 144, 147, 151, 154, 157, 161, 164, 168, 172, 176, 179,
            183, 188, 192, 196, 200, 205, 209, 214, 218, 223, 228, 233, 238, 244, 249, 255
        }; /* TODO: PROGMEM */
    };
}


#endif //CORE_LIGHTEFFECTCURVE_HH
