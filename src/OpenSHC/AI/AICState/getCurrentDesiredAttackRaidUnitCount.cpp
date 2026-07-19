#include "OpenSHC/AI/AICState.hpp"

#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/TrailType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D12A0
    int AICState::getCurrentDesiredAttackRaidUnitCount(int aiType, int playerID)
    {
        if (((DAT_GameCore::instance.gameMode_2 == Game::GM_SKIRMISH_AND_MULTIPLAYER) &&
            (DAT_GameCore::instance.isSkirmishTrail == TRUE)) && (DAT_GameCore::instance.currentTrailType == Game::TT_EXTREME)) {
            return (int)((DAT_GameState::instance.playerDataArray[playerID].currentAttackRaidParameter + this->DAT_AICArray[aiType].RaidUnitsBase) * 4) / 3;
        }
        return DAT_GameState::instance.playerDataArray[playerID].currentAttackRaidParameter + this->DAT_AICArray[aiType].RaidUnitsBase;
    }
}
}
