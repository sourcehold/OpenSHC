/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Audio/SFX/UnitSpeechData.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Audio {
    namespace SFX {

#pragma pack(push, 1)
        // SIZE: 0x00000094
        typedef struct UnitSpeechData {

            int unk_1; // 0x00000000 length: 4
            char* filenames[18]; // 0x00000004 length: 72
            int unk_2; // 0x0000004C length: 4
            byte unk_3[68]; // 0x00000050 length: 68

        } UnitSpeechData;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(UnitSpeechData) == 148, UnitSpeechData);
    } // namespace SFX
} // namespace Audio
} // namespace OpenSHC
