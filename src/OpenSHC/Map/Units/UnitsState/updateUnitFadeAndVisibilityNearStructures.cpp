#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00533D50
        void UnitsState::updateUnitFadeAndVisibilityNearStructures(int unitID)
        {
            int _tile = this->units[unitID].tile;
            uint _logicFlags = DAT_TileMapState::instance.LogicLayer[_tile];
            byte _gateFadeType = 0;
            byte _towerFadeType = 0;
            byte _fadeType = 0;
            bool _isOnDefensiveStructure = false;
            if (this->units[unitID].unknownCountdown_0x402 != 0) {
                this->units[unitID].unknownCountdown_0x402 = this->units[unitID].unknownCountdown_0x402 - 1;
            }
            if (DAT_TileMapState::instance.BuildingLayer[_tile] == 0) {
                if ((_logicFlags & 0x100) != 0) {
                    _isOnDefensiveStructure = true;
                }
            } else {
                switch (DAT_BuildingsState::instance.buildings[DAT_TileMapState::instance.BuildingLayer[_tile]]
                        .buildingType) {
                case OpenSHC::Map::Buildings::BT_GATEHOUSELARGE:
                case OpenSHC::Map::Buildings::BT_GATEHOUSESMALL:
                    _gateFadeType = 0xb;
                    break;
                case OpenSHC::Map::Buildings::BT_WOODGATE1:
                    _gateFadeType = 10;
                    break;
                case OpenSHC::Map::Buildings::BT_TOWER1:
                    _towerFadeType = 1;
                    break;
                case OpenSHC::Map::Buildings::BT_TOWER2:
                    _towerFadeType = 2;
                    break;
                case OpenSHC::Map::Buildings::BT_TOWER3:
                    _towerFadeType = 3;
                    break;
                case OpenSHC::Map::Buildings::BT_TOWER4:
                case OpenSHC::Map::Buildings::BT_TOWER5:
                    _towerFadeType = 4;
                }
            }
            if (this->units[unitID].field171_0x308 == 2 && _isOnDefensiveStructure) {
                _fadeType = 1;
            }
            if (this->units[unitID].field171_0x308 == 1 && _towerFadeType != 0) {
                _fadeType = _towerFadeType;
            }
            if (this->units[unitID].field171_0x308 == 0 && _gateFadeType != 0) {
                if ((DAT_TileMapState::instance.LogicLayer[this->units[unitID].destinationTilePosition] & 0x100U) != 0
                    || DAT_BuildingDefinedData::instance.IsGateOrTowerArray[(short)DAT_BuildingsState::instance
                               .buildings[DAT_TileMapState::instance
                                       .BuildingLayer[this->units[unitID].destinationTilePosition]]
                               .buildingType]
                        != FALSE) {
                    _fadeType = _gateFadeType;
                }
            }
            if (_gateFadeType != 0) {
                if ((DAT_TileMapState::instance.LogicLayer[this->units[unitID].destinationTilePosition] & 0x100U) == 0
                    || (DAT_TileMapState::instance.LogicLayer[this->units[unitID].destinationTilePosition] & 2U) != 0) {
                    this->units[unitID].unknownCountdown_0x402
                        = (DAT_BuildingDefinedData::instance.IsGateOrTowerArray[(short)DAT_BuildingsState::instance
                                   .buildings[DAT_TileMapState::instance
                                           .BuildingLayer[this->units[unitID].destinationTilePosition]]
                                   .buildingType]
                              != FALSE)
                            - 1U
                        & 10;
                } else {
                    this->units[unitID].unknownCountdown_0x402 = 0;
                }
            }
            if (_isOnDefensiveStructure) {
                this->units[unitID].field171_0x308 = 1;
            } else if (_towerFadeType == 0) {
                this->units[unitID].field171_0x308 = _gateFadeType != 0 ? 3 : 0;
            } else {
                this->units[unitID].field171_0x308 = 2;
            }
            if (this->units[unitID].unknownCountdown_0x402 == 0
                || (DAT_TileMapState::instance.MiscDisplayLayer[this->units[unitID].nextTileUnk] & 0x10) != 0) {
                this->units[unitID].vanish = 0;
            } else if ((DAT_TileMapState::instance.MiscDisplayLayer[this->units[unitID].currentTilePosition_2Unk]
                           & 0x10)
                == 0) {
                if (this->units[unitID].vanish < 1) {
                    this->units[unitID].vanish = 1;
                }
            } else {
                this->units[unitID].vanish = 0xf;
            }
            if (_fadeType != 0) {
                this->units[unitID].fadeType = _fadeType;
                this->units[unitID].fadeCounter = 0;
            }
        }

    }
}
}
