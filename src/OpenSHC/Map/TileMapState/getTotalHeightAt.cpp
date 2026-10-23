#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BUILDING;
    using OpenSHC::Map::LogicHelpers::L_CRENEL;
    using OpenSHC::Map::LogicHelpers::L_CRENEL_VARIATIONUnk;
    using OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE;
    using OpenSHC::Map::LogicHelpers::L_ROCKY;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;


    using OpenSHC::Map::Buildings::BuildingType;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004FFBA0
    int TileMapState::getTotalHeightAt(int tile, int playerID)
    {
        uint logic = this->LogicLayer[tile];
        int extra = 0;
        int exposed = 0;
        if ((logic & L_KEEP_NON_MANOR_HOUSE) != 0) {
            int buildingID = this->BuildingLayer[tile];
            extra = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID, DAT_BuildingsState::ptr)(buildingID);
            for (int i = 0; i < 8; i++) {
                if (this->BuildingLayer[DAT_TileMapState::instance.directionTranslationMatrix[DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile]][i] + tile] != buildingID) {
                    exposed = 1;
                    break;
                }
            }
            if (playerID != 0 && DAT_BuildingsState::instance.buildings[buildingID].owner != playerID) {
                exposed = 0;
            }
        } else if ((logic & L_BUILDING) != 0) {
            int buildingID = this->BuildingLayer[tile];
            int type = DAT_BuildingsState::instance.buildings[buildingID].buildingType;
            switch (type) {
            case 0x3d:
            case 0x4a:
            case 0x4b:
            case 0x4c:
            case 0x4d:
            case 0x4e:
                extra = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID, DAT_BuildingsState::ptr)(buildingID) + 0x14;
                exposed = 1;
                break;
            case 0x28:
            case 0x29:
            case 0x2a:
            case 0x2b:
            case 0x2c:
                extra = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID, DAT_BuildingsState::ptr)(buildingID);
                if (DAT_BuildingsState::instance.buildings[buildingID].buildingType != OpenSHC::Map::Buildings::BT_MANORHOUSE) {
                    for (int i = 0; i < 8; i++) {
                        if (this->BuildingLayer[DAT_TileMapState::instance.directionTranslationMatrix[DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile]][i] + tile] != buildingID) {
                            exposed = 1;
                            break;
                        }
                    }
                }
                break;
            case 0x2d:
            case 0x2e:
                extra = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID, DAT_BuildingsState::ptr)(buildingID);
                exposed = 1;
                break;
            default:
                extra = DAT_BuildingDefinedData::instance.BuildingHeights[type];
                break;
            }
            if (playerID != 0 && DAT_BuildingsState::instance.buildings[buildingID].owner != playerID) {
                exposed = 0;
            }
        } else if ((logic & L_ROCKY) != 0 && (logic & L_WALL_OR_GATEHOUSE) == 0) {
            /* rock ids are biased by 2000 */
            int organism = this->OrganismLayer[tile];
            if (organism >= 2000) {
                short rockType = DAT_LandscapeState::instance.rocks[organism - 2000].type;
                if (rockType >= 0xd) {
                    extra = 0x46;
                } else if (rockType >= 9) {
                    extra = 0x32;
                }
            }
        } else if ((logic & L_CRENEL_VARIATIONUnk) != 0) {
            extra = 0x14;
            exposed = 1;
            if (playerID != 0 && (this->WallOwnerLayer[tile] & 7) + 1 != playerID) {
                exposed = 0;
            }
        } else if ((logic & L_CRENEL) != 0) {
            extra = 10;
            exposed = 1;
            if (playerID != 0 && (this->WallOwnerLayer[tile] & 7) + 1 != playerID) {
                exposed = 0;
            }
        } else {
            short building = this->BuildingLayer[tile];
            if (building != 0) {
                int buildingID = building;
                short type = DAT_BuildingsState::instance.buildings[buildingID].buildingType;
                extra = 0x1e;
                if (type == OpenSHC::Map::Buildings::BT_GATEHOUSELARGE
                    || type == OpenSHC::Map::Buildings::BT_GATEHOUSESMALL) {
                    /* a gatehouse only counts as cover while both of its span tiles are still standing */
                    int first;
                    int second;
                    if (DAT_BuildingsState::instance.buildings[buildingID].buildingVariation == 0x50) {
                        first = 2;
                        second = 6;
                    } else {
                        first = 0;
                        second = 4;
                    }
                    if (this->BuildingLayer[DAT_TileMapState::instance.directionTranslationMatrix[DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile]][first] + tile] != buildingID) {
                        exposed = 1;
                    }
                    if (this->BuildingLayer[DAT_TileMapState::instance.directionTranslationMatrix[DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile]][second] + tile] != buildingID) {
                        exposed = 1;
                    }
                }
                if (playerID != 0 && DAT_BuildingsState::instance.buildings[buildingID].owner != playerID) {
                    exposed = 0;
                }
            }
        }

        extra = extra + this->HeightLayer[tile];
        if (exposed != 0) {
            return extra;
        }
        return -1 - extra;
    }

}
}
