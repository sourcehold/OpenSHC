#include "../TileMapState.func.hpp"

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

    // FUNCTION: STRONGHOLDCRUSADER 0x004FFBA0
    int TileMapState::getTotalHeightAt(int tile, int playerID)
    {
        int extra = 0;
        BOOLEnum exposed = FALSE;
        uint const logic = this->LogicLayer[tile];
        if ((logic & L_KEEP_NON_MANOR_HOUSE) != 0) {
            int const buildingID = this->BuildingLayer[tile];
            extra = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                DAT_BuildingsState::ptr)(buildingID);
            for (int i = 0; i < 8; i++) {
                if (this->BuildingLayer[DAT_TileMapState::instance.directionTranslationMatrix[DAT_ViewportRenderState::
                                                instance.tileTranslationMatrix_YComponent[tile]][i]
                        + tile]
                    != buildingID) {
                    exposed = TRUE;
                    break;
                }
            }
            if (playerID != 0 && DAT_BuildingsState::instance.buildings[buildingID].owner != playerID) {
                exposed = FALSE;
            }
        } else if ((logic & L_BUILDING) != 0) {
            int const buildingID = this->BuildingLayer[tile];
            int const type = DAT_BuildingsState::instance.buildings[buildingID].buildingType;
            switch (type) {
            case OpenSHC::Map::Buildings::BT_TOWER:
            case OpenSHC::Map::Buildings::BT_TOWER1:
            case OpenSHC::Map::Buildings::BT_TOWER2:
            case OpenSHC::Map::Buildings::BT_TOWER3:
            case OpenSHC::Map::Buildings::BT_TOWER4:
            case OpenSHC::Map::Buildings::BT_TOWER5:
                extra = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                            DAT_BuildingsState::ptr)(buildingID)
                    + 20;
                exposed = TRUE;
                break;
            case OpenSHC::Map::Buildings::BT_MANORHOUSE:
            case OpenSHC::Map::Buildings::BT_STONEKEEP:
            case OpenSHC::Map::Buildings::BT_STRONGHOLD:
            case OpenSHC::Map::Buildings::BT_KEEPFOUR:
            case OpenSHC::Map::Buildings::BT_KEEPFIVE:
                extra = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                    DAT_BuildingsState::ptr)(buildingID);
                if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    != OpenSHC::Map::Buildings::BT_MANORHOUSE) {
                    for (int i = 0; i < 8; i++) {
                        if (this->BuildingLayer[DAT_TileMapState::instance
                                                    .directionTranslationMatrix[DAT_ViewportRenderState::instance
                                                            .tileTranslationMatrix_YComponent[tile]][i]
                                + tile]
                            != buildingID) {
                            exposed = TRUE;
                            break;
                        }
                    }
                }
                break;
            case OpenSHC::Map::Buildings::BT_GATEHOUSELARGE:
            case OpenSHC::Map::Buildings::BT_GATEHOUSESMALL:
                extra = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                    DAT_BuildingsState::ptr)(buildingID);
                exposed = TRUE;
                break;
            default:
                extra = DAT_BuildingDefinedData::instance.BuildingHeights[type];
                break;
            }
            if (playerID != 0 && DAT_BuildingsState::instance.buildings[buildingID].owner != playerID) {
                exposed = FALSE;
            }
        } else if ((logic & L_ROCKY) != 0 && (logic & L_WALL_OR_GATEHOUSE) == 0) {
            // rock ids are biased by 2000
            int const organism = this->OrganismLayer[tile];
            if (organism >= 2000) {
                short const rockType = DAT_LandscapeState::instance.rocks[organism - 2000].type;
                if (rockType >= 13) {
                    extra = 70;
                } else if (rockType >= 9) {
                    extra = 50;
                }
            }
            if (playerID != 0 && (this->WallOwnerLayer[tile] & 7) + 1 != playerID) {
                exposed = FALSE;
            }
        } else if ((logic & L_CRENEL_VARIATIONUnk) != 0) {
            extra = 20;
            exposed = TRUE;
            if (playerID != 0 && (this->WallOwnerLayer[tile] & 7) + 1 != playerID) {
                exposed = FALSE;
            }
        } else if ((logic & L_CRENEL) != 0) {
            extra = 10;
            exposed = TRUE;
            if (playerID != 0 && (this->WallOwnerLayer[tile] & 7) + 1 != playerID) {
                exposed = FALSE;
            }
        } else if (this->BuildingLayer[tile] != 0) {
            int const buildingID = this->BuildingLayer[tile];
            extra = 30;
            if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    == OpenSHC::Map::Buildings::BT_GATEHOUSELARGE
                || DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    == OpenSHC::Map::Buildings::BT_GATEHOUSESMALL) {
                // a gatehouse only counts as cover while both of its span tiles are still standing
                int first;
                int second;
                if (DAT_BuildingsState::instance.buildings[buildingID].buildingVariation == 80) {
                    first = 2;
                    second = 6;
                } else {
                    first = 0;
                    second = 4;
                }
                int const tileY = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
                if (this->BuildingLayer[DAT_TileMapState::instance.directionTranslationMatrix[tileY][first] + tile]
                    != buildingID) {
                    exposed = TRUE;
                }
                if (this->BuildingLayer[DAT_TileMapState::instance.directionTranslationMatrix[tileY][second] + tile]
                    != buildingID) {
                    exposed = TRUE;
                }
            }
            if (playerID != 0 && DAT_BuildingsState::instance.buildings[buildingID].owner != playerID) {
                exposed = FALSE;
            }
        }

        extra += this->HeightLayer[tile];
        if (exposed) {
            return extra;
        }
        return -1 - extra;
    }

}
}
