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
        int _hovelID;
        if ((((DAT_GameState::instance.playerDataArray[playerID].aiType != AITA_NULL)
                 && (_hovelID = DAT_GameState::instance.playerDataArray[playerID].currentPopulation,
                     _hovelID <= DAT_GameState::instance.playerDataArray[playerID].populationCap))
                && (8 < _hovelID))
            && (0x14 < DAT_GameState::instance.playerDataArray[playerID].averagePopulationGrowthUnk)) {
            _hovelID = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::findFirstBuildingIDForPlayerAndType,
                DAT_BuildingsState::ptr)(playerID, Map::Buildings::BT_HOVEL);
            if (_hovelID == 0) {
                return FALSE;
            }
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::giveBackResourceForDestroyedBuilding,
                DAT_BuildingsState::ptr)(_hovelID, playerID, 0x32);
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(_hovelID);
            return TRUE;
        }
        return FALSE;
    }
}
}
