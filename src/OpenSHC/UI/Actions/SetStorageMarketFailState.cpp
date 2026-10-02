#include "../Actions.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Map::Buildings::BuildingType;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00465DB0
    void Actions::SetStorageMarketFailState(int state, ResourceType resource)
    {
        BuildingType _building;
        DWORD _currentTime;
        int _playerSlot;
        _building
            = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingStorageTypeForResourceType,
                DAT_BuildingsState::ptr)(resource);
        _playerSlot = DAT_GameSynchronyState::instance.currentPlayerSlotID;
        _currentTime = timeGetTime();
        DAT_GameState::instance.playerDataArray[_playerSlot].timeStorageMarketFailState = _currentTime;
        if (state == 3) {
            /*
              missing stock building
             */
            if (_building == OpenSHC::Map::Buildings::BT_STOCKPILE) {
                DAT_GameState::instance.playerDataArray[_playerSlot].storageMarketFailState = 6;
            }
            if (_building == OpenSHC::Map::Buildings::BT_GRANARY) {
                DAT_GameState::instance.playerDataArray[_playerSlot].storageMarketFailState = 5;
            }
            if (_building == OpenSHC::Map::Buildings::BT_ARMORY) {
                DAT_GameState::instance.playerDataArray[_playerSlot].storageMarketFailState = 7;
            }
        } else if (state == 4) {
            /*
              not enough space
             */
            if (_building == OpenSHC::Map::Buildings::BT_STOCKPILE) {
                DAT_GameState::instance.playerDataArray[_playerSlot].storageMarketFailState = 9;
            }
            if (_building == OpenSHC::Map::Buildings::BT_GRANARY) {
                DAT_GameState::instance.playerDataArray[_playerSlot].storageMarketFailState = 8;
            }
            if (_building == OpenSHC::Map::Buildings::BT_ARMORY) {
                DAT_GameState::instance.playerDataArray[_playerSlot].storageMarketFailState = 10;
            }
        } else {
            /*
              Generally used for "2" meaning not enough goods to sell
             */
            DAT_GameState::instance.playerDataArray[_playerSlot].storageMarketFailState = state;
        }
    }

}
}
