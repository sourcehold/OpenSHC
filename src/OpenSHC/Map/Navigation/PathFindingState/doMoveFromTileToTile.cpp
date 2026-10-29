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
            int unitID, int tileUnk, int y, int direction, int param_5, int ignoreAssassinClimbing)
        {
            uint uVar3;
            int _targetTile;
            uint uVar4;
            ushort _height;
            if (param_5 == 0) {
                /*
                  if we cannot move in that direction from the current tileUnk?
                 */
                if ((DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[direction]
                        & DAT_TileMapState::instance.PathLinkageLayer[tileUnk])
                    == 0) {
                    _targetTile = DAT_TileMapState::instance.directionTranslationMatrix[y][direction] + tileUnk;
                    if (ignoreAssassinClimbing == 0) {
                        if (DAT_UnitsState::instance.units[unitID].unitType == OpenSHC::Map::Units::UT_A_ASSASSIN) {
                            uVar3 = DAT_TileMapState::instance.LogicLayer[_targetTile];
                            if ((uVar3 & 0x4a5014b1) != 0) {
                                return FALSE;
                            }
                            uVar4 = DAT_TileMapState::instance.LogicLayer[tileUnk] & 0x100;
                            if (uVar4 != 0 && (uVar3 & 0x100) != 0) {
                                return FALSE;
                            }
                            if (uVar4 == 0 && (uVar3 & 0x100) == 0) {
                                return FALSE;
                            }
                            _height = DAT_TileMapState::instance.HeightLayer[tileUnk];
                            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                            DAT_UnitsState::instance.units[unitID].field306_0x418 = 0;
                            if (uVar4 != 0) {
                                DAT_UnitsState::instance.units[unitID].state.generic
                                    = OpenSHC::Map::Units::States::US_ASSASSIN_START_CLIMBING_DOWN;
                                DAT_UnitsState::instance.units[unitID].assassinHeightDifference
                                    = _height - (ushort)DAT_TileMapState::instance.HeightLayer[_targetTile];
                                DAT_UnitsState::instance.units[unitID].assassinClimbingUpUnk_OR_previousFacingDirection = 0;
                            } else {
                                DAT_UnitsState::instance.units[unitID].state.generic
                                    = OpenSHC::Map::Units::States::US_ASSASSIN_THROWING_HOOK;
                                DAT_UnitsState::instance.units[unitID].assassinHeightDifference
                                    = (ushort)DAT_TileMapState::instance.HeightLayer[_targetTile] - _height;
                                DAT_UnitsState::instance.units[unitID].assassinClimbingUpUnk_OR_previousFacingDirection = 1;
                                DAT_UnitsState::instance.units[unitID].ownerOfAssassinScaledObject
                                    = (DAT_TileMapState::instance.WallOwnerLayer[_targetTile] & 7) + 1;
                            }
                            if (DAT_UnitsState::instance.units[unitID].assassinHeightDifference < 0) {
                                DAT_UnitsState::instance.units[unitID].assassinHeightDifference = 0;
                            }
                            return TRUE;
                        }
                    } else {
                        uVar3 = DAT_TileMapState::instance.LogicLayer[_targetTile];
                        if ((uVar3 & 0x40000000) != 0) {
                            return TRUE;
                        }
                        if ((DAT_TileMapState::instance.LogicLayer[tileUnk] & 0x40000000U) != 0
                            && (uVar3 & 0x4a5014b1) == 0) {
                            return ~(uVar3 >> 8) & TRUE;
                        }
                    }
                } else {
                    if ((DAT_EntityState::instance.fireCount == 0)
                        || (DAT_UnitsState::instance.units[unitID].field295_0x40a != 0)) {
                        DAT_UnitsState::instance.units[unitID].counter = 0;
                        return TRUE;
                    }
                    int _entity = (short)DAT_TileMapState::instance
                                      .EntityLayer[DAT_TileMapState::instance.directionTranslationMatrix[y][direction] + tileUnk];
                    if (_entity == 0) {
                        return TRUE;
                    }
                    if (DAT_EntityState::instance.entityArray[_entity].entityType != OpenSHC::Map::Entities::ET_FIRE) {
                        return TRUE;
                    }
                    _entity = (short)DAT_TileMapState::instance.EntityLayer[tileUnk];
                    if (_entity != 0
                        && DAT_EntityState::instance.entityArray[_entity].entityType == OpenSHC::Map::Entities::ET_FIRE) {
                        return TRUE;
                    }
                    DAT_UnitsState::instance.units[unitID].counter = DAT_UnitsState::instance.units[unitID].counter + 1;
                    DAT_UnitsState::instance.units[unitID].field280_0x3f4 = 5;
                    DAT_UnitsState::instance.units[unitID].field295_0x40a = 1;
                }
                return FALSE;
            }
            if (param_5 == 1) {
                uVar3 = DAT_TileMapState::instance
                            .LogicLayer[DAT_TileMapState::instance.directionTranslationMatrix[y][direction] + tileUnk];
                if ((uVar3 & 0x30) != 0) {
                    return FALSE;
                }
                if ((uVar3 & 1) == 0) {
                    return TRUE;
                }
                return FALSE;
            }
            return TRUE;
        }

    }
}
}
