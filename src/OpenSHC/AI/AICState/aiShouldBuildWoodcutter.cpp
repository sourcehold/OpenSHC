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
    BOOLEnum AICState::aiShouldBuildWoodcutter(int playerID)
    {
        if (DAT_AIVState::instance.mapExtraInfo.totalWoodAvailable <= 0) {
            return FALSE;
        }
        int aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (aiType == AITA_NULL) {
            return FALSE;
        }
        aiType -= 1;
        // AICSpecification const* spec = &this->aics[aiType];
        if ((int)this->aics[aiType].populationPerWoodcutter <= 0) {
            return FALSE;
        }
        int iVar3 = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::countBuildingsForPlayer,
            DAT_BuildingsState::ptr)(playerID, Map::Buildings::BT_WOODCUTTERSHUT, 1);
        if (iVar3 <= 0) {
            iVar3 = 1;
        } else {
            if (iVar3 >= (int)this->aics[aiType].maxWoodcutters) {
                return FALSE;
            }
            if ((6 <= iVar3) && (DAT_AIVState::instance.mapExtraInfo.totalWoodAvailable <= 90)) {
                return FALSE;
            }
            if ((3 <= iVar3) && (DAT_AIVState::instance.mapExtraInfo.totalWoodAvailable <= 30)) {
                return FALSE;
            }
        }
        return DAT_GameState::instance.playerDataArray[playerID].currentPopulation / iVar3
            >= (int)this->aics[aiType].populationPerWoodcutter;
    }
}
}
