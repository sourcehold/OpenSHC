#include "../Audio.func.hpp"

#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentPlayerRanking.hpp"
#include "OpenSHC/Globals/DAT_CurrentPlayerUnitLosses.hpp"
#include "OpenSHC/Globals/DAT_CurrentPlayerUnitLossesHistory.hpp"
#include "OpenSHC/Globals/DAT_DestroyedBuildingsCountHistory.hpp"
#include "OpenSHC/Globals/DAT_IsKeepEnclosed.hpp"
#include "OpenSHC/Globals/DAT_KeepEnclosementCooldown.hpp"
#include "OpenSHC/Globals/DAT_TotalUnitValueLossesEnemyHistory.hpp"
#include "OpenSHC/Globals/DAT_UnitValueLossesPerEnemyPlayer.hpp"
#include "OpenSHC/Globals/DWORD_KeepEnclosementTimer.hpp"
#include "OpenSHC/Globals/DWORD_LatestPLayerStatusMessageTime.hpp"
#include "OpenSHC/Globals/Dat_UnitValueLossesHistoryPerEnemyPlayer.hpp"
#include "OpenSHC/Globals/INT_00b98484.hpp"
#include "OpenSHC/Globals/INT_00b98664.hpp"
#include "OpenSHC/Globals/INT_00b98698.hpp"

namespace OpenSHC {
namespace Audio {

    // FUNCTION: STRONGHOLDCRUSADER 0x0044A720
    void __cdecl ResetGreatestLordGenieSpeechState()
    {
        DAT_CurrentPlayerRanking::instance = -1;
        INT_00b98698::instance = -1;
        INT_00b98484::instance = -1;
        DAT_IsKeepEnclosed::instance = 0;

        unsigned int currentTime = timeGetTime();
        DWORD_KeepEnclosementTimer::instance = currentTime;
        DWORD_LatestPLayerStatusMessageTime::instance = currentTime;
        DAT_KeepEnclosementCooldown::instance = currentTime;

        DAT_CurrentPlayerUnitLosses::instance = 0;
        for (int i = 0; i < 9; i++) {
            DAT_UnitValueLossesPerEnemyPlayer::instance[i] = 0;
        }
        memset(DAT_CurrentPlayerUnitLossesHistory::instance, 0, sizeof(DAT_CurrentPlayerUnitLossesHistory::instance));
        memset(
            DAT_TotalUnitValueLossesEnemyHistory::instance, 0, sizeof(DAT_TotalUnitValueLossesEnemyHistory::instance));
        MACRO_CALL(OS_Func::_memset)(Dat_UnitValueLossesHistoryPerEnemyPlayer::ptr, 0,
            sizeof(Dat_UnitValueLossesHistoryPerEnemyPlayer::instance));

        INT_00b98664::instance = 1;

        memset(DAT_DestroyedBuildingsCountHistory::instance, 0, sizeof(DAT_DestroyedBuildingsCountHistory::instance));
    }

}
}
