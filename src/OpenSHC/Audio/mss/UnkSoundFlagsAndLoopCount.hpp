/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Audio/MSS/UnkSoundFlagsAndLoopCount.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Audio {
    namespace MSS {

#pragma pack(push, 1)
        // SIZE: 0x00000004
        typedef struct UnkSoundFlagsAndLoopCount {

            unsigned int loopCount : 16;
            int reserved : 13;
            int unknownFlag1 : 1;
            int unknownFlag2 : 1;
            int uninterruptable : 1;

        } UnkSoundFlagsAndLoopCount;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(UnkSoundFlagsAndLoopCount) == 4, UnkSoundFlagsAndLoopCount);
    } // namespace MSS
} // namespace Audio
} // namespace OpenSHC
