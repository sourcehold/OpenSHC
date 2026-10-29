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
        int brushStep = DAT_TerrainDefinedData::instance.field12_0xc[index];
        if (brushStep == 0xf) {
            return;
        }
        if (brushStep < 8) {
            *tilePointer = *tilePointer + this->directionTranslationMatrix[*yPointer][brushStep];
            *yPointer = *yPointer
                + DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[brushStep].int_.yOffset;
            return;
        }

        if (brushStep < 28) {
            brushStep = brushStep - 20;
            *tilePointer = *tilePointer + this->directionTranslationMatrix[*yPointer][brushStep];
            *yPointer
                = *yPointer + DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[brushStep].int_.yOffset;
            *tilePointer = *tilePointer + this->directionTranslationMatrix[*yPointer][brushStep];
            *yPointer
                = *yPointer + DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[brushStep].int_.yOffset;
        } else if (brushStep < 48) {
            brushStep = brushStep - 40;
            *tilePointer = *tilePointer + this->directionTranslationMatrix[*yPointer][brushStep];
            *yPointer
                = *yPointer + DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[brushStep].int_.yOffset;
            *tilePointer = *tilePointer + this->directionTranslationMatrix[*yPointer][brushStep];
            *yPointer
                = *yPointer + DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[brushStep].int_.yOffset;
            *tilePointer = *tilePointer + this->directionTranslationMatrix[*yPointer][brushStep];
            *yPointer
                = *yPointer + DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[brushStep].int_.yOffset;
        }
    }

}
}
