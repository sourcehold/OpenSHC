#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004FBD80
    void TileMapState::getTileForBrush(int square, int index, int* tilePointer, int* yPointer, int baseTile, uint y)
    {
        if (square != 0) {
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Navigation::PathFindingState_Func::getTileInSquareBrush, DAT_PathFindingState::ptr)(
                index, baseTile - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile, y);
            *tilePointer = DAT_PathFindingState::instance.resultTile;
            *yPointer = DAT_PathFindingState::instance.resultY;
            return;
        }

        if (index >= 37) {
            index = 0;
        }
        int direction = DAT_TerrainDefinedData::instance.field12_0xc[index];
        if (direction == 0xf) {
            return;
        }
        if (direction < 8) {
            *tilePointer = *tilePointer + this->directionTranslationMatrix[*yPointer][direction];
            *yPointer = *yPointer
                + DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction].int_.yOffset;
            return;
        }

        /* 20 to 27 step twice in a direction, 40 to 47 three times */
        if (direction < 28) {
            direction = direction - 20;
        } else {
            if (direction >= 48) {
                return;
            }
            direction = direction - 40;
            *tilePointer = *tilePointer + this->directionTranslationMatrix[*yPointer][direction];
            *yPointer = *yPointer
                + DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction].int_.yOffset;
        }
        *tilePointer = *tilePointer + this->directionTranslationMatrix[*yPointer][direction];
        *yPointer
            = *yPointer + DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction].int_.yOffset;
        *tilePointer = *tilePointer + this->directionTranslationMatrix[*yPointer][direction];
        *yPointer
            = *yPointer + DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction].int_.yOffset;
    }

}
}
