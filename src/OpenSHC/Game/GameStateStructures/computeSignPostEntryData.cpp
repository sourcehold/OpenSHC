#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Game::GameMode;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00456810
    void GameStateStructures::computeSignPostEntryData()
    {
        if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
            return;
        }
        for (int signpostID = 0; signpostID < 8; signpostID++) {
            if ((this->mapAndTime.signpostEntryData[signpostID].x != 0)
                || (this->mapAndTime.signpostEntryData[signpostID].y != 0)) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findSuitableSpawnLocationUnk,
                    DAT_PathFindingState::ptr)(this->mapAndTime.signpostEntryData[signpostID].x,
                    this->mapAndTime.signpostEntryData[signpostID].y, -1, -1, 1000000, 0);
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::storeDestinationOptionsUnk,
                    DAT_PathFindingState::ptr)(signpostID);
            }
        }
    }
}
}
