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
        if (DAT_AIVState::instance.mapExtraInfo.totalWoodAvailable <= 0) {
            return 0;
        }
        int aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (aiType == AITA_NULL) {
            return 0;
        }
        aiType -= 1;
        // AICSpecification const* spec = &this->DAT_AICArray[aiType];
        if ((int)this->DAT_AICArray[aiType].populationPerWoodcutter <= 0) {
            return 0;
        }
        int iVar3 = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::countBuildingsForPlayer,
            DAT_BuildingsState::ptr)(playerID, Map::Buildings::BT_WOODCUTTERSHUT, 1);
        if (iVar3 <= 0) {
            iVar3 = 1;
        } else {
            if (iVar3 >= (int)this->DAT_AICArray[aiType].maxWoodcutters) {
                return 0;
            }
            if ((6 <= iVar3) && (DAT_AIVState::instance.mapExtraInfo.totalWoodAvailable <= 90)) {
                return 0;
            }
            if ((3 <= iVar3) && (DAT_AIVState::instance.mapExtraInfo.totalWoodAvailable <= 30)) {
                return 0;
            }
        }
        return DAT_GameState::instance.playerDataArray[playerID].currentPopulation / iVar3
            >= (int)this->DAT_AICArray[aiType].populationPerWoodcutter;
    }
}
}
