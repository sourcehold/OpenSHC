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
        short* psVar1;
        short sVar2;
        short sVar3;
        int* piVar4;
        uint _randomDirection;
        int iVar5;
        uint uVar6;
        int iVar7;
        int iVar8;
        int* piVar9;
        uint uVar10;
        int _x10;
        int iVar11;
        int _y10;
        int local_18;
        int local_c;
        int _count;
        int _currentArea;
        uint _destinationY;
        uint _destinationX;
        sVar2 = DAT_TribesState::instance.tribes[tribeID].selectionTargetUnitID;
        _x10 = (int)DAT_UnitsState::instance.units[sVar2].x / 10;
        _y10 = (int)DAT_UnitsState::instance.units[sVar2].y / 10;
        this->casDisRelated = always2or3or5;
        this->candidateIndex = 0;
        this->candidateIndex2 = 1;
        piVar9 = &this->grid[0][0].field15_0x3c;
        iVar11 = 0x28;
        do {
            iVar5 = 0x28;
            piVar4 = piVar9;
            do {
                piVar4[-1] = 0;
                *piVar4 = 0;
                piVar4 = piVar4 + 0x640;
                iVar5 = iVar5 + -1;
            } while (iVar5);
            piVar9 = piVar9 + 0x28;
            iVar11 = iVar11 + -1;
        } while (iVar11);
        this->DAT_Y10_Array_Section1034[0] = (short)_y10;
        this->DAT_X10_Array_Section1034[0] = (short)_x10;
        _currentArea = this->grid[_x10][_y10].separateAreaID;
        this->grid[_x10][_y10].casDisRelated2 = always2or3or5;
        if (this->candidateIndex != this->candidateIndex2) {
            do {
                sVar2 = this->DAT_X10_Array_Section1034[this->candidateIndex];
                sVar3 = this->DAT_Y10_Array_Section1034[this->candidateIndex];
                this->casDisRelated = this->grid[sVar2][sVar3].casDisRelated2;
                if (this->casDisRelated < 2)
                    break;
                iVar11 = this->casDisRelated + -1;
                piVar9 = &DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[0].int_.yOffset;
                do {
                    uVar10 = *piVar9 + (int)sVar3;
                    uVar6 = ((Point8IntXY*)(piVar9 + -1))->xOffset + (int)sVar2;
                    if (uVar6 < 0x28 && uVar10 < 0x28 && 0 < this->grid[uVar6][uVar10].firstMember
                        && _currentArea == this->grid[uVar6][uVar10].separateAreaID) {
                        if (!always0or1) {
                            if (this->grid[uVar6][uVar10].field13_0x34 == 0) {
                                if (DAT_TribesState::instance.tribes[tribeID].tribeType
                                    == (AI::Tribes::AITT_SWORDSMEN | AI::Tribes::AITT_SPEARMEN)) {
                                    _count = this->grid[uVar6][uVar10].deerCount;
                                    goto LAB_0052cc5e;
                                }
                            LAB_0052cc66:
                                if (this->grid[uVar6][uVar10].casDisRelated2 < iVar11) {
                                    this->grid[uVar6][uVar10].casDisRelated2 = iVar11;
                                    this->DAT_X10_Array_Section1034[this->candidateIndex2] = (short)uVar6;
                                    this->DAT_Y10_Array_Section1034[this->candidateIndex2] = (short)uVar10;
                                    this->candidateIndex2 = this->candidateIndex2 + 1;
                                    if (1600 < this->candidateIndex2) {
                                        this->candidateIndex2 = 0;
                                    }
                                }
                            }
                        } else if (this->grid[uVar6][uVar10].unstalkedUnitCount == 0) {
                            _count = this->grid[uVar6][uVar10].buildingTiles;
                        LAB_0052cc5e:
                            if ((!_count) && (this->grid[uVar6][uVar10].lionCount == 0))
                                goto LAB_0052cc66;
                        }
                    }
                    piVar9 = piVar9 + 2;
                } while ((int)piVar9 < 0xb4908c);
                this->candidateIndex = this->candidateIndex + 1;
                if (1600 < this->candidateIndex) {
                    this->candidateIndex = 0;
                }
            } while (this->candidateIndex != this->candidateIndex2);
        }
        _randomDirection = (uint)(byte)SEC_RNG::instance.currentNumber2;
        DAT_TribesState::instance.tribes[tribeID].currentRallyPointIndex = 0;
        DAT_TribesState::instance.tribes[tribeID].rallyPointCount = 0;
        this->grid[_x10][_y10].field15_0x3c = 1;
        this->grid[_x10][_y10].casDisRelated2 = 0;
        while (true) {
            local_18 = -1;
            local_c = 2;
            iVar11 = (_randomDirection & 7) * 8 + 8;
            iVar5 = (_randomDirection & 7) - 7;
            do {
                iVar8 = iVar5 + 7;
                iVar7 = iVar11 + -8;
                if (7 < iVar8) {
                    iVar8 = iVar5 + -1;
                    iVar7 = iVar11 + -0x48;
                }
                uVar6
                    = *(int*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix + iVar7) + _x10;
                uVar10 = *(int*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix + iVar7 + 4)
                    + _y10;
                if (uVar6 < 0x28 && uVar10 < 0x28 && 0 < this->grid[uVar6][uVar10].firstMember
                    && (iVar7 = this->grid[uVar6][uVar10].casDisRelated2, iVar7 != 0 && (iVar7 < always2or3or5))) {
                    this->grid[uVar6][uVar10].casDisRelated2 = 0;
                    always2or3or5 = iVar7;
                    local_18 = iVar8;
                }
                iVar8 = iVar11;
                iVar7 = iVar5 + 8;
                if (7 < iVar5 + 8) {
                    iVar8 = iVar11 + -0x40;
                    iVar7 = iVar5;
                }
                uVar10 = *(int*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix + iVar8 + 4)
                    + _y10;
                uVar6
                    = *(int*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix + iVar8) + _x10;
                if (uVar6 < 0x28 && uVar10 < 0x28 && 0 < this->grid[uVar6][uVar10].firstMember
                    && (iVar8 = this->grid[uVar6][uVar10].casDisRelated2, iVar8 && (iVar8 < always2or3or5))) {
                    this->grid[uVar6][uVar10].casDisRelated2 = 0;
                    always2or3or5 = iVar8;
                    local_18 = iVar7;
                }
                iVar8 = iVar5 + 9;
                iVar7 = iVar11 + 8;
                if (7 < iVar8) {
                    iVar8 = iVar5 + 1;
                    iVar7 = iVar11 + -0x38;
                }
                uVar10 = *(int*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix + iVar7 + 4)
                    + _y10;
                uVar6
                    = *(int*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix + iVar7) + _x10;
                if (uVar6 < 0x28 && uVar10 < 0x28 && 0 < this->grid[uVar6][uVar10].firstMember
                    && (iVar7 = this->grid[uVar6][uVar10].casDisRelated2, iVar7 != 0 && (iVar7 < always2or3or5))) {
                    this->grid[uVar6][uVar10].casDisRelated2 = 0;
                    always2or3or5 = iVar7;
                    local_18 = iVar8;
                }
                iVar8 = iVar5 + 10;
                iVar7 = iVar11 + 0x10;
                if (7 < iVar8) {
                    iVar8 = iVar5 + 2;
                    iVar7 = iVar11 + -0x30;
                }
                uVar10 = *(int*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix + iVar7 + 4)
                    + _y10;
                uVar6
                    = *(int*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix + iVar7) + _x10;
                if (uVar6 < 0x28 && uVar10 < 0x28 && 0 < this->grid[uVar6][uVar10].firstMember
                    && (iVar7 = this->grid[uVar6][uVar10].casDisRelated2, iVar7 && (iVar7 < always2or3or5))) {
                    this->grid[uVar6][uVar10].casDisRelated2 = 0;
                    always2or3or5 = iVar7;
                    local_18 = iVar8;
                }
                iVar11 = iVar11 + 0x20;
                iVar5 = iVar5 + 4;
                local_c = local_c + -1;
            } while (local_c);
            if (local_18 < 0)
                break;
            _x10 = _x10 + DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[local_18].int_.xOffset;
            _y10 = _y10
                + *(int*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix + local_18 * 8 + 4);
            this->grid[_x10][_y10].field15_0x3c = 1;
            _destinationY = _y10 * 10 + 5;
            uVar6 = _x10 * 10 + 5;
            if (uVar6 < 400 && _destinationY < 400 && *(char*)(_destinationY * 400 + (int)DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400 + uVar6) != '\0') {
                MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::pathFindingDeerAndLionsUnk,
                    DAT_PathFindingState::ptr)(_currentArea, uVar6, _destinationY);
                DAT_TribesState::instance.tribes[tribeID]
                    .rallyPointArray[DAT_TribesState::instance.tribes[tribeID].rallyPointCount][0]
                    = (short)DAT_PathFindingState::instance.climbX;
                DAT_TribesState::instance.tribes[tribeID]
                    .rallyPointArray[DAT_TribesState::instance.tribes[tribeID].rallyPointCount][1]
                    = (short)DAT_PathFindingState::instance.climbY;
                psVar1 = &DAT_TribesState::instance.tribes[tribeID].rallyPointCount;
                *psVar1 = *psVar1 + 1;
            }
        }
    }

}
}
