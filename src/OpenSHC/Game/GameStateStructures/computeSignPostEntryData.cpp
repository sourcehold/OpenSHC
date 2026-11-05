#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x00456810
    void GameStateStructures::computeSignPostEntryData()
    {
        if (DAT_GameSynchronyState::instance.currentGameMode != GM_SOLITARY) {
            return;
        }
        for (int signpostID = 0; signpostID < 8; ++signpostID) {
            if (this->mapAndTime.signpostEntryData[signpostID].x != 0
                || this->mapAndTime.signpostEntryData[signpostID].y != 0) {
                MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findSuitableSpawnLocationUnk,
                    DAT_PathFindingState::ptr)(this->mapAndTime.signpostEntryData[signpostID].x,
                    this->mapAndTime.signpostEntryData[signpostID].y, -1, -1, 1000000, 0);
                MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::storeDestinationOptionsUnk,
                    DAT_PathFindingState::ptr)(signpostID);
            }
        }
    }

}
}
