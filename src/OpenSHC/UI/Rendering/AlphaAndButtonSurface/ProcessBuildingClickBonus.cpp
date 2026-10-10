#include "../AlphaAndButtonSurface.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using Map::Buildings::BuildingType;
        using Map::Buildings::BuildingTypeShort;

        // FUNCTION: STRONGHOLDCRUSADER 0x00463270
        void AlphaAndButtonSurface::ProcessBuildingClickBonus(int buildingIndex)
        {
            if (0 < buildingIndex) {
                int _playerIndex = (int)DAT_BuildingsState::instance.buildings[buildingIndex].owner;
                if (DAT_GameState::instance.mapAndTime.playerTeams[_playerIndex]
                        == DAT_GameState::instance.mapAndTime
                            .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    || (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[_playerIndex] == -1
                        && (DAT_GameSynchronyState::instance.currentAIArray[_playerIndex] != 0))) {
                    MACRO_CALL_MEMBER(
                        Map::Buildings::BuildingsState_Func::extendResourceCountdownForPlayerBuildingsOfType,
                        DAT_BuildingsState::ptr)(
                        (Map::Buildings::BuildingType)(int)(short)DAT_BuildingsState::instance.buildings[buildingIndex]
                            .buildingType,
                        1, _playerIndex);
                    BuildingTypeShort _buildingType
                        = DAT_BuildingsState::instance.buildings[buildingIndex].buildingType;
                    if (_buildingType == Map::Buildings::BT_MANORHOUSE || _buildingType == Map::Buildings::BT_STONEKEEP
                        || _buildingType == Map::Buildings::BT_STRONGHOLD
                        || _buildingType == Map::Buildings::BT_CAMPGROUND) {
                        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::displayPopularityAndGoldPopups,
                            DAT_BuildingsState::ptr)(buildingIndex, 0, 0, 0);
                    }
                }
            }
        }

    }
}
}
