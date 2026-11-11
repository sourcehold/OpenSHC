#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00511850
    void TileMapState::updateGameRelatedValue()
    {
        if (DAT_GameState::instance.mapAndTime.gameEventRelatedCountdown == 0) {
            return;
        }

        if (DAT_GameState::instance.mapAndTime.gameEventRelatedCountdown == 40) {
            this->field_0x554a10 = -1;
        }
        DAT_GameState::instance.mapAndTime.gameEventRelatedCountdown -= 1;
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setSignpostDistanceForCampaignMission, this)();
        int signpostDistance = ((40 - DAT_GameState::instance.mapAndTime.gameEventRelatedCountdown)
                                   * DAT_GameState::instance.mapAndTime.unk_signpostDistance)
            / 40;
        if (signpostDistance == this->field_0x554a10) {
            return;
        }

        this->field_0x554a10 = signpostDistance;
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::pathfindingUpdate_0x4a8ab0,
            DAT_PathFindingState::ptr)(signpostDistance);
    }

}
}
