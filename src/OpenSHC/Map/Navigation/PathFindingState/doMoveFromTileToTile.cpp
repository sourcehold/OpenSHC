#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::Map::Entities::EntityType;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::Map::Units::States::UnitState;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00497280
        BOOLEnum PathFindingState::doMoveFromTileToTile(
            int unitID, int tile, int y, int direction, int param_5, int ignoreAssassinClimbing)
        {
            short* psVar1;
            int bVar2;
            uint uVar3;
            int _targetTile;
            uint uVar4;
            int _terrainHeight2;
            int _height;
            int _terrainHeight;
            if (param_5 != 0) {
                if (param_5 == 1) {
                    if ((DAT_TileMapState::instance
                                .LogicLayer[DAT_TileMapState::instance.directionTranslationMatrix[y][direction] + tile]
                            & 0x30U)
                        != 0) {
                        return FALSE;
                    }
                    if ((DAT_TileMapState::instance
                                .LogicLayer[DAT_TileMapState::instance.directionTranslationMatrix[y][direction] + tile]
                            & 1U)
                        != 0) {
                        return FALSE;
                    }
                }
                return TRUE;
            }
            /*
              if we cannot move in that direction from the current tile?
             */
            if ((DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[direction]
                    & DAT_TileMapState::instance.PathLinkageLayer[tile])
                == 0) {
                _targetTile = DAT_TileMapState::instance.directionTranslationMatrix[y][direction] + tile;
                if (ignoreAssassinClimbing == 0) {
                    if (DAT_UnitsState::instance.units[unitID].unitType == OpenSHC::Map::Units::UT_A_ASSASSIN) {
                        uVar3 = DAT_TileMapState::instance.LogicLayer[_targetTile];
                        if ((uVar3 & 0x4a5014b1) == 0
                            && (uVar4 = DAT_TileMapState::instance.LogicLayer[tile] & 0x100,
                                uVar4 == 0 || ((uVar3 & 0x100) == 0))
                            && (uVar4 != 0 || ((uVar3 & 0x100) != 0))) {
                            _height = DAT_TileMapState::instance.HeightLayer[tile];
                            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                            DAT_UnitsState::instance.units[unitID].field306_0x418 = 0;
                            if (uVar4 == 0) {
                                _terrainHeight = DAT_TileMapState::instance.HeightLayer[_targetTile];
                                bVar2 = DAT_TileMapState::instance.WallOwnerLayer[_targetTile];
                                DAT_UnitsState::instance.units[unitID].state.generic
                                    = OpenSHC::Map::Units::States::US_ASSASSIN_THROWING_HOOK;
                                DAT_UnitsState::instance.units[unitID].assassinHeightDifference
                                    = (ushort)_terrainHeight - (ushort)_height;
                                DAT_UnitsState::instance.units[unitID].assassinClimbingUpUnk_OR_previousFacingDirection
                                    = 1;
                                DAT_UnitsState::instance.units[unitID].ownerOfAssassinScaledObject = (bVar2 & 7) + 1;
                            } else {
                                _terrainHeight2 = DAT_TileMapState::instance.HeightLayer[_targetTile];
                                DAT_UnitsState::instance.units[unitID].state.generic
                                    = OpenSHC::Map::Units::States::US_ASSASSIN_START_CLIMBING_DOWN;
                                DAT_UnitsState::instance.units[unitID].assassinHeightDifference
                                    = (ushort)_height - (ushort)_terrainHeight2;
                                DAT_UnitsState::instance.units[unitID].assassinClimbingUpUnk_OR_previousFacingDirection
                                    = 0;
                            }
                            if (DAT_UnitsState::instance.units[unitID].assassinHeightDifference < 0) {
                                DAT_UnitsState::instance.units[unitID].assassinHeightDifference = 0;
                            }
                            return TRUE;
                        }
                        return FALSE;
                    }
                } else {
                    uVar3 = DAT_TileMapState::instance.LogicLayer[_targetTile];
                    if ((uVar3 & 0x40000000) != 0) {
                        return TRUE;
                    }
                    if ((DAT_TileMapState::instance.LogicLayer[tile] & 0x40000000U) != 0 && (uVar3 & 0x4a5014b1) == 0) {
                        return ~(uVar3 >> 8) & TRUE;
                    }
                }
            } else {
                if ((DAT_EntityState::instance.fireCount == 0)
                    || (DAT_UnitsState::instance.units[unitID].field295_0x40a != 0)) {
                    DAT_UnitsState::instance.units[unitID].counter = 0;
                    return TRUE;
                }
                if (DAT_TileMapState::instance
                        .EntityLayer[DAT_TileMapState::instance.directionTranslationMatrix[y][direction] + tile]
                    == 0) {
                    return TRUE;
                }
                if (DAT_EntityState::instance
                        .entityArray[DAT_TileMapState::instance.EntityLayer
                                [DAT_TileMapState::instance.directionTranslationMatrix[y][direction] + tile]]
                        .entityType
                    != OpenSHC::Map::Entities::ET_FIRE) {
                    return TRUE;
                }
                if ((DAT_TileMapState::instance.EntityLayer[tile] != 0)
                    && (DAT_EntityState::instance.entityArray[DAT_TileMapState::instance.EntityLayer[tile]].entityType
                        == OpenSHC::Map::Entities::ET_FIRE)) {
                    return TRUE;
                }
                DAT_UnitsState::instance.units[unitID].counter = DAT_UnitsState::instance.units[unitID].counter + 1;
                DAT_UnitsState::instance.units[unitID].field280_0x3f4 = 5;
                DAT_UnitsState::instance.units[unitID].field295_0x40a = 1;
            }
            return FALSE;
        }

    }
}
}
