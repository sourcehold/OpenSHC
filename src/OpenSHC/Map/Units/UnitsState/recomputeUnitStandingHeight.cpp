#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Buildings::BuildingType;
        using OpenSHC::Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0052F0D0
        void UnitsState::recomputeUnitStandingHeight(int unitID)
        {
            int _tile = this->units[unitID].tile;
            uint _logicFlags = DAT_TileMapState::instance.LogicLayer[_tile];
            int _buildingID = DAT_TileMapState::instance.BuildingLayer[_tile];
            this->units[unitID].buildingHeight = 0;
            this->units[unitID].field58_0x84 = 0;
            if ((_logicFlags & 0x10010d00) == 0) {
                if (_buildingID == 0) {
                    if (this->units[unitID].wasOnStoneGate != 0) {
                        this->units[unitID].terrainOrClimbHeight = DAT_TileMapState::instance.HeightLayer[_tile];
                        this->units[unitID].wasOnStoneGate = 0;
                    }
                } else if (DAT_BuildingsState::instance.buildings[_buildingID].buildingType
                    == OpenSHC::Map::Buildings::BT_DRAWBRIDGE) {
                    this->units[unitID].buildingHeight = 8 - this->units[unitID].terrainOrClimbHeight;
                }
            } else if ((_logicFlags & 0x800) != 0) {
                this->units[unitID].buildingHeight = 0xc;
            } else if ((_logicFlags & 0x100) != 0) {
                if (_buildingID == 0) {
                    this->units[unitID].buildingHeight = 4;
                } else if (this->units[unitID].unknownCountdown_0x402 == 0) {
                    this->units[unitID].buildingHeight = 0x28;
                } else {
                    this->units[unitID].buildingHeight = -0x5a;
                    if (this->units[unitID].terrainOrClimbHeight + -0x5a < 8) {
                        this->units[unitID].buildingHeight = 0;
                    }
                    this->units[unitID].wasOnStoneGate = 1;
                }
            } else if ((_logicFlags & 0x400) != 0) {
                this->units[unitID].buildingHeight = 2;
            } else if ((_logicFlags & 0x10000000) != 0) {
                if (this->units[unitID].unknownCountdown_0x402 == 0
                    && this->units[unitID].unitType != OpenSHC::Map::Units::UT_S_TOWER) {
                    this->units[unitID].buildingHeight = (short)MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                        DAT_BuildingsState::ptr)(_buildingID);
                }
                this->units[unitID].field58_0x84 = (short)MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID2,
                    DAT_BuildingsState::ptr)(_buildingID);
                this->units[unitID].terrainOrClimbHeight
                    = DAT_BuildingsState::instance.buildings[_buildingID].terrainHeightUnk;
            }
            if (this->units[DAT_CurrentUnitSlotID::instance].field306_0x418 != 0) {
                this->units[unitID].buildingHeight
                    = this->units[unitID].buildingHeight + this->units[DAT_CurrentUnitSlotID::instance].field306_0x418;
            }
        }

    }
}
}
