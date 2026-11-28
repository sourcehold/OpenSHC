#include "../../Map.func.hpp"
#include "../WildlifeState.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    using WindowsHelper::Enums::BOOLEnum;

    /*
      Takes a tribe index (param_1) and builds a rally point path for that tribe. First BFS-floods   field20_0x50
      outward from the tribe's unit position (derived from selectionTargetUnitID),   restricted to cells in the same
      separateAreaID. Then greedily traces a path from the start cell   by always stepping to the highest-scoring
      unvisited neighbour, recording each step as a rally   point in the tribe's rallyPointArray. Returns 1 on success,
      0 if the start cell has no   field20_0x50 value (unreachable or unscored area).      renamed by: Claude Sonnet 4.6
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0052CFE0
    BOOLEnum WildlifeState::buildRallyPointPathForTribe(int param_1, int param_2)
    {
        int x = DAT_UnitsState::instance.units[DAT_TribesState::instance.tribes[param_1].selectionTargetUnitID].x / 10;
        int y = DAT_UnitsState::instance.units[DAT_TribesState::instance.tribes[param_1].selectionTargetUnitID].y / 10;
        this->casDisRelated = param_2;
        this->candidateIndex = 0;
        this->candidateIndex2 = 1;
        if (this->grid[x][y].field_0x50 == 0) {
            return FALSE;
        }
        for (int row = 0; row < 40; row++) {
            for (int column = 0; column < 40; column++) {
                this->grid[column][row].casDisRelated2 = 0;
                this->grid[column][row].field_0x3c = 0;
            }
        }
        this->DAT_Y10_Array_Section1034[0] = (short)y;
        this->DAT_X10_Array_Section1034[0] = (short)x;
        this->grid[x][y].casDisRelated2 = this->grid[x][y].field_0x50;
        int const areaID = this->grid[x][y].separateAreaID;
        while (this->candidateIndex != this->candidateIndex2) {
            int const candidateX = this->DAT_X10_Array_Section1034[this->candidateIndex];
            int const candidateY = this->DAT_Y10_Array_Section1034[this->candidateIndex];
            for (int direction = 0; direction < 8; direction++) {
                uint const neighbourX
                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction].int_.xOffset
                    + candidateX;
                uint const neighbourY
                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction].int_.yOffset
                    + candidateY;
                if (neighbourX <= 39 && neighbourY <= 39 && this->grid[neighbourX][neighbourY].firstMember > 0
                    && areaID == this->grid[neighbourX][neighbourY].separateAreaID
                    && this->grid[neighbourX][neighbourY].field_0x50 > 0
                    && this->grid[neighbourX][neighbourY].casDisRelated2 == 0) {
                    this->grid[neighbourX][neighbourY].casDisRelated2 = this->grid[neighbourX][neighbourY].field_0x50;
                    this->DAT_X10_Array_Section1034[this->candidateIndex2] = (short)neighbourX;
                    this->DAT_Y10_Array_Section1034[this->candidateIndex2] = (short)neighbourY;
                    this->candidateIndex2 = this->candidateIndex2 + 1;
                    if (this->candidateIndex2 >= 1600) {
                        this->candidateIndex2 = 0;
                    }
                }
            }
            this->candidateIndex = this->candidateIndex + 1;
            if (this->candidateIndex >= 1600) {
                this->candidateIndex = 0;
            }
        }
        uint const rng = (byte)SEC_RNG::instance.currentNumber2;
        DAT_TribesState::instance.tribes[param_1].currentRallyPointIndex = 0;
        DAT_TribesState::instance.tribes[param_1].rallyPointCount = 0;
        this->grid[x][y].field_0x3c = 1;
        this->grid[x][y].casDisRelated2 = 0;
        while (true) {
            int bestDirection = -1;
            for (int k = 0; k < 8; k++) {
                int direction = (rng & 7) + k;
                if (direction >= 8) {
                    direction = direction - 8;
                }
                uint const neighbourX
                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction].int_.xOffset + x;
                uint const neighbourY
                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction].int_.yOffset + y;
                if (neighbourX <= 39 && neighbourY <= 39 && this->grid[neighbourX][neighbourY].firstMember > 0
                    && this->grid[neighbourX][neighbourY].casDisRelated2 != 0
                    && this->grid[neighbourX][neighbourY].casDisRelated2 > param_2) {
                    int const distance = this->grid[neighbourX][neighbourY].casDisRelated2;
                    this->grid[neighbourX][neighbourY].casDisRelated2 = 0;
                    param_2 = distance;
                    bestDirection = direction;
                }
            }
            if (bestDirection <= -1) {
                return TRUE;
            }
            x = x + DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[bestDirection].int_.xOffset;
            y = y + DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[bestDirection].int_.yOffset;
            this->grid[x][y].field_0x3c = 1;
            uint const tileX = x * 10 + 5;
            uint const tileY = y * 10 + 5;
            if (tileX <= 399 && tileY <= 399
                && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[tileY * 400 + tileX] != '\0') {
                DAT_TribesState::instance.tribes[param_1]
                    .rallyPointArray[DAT_TribesState::instance.tribes[param_1].rallyPointCount][0] = (short)x * 10 + 5;
                DAT_TribesState::instance.tribes[param_1]
                    .rallyPointArray[DAT_TribesState::instance.tribes[param_1].rallyPointCount][1] = (short)y * 10 + 5;
                DAT_TribesState::instance.tribes[param_1].rallyPointCount
                    = DAT_TribesState::instance.tribes[param_1].rallyPointCount + 1;
            }
        }
    }

}
}
