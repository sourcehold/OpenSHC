#include "../UnitsState.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00533D50
        void UnitsState::updateUnitFadeAndVisibilityNearStructures(int unitID)
        {
            int _tile = DAT_UnitsState::instance.units[unitID].tile;
            int const buildingID = DAT_TileMapState::instance.BuildingLayer[_tile];
            uint _logicFlags = DAT_TileMapState::instance.LogicLayer[_tile];
            int _gateFadeType = 0;
            BOOLEnum _isOnDefensiveStructure = FALSE;
            int _towerFadeType = 0;
            int _fadeType = 0;
            if (DAT_UnitsState::instance.units[unitID].unknownCountdown_0x402 != 0) {
                DAT_UnitsState::instance.units[unitID].unknownCountdown_0x402
                    = DAT_UnitsState::instance.units[unitID].unknownCountdown_0x402 - 1;
            }
            if (buildingID != 0) {
                switch (DAT_BuildingsState::instance.buildings[buildingID].buildingType) {
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
                    break;
                case OpenSHC::Map::Buildings::BT_WOODGATE1:
                    _gateFadeType = 10;
                    break;
                case OpenSHC::Map::Buildings::BT_GATEHOUSELARGE:
                case OpenSHC::Map::Buildings::BT_GATEHOUSESMALL:
                    _gateFadeType = 11;
                    break;
                }
            } else if ((_logicFlags & 0x100) != 0) {
                _isOnDefensiveStructure = TRUE;
            }
            if (DAT_UnitsState::instance.units[unitID].field_0x308 == 2 && _isOnDefensiveStructure) {
                _fadeType = 1;
            }
            if (DAT_UnitsState::instance.units[unitID].field_0x308 == 1 && _towerFadeType != 0) {
                _fadeType = _towerFadeType;
            }
            if (DAT_UnitsState::instance.units[unitID].field_0x308 == 0 && _gateFadeType != 0) {
                if ((DAT_TileMapState::instance
                            .LogicLayer[DAT_UnitsState::instance.units[unitID].destinationTilePosition]
                        & 0x100U)
                        != 0
                    || DAT_BuildingDefinedData::instance.IsGateOrTowerArray[DAT_BuildingsState::instance
                               .buildings[DAT_TileMapState::instance
                                       .BuildingLayer[DAT_UnitsState::instance.units[unitID].destinationTilePosition]]
                               .buildingType]
                        != FALSE) {
                    _fadeType = _gateFadeType;
                }
            }
            if (_gateFadeType != 0) {
                uint const destinationFlags
                    = DAT_TileMapState::instance
                          .LogicLayer[DAT_UnitsState::instance.units[unitID].destinationTilePosition];
                int const destinationBuildingID
                    = DAT_TileMapState::instance
                          .BuildingLayer[DAT_UnitsState::instance.units[unitID].destinationTilePosition];
                if ((destinationFlags & 0x100U) != 0 && (destinationFlags & 2U) == 0) {
                    DAT_UnitsState::instance.units[unitID].unknownCountdown_0x402 = 0;
                } else {
                    DAT_UnitsState::instance.units[unitID].unknownCountdown_0x402
                        = (DAT_BuildingDefinedData::instance.IsGateOrTowerArray
                                  [DAT_BuildingsState::instance.buildings[destinationBuildingID].buildingType]
                              != FALSE)
                            - 1U
                        & 10;
                }
            }
            if (_isOnDefensiveStructure) {
                DAT_UnitsState::instance.units[unitID].field_0x308 = 1;
            } else if (_towerFadeType != 0) {
                DAT_UnitsState::instance.units[unitID].field_0x308 = 2;
            } else {
                DAT_UnitsState::instance.units[unitID].field_0x308 = _gateFadeType != 0 ? 3 : 0;
            }
            if (DAT_UnitsState::instance.units[unitID].unknownCountdown_0x402 == 0
                || (DAT_TileMapState::instance.MiscDisplayLayer[DAT_UnitsState::instance.units[unitID].nextTileUnk]
                       & 0x10)
                    != 0) {
                DAT_UnitsState::instance.units[unitID].vanish = 0;
            } else if ((DAT_TileMapState::instance
                               .MiscDisplayLayer[DAT_UnitsState::instance.units[unitID].currentTilePosition_2Unk]
                           & 0x10)
                != 0) {
                DAT_UnitsState::instance.units[unitID].vanish = 15;
            } else if (DAT_UnitsState::instance.units[unitID].vanish <= 0) {
                DAT_UnitsState::instance.units[unitID].vanish = 1;
            }
            if (_fadeType != 0) {
                DAT_UnitsState::instance.units[unitID].fadeType = _fadeType;
                DAT_UnitsState::instance.units[unitID].fadeCounter = 0;
            }
        }

    }
}
}
