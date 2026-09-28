#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
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
    // FUNCTION: STRONGHOLDCRUSADER 0x00500980
    undefined4 TileMapState::findNearestValidDigTileNearTarget(uint x1, uint y1, uint x2, uint y2)
    {
        if (x1 > 399 || y1 > 399) {
            return 0;
        }
        if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y1 * 400 + x1] == 0) {
            return 0;
        }
        if (x2 > 399 || y2 > 399) {
            return 0;
        }
        if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y2 * 400 + x2] == 0) {
            return 0;
        }

        ushort area
            = this->PathConnectionLayer[DAT_ViewportRenderState::instance.translationMatrix[y1].addXgetTile + x1];
        int targetTile = DAT_ViewportRenderState::instance.translationMatrix[y2].addXgetTile + x2;
        uint targetHeight = this->HeightLayer[targetTile];
        int bestDistance = 10000;
        int bestIndex = -1;
        if (this->BuildingLayer[targetTile] != 0) {
            targetHeight = targetHeight
                + MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                    DAT_BuildingsState::ptr)(this->BuildingLayer[targetTile]);
        }

        for (int index = 0; index < 4; index++) {
            int fromXPosition = DAT_TerrainDefinedData::instance.field2478_0x378c[index].x + x2;
            int fromYPosition = DAT_TerrainDefinedData::instance.field2478_0x378c[index].y + y2;
            int tile = DAT_ViewportRenderState::instance.translationMatrix[fromYPosition].addXgetTile + fromXPosition;
            if (this->PathConnectionLayer[tile] != area) {
                continue;
            }
            uint height = this->HeightLayer[tile];
            if (this->BuildingLayer[tile] != 0) {
                height = height
                    + MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                        DAT_BuildingsState::ptr)(this->BuildingLayer[tile]);
            }
            if ((int)height >= (int)(targetHeight + 0x10) || (int)(targetHeight - 0x10) >= (int)height) {
                continue;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                DAT_DirectionAlgorithmState::ptr)(x1, y1, fromXPosition, fromYPosition);
            if (DAT_DirectionAlgorithmState::instance.distanceHigh < bestDistance) {
                bestDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                bestIndex = index;
            }
        }

        if (bestIndex >= 0) {
            this->field155_0x5549a8 = DAT_TerrainDefinedData::instance.field2478_0x378c[bestIndex].x + x2;
            this->field156_0x5549ac = DAT_TerrainDefinedData::instance.field2478_0x378c[bestIndex].y + y2;
            return 1;
        }
        this->field155_0x5549a8 = x2;
        this->field156_0x5549ac = y2;
        return 0;
    }

}
}
