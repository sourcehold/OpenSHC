
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00511850
    void TileMapState::updateGameRelatedValue()
    {
        if (DAT_GameState::instance.mapAndTime.gameEventRelatedCountdown == 0) {
            return;
        }

        if (DAT_GameState::instance.mapAndTime.gameEventRelatedCountdown == 0x28) {
            this->field187_0x554a10 = -1;
        }
        DAT_GameState::instance.mapAndTime.gameEventRelatedCountdown
            = DAT_GameState::instance.mapAndTime.gameEventRelatedCountdown - 1;
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setSignpostDistanceForCampaignMission, this)();
        int signpostDistance = ((0x28 - DAT_GameState::instance.mapAndTime.gameEventRelatedCountdown)
                                   * DAT_GameState::instance.mapAndTime.unk_signpostDistance)
            / 0x28;
        if (signpostDistance == this->field187_0x554a10) {
            return;
        }

        this->field187_0x554a10 = signpostDistance;
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::pathfindingUpdate_0x4a8ab0,
            DAT_PathFindingState::ptr)(signpostDistance);
    }

}
}
