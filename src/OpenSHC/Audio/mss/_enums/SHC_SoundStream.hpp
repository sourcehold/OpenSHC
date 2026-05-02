/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Audio/mss/_enums/SHC_SoundStream.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Audio {
    namespace mss {
        namespace _enums {
            typedef enum SHC_SoundStream {

                SND_STR_MUSIC = 0, // 0x00000000
                SND_STR_SFX_1Unk = 1, // 0x00000001
                SND_STR_SFX_2Unk = 2, // 0x00000002
                SND_STR_SPEECH_1 = 3, // 0x00000003
                SND_STR_SPEECH_2 = 4 // 0x00000004

            } SHC_SoundStream;

            static_assert_cpp98_obj(sizeof(SHC_SoundStream) == 4, SHC_SoundStream);
        } // namespace _enums
    } // namespace mss
} // namespace Audio
} // namespace OpenSHC
