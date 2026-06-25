/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Audio/MSS/SoundFlagsAndLoopCountBitwiseFlagEnum.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Audio {
    namespace MSS {
        typedef enum SoundFlagsAndLoopCountBitwiseFlagEnum {

            FLAG_SOUND_LOOP_COUNT_FIELD = 0x0000FFFF, // 0x0000FFFF
            FLAG_SOUND_UNKNOWN_FLAG_1 = 0x20000000, // 0x20000000
            FLAG_SOUND_UNKNOWN_FLAG_2 = 0x40000000, // 0x40000000
            FLAG_SOUND_UNINTERRUPTABLE = 0x80000000 // 0x80000000

        } SoundFlagsAndLoopCountBitwiseFlagEnum;

        static_assert_cpp98_obj(
            sizeof(SoundFlagsAndLoopCountBitwiseFlagEnum) == 4, SoundFlagsAndLoopCountBitwiseFlagEnum);
    } // namespace MSS
} // namespace Audio
} // namespace OpenSHC
