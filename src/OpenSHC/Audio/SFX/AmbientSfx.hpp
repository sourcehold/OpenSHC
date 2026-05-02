/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Audio/SFX/AmbientSfx.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Audio {
    namespace SFX {

#pragma pack(push, 1)
        // SIZE: 0x00000048
        typedef struct AmbientSfx {

            int field0_0x0; // 0x00000000 length: 4
            char* ambientWavs_0x8[8]; // 0x00000004 length: 32
            int volumeUnk_0x28[8]; // 0x00000024 length: 32
            int field3_0x44; // 0x00000044 length: 4

        } AmbientSfx;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(AmbientSfx) == 72, AmbientSfx);
    } // namespace SFX
} // namespace Audio
} // namespace OpenSHC
