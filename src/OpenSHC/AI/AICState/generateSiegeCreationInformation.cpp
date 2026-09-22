#include "../AICState.func.hpp"

#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CC420
    void AICState::generateSiegeCreationInformation(int playerID, int buildingID, int unitID)
    {
        if (DAT_GameState::instance.playerDataArray[playerID].aiType == OpenSHC::AI::AIT_NULL)
            return;
        if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY)
            return;

        int siegeIndex;
        if (DAT_UnitsState::instance.units[unitID].unitType == OpenSHC::Map::Units::UT_S_TREBUCHET)
            siegeIndex = 2;
        else if (DAT_UnitsState::instance.units[unitID].unitType == OpenSHC::Map::Units::UT_S_FBALLISTA)
            siegeIndex = 3;
        else
            return;

        int slot = DAT_SkirmishDefinedData::instance.SiegeEngineMetaInfoArray[siegeIndex].slot;
        int locationCount = DAT_GameState::instance.playerDataArray[playerID].aivUnitLocationSlotLocationCount[slot];
        int i;
        for (i = 0; i < locationCount; i++) {
            if (DAT_GameState::instance.playerDataArray[playerID].aivUnitLocationSlots[slot][i] > 0
                && DAT_GameState::instance.playerDataArray[playerID].aiSiegeCreationInformation[siegeIndex][i].buildingID
                    == buildingID)
                break;
        }
        if (i >= locationCount)
            return;

        DAT_GameState::instance.playerDataArray[playerID].aiSiegeCreationInformation[siegeIndex][i].unitID = unitID;
        DAT_GameState::instance.playerDataArray[playerID].aiSiegeCreationInformation[siegeIndex][i].uid
            = DAT_UnitsState::instance.units[unitID].uid;
        DAT_GameState::instance.playerDataArray[playerID].aiSiegeCreationInformation[siegeIndex][i].buildingID = 0;
    }

}
}
