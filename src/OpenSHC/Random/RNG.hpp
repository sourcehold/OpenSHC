/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Random/RNG.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Random {

#pragma pack(push, 1)

    // SIZE: 0x00009C50
    class RNG {
    public:
        short currentNumber1; // 0x00000000 length: 2
        short currentNumber2; // 0x00000002 length: 2
        int seed; // 0x00000004 length: 4
        short randomNumbers[20000]; // 0x00000008 length: 40000
        int index2; // 0x00009C48 length: 4
        int index1; // 0x00009C4C length: 4

    private:
        RNG(RNG const&);
        void operator=(RNG const&);

        RNG();
        ~RNG();

    public:
        // Constructor
        RNG* Constructor_RNG();

        void setTimeBasedSeed();

        void populateRNG1040();

        void nextRandomNumber2();

        void nextRandomNumber1();
    };

    static_assert_cpp98_obj(sizeof(RNG) == 40016, RNG);

#pragma pack(pop)

    MACRO_STRUCT_RESOLVER(RNG, false, Address::SHC_3BB0A8C1_0x01A279C0) pDAT_RNG;

} // namespace Random
} // namespace OpenSHC
