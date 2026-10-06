#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Buildings::BuildingType;
        using OpenSHC::Map::Buildings::BuildingTypeShort;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00536780
        BOOLEnum UnitsState::isTowerTileOvercrowdedByCurrentPlayer(int tile)
        {
            int _buildingID = DAT_TileMapState::instance.BuildingLayer[tile];
            if (_buildingID == 0) {
                return FALSE;
            }
            BuildingTypeShort _buildingType = DAT_BuildingsState::instance.buildings[_buildingID].buildingType;
            if (_buildingType != OpenSHC::Map::Buildings::BT_TOWER1
                && _buildingType != OpenSHC::Map::Buildings::BT_TOWER2
                && _buildingType != OpenSHC::Map::Buildings::BT_TOWER3
                && _buildingType != OpenSHC::Map::Buildings::BT_TOWER4
                && _buildingType != OpenSHC::Map::Buildings::BT_TOWER5
                && _buildingType != OpenSHC::Map::Buildings::BT_STONEKEEP
                && _buildingType != OpenSHC::Map::Buildings::BT_STRONGHOLD
                && _buildingType != OpenSHC::Map::Buildings::BT_KEEPFOUR
                && _buildingType != OpenSHC::Map::Buildings::BT_KEEPFIVE) {
                return FALSE;
            }
            int _tileCapacity = DAT_BuildingsState::instance.buildings[_buildingID].widthOrHeight
                * DAT_BuildingsState::instance.buildings[_buildingID].widthOrHeight;
            if (_buildingType == OpenSHC::Map::Buildings::BT_TOWER1) {
                _tileCapacity = 5;
            }
            int _ownUnitsOnBuilding = 0;
            for (int _constructionTile = 0; _constructionTile < DAT_TileMapState::instance.constructionTileCount;
                ++_constructionTile) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, DAT_TileMapState::ptr)(
                    _constructionTile, DAT_BuildingsState::instance.buildings[_buildingID].widthOrHeight);
                for (int _otherUnitID = (short)DAT_TileMapState::instance
                         .UnitLayer[DAT_ViewportRenderState::instance
                                        .translationMatrix[DAT_TileMapState::instance.buildingY
                                            + (short)DAT_BuildingsState::instance.buildings[_buildingID].y]
                                        .addXgetTile
                             + DAT_TileMapState::instance.buildingX
                             + (short)DAT_BuildingsState::instance.buildings[_buildingID].x];
                    _otherUnitID != 0;
                    _otherUnitID = (short)DAT_UnitsState::instance.units[_otherUnitID].nextUnitOnTheSameTile) {
                    if (DAT_UnitsState::instance.units[_otherUnitID].owner
                        == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        _ownUnitsOnBuilding = _ownUnitsOnBuilding + 1;
                    }
                }
            }
            if (_ownUnitsOnBuilding < _tileCapacity / 2) {
                return FALSE;
            }
            if (_tileCapacity <= _ownUnitsOnBuilding) {
                return TRUE;
            }
            int _selectedUnitCount = 0;
            for (int i = 0; i < 27; ++i) {
                if (i != 6 && i != 8 && i != 11 && i != 12 && i != 13 && i != 14) {
                    _selectedUnitCount = _selectedUnitCount + (&this->selectionEuropeanArchers)[i];
                }
            }
            return (BOOLEnum)((_tileCapacity - _ownUnitsOnBuilding) * 2 < _selectedUnitCount);
        }

    }
}
}
