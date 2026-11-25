#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051F4B0
        void TroopValueState::scanForSupportPoints()
        {
            DAT_TroopValueState::instance.attackInfo.supportPoints = 0;
            for (int tile = 0; tile < countof(DAT_TileMapState::instance.AIInfoLayer); ++tile) {
                if (DAT_TileMapState::instance.AIInfoLayer[tile] != 1) {
                    continue;
                }
                uint const y = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
                for (int direction = 0; direction < 4; ++direction) {
                    if ((DAT_TileMapState::instance
                                .AIInfoLayer[DAT_TileMapState::instance.directionTranslationMatrix[y][direction * 2]
                                    + tile]
                            & 0xf)
                            != 2
                        || (DAT_TileMapState::instance
                                .RandomLayer[DAT_TileMapState::instance.directionTranslationMatrix[y][direction * 2]
                                    + tile]
                            & 3)) {
                        continue;
                    }
                    uint const x = tile - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
                    BOOLEnum const hasSupportZoneFlag
                        = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findAIZoneWithFlags,
                            DAT_PathFindingState::ptr)(8, x, y, 0x40);
                    if (hasSupportZoneFlag) {
                        continue;
                    }
                    DAT_TileMapState::instance.AIInfoLayer[tile] |= 0x40;
                    int const existingPointIndex
                        = MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::getSupportPointIndex, this)(tile);
                    int const nextPointIndex = DAT_TroopValueState::instance.attackInfo.supportPointsNext;
                    if (existingPointIndex) {
                        DAT_TroopValueState::instance.attackInfo.supportPointsArray[existingPointIndex].someCounter
                            = DAT_TroopValueState::instance.attackInfo.someCounter1;
                    } else {
                        DAT_TroopValueState::instance.attackInfo
                            .supportPointsArray[DAT_TroopValueState::instance.attackInfo.supportPointsNext]
                            .x = x;
                        DAT_TroopValueState::instance.attackInfo.supportPointsArray[nextPointIndex].y = y;
                        DAT_TroopValueState::instance.attackInfo.supportPointsArray[nextPointIndex].tile = tile;
                        DAT_TroopValueState::instance.attackInfo.supportPointsArray[nextPointIndex].someCounter
                            = DAT_TroopValueState::instance.attackInfo.someCounter1;
                    }
                    ++DAT_TroopValueState::instance.attackInfo.supportPoints;
                    if (200 <= DAT_TroopValueState::instance.attackInfo.supportPoints) {
                        return;
                    }
                    break;
                }
            }
        }

    }
}
}
