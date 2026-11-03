#include "../Actions.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Map::Buildings::BuildingType;

    // FUNCTION: STRONGHOLDCRUSADER 0x00465DB0
    void Actions::SetStorageMarketFailState(int state, ResourceType resource)
    {
        BuildingType const _building
            = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingStorageTypeForResourceType,
                DAT_BuildingsState::ptr)(resource);
        int const _playerSlot = DAT_GameSynchronyState::instance.currentPlayerSlotID;
        DWORD const _currentTime = timeGetTime();
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
