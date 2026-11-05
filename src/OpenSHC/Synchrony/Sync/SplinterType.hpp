/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Synchrony/Sync/SplinterType.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Synchrony {
    namespace Sync {
        typedef enum SplinterType {

            ST_CHIMPS = 0, // 0x00000000
            ST_STRUCTURES = 1, // 0x00000001
            ST_VEGETATION = 2, // 0x00000002
            ST_TRIBES = 3, // 0x00000003
            ST_PLAYERS = 4, // 0x00000004
            ST_GAME_ELEMENTS = 5, // 0x00000005
            ST_LAYERS = 6, // 0x00000006
            ST_FLIES = 7, // 0x00000007
            ST_MOATS = 8, // 0x00000008
            ST_TELEPORTS = 9, // 0x00000009
            ST_PITCH_DITCHES = 10, // 0x0000000A
            ST_ZONES = 11 // 0x0000000B

        } SplinterType;

        static_assert_cpp98_obj(sizeof(SplinterType) == 4, SplinterType);
    } // namespace Sync
} // namespace Synchrony
} // namespace OpenSHC
