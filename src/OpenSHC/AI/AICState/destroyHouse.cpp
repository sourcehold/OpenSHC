#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/AI/AITypeA.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CB810
    BOOLEnum AICState::destroyHouse(int playerID)
    {
        if (DAT_GameState::instance.playerDataArray[playerID].aiType == AITA_NULL)
            return FALSE;
        if (DAT_GameState::instance.playerDataArray[playerID].currentPopulation
            > DAT_GameState::instance.playerDataArray[playerID].populationCap)
            return FALSE;
        if (DAT_GameState::instance.playerDataArray[playerID].currentPopulation <= 8)
            return FALSE;
        if (DAT_GameState::instance.playerDataArray[playerID].averagePopulationGrowthUnk <= 20)
            return FALSE;

        int hovelID = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::findFirstBuildingIDForPlayerAndType,
            DAT_BuildingsState::ptr)(playerID, Map::Buildings::BT_HOVEL);
        if (hovelID == 0)
            return FALSE;

        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::giveBackResourceForDestroyedBuilding,
            DAT_BuildingsState::ptr)(hovelID, playerID, 50);
        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(hovelID);
        return TRUE;
    }
}
}
