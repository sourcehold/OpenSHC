#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040B840
        BOOLEnum BuildingsState::isBuildingPathBlockerOrDamageable(uint param_1, int param_2)
        {
            if (param_1 == 0) {
                return FALSE;
            }
            switch (this->buildings[param_1].buildingType) {
            case BT_GATEHOUSELARGE:
            case BT_GATEHOUSESMALL:
            case BT_TOWER1:
            case BT_TOWER2:
            case BT_TOWER3:
            case BT_TOWER4:
            case BT_TOWER5: {
                int const buildingTile
                    = DAT_ViewportRenderState::instance.translationMatrix[this->buildings[param_1].y + 1].addXgetTile
                    + this->buildings[param_1].x + 1;
                return MACRO_CALL_MEMBER(
                           Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                           DAT_PathFindingState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID,
                           (short)DAT_TileMapState::instance.PathConnectionLayer[param_2],
                           (short)DAT_TileMapState::instance.PathConnectionLayer[buildingTile], 0)
                    == 0;
            }
            default:
                return DAT_BuildingDefinedData::instance.BuildingTypeHasHealth[this->buildings[param_1].buildingType]
                    != 0;
            }
        }

    }
}
}
