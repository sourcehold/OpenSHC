#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/AI/AITypeA.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_AIVState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CB290
    uint AICState::aiShouldBuildWoodcutter(PlayerID playerID)
    {
        if (DAT_AIVState::instance.mapExtraInfo.totalWoodAvailable < 1) {
            return 0;
        }
        int const aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (aiType == AITA_NULL) {
            return 0;
        }
        AICSpecification const* spec = &this->DAT_AICArray[aiType - 1];
        if ((int)spec->populationPerWoodcutter <= 0) {
            return 0;
        }
        int iVar3 = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::countBuildingsForPlayer,
            DAT_BuildingsState::ptr)(playerID, Map::Buildings::BT_WOODCUTTERSHUT, 1);
        if (iVar3 < 1) {
            iVar3 = 1;
        } else {
            if (iVar3 >= (int)spec->maxWoodcutters) {
                return 0;
            }
            if ((5 < iVar3) && (DAT_AIVState::instance.mapExtraInfo.totalWoodAvailable < 91)) {
                return 0;
            }
            if ((2 < iVar3) && (DAT_AIVState::instance.mapExtraInfo.totalWoodAvailable < 31)) {
                return 0;
            }
        }
        return DAT_GameState::instance.playerDataArray[playerID].currentPopulation / iVar3
            >= (int)spec->populationPerWoodcutter;
    }
}
}
