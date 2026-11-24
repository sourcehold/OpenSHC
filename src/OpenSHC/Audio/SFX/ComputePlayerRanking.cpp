#include "../SFX.func.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Audio {
    namespace SFX {

        struct PlayerRankingEntry {
            int playerID;
            int points;
        };

        // FUNCTION: STRONGHOLDCRUSADER 0x0044B680
        int __cdecl ComputePlayerRanking(int playerID)
        {
            PlayerRankingEntry entries[10];
            WindowsHelper::Enums::BOOLEnum deadPlayersUnk[10];

            for (int i = 0; i < countof(entries); ++i) {
                entries[i].playerID = 0;
            }

            int count = 0;
            for (int i = 1; i < 9; ++i) {
                if (DAT_GameSynchronyState::instance.finalResults.active[i] == 0) {
                    continue;
                }
                entries[count].playerID = i;
                if (MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(i)
                    == 0) {
                    if (i == playerID) {
                        return 0;
                    }
                    deadPlayersUnk[i] = TRUE;
                    entries[count].points = 0;
                } else {
                    entries[count].points = MACRO_CALL(SFX_Func::ComputePlayerPoints1)(i);
                }
                ++count;
            }

            int bestPoints;
            for (int rank = 0; rank < count; ++rank) {
                int bestIndex = -1;
                for (int i = 0; i < count; ++i) {
                    if (entries[i].playerID != 0 && (bestIndex == -1 || entries[i].points > bestPoints)) {
                        bestPoints = entries[i].points;
                        bestIndex = i;
                    }
                }
                if (bestIndex < 0) {
                    return 0;
                }
                // Clearing playerID before the equality check keeps playerID in ebp (~88.4% norm vs ~52.1% norm)
                int const bestPlayerID = entries[bestIndex].playerID;
                entries[bestIndex].playerID = 0;
                if (bestPlayerID == playerID) {
                    return rank + 1;
                }
            }
            return 0;
        }

    } // namespace SFX
} // namespace Audio
} // namespace OpenSHC
