#include "OpenSHC/AI/AICState.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CD110
    void AICState::sendUnitsToCampfire(int tribeID, int playerID)
    {
        if (0 < DAT_GameState::instance.playerDataArray[playerID].campground.id) {
            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::commandUnitsToLocation, DAT_TribesState::ptr)(tribeID, DAT_GameState::instance.playerDataArray[playerID].campground.xEntry, DAT_GameState::instance.playerDataArray[playerID].campground.yEntry, 0);
            DAT_TribesState::instance.tribes[tribeID].unitStance = Map::Units::Behavior::USE_AGGRESSIVE;
        }
    }
}
}
