#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Buildings::BuildingType;

        // FUNCTION: STRONGHOLDCRUSADER 0x005371F0
        uint UnitsState::findFreeTileNearby(uint unitID, uint tile)
        {
            int _ownerPlayerID = DAT_UnitsState::instance.units[unitID].owner;
            int _originY = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
            dword _areaAtUnit
                = (short)DAT_TileMapState::instance.PathConnectionLayer[DAT_UnitsState::instance.units[unitID].tile];
            int _originX = tile - DAT_ViewportRenderState::instance.translationMatrix[_originY].addXgetTile;
            /* original_y-2 */
            uint _northTile = DAT_ViewportRenderState::instance.translationMatrix[_originY + -2].addXgetTile + _originX;
            if (MACRO_CALL_MEMBER(
                    OpenSHC::Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                    DAT_PathFindingState::ptr)(
                    _ownerPlayerID, _areaAtUnit, (short)DAT_TileMapState::instance.PathConnectionLayer[_northTile], 0)
                == 0) {
                _northTile = 0;
            }
            /* original_x+2 */
            uint _eastTile = DAT_ViewportRenderState::instance.translationMatrix[_originY].addXgetTile + 2 + _originX;
            if (MACRO_CALL_MEMBER(
                    OpenSHC::Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                    DAT_PathFindingState::ptr)(
                    _ownerPlayerID, _areaAtUnit, (short)DAT_TileMapState::instance.PathConnectionLayer[_eastTile], 0)
                == 0) {
                _eastTile = 0;
            }
            /* original_y+2 */
            uint _southTile = DAT_ViewportRenderState::instance.translationMatrix[_originY + 2].addXgetTile + _originX;
            if (MACRO_CALL_MEMBER(
                    OpenSHC::Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                    DAT_PathFindingState::ptr)(
                    _ownerPlayerID, _areaAtUnit, (short)DAT_TileMapState::instance.PathConnectionLayer[_southTile], 0)
                == 0) {
                _southTile = 0;
            }
            /* original_x-2 */
            uint _westTile = DAT_ViewportRenderState::instance.translationMatrix[_originY].addXgetTile + -2 + _originX;
            if (MACRO_CALL_MEMBER(
                    OpenSHC::Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                    DAT_PathFindingState::ptr)(
                    _ownerPlayerID, _areaAtUnit, (short)DAT_TileMapState::instance.PathConnectionLayer[_westTile], 0)
                == 0) {
                _westTile = 0;
            }
            if (_westTile == 0 && _southTile == 0 && _eastTile == 0 && _northTile == 0) {
                return 0;
            }
            if ((_northTile != 0 || _southTile != 0)
                && ((DAT_TileMapState::instance
                            .LogicLayer[DAT_ViewportRenderState::instance.translationMatrix[_originY].addXgetTile
                                + _originX - 1]
                        & 0x100)
                        == 0
                    || (DAT_TileMapState::instance
                               .LogicLayer[DAT_ViewportRenderState::instance.translationMatrix[_originY].addXgetTile
                                   + _originX + 1]
                           & 0x100)
                        == 0)) {
                _southTile = 0;
                _northTile = 0;
            }
            if ((_westTile != 0 || _eastTile != 0)
                && ((DAT_TileMapState::instance
                            .LogicLayer[DAT_ViewportRenderState::instance.translationMatrix[_originY + -1].addXgetTile
                                + _originX]
                        & 0x100)
                        == 0
                    || (DAT_TileMapState::instance
                               .LogicLayer[DAT_ViewportRenderState::instance.translationMatrix[_originY + 1].addXgetTile
                                   + _originX]
                           & 0x100)
                        == 0)) {
                _eastTile = 0;
                _westTile = 0;
            }
            if (_northTile != 0) {
                for (int i = 0; i < 9; ++i) {
                    uint _checkX = DAT_UnitPropertiesDefinedData::instance.field120_0x1213c[i].x + _originX;
                    uint _checkY = DAT_UnitPropertiesDefinedData::instance.field120_0x1213c[i].y + _originY;
                    if (_checkX >= 400 || _checkY >= 400) {
                        continue;
                    }
                    if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[_checkX + _checkY * 400] == 0) {
                        continue;
                    }
                    int _checkTile = DAT_ViewportRenderState::instance.translationMatrix[_checkY].addXgetTile
                        + DAT_UnitPropertiesDefinedData::instance.field120_0x1213c[i].x + _originX;
                    if ((DAT_TileMapState::instance.LogicLayer[_checkTile] & 0x100) != 0
                        || (DAT_TileMapState::instance.LogicLayer[_checkTile] & 0x4a5014b1) != 0
                        || (DAT_TileMapState::instance.BuildingLayer[_checkTile] != 0
                            && DAT_BuildingsState::instance
                                    .buildings[DAT_TileMapState::instance.BuildingLayer[_checkTile]]
                                    .buildingType
                                != OpenSHC::Map::Buildings::BT_KILLINGPIT)) {
                        _northTile = 0;
                        break;
                    }
                }
            }
            if (_eastTile != 0) {
                for (int i = 0; i < 9; ++i) {
                    uint _checkX = DAT_UnitPropertiesDefinedData::instance.field121_0x12184[i].x + _originX;
                    uint _checkY = DAT_UnitPropertiesDefinedData::instance.field121_0x12184[i].y + _originY;
                    if (_checkX >= 400 || _checkY >= 400) {
                        continue;
                    }
                    if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[_checkX + _checkY * 400] == 0) {
                        continue;
                    }
                    int _checkTile = DAT_ViewportRenderState::instance.translationMatrix[_checkY].addXgetTile
                        + DAT_UnitPropertiesDefinedData::instance.field121_0x12184[i].x + _originX;
                    if ((DAT_TileMapState::instance.LogicLayer[_checkTile] & 0x100) != 0
                        || (DAT_TileMapState::instance.LogicLayer[_checkTile] & 0x4a5014b1) != 0
                        || (DAT_TileMapState::instance.BuildingLayer[_checkTile] != 0
                            && DAT_BuildingsState::instance
                                    .buildings[DAT_TileMapState::instance.BuildingLayer[_checkTile]]
                                    .buildingType
                                != OpenSHC::Map::Buildings::BT_KILLINGPIT)) {
                        _eastTile = 0;
                        break;
                    }
                }
            }
            if (_southTile != 0) {
                for (int i = 0; i < 9; ++i) {
                    uint _checkX = DAT_UnitPropertiesDefinedData::instance.field122_0x121cc[i].x + _originX;
                    uint _checkY = DAT_UnitPropertiesDefinedData::instance.field122_0x121cc[i].y + _originY;
                    if (_checkX >= 400 || _checkY >= 400) {
                        continue;
                    }
                    if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[_checkX + _checkY * 400] == 0) {
                        continue;
                    }
                    int _checkTile = DAT_ViewportRenderState::instance.translationMatrix[_checkY].addXgetTile
                        + DAT_UnitPropertiesDefinedData::instance.field122_0x121cc[i].x + _originX;
                    if ((DAT_TileMapState::instance.LogicLayer[_checkTile] & 0x100) != 0
                        || (DAT_TileMapState::instance.LogicLayer[_checkTile] & 0x4a5014b1) != 0
                        || (DAT_TileMapState::instance.BuildingLayer[_checkTile] != 0
                            && DAT_BuildingsState::instance
                                    .buildings[DAT_TileMapState::instance.BuildingLayer[_checkTile]]
                                    .buildingType
                                != OpenSHC::Map::Buildings::BT_KILLINGPIT)) {
                        _southTile = 0;
                        break;
                    }
                }
            }
            if (_westTile != 0) {
                for (int i = 0; i < 9; ++i) {
                    uint _checkX = DAT_UnitPropertiesDefinedData::instance.field123_0x12214[i].x + _originX;
                    uint _checkY = DAT_UnitPropertiesDefinedData::instance.field123_0x12214[i].y + _originY;
                    if (_checkX >= 400 || _checkY >= 400) {
                        continue;
                    }
                    if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[_checkX + _checkY * 400] == 0) {
                        continue;
                    }
                    int _checkTile = DAT_ViewportRenderState::instance.translationMatrix[_checkY].addXgetTile
                        + DAT_UnitPropertiesDefinedData::instance.field123_0x12214[i].x + _originX;
                    if ((DAT_TileMapState::instance.LogicLayer[_checkTile] & 0x100) != 0
                        || (DAT_TileMapState::instance.LogicLayer[_checkTile] & 0x4a5014b1) != 0
                        || (DAT_TileMapState::instance.BuildingLayer[_checkTile] != 0
                            && DAT_BuildingsState::instance
                                    .buildings[DAT_TileMapState::instance.BuildingLayer[_checkTile]]
                                    .buildingType
                                != OpenSHC::Map::Buildings::BT_KILLINGPIT)) {
                        _westTile = 0;
                        break;
                    }
                }
            }
            int _unitY = DAT_ViewportRenderState::instance
                             .tileTranslationMatrix_YComponent[DAT_UnitsState::instance.units[unitID].tile];
            int _unitX = DAT_UnitsState::instance.units[unitID].tile
                - DAT_ViewportRenderState::instance.translationMatrix[_unitY].addXgetTile;
            uint _closestTile = 0;
            int _closestDistance = 100000;
            if (_northTile != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                    DAT_DirectionAlgorithmState::ptr)(_northTile
                        - DAT_ViewportRenderState::instance
                            .translationMatrix[DAT_ViewportRenderState::instance
                                    .tileTranslationMatrix_YComponent[_northTile]]
                            .addXgetTile,
                    DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_northTile], _unitX, _unitY);
                if (DAT_DirectionAlgorithmState::instance.distanceHigh < _closestDistance) {
                    _closestTile = _northTile;
                    _closestDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                }
            }
            if (_southTile != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                    DAT_DirectionAlgorithmState::ptr)(_southTile
                        - DAT_ViewportRenderState::instance
                            .translationMatrix[DAT_ViewportRenderState::instance
                                    .tileTranslationMatrix_YComponent[_southTile]]
                            .addXgetTile,
                    DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_southTile], _unitX, _unitY);
                if (DAT_DirectionAlgorithmState::instance.distanceHigh < _closestDistance) {
                    _closestTile = _southTile;
                    _closestDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                }
            }
            if (_eastTile != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                    DAT_DirectionAlgorithmState::ptr)(_eastTile
                        - DAT_ViewportRenderState::instance
                            .translationMatrix[DAT_ViewportRenderState::instance
                                    .tileTranslationMatrix_YComponent[_eastTile]]
                            .addXgetTile,
                    DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_eastTile], _unitX, _unitY);
                if (DAT_DirectionAlgorithmState::instance.distanceHigh < _closestDistance) {
                    _closestTile = _eastTile;
                    _closestDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                }
            }
            if (_westTile != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                    DAT_DirectionAlgorithmState::ptr)(_westTile
                        - DAT_ViewportRenderState::instance
                            .translationMatrix[DAT_ViewportRenderState::instance
                                    .tileTranslationMatrix_YComponent[_westTile]]
                            .addXgetTile,
                    DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_westTile], _unitX, _unitY);
                if (DAT_DirectionAlgorithmState::instance.distanceHigh < _closestDistance) {
                    _closestTile = _westTile;
                    _closestDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                }
            }
            return _closestTile;
        }

    }
}
}
