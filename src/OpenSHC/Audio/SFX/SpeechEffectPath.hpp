/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Audio/SFX/SpeechEffectPath.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Audio {
    namespace SFX {

#pragma pack(push, 1)
        // SIZE: 0x00000010
        typedef struct SpeechEffectPath {

            undefined4 field0_0x0; // 0x00000000 length: 4
            pointer* europeanSound; // 0x00000004 length: 4
            pointer* arabianSound; // 0x00000008 length: 4
            undefined4 field3_0xc; // 0x0000000C length: 4

        } SpeechEffectPath;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(SpeechEffectPath) == 16, SpeechEffectPath);
    } // namespace SFX
} // namespace Audio
} // namespace OpenSHC
