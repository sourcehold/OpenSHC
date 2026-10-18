#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0052F5B0
        undefined4 UnitsState::ifAnyUnitOnSameTileIsLadderInRightDirection(int tile, int y)
        {
            /* the original is written out per direction rather than looped */
            int _neighbourTile = DAT_TileMapState::instance.directionTranslationMatrix[y][0] + tile;
            if ((DAT_TileMapState::instance.LogicLayer[_neighbourTile] & 0x4a5015b1U) == 0
                && DAT_TileMapState::instance.UnitLayer[_neighbourTile] != 0
                && MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::ifAnyUnitOnSameTileIsLadder, this)(
                       _neighbourTile)
                    != FALSE) {
                return 1;
            }
            _neighbourTile = DAT_TileMapState::instance.directionTranslationMatrix[y][2] + tile;
            if ((DAT_TileMapState::instance.LogicLayer[_neighbourTile] & 0x4a5015b1U) == 0
                && DAT_TileMapState::instance.UnitLayer[_neighbourTile] != 0
                && MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::ifAnyUnitOnSameTileIsLadder, this)(
                       _neighbourTile)
                    != FALSE) {
                return 1;
            }
            _neighbourTile = DAT_TileMapState::instance.directionTranslationMatrix[y][4] + tile;
            if ((DAT_TileMapState::instance.LogicLayer[_neighbourTile] & 0x4a5015b1U) == 0
                && DAT_TileMapState::instance.UnitLayer[_neighbourTile] != 0
                && MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::ifAnyUnitOnSameTileIsLadder, this)(
                       _neighbourTile)
                    != FALSE) {
                return 1;
            }
            _neighbourTile = DAT_TileMapState::instance.directionTranslationMatrix[y][6] + tile;
            if ((DAT_TileMapState::instance.LogicLayer[_neighbourTile] & 0x4a5015b1U) == 0
                && DAT_TileMapState::instance.UnitLayer[_neighbourTile] != 0
                && MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::ifAnyUnitOnSameTileIsLadder, this)(
                       _neighbourTile)
                    != FALSE) {
                return 1;
            }
            return 0;
        }

    }
}
}
