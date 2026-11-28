#include "../../Audio.func.hpp"

#include "OpenSHC/Audio/SFX.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Audio {

    /*
      variable _playerPointsArray made by gynt   decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0044B680
    int SFX::ComputePlayerRanking(int playerID)
    {
        int deadPlayers[10];
        int playerPoints[10][2];
        for (int i = 0; i < 10; i++) {
            playerPoints[i][0] = 0;
        }
        int count = 0;
        for (int player = 1; player < 9; player++) {
            if (DAT_GameSynchronyState::instance.finalResults.active[player] == 0) {
                continue;
            }
            playerPoints[count][0] = player;
            if (!MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(player)) {
                if (player == playerID) {
                    return 0;
                }
                deadPlayers[player] = 1;
                playerPoints[count][1] = 0;
            } else {
                playerPoints[count][1] = MACRO_CALL(Audio::SFX_Func::ComputePlayerPoints1)(player);
            }
            count = count + 1;
        }
        int highestPoints;
        for (int rank = 0; rank < count; rank++) {
            int highestIndex = -1;
            for (int i = 0; i < count; i++) {
                if (playerPoints[i][0] != 0 && (highestIndex == -1 || playerPoints[i][1] > highestPoints)) {
                    highestPoints = playerPoints[i][1];
                    highestIndex = i;
                }
            }
            if (highestIndex < 0) {
                return 0;
            }
            if (playerPoints[highestIndex][0] == playerID) {
                return rank + 1;
            }
            playerPoints[highestIndex][0] = 0;
        }
        return 0;
    }

}
}
