#include "../UnitsState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Buildings::BuildingType;
        using OpenSHC::Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0052F0D0
        void UnitsState::recomputeUnitStandingHeight(int unitID)
        {
            int _tile = this->units[unitID].tile;
            uint _logicFlags = DAT_TileMapState::instance.LogicLayer[_tile]
                & (LogicHelpers::L_STAIRS | LogicHelpers::L_WALL_OR_GATEHOUSE | LogicHelpers::L_BUILDING
                    | LogicHelpers::L_KEEP_NON_MANOR_HOUSE | LogicHelpers::L_UNKNOWN_WALL_RELATED);
            int _buildingID = DAT_TileMapState::instance.BuildingLayer[_tile];
            this->units[unitID].buildingHeight = 0;
            this->units[unitID].field_0x84 = 0;
            if (_logicFlags != 0) {
                if ((_logicFlags & LogicHelpers::L_STAIRS) != 0) {
                    this->units[unitID].buildingHeight = 12;
                } else if ((_logicFlags & LogicHelpers::L_WALL_OR_GATEHOUSE) != 0) {
                    if (_buildingID != 0) {
                        if (this->units[unitID].unknownCountdown_0x402 != 0) {
                            this->units[unitID].buildingHeight = -90;
                            if (this->units[unitID].terrainOrClimbHeight - 90 < 8) {
                                this->units[unitID].buildingHeight = 0;
                            }
                            this->units[unitID].wasOnStoneGate = 1;
                        } else {
                            this->units[unitID].buildingHeight = 40;
                        }
                    } else {
                        this->units[unitID].buildingHeight = 4;
                    }
                } else if ((_logicFlags & LogicHelpers::L_BUILDING) != 0) {
                    this->units[unitID].buildingHeight = 2;
                } else if ((_logicFlags & LogicHelpers::L_KEEP_NON_MANOR_HOUSE) != 0) {
                    if (this->units[unitID].unknownCountdown_0x402 == 0
                        && this->units[unitID].unitType != OpenSHC::Map::Units::UT_S_TOWER) {
                        this->units[unitID].buildingHeight = MACRO_CALL_MEMBER(
                            OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                            DAT_BuildingsState::ptr)(_buildingID);
                    }
                    this->units[unitID].field_0x84 = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID2,
                        DAT_BuildingsState::ptr)(_buildingID);
                    this->units[unitID].terrainOrClimbHeight
                        = DAT_BuildingsState::instance.buildings[_buildingID].terrainHeightUnk;
                }
            } else if (_buildingID != 0) {
                if (DAT_BuildingsState::instance.buildings[_buildingID].buildingType
                    == OpenSHC::Map::Buildings::BT_DRAWBRIDGE) {
                    this->units[unitID].buildingHeight = 8 - this->units[unitID].terrainOrClimbHeight;
                }
            } else if (this->units[unitID].wasOnStoneGate != 0) {
                this->units[unitID].terrainOrClimbHeight = DAT_TileMapState::instance.HeightLayer[_tile];
                this->units[unitID].wasOnStoneGate = 0;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x418 != 0) {
                this->units[unitID].buildingHeight = this->units[unitID].buildingHeight
                    + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x418;
            }
        }

    }
}
}
