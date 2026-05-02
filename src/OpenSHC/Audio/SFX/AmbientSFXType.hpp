/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Audio/SFX/AmbientSFXType.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Audio {
    namespace SFX {
        typedef enum AmbientSFXType {

            ASFXT_WIND_0 = 0, // 0x00000000
            ASFXT_WIND_1 = 1, // 0x00000001
            ASFXT_UNKNOWN = 2, // 0x00000002
            ASFXT_HEAVY = 3, // 0x00000003
            ASFXT_BATTLE_OR_INTENSE = 4 // 0x00000004

        } AmbientSFXType;

        static_assert_cpp98_obj(sizeof(AmbientSFXType) == 4, AmbientSFXType);
    } // namespace SFX
} // namespace Audio
} // namespace OpenSHC
