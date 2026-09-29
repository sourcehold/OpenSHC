
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00515A20
    void TileMapState::clearBuildingFromTerrain(int buildingID)
    {
        uint y = (short)DAT_BuildingsState::instance.buildings[buildingID].y;
        uint size = DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight;
        uint x = (short)DAT_BuildingsState::instance.buildings[buildingID].x;
        if (DAT_BuildingsState::instance.buildings[buildingID].buildingType != OpenSHC::Map::Buildings::BT_KILLINGPIT) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::validateBuildingPlacementAtTile, this)(
                DAT_BuildingsState::instance.buildings[buildingID].owner, x, y);
            if (this->buildingPlacementFail != FALSE) {
                return;
            }
        }

        if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_STOCKPILE) {
            if (DAT_BuildingsState::instance.buildings[buildingID].field125_0x190 == 1) {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearStockpileFootprintTiles, this)(x, y);
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearFixedSizeTwoBuildingFootprint, this)(x, y);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateAreaBasedOnSurrounding, this)(x, y, size);
        } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_WHEATFARM || DAT_BuildingsState::instance.buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_HOPFARM) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearBuildingFootprintAndResetUnits, this)(x, y, size);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearBuildingDisplayFlagsAndEntities, this)(buildingID, 1);
            int surfaceArea;
            if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_WHEATFARM) {
                surfaceArea = 36;
            } else {
                surfaceArea = 24;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearBuildingTilesAndTrees, this)(buildingID, surfaceArea);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::unmarkBuildingFootprintFlag, this)(x, y, 9);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateAreaBasedOnSurrounding, this)(x, y, 9);
            size = 6;
        } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_DAIRYFARM) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearBuildingFootprintAndResetUnits, this)(x, y, size);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearBuildingDisplayFlagsAndEntities, this)(buildingID, 1);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearBuildingTilesAndTrees, this)(buildingID, 0x1b);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::unmarkBuildingFootprintFlag, this)(x, y, 10);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateAreaBasedOnSurrounding, this)(x, y, 10);
            size = 6;
        } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_APPLEFARM) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearBuildingFootprintAndResetUnits, this)(x, y, size);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearBuildingDisplayFlagsAndEntities, this)(buildingID, 1);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearBuildingTilesAndTrees, this)(buildingID, 8);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::unmarkBuildingFootprintFlag, this)(x, y, 0xb);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateAreaBasedOnSurrounding, this)(x, y, 0xb);
            size = 6;
        } else {
            if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_DRAWBRIDGE) {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearSizeFiveBuildingFootprintAndMoats, this)(x, y);
            } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_CATAPULT || DAT_BuildingsState::instance.buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_TREBUCHET || DAT_BuildingsState::instance.buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_BATTERINGRAM || DAT_BuildingsState::instance.buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_SIEGETOWER || DAT_BuildingsState::instance.buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_SHIELD || DAT_BuildingsState::instance.buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_FIREBALLISTA) {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearBuildingFootprintWithEdgeRubble, this)(x, y, size);
            } else if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_SIEGETOWER_PLACED) {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearBuildingFootprintAndRemoveSiegeTower, this)(x, y, size);
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearBuildingFootprintAndResetUnits, this)(x, y, size);
            } else {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearBuildingFootprintAndResetUnits, this)(x, y, size);
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearBuildingDisplayFlagsAndEntities, this)(buildingID, 1);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateAreaBasedOnSurrounding, this)(x, y, size);
        }

        if (DAT_BuildingsState::instance.buildings[buildingID].buildingType != OpenSHC::Map::Buildings::BT_SIEGETOWER_PLACED) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(buildingID);
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer, DAT_PathFindingState::ptr)(size + 6, x, y);
        DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
        this->field204_0x554a30 = 1;
        MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::triggerMinimapRedraw, DAT_MinimapViewState::ptr)(1);
    }

}
}
