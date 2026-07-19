#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/AI/AITypeA.hpp"

#include "OpenSHC/AI/AIVState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_AIVState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CB890
    BOOLEnum AICState::shouldDestroyWoodCutterUnk(int playerID)
    {
        int _hut;
        if (DAT_GameState::instance.playerDataArray[playerID].aiType == AITA_NULL) {
            return FALSE;
        }
        if (DAT_AIVState::instance.mapExtraInfo.totalWoodAvailable < 1) {
            _hut = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::findFirstBuildingIDForPlayerAndType, DAT_BuildingsState::ptr)(playerID, Map::Buildings::BT_WOODCUTTERSHUT);
        }
        else {
            if (DAT_GameState::instance.playerDataArray[playerID].currentResources[2] < 0x15) {
                return FALSE;
            }
            if (DAT_GameState::instance.playerDataArray[playerID].noLabourerBuildingCount < 2) {
                return FALSE;
            }
            if (DAT_GameState::instance.playerDataArray[playerID].someCount10 < 25) {
                return FALSE;
            }
            _hut = DAT_GameState::instance.playerDataArray[playerID].someCount11;
        }
        if (_hut == 0) {
            return FALSE;
        }
        MACRO_CALL_MEMBER(AIVState_Func::set0x13ValueTo10InHeatMap, DAT_AIVState::ptr)((int)(short)DAT_BuildingsState::instance.buildings[_hut].x, (int)(short)DAT_BuildingsState::instance.buildings[_hut].y);
        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::giveBackResourceForDestroyedBuilding, DAT_BuildingsState::ptr)(_hut, playerID, 50);
        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(_hut);
        return TRUE;
    }
}
}
