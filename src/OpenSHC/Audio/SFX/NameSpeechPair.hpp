/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Audio/SFX/NameSpeechPair.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Audio {
    namespace SFX {

#pragma pack(push, 1)
        // SIZE: 0x000007D0
        typedef struct NameSpeechPair {

            char name[1000]; // 0x00000000 length: 1000
            char source[1000]; // 0x000003E8 length: 1000

        } NameSpeechPair;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(NameSpeechPair) == 2000, NameSpeechPair);
    } // namespace SFX
} // namespace Audio
} // namespace OpenSHC
