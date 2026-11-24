/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Audio/SFX/PlayerRankingEntry.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Audio {
    namespace SFX {

#pragma pack(push, 1)
        // SIZE: 0x00000008
        typedef struct PlayerRankingEntry {

            int playerID; // 0x00000000 length: 4
            int points; // 0x00000004 length: 4

        } PlayerRankingEntry;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(PlayerRankingEntry) == 8, PlayerRankingEntry);
    } // namespace SFX
} // namespace Audio
} // namespace OpenSHC
