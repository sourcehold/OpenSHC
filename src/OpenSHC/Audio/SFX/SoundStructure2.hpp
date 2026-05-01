/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Audio/SFX/SoundStructure2.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Audio {
    namespace SFX {

#pragma pack(push, 1)
        // SIZE: 0x00000010
        typedef struct SoundStructure2 {

            int soundID; // 0x00000000 length: 4
            int field1_0x4; // 0x00000004 length: 4
            int variationCount; // 0x00000008 length: 4
            int variationCounter; // 0x0000000C length: 4

        } SoundStructure2;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(SoundStructure2) == 16, SoundStructure2);
    } // namespace SFX
} // namespace Audio
} // namespace OpenSHC
