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
        short* psVar1;
        short sVar2;
        int iVar3;
        int* piVar4;
        int iVar5;
        int* piVar6;
        uint uVar7;
        int iVar8;
        uint uVar9;
        int iVar10;
        uint uVar11;
        int iVar12;
        int local_1c;
        int local_14;
        int local_10;
        sVar2 = DAT_TribesState::instance.tribes[param_1].selectionTargetUnitID;
        iVar5 = (int)DAT_UnitsState::instance.units[sVar2].x / 10;
        local_1c = (int)DAT_UnitsState::instance.units[sVar2].y / 10;
        this->casDisRelated = param_2;
        this->candidateIndex = 0;
        this->candidateIndex2 = 1;
        if (this->grid[iVar5][local_1c].field20_0x50 != 0) {
            piVar4 = &this->grid[0][0].field15_0x3c;
            iVar12 = 0x28;
            do {
                iVar3 = 0x28;
                piVar6 = piVar4;
                do {
                    piVar6[-1] = 0;
                    *piVar6 = 0;
                    piVar6 = piVar6 + 0x640;
                    iVar3 = iVar3 + -1;
                } while (iVar3);
                piVar4 = piVar4 + 0x28;
                iVar12 = iVar12 + -1;
            } while (iVar12);
            this->DAT_Y10_Array_Section1034[0] = (short)local_1c;
            this->DAT_X10_Array_Section1034[0] = (short)iVar5;
            this->grid[iVar5][local_1c].casDisRelated2 = this->grid[iVar5][local_1c].field20_0x50;
            iVar12 = this->grid[iVar5][local_1c].separateAreaID;
            if (this->candidateIndex != this->candidateIndex2) {
                do {
                    iVar3 = (int)this->DAT_Y10_Array_Section1034[this->candidateIndex];
                    iVar8 = (int)this->DAT_X10_Array_Section1034[this->candidateIndex];
                    piVar4 = &DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[0].int_.yOffset;
                    do {
                        uVar9 = *piVar4 + iVar3;
                        uVar7 = ((Point8IntXY*)(piVar4 + -1))->xOffset + iVar8;
                        if (uVar7 < 0x28 && uVar9 < 0x28 && 0 < this->grid[uVar7][uVar9].firstMember
                            && iVar12 == this->grid[uVar7][uVar9].separateAreaID
                            && (iVar10 = this->grid[uVar7][uVar9].field20_0x50, 0 < iVar10)
                            && this->grid[uVar7][uVar9].casDisRelated2 == 0) {
                            this->grid[uVar7][uVar9].casDisRelated2 = iVar10;
                            this->DAT_X10_Array_Section1034[this->candidateIndex2] = (short)uVar7;
                            this->DAT_Y10_Array_Section1034[this->candidateIndex2] = (short)uVar9;
                            this->candidateIndex2 = this->candidateIndex2 + 1;
                            if (0x63f < this->candidateIndex2) {
                                this->candidateIndex2 = 0;
                            }
                        }
                        uVar9 = piVar4[2] + iVar3;
                        uVar7 = piVar4[1] + iVar8;
                        if (uVar7 < 0x28 && uVar9 < 0x28 && 0 < this->grid[uVar7][uVar9].firstMember
                            && iVar12 == this->grid[uVar7][uVar9].separateAreaID
                            && (iVar10 = this->grid[uVar7][uVar9].field20_0x50, 0 < iVar10)
                            && this->grid[uVar7][uVar9].casDisRelated2 == 0) {
                            this->grid[uVar7][uVar9].casDisRelated2 = iVar10;
                            this->DAT_X10_Array_Section1034[this->candidateIndex2] = (short)uVar7;
                            this->DAT_Y10_Array_Section1034[this->candidateIndex2] = (short)uVar9;
                            this->candidateIndex2 = this->candidateIndex2 + 1;
                            if (0x63f < this->candidateIndex2) {
                                this->candidateIndex2 = 0;
                            }
                        }
                        uVar9 = piVar4[4] + iVar3;
                        uVar7 = piVar4[3] + iVar8;
                        if (uVar7 < 0x28 && uVar9 < 0x28 && 0 < this->grid[uVar7][uVar9].firstMember
                            && iVar12 == this->grid[uVar7][uVar9].separateAreaID
                            && (iVar10 = this->grid[uVar7][uVar9].field20_0x50, 0 < iVar10)
                            && this->grid[uVar7][uVar9].casDisRelated2 == 0) {
                            this->grid[uVar7][uVar9].casDisRelated2 = iVar10;
                            this->DAT_X10_Array_Section1034[this->candidateIndex2] = (short)uVar7;
                            this->DAT_Y10_Array_Section1034[this->candidateIndex2] = (short)uVar9;
                            this->candidateIndex2 = this->candidateIndex2 + 1;
                            if (0x63f < this->candidateIndex2) {
                                this->candidateIndex2 = 0;
                            }
                        }
                        uVar9 = piVar4[6] + iVar3;
                        uVar7 = piVar4[5] + iVar8;
                        if (uVar7 < 0x28 && uVar9 < 0x28 && 0 < this->grid[uVar7][uVar9].firstMember
                            && iVar12 == this->grid[uVar7][uVar9].separateAreaID
                            && (iVar10 = this->grid[uVar7][uVar9].field20_0x50, 0 < iVar10)
                            && this->grid[uVar7][uVar9].casDisRelated2 == 0) {
                            this->grid[uVar7][uVar9].casDisRelated2 = iVar10;
                            this->DAT_X10_Array_Section1034[this->candidateIndex2] = (short)uVar7;
                            this->DAT_Y10_Array_Section1034[this->candidateIndex2] = (short)uVar9;
                            this->candidateIndex2 = this->candidateIndex2 + 1;
                            if (0x63f < this->candidateIndex2) {
                                this->candidateIndex2 = 0;
                            }
                        }
                        piVar4 = piVar4 + 8;
                    } while ((int)piVar4 < 0xb4908c);
                    this->candidateIndex = this->candidateIndex + 1;
                    if (0x63f < this->candidateIndex) {
                        this->candidateIndex = 0;
                    }
                } while (this->candidateIndex != this->candidateIndex2);
            }
            uVar7 = (uint)(byte)SEC_RNG::instance.currentNumber2;
            DAT_TribesState::instance.tribes[param_1].currentRallyPointIndex = 0;
            DAT_TribesState::instance.tribes[param_1].rallyPointCount = 0;
            this->grid[iVar5][local_1c].field15_0x3c = 1;
            this->grid[iVar5][local_1c].casDisRelated2 = 0;
            while (true) {
                local_14 = -1;
                local_10 = 2;
                iVar12 = (uVar7 & 7) - 7;
                iVar3 = (uVar7 & 7) * 8 + 8;
                do {
                    iVar8 = iVar12 + 7;
                    iVar10 = iVar3 + -8;
                    if (7 < iVar8) {
                        iVar8 = iVar12 + -1;
                        iVar10 = iVar3 + -72;
                    }
                    uVar9 = *(int*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix + iVar10)
                        + iVar5;
                    uVar11
                        = *(int*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix + iVar10 + 4)
                        + local_1c;
                    if (uVar9 < 0x28 && uVar11 < 0x28 && 0 < this->grid[uVar9][uVar11].firstMember
                        && (iVar10 = this->grid[uVar9][uVar11].casDisRelated2, iVar10 != 0 && (param_2 < iVar10))) {
                        this->grid[uVar9][uVar11].casDisRelated2 = 0;
                        param_2 = iVar10;
                        local_14 = iVar8;
                    }
                    iVar8 = iVar3;
                    iVar10 = iVar12 + 8;
                    if (7 < iVar12 + 8) {
                        iVar8 = iVar3 + -0x40;
                        iVar10 = iVar12;
                    }
                    uVar11
                        = *(int*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix + iVar8 + 4)
                        + local_1c;
                    uVar9 = *(int*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix + iVar8)
                        + iVar5;
                    if (uVar9 < 0x28 && uVar11 < 0x28 && 0 < this->grid[uVar9][uVar11].firstMember
                        && (iVar8 = this->grid[uVar9][uVar11].casDisRelated2, iVar8 && (param_2 < iVar8))) {
                        this->grid[uVar9][uVar11].casDisRelated2 = 0;
                        param_2 = iVar8;
                        local_14 = iVar10;
                    }
                    iVar8 = iVar12 + 9;
                    iVar10 = iVar3 + 8;
                    if (7 < iVar8) {
                        iVar8 = iVar12 + 1;
                        iVar10 = iVar3 + -0x38;
                    }
                    uVar11
                        = *(int*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix + iVar10 + 4)
                        + local_1c;
                    uVar9 = *(int*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix + iVar10)
                        + iVar5;
                    if (uVar9 < 0x28 && uVar11 < 0x28 && 0 < this->grid[uVar9][uVar11].firstMember
                        && (iVar10 = this->grid[uVar9][uVar11].casDisRelated2, iVar10 != 0 && (param_2 < iVar10))) {
                        this->grid[uVar9][uVar11].casDisRelated2 = 0;
                        param_2 = iVar10;
                        local_14 = iVar8;
                    }
                    iVar8 = iVar12 + 10;
                    iVar10 = iVar3 + 0x10;
                    if (7 < iVar8) {
                        iVar8 = iVar12 + 2;
                        iVar10 = iVar3 + -0x30;
                    }
                    uVar11
                        = *(int*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix + iVar10 + 4)
                        + local_1c;
                    uVar9 = *(int*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix + iVar10)
                        + iVar5;
                    if (uVar9 < 0x28 && uVar11 < 0x28 && 0 < this->grid[uVar9][uVar11].firstMember
                        && (iVar10 = this->grid[uVar9][uVar11].casDisRelated2, iVar10 && (param_2 < iVar10))) {
                        this->grid[uVar9][uVar11].casDisRelated2 = 0;
                        param_2 = iVar10;
                        local_14 = iVar8;
                    }
                    iVar3 = iVar3 + 0x20;
                    iVar12 = iVar12 + 4;
                    local_10 = local_10 + -1;
                } while (local_10);
                if (local_14 < 0)
                    break;
                iVar5 = iVar5
                    + DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[local_14].int_.xOffset;
                local_1c = local_1c
                    + *(int*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix + local_14 * 8
                        + 4);
                this->grid[iVar5][local_1c].field15_0x3c = 1;
                uVar9 = iVar5 * 10 + 5;
                uVar11 = local_1c * 10 + 5;
                if (uVar9 < 400 && uVar11 < 400 && *(char*)(uVar11 * 400 + (int)DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400 + uVar9) != '\0') {
                    DAT_TribesState::instance.tribes[param_1]
                        .rallyPointArray[DAT_TribesState::instance.tribes[param_1].rallyPointCount][0]
                        = (short)iVar5 * 10 + 5;
                    DAT_TribesState::instance.tribes[param_1]
                        .rallyPointArray[DAT_TribesState::instance.tribes[param_1].rallyPointCount][1]
                        = (short)local_1c * 10 + 5;
                    psVar1 = &DAT_TribesState::instance.tribes[param_1].rallyPointCount;
                    *psVar1 = *psVar1 + 1;
                }
            }
            return TRUE;
        }
        return FALSE;
    }

}
}
