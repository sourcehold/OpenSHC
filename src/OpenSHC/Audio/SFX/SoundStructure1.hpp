/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Audio/SFX/SoundStructure1.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Audio {
    namespace SFX {

#pragma pack(push, 1)
        // SIZE: 0x00000018
        typedef struct SoundStructure1 {

            int volumePercentage; // 0x00000000 length: 4
            int samplePan; // 0x00000004 length: 4
            int scheduledPlayCounter; // 0x00000008 length: 4
            int field3_0xc; // 0x0000000C length: 4
            int baseVolumePercentageUnk; // 0x00000010 length: 4
            pointer* pointerToFilename; // 0x00000014 length: 4

        } SoundStructure1;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(SoundStructure1) == 24, SoundStructure1);
    } // namespace SFX
} // namespace Audio
} // namespace OpenSHC
