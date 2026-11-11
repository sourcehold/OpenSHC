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
    BOOLEnum TileMapState::findNearestValidDigTileNearTarget(uint x1, uint y1, uint x2, uint y2)
    {
        if (x1 > MC_MAP_XY_LIMIT_INCLUSIVE || y1 > MC_MAP_XY_LIMIT_INCLUSIVE) {
            return FALSE;
        }
        if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y1 * MC_MAP_XY_LIMIT + x1] == 0) {
            return FALSE;
        }
        if (x2 > MC_MAP_XY_LIMIT_INCLUSIVE || y2 > MC_MAP_XY_LIMIT_INCLUSIVE
            || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y2 * MC_MAP_XY_LIMIT + x2] == 0) {
            return FALSE;
        }

        int area = (short)this
                       ->PathConnectionLayer[DAT_ViewportRenderState::instance.translationMatrix[y1].addXgetTile + x1];
        int targetTile = DAT_ViewportRenderState::instance.translationMatrix[y2].addXgetTile + x2;
        int bestDistance = 10000;
        int bestIndex = -1;
        uint targetHeight = this->HeightLayer[targetTile];
        int targetBuildingID = this->BuildingLayer[targetTile];
        if (targetBuildingID != 0) {
            targetHeight
                += MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                    DAT_BuildingsState::ptr)(targetBuildingID);
        }

        for (int index = 0; index < countof(DAT_TerrainDefinedData::instance.field_0x378c); index++) {
            int fromXPosition = DAT_TerrainDefinedData::instance.field_0x378c[index].x + x2;
            int fromYPosition = DAT_TerrainDefinedData::instance.field_0x378c[index].y + y2;
            int tile = DAT_ViewportRenderState::instance.translationMatrix[fromYPosition].addXgetTile + fromXPosition;
            if (this->PathConnectionLayer[tile] != area) {
                continue;
            }
            uint height = this->HeightLayer[tile];
            int buildingID = this->BuildingLayer[tile];
            if (buildingID != 0) {
                height
                    += MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                        DAT_BuildingsState::ptr)(buildingID);
            }
            if ((int)height >= (int)(targetHeight + 16) || (int)height <= (int)(targetHeight - 16)) {
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
            this->field_0x5549a8 = x2;
            this->field_0x5549ac = y2;
            return FALSE;
        }
        this->field_0x5549a8 = DAT_TerrainDefinedData::instance.field_0x378c[bestIndex].x + x2;
        this->field_0x5549ac = DAT_TerrainDefinedData::instance.field_0x378c[bestIndex].y + y2;
        return TRUE;
    }

}
}
