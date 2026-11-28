#include "../../Map.func.hpp"
#include "../WildlifeState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/AI/Tribes/AITribeType.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    using AI::Tribes::AITribeType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0052CAB0
    void WildlifeState::findAndSetNewRallyPointForDeerAndLions(int tribeID, int always2or3or5, int always0or1)
    {
        int x = DAT_UnitsState::instance.units[DAT_TribesState::instance.tribes[tribeID].selectionTargetUnitID].x / 10;
        int y = DAT_UnitsState::instance.units[DAT_TribesState::instance.tribes[tribeID].selectionTargetUnitID].y / 10;
        this->casDisRelated = always2or3or5;
        this->candidateIndex = 0;
        this->candidateIndex2 = 1;
        for (int row = 0; row < 40; row++) {
            for (int column = 0; column < 40; column++) {
                this->grid[column][row].casDisRelated2 = 0;
                this->grid[column][row].field_0x3c = 0;
            }
        }
        this->DAT_Y10_Array_Section1034[0] = (short)y;
        this->DAT_X10_Array_Section1034[0] = (short)x;
        int const areaID = this->grid[x][y].separateAreaID;
        this->grid[x][y].casDisRelated2 = always2or3or5;
        while (this->candidateIndex != this->candidateIndex2) {
            int const candidateX = this->DAT_X10_Array_Section1034[this->candidateIndex];
            int const candidateY = this->DAT_Y10_Array_Section1034[this->candidateIndex];
            this->casDisRelated = this->grid[candidateX][candidateY].casDisRelated2;
            if (this->casDisRelated <= 1) {
                break;
            }
            int const level = this->casDisRelated - 1;
            for (int direction = 0; direction < 8; direction++) {
                uint const neighbourX
                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction].int_.xOffset
                    + candidateX;
                uint const neighbourY
                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[direction].int_.yOffset
                    + candidateY;
                if (neighbourX > 39 || neighbourY > 39 || this->grid[neighbourX][neighbourY].firstMember <= 0
                    || areaID != this->grid[neighbourX][neighbourY].separateAreaID) {
                    continue;
                }
                if (!always0or1) {
                    if (this->grid[neighbourX][neighbourY].field_0x34 != 0) {
                        continue;
                    }
                    // 13: the wildlife tribe
                    if (DAT_TribesState::instance.tribes[tribeID].tribeType == 13
                        && (this->grid[neighbourX][neighbourY].deerCount != 0
                            || this->grid[neighbourX][neighbourY].lionCount != 0)) {
                        continue;
                    }
                } else if (this->grid[neighbourX][neighbourY].unstalkedUnitCount != 0
                    || this->grid[neighbourX][neighbourY].buildingTiles != 0
                    || this->grid[neighbourX][neighbourY].lionCount != 0) {
                    continue;
                }
                if (this->grid[neighbourX][neighbourY].casDisRelated2 < level) {
                    this->grid[neighbourX][neighbourY].casDisRelated2 = level;
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
        DAT_TribesState::instance.tribes[tribeID].currentRallyPointIndex = 0;
        DAT_TribesState::instance.tribes[tribeID].rallyPointCount = 0;
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
                    && this->grid[neighbourX][neighbourY].casDisRelated2 < always2or3or5) {
                    int const distance = this->grid[neighbourX][neighbourY].casDisRelated2;
                    this->grid[neighbourX][neighbourY].casDisRelated2 = 0;
                    always2or3or5 = distance;
                    bestDirection = direction;
                }
            }
            if (bestDirection <= -1) {
                return;
            }
            x = x + DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[bestDirection].int_.xOffset;
            y = y + DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[bestDirection].int_.yOffset;
            this->grid[x][y].field_0x3c = 1;
            uint const tileY = y * 10 + 5;
            uint const tileX = x * 10 + 5;
            if (tileX <= 399 && tileY <= 399
                && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[tileY * 400 + tileX] != '\0') {
                MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::pathFindingDeerAndLionsUnk,
                    DAT_PathFindingState::ptr)(areaID, tileX, tileY);
                DAT_TribesState::instance.tribes[tribeID]
                    .rallyPointArray[DAT_TribesState::instance.tribes[tribeID].rallyPointCount][0]
                    = (short)DAT_PathFindingState::instance.climbX;
                DAT_TribesState::instance.tribes[tribeID]
                    .rallyPointArray[DAT_TribesState::instance.tribes[tribeID].rallyPointCount][1]
                    = (short)DAT_PathFindingState::instance.climbY;
                DAT_TribesState::instance.tribes[tribeID].rallyPointCount
                    = DAT_TribesState::instance.tribes[tribeID].rallyPointCount + 1;
            }
        }
    }

}
}
