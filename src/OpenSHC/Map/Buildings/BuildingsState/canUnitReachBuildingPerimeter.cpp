#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00410440
        undefined4 BuildingsState::canUnitReachBuildingPerimeter(int param_1, int param_2)
        {
            // param_1 is the building, param_2 the unit
            if (param_1 == 0 || param_1 >= 2000) {
                return 0;
            }
            int unitArea
                = (short)DAT_TileMapState::instance.PathConnectionLayer[DAT_UnitsState::instance.units[param_2].tile];
            int buildingHeight
                = DAT_TileMapState::instance.DefaultHeightLayer[this->buildings[param_1].currentTilePositionAdjusted];
            uint size = this->buildings[param_1].widthOrHeight;
            int tileCount = DAT_BuildingDefinedData::instance.BuildingAccessibleTilesCount[size];
            BOOLEnum onlyAssassins = MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::UnitsState_Func::selectionContainsOnlyArabAssassins, DAT_UnitsState::ptr)();
            for (int i = 0; i < tileCount; ++i) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::setupNextCandidateLocationComputeOffsets2, this)(
                    size, 1, i, 0);
                int tile = DAT_ViewportRenderState::instance
                               .translationMatrix[(short)this->buildings[param_1].y + this->DAT_TempYOffset]
                               .addXgetTile
                    + (short)this->buildings[param_1].x + this->DAT_TempXOffset;
                int tileArea = (short)DAT_TileMapState::instance.PathConnectionLayer[tile];
                int tileHeight = DAT_TileMapState::instance.HeightLayer[tile];
                if (DAT_TileMapState::instance.BuildingLayer[tile] != 0) {
                    tileHeight += MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                        DAT_BuildingsState::ptr)((short)DAT_TileMapState::instance.BuildingLayer[tile]);
                }
                if (abs(buildingHeight - tileHeight) >= 16 || tileArea == 0) {
                    continue;
                }
                BOOLEnum reachable;
                if (onlyAssassins == FALSE) {
                    reachable = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                        DAT_PathFindingState::ptr)(DAT_UnitsState::instance.units[param_2].owner, unitArea, tileArea,
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::canAUnitClimb, DAT_UnitsState::ptr)());
                } else {
                    reachable = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::PathFindingState_Func::calculateCanReachUsingCachedAreaLogic,
                        DAT_PathFindingState::ptr)(DAT_UnitsState::instance.units[param_2].tile, tile);
                }
                if (reachable != FALSE) {
                    return 1;
                }
            }
            return 0;
        }

    }
}
}
