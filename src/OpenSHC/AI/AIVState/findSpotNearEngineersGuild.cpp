#include "../AIVState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004EFB90
    BOOLEnum AIVState::findSpotNearEngineersGuild(int playerID)
    {
        int const guildID = DAT_GameState::instance.playerDataArray[playerID].engineersGuild.id;
        if (guildID <= 0) {
            return FALSE;
        }
        if (DAT_BuildingsState::instance.buildings[guildID].buildingType != Map::Buildings::BT_ENGINEERSGUILD) {
            return FALSE;
        }
        MACRO_CALL_MEMBER(AIVState_Func::findSuitableGridLocationFittingCriteria, this)(
            (short)DAT_BuildingsState::instance.buildings[guildID].x / 5,
            (short)DAT_BuildingsState::instance.buildings[guildID].y / 5);
        if (this->buildingApproriateGridXPosition == -1) {
            return FALSE;
        }
        ++this->heatMaps[this->buildingApproriateGridXPosition][this->buildingAppropriateGridYPosition].structureCount;
        return TRUE;
    }

}
}
