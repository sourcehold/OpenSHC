/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Audio/mss/UnkSoundFlagsAndLoopCount.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Audio {
    namespace mss {

#pragma pack(push, 1)
        // SIZE: 0x00000004
        typedef struct UnkSoundFlagsAndLoopCount {

            ushort loopCount; // 0x00000000 length: 2
            undefined1 padding_0x2[1]; // 0x00000002 length: 1
            byte flagsUnk; // 0x00000003 length: 1

        } UnkSoundFlagsAndLoopCount;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(UnkSoundFlagsAndLoopCount) == 4, UnkSoundFlagsAndLoopCount);
    } // namespace mss
} // namespace Audio
} // namespace OpenSHC
