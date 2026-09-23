#include "../AICState.func.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CF920
    undefined4 AICState::giveSomeRaidCommand(int tribeIndex, int tribeType)
    {
        int owner = DAT_TribesState::instance.tribes[tribeIndex].owner;
        int targetBuildingID = DAT_TribesState::instance.tribes[tribeIndex].targetBuildingID;
        if (tribeType == 186 || tribeType == 18 || tribeType == 14 || tribeType == 13)
            return 0;

        if (targetBuildingID != 0
            && DAT_BuildingsState::instance.buildings[targetBuildingID].uid
                == DAT_TribesState::instance.tribes[tribeIndex].targetBuildingUID
            && DAT_BuildingsState::instance.buildings[targetBuildingID].fireDuration == 0)
            return 1;

        DAT_TribesState::instance.tribes[tribeIndex].targetBuildingID = 0;
        int buildingID
            = MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::chooseRandomBuildingIDFromPlayersArrayOfBuildings, this)(
                DAT_GameState::instance.playerDataArray[owner].attackedPlayerID);
        if (buildingID == 0)
            return 0;

        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::queueDisbandAndAttackCommand4Params,
            DAT_UnitsState::ptr)(tribeIndex, 9, buildingID, DAT_BuildingsState::instance.buildings[buildingID].uid);
        DAT_TribesState::instance.tribes[tribeIndex].targetBuildingUID
            = DAT_BuildingsState::instance.buildings[buildingID].uid;
        DAT_TribesState::instance.tribes[tribeIndex].unitStance = OpenSHC::Map::Units::Behavior::USE_DEFENSIVE;
        DAT_TribesState::instance.tribes[tribeIndex].targetBuildingID = buildingID;
        return 1;
    }

}
}
