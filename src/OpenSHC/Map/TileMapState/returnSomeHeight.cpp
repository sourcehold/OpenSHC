#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BUILDING;
    using OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE;
    using OpenSHC::Map::LogicHelpers::L_ROCKY;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    // FUNCTION: STRONGHOLDCRUSADER 0x004FF990
    uint TileMapState::returnSomeHeight(int tile, int ignoreHuntersHut)
    {
        uint const logic = this->LogicLayer[tile];
        int extraHeight = 0;
        if ((logic & L_KEEP_NON_MANOR_HOUSE) != 0) {
            extraHeight
                = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                    DAT_BuildingsState::ptr)(this->BuildingLayer[tile]);
        } else if ((logic & L_BUILDING) != 0) {
            int const buildingID = this->BuildingLayer[tile];
            int const type = DAT_BuildingsState::instance.buildings[buildingID].buildingType;
            switch (type) {
            case OpenSHC::Map::Buildings::BT_GATEHOUSELARGE:
            case OpenSHC::Map::Buildings::BT_GATEHOUSESMALL:
            case OpenSHC::Map::Buildings::BT_TOWER:
            case OpenSHC::Map::Buildings::BT_TOWER1:
            case OpenSHC::Map::Buildings::BT_TOWER2:
            case OpenSHC::Map::Buildings::BT_TOWER3:
            case OpenSHC::Map::Buildings::BT_TOWER4:
            case OpenSHC::Map::Buildings::BT_TOWER5:
                extraHeight
                    = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                          DAT_BuildingsState::ptr)(buildingID)
                    + 10;
                break;
            case OpenSHC::Map::Buildings::BT_HUNTERSHUT:
                if (ignoreHuntersHut != 0) {
                    extraHeight = 0;
                    break;
                }
            default:
                extraHeight = DAT_BuildingDefinedData::instance.BuildingHeights[type];
                break;
            case OpenSHC::Map::Buildings::BT_MANORHOUSE:
            case OpenSHC::Map::Buildings::BT_STONEKEEP:
            case OpenSHC::Map::Buildings::BT_STRONGHOLD:
            case OpenSHC::Map::Buildings::BT_KEEPFOUR:
            case OpenSHC::Map::Buildings::BT_KEEPFIVE:
                extraHeight
                    = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                        DAT_BuildingsState::ptr)(buildingID);
                break;
            }
        } else if ((logic & L_ROCKY) != 0 && (logic & L_WALL_OR_GATEHOUSE) == 0) {
            int const organism = this->OrganismLayer[tile];
            if (organism >= 2000) {
                short const rockType = DAT_LandscapeState::instance.rocks[organism - 2000].type;
                if (rockType >= 13) {
                    extraHeight = 70;
                } else if (rockType >= 9) {
                    extraHeight = 50;
                }
            }
        }
        return this->HeightLayer[tile] + extraHeight;
    }

}
}
