#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00515A20
    void TileMapState::clearBuildingFromTerrain(int buildingID)
    {
        uint x = (short)DAT_BuildingsState::instance.buildings[buildingID].x;
        uint y = (short)DAT_BuildingsState::instance.buildings[buildingID].y;
        uint size = DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight;
        if (DAT_BuildingsState::instance.buildings[buildingID].buildingType != OpenSHC::Map::Buildings::BT_KILLINGPIT) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::validateBuildingPlacementAtTile, this)(
                DAT_BuildingsState::instance.buildings[buildingID].owner, x, y);
            if (this->buildingPlacementFail != FALSE) {
                return;
            }
        }

        if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_STOCKPILE) {
            if (DAT_BuildingsState::instance.buildings[buildingID].field_0x190 == 1) {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearStockpileFootprintTiles, this)(x, y);
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearFixedSizeTwoBuildingFootprint, this)(x, y);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateAreaBasedOnSurrounding, this)(x, y, size);
        } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
            == OpenSHC::Map::Buildings::BT_WHEATFARM) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearBuildingFootprintAndResetUnits, this)(x, y, size);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearBuildingDisplayFlagsAndEntities, this)(
                buildingID, 1);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearBuildingTilesAndTrees, this)(buildingID, 36);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::unmarkBuildingFootprintFlag, this)(x, y, 9);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateAreaBasedOnSurrounding, this)(x, y, 9);
            size = 6;
        } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
            == OpenSHC::Map::Buildings::BT_HOPFARM) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearBuildingFootprintAndResetUnits, this)(x, y, size);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearBuildingDisplayFlagsAndEntities, this)(
                buildingID, 1);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearBuildingTilesAndTrees, this)(buildingID, 24);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::unmarkBuildingFootprintFlag, this)(x, y, 9);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateAreaBasedOnSurrounding, this)(x, y, 9);
            size = 6;
        } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
            == OpenSHC::Map::Buildings::BT_DAIRYFARM) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearBuildingFootprintAndResetUnits, this)(x, y, size);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearBuildingDisplayFlagsAndEntities, this)(
                buildingID, 1);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearBuildingTilesAndTrees, this)(buildingID, 27);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::unmarkBuildingFootprintFlag, this)(x, y, 10);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateAreaBasedOnSurrounding, this)(x, y, 10);
            size = 6;
        } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
            == OpenSHC::Map::Buildings::BT_APPLEFARM) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearBuildingFootprintAndResetUnits, this)(x, y, size);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearBuildingDisplayFlagsAndEntities, this)(
                buildingID, 1);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearBuildingTilesAndTrees, this)(buildingID, 8);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::unmarkBuildingFootprintFlag, this)(x, y, 11);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateAreaBasedOnSurrounding, this)(x, y, 11);
            size = 6;
        } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
            == OpenSHC::Map::Buildings::BT_DRAWBRIDGE) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearSizeFiveBuildingFootprintAndMoats, this)(x, y);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearBuildingDisplayFlagsAndEntities, this)(
                buildingID, 1);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateAreaBasedOnSurrounding, this)(x, y, size);
        } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                == OpenSHC::Map::Buildings::BT_CATAPULT
            || DAT_BuildingsState::instance.buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_TREBUCHET
            || DAT_BuildingsState::instance.buildings[buildingID].buildingType
                == OpenSHC::Map::Buildings::BT_BATTERINGRAM
            || DAT_BuildingsState::instance.buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_SIEGETOWER
            || DAT_BuildingsState::instance.buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_SHIELD
            || DAT_BuildingsState::instance.buildings[buildingID].buildingType
                == OpenSHC::Map::Buildings::BT_FIREBALLISTA) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearBuildingFootprintWithEdgeRubble, this)(x, y, size);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearBuildingDisplayFlagsAndEntities, this)(
                buildingID, 1);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateAreaBasedOnSurrounding, this)(x, y, size);
        } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
            == OpenSHC::Map::Buildings::BT_SIEGETOWER_PLACED) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearBuildingFootprintAndRemoveSiegeTower, this)(
                x, y, size);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearBuildingFootprintAndResetUnits, this)(x, y, size);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearBuildingDisplayFlagsAndEntities, this)(
                buildingID, 1);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateAreaBasedOnSurrounding, this)(x, y, size);
        } else {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearBuildingFootprintAndResetUnits, this)(x, y, size);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearBuildingDisplayFlagsAndEntities, this)(
                buildingID, 1);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateAreaBasedOnSurrounding, this)(x, y, size);
        }

        if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
            != OpenSHC::Map::Buildings::BT_SIEGETOWER_PLACED) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(buildingID);
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
            DAT_PathFindingState::ptr)(size + 6, x, y);
        DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
        DAT_TileMapState::instance.field_0x554a30 = 1;
        MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::triggerMinimapRedraw, DAT_MinimapViewState::ptr)(1);
    }

}
}
