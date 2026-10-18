#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051F340
        void TroopValueState::scanForArcherPoints()
        {
            BOOLEnum hasArcherZoneFlag;
            int _existingPointIndex;
            int _searchRadius;
            DAT_TroopValueState::instance.attackInfo.archerPoints = 0;
            if ((int)DAT_TroopValueState::instance.attackInfo.archerPointCountPrev < 0) {
                _searchRadius = 8;
            } else if ((int)DAT_TroopValueState::instance.attackInfo.archerPointCountPrev < 2) {
                _searchRadius = 5;
            } else if ((int)DAT_TroopValueState::instance.attackInfo.archerPointCountPrev < 4) {
                _searchRadius = 6;
            } else if ((int)DAT_TroopValueState::instance.attackInfo.archerPointCountPrev < 8) {
                _searchRadius = 7;
            } else {
                _searchRadius
                    = (uint)(0x14 <= (int)DAT_TroopValueState::instance.attackInfo.archerPointCountPrev) * 2 + 8;
            }
            for (int tile = 0; tile < 80400; tile = tile + 1) {
                if (DAT_TileMapState::instance.AIInfoLayer[tile] == '') {
                    uint const y = (uint)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
                    for (int _direction = 0; _direction < 4; _direction = _direction + 1) {
                        if ((DAT_TileMapState::instance.AIInfoLayer
                                    [DAT_TileMapState::instance.directionTranslationMatrix[y][_direction * 2] + tile]
                                & 0xf)
                                == 4
                            && !(DAT_TileMapState::instance.RandomLayer
                                     [DAT_TileMapState::instance.directionTranslationMatrix[y][_direction * 2] + tile]
                                & 3)) {
                            uint const x = tile - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
                            hasArcherZoneFlag
                                = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findAIZoneWithFlags,
                                    DAT_PathFindingState::ptr)(_searchRadius, x, y, 0x10);
                            if (!hasArcherZoneFlag) {
                                DAT_TileMapState::instance.AIInfoLayer[tile]
                                    = DAT_TileMapState::instance.AIInfoLayer[tile] | 0x10;
                                _existingPointIndex = MACRO_CALL_MEMBER(
                                    Map::Units::TroopValueState_Func::findOrReserveArcherPointSlot, this)(tile);
                                int const _nextPointIndex = DAT_TroopValueState::instance.attackInfo.archerPointsNext;
                                if (_existingPointIndex) {
                                    DAT_TroopValueState::instance.attackInfo.archerPointArray[_existingPointIndex]
                                        .lastSeenCounter = DAT_TroopValueState::instance.attackInfo.someCounter1;
                                } else {
                                    DAT_TroopValueState::instance.attackInfo
                                        .archerPointArray[DAT_TroopValueState::instance.attackInfo.archerPointsNext]
                                        .field0_0x0 = x;
                                    DAT_TroopValueState::instance.attackInfo.archerPointArray[_nextPointIndex]
                                        .field1_0x4 = y;
                                    DAT_TroopValueState::instance.attackInfo.archerPointArray[_nextPointIndex].tile
                                        = tile;
                                    DAT_TroopValueState::instance.attackInfo.archerPointArray[_nextPointIndex]
                                        .lastSeenCounter = DAT_TroopValueState::instance.attackInfo.someCounter1;
                                }
                                DAT_TroopValueState::instance.attackInfo.archerPoints
                                    = DAT_TroopValueState::instance.attackInfo.archerPoints + 1;
                                if (200 <= DAT_TroopValueState::instance.attackInfo.archerPoints) {
                                    DAT_TroopValueState::instance.attackInfo.archerPointCountPrev
                                        = DAT_TroopValueState::instance.attackInfo.archerPoints;
                                    return;
                                }
                                break;
                            }
                        }
                    }
                }
            }
            DAT_TroopValueState::instance.attackInfo.archerPointCountPrev
                = DAT_TroopValueState::instance.attackInfo.archerPoints;
        }

    }
}
}
