#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/MapConstants.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00500980
    BOOLEnum TileMapState::findNearestValidDigTileNearTarget(int x1, int y1, int x2, int y2)
    {
        if (x1 < 0 || x1 > MC_MAP_XY_LIMIT_INCLUSIVE || y1 < 0 || y1 > MC_MAP_XY_LIMIT_INCLUSIVE) {
            return FALSE;
        }
        if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y1 * MC_MAP_XY_LIMIT + x1] == 0) {
            return FALSE;
        }
        if (x2 < 0 || x2 > MC_MAP_XY_LIMIT_INCLUSIVE || y2 < 0 || y2 > MC_MAP_XY_LIMIT_INCLUSIVE
            || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y2 * MC_MAP_XY_LIMIT + x2] == 0) {
            return FALSE;
        }

        int area = this->PathConnectionLayer[DAT_ViewportRenderState::instance.translationMatrix[y1].addXgetTile + x1];
        int targetTile = DAT_ViewportRenderState::instance.translationMatrix[y2].addXgetTile + x2;
        int bestDistance = 10000;
        int bestIndex = -1;
        int targetHeight = this->HeightLayer[targetTile];
        int targetBuildingID = this->BuildingLayer[targetTile];
        if (targetBuildingID != 0) {
            targetHeight
                += MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                    DAT_BuildingsState::ptr)(targetBuildingID);
        }

        for (int index = 0; index < countof(DAT_TerrainDefinedData::instance.twoTileAxisOffsets); index++) {
            int fromXPosition = DAT_TerrainDefinedData::instance.twoTileAxisOffsets[index].x + x2;
            int fromYPosition = DAT_TerrainDefinedData::instance.twoTileAxisOffsets[index].y + y2;
            int tile = DAT_ViewportRenderState::instance.translationMatrix[fromYPosition].addXgetTile + fromXPosition;
            if (this->PathConnectionLayer[tile] != area) {
                continue;
            }
            int height = this->HeightLayer[tile];
            int buildingID = this->BuildingLayer[tile];
            if (buildingID != 0) {
                height
                    += MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                        DAT_BuildingsState::ptr)(buildingID);
            }
            if (height >= targetHeight + 16 || height <= targetHeight - 16) {
                continue;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                DAT_DirectionAlgorithmState::ptr)(x1, y1, fromXPosition, fromYPosition);
            if (DAT_DirectionAlgorithmState::instance.distanceHigh < bestDistance) {
                bestDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                bestIndex = index;
            }
        }

        if (bestIndex <= -1) {
            this->destinationNearTargetX = x2;
            this->destinationNearTargetY = y2;
            return FALSE;
        }
        this->destinationNearTargetX = DAT_TerrainDefinedData::instance.twoTileAxisOffsets[bestIndex].x + x2;
        this->destinationNearTargetY = DAT_TerrainDefinedData::instance.twoTileAxisOffsets[bestIndex].y + y2;
        return TRUE;
    }

}
}
