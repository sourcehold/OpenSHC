#include "../UnitsState.func.hpp"

#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Units/Selection/UnitSelectionEnumInt.hpp"
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
            if (_buildingID != 0) {
                BuildingTypeShort _buildingType = DAT_BuildingsState::instance.buildings[_buildingID].buildingType;
                if (_buildingType == OpenSHC::Map::Buildings::BT_TOWER1
                    || _buildingType == OpenSHC::Map::Buildings::BT_TOWER2
                    || _buildingType == OpenSHC::Map::Buildings::BT_TOWER3
                    || _buildingType == OpenSHC::Map::Buildings::BT_TOWER4
                    || _buildingType == OpenSHC::Map::Buildings::BT_TOWER5
                    || _buildingType == OpenSHC::Map::Buildings::BT_STONEKEEP
                    || _buildingType == OpenSHC::Map::Buildings::BT_STRONGHOLD
                    || _buildingType == OpenSHC::Map::Buildings::BT_KEEPFOUR
                    || _buildingType == OpenSHC::Map::Buildings::BT_KEEPFIVE) {
                    int _tileCapacity = DAT_BuildingsState::instance.buildings[_buildingID].widthOrHeight
                        * DAT_BuildingsState::instance.buildings[_buildingID].widthOrHeight;
                    if (_buildingType == OpenSHC::Map::Buildings::BT_TOWER1) {
                        _tileCapacity = 5;
                    }
                    int _buildingY = DAT_BuildingsState::instance.buildings[_buildingID].y;
                    int _buildingX = DAT_BuildingsState::instance.buildings[_buildingID].x;
                    /* The original counts the own units in the parameter's stack slot. */
                    tile = 0;
                    int _constructionTile = 0;
                    /* a do-while: the original runs the body once even when there is no construction tile */
                    do {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, DAT_TileMapState::ptr)(
                            _constructionTile, DAT_BuildingsState::instance.buildings[_buildingID].widthOrHeight);
                        for (int _otherUnitID = (short)DAT_TileMapState::instance
                                 .UnitLayer[DAT_ViewportRenderState::instance
                                                .translationMatrix[DAT_TileMapState::instance.buildingY + _buildingY]
                                                .addXgetTile
                                     + DAT_TileMapState::instance.buildingX + _buildingX];
                            _otherUnitID != 0;
                            _otherUnitID = DAT_UnitsState::instance.units[_otherUnitID].nextUnitOnTheSameTile) {
                            if (DAT_UnitsState::instance.units[_otherUnitID].owner
                                == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                                tile = tile + 1;
                            }
                        }
                        _constructionTile++;
                    } while (_constructionTile < DAT_TileMapState::instance.constructionTileCount);
                    if (tile >= _tileCapacity / 2) {
                        if (tile >= _tileCapacity) {
                            return TRUE;
                        }
                        int _freeCapacity = _tileCapacity - tile;
                        int _selectedUnitCount = 0;
                        for (int i = 0; i <= 26; ++i) {
                            if (i != Selection::USE_E_KNIGHTS && i != Selection::USE_E_LADDERMEN
                                && i != Selection::USE_E_BATTERING_RAMS && i != Selection::USE_E_TREBUCHETS
                                && i != Selection::USE_E_CATAPULTS && i != Selection::USE_E_SIEGETOWERS) {
                                _selectedUnitCount = _selectedUnitCount + this->selectionUnitType[i];
                            }
                        }
                        return _selectedUnitCount > _freeCapacity * 2;
                    }
                }
            }
            return FALSE;
        }

    }
}
}
