#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Map/Location/Point8ShortXY.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {
            using OpenSHC::Map::Location::Point8ShortXY;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          BFS from tile param_1 up to distance param_2. For every unit owned by player param_3 found on   visited tiles,
          adds param_4 health, clamped to the unit's maxHealth. Also updates   healthPercentage and healthbar fields
          accordingly. Used for area healing effects such as from   buildings or abilities.      renamed by: Claude
          Sonnet 4.6
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A36B0
        undefined4 PathFindingState::healUnitsOfPlayerWithinRadius(int param_1, int param_2, int param_3, int param_4)
        {
            short sVar1;
            short sVar2;
            ushort uVar3;
            uint uVar4;
            int iVar5;
            short sVar6;
            short* psVar7;
            int iVar8;
            int* piVar9;
            this->searchGeneration = this->searchGeneration + 1;
            this->calculations = this->calculations + 1;
            if (32000 < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
            }
            this->searchQueue.yQueue[0] = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[param_1];
            this->searchQueue.xQueue[0] = (short)param_1
                - (short)DAT_ViewportRenderState::instance.translationMatrix[this->searchQueue.yQueue[0]].addXgetTile;
            this->searchQueue.tilesQueue[0] = param_1;
            this->searchQueue.readIndex = 0;
            this->searchQueue.writeIndex = 1;
            this->searchQueue.currentDistance = 1;
            DAT_TileMapState::instance.CertainPathLayer[param_1] = 1;
            DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
            if (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                while (uVar4 = this->searchQueue.tilesQueue[this->searchQueue.readIndex], uVar4 < 0x13a10) {
                    sVar1 = this->searchQueue.xQueue[this->searchQueue.readIndex];
                    sVar2 = this->searchQueue.yQueue[this->searchQueue.readIndex];
                    this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[uVar4];
                    if (0x13a10 < this->searchQueue.currentDistance) {
                        return (undefined4)(0);
                    }
                    if (param_2 < this->searchQueue.currentDistance) {
                        return (undefined4)(0);
                    }
                    uVar3 = DAT_TileMapState::instance.UnitLayer[uVar4];
                    while (iVar8 = (int)(short)uVar3, iVar8 != 0) {
                        if (DAT_UnitsState::instance.units[iVar8].owner == param_3) {
                            piVar9 = &DAT_UnitsState::instance.units[iVar8].health;
                            *piVar9 = *piVar9 + param_4;
                            iVar5 = DAT_UnitsState::instance.units[iVar8].maxHealth;
                            if (iVar5 < DAT_UnitsState::instance.units[iVar8].health) {
                                DAT_UnitsState::instance.units[iVar8].health = iVar5;
                            }
                            if (iVar5 == 0) {
                                sVar6 = 100;
                            } else {
                                sVar6 = (short)((DAT_UnitsState::instance.units[iVar8].health * 100) / iVar5);
                            }
                            DAT_UnitsState::instance.units[iVar8].healthPercentage = sVar6;
                            DAT_UnitsState::instance.units[iVar8].healthbar
                                = (sVar6 / 10 + (sVar6 >> 0xf)) - (short)((longlong)(int)sVar6 * 0x66666667 >> 0x3f);
                        }
                        uVar3 = DAT_UnitsState::instance.units[iVar8].nextUnitOnTheSameTile;
                    }
                    psVar7 = &DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[0].short_.yOffset;
                    piVar9 = DAT_TileMapState::instance.directionTranslationMatrix[sVar2] + 1;
                    do {
                        iVar8 = (*(int (*)[8])(piVar9 + -1))[0] + uVar4;
                        if ((DAT_TileMapState::instance.WalkLayer[iVar8] != this->searchGeneration)
                            && ((DAT_TileMapState::instance.LogicLayer[iVar8] & 0x30) == 0)) {
                            DAT_TileMapState::instance.CertainPathLayer[iVar8]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.WalkLayer[iVar8] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                = ((Point8ShortXY*)(psVar7 + -2))->xOffset + sVar1;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex] = *psVar7 + sVar2;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar8;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a0f < this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                        iVar8 = *piVar9 + uVar4;
                        if ((DAT_TileMapState::instance.WalkLayer[iVar8] != this->searchGeneration)
                            && ((DAT_TileMapState::instance.LogicLayer[iVar8] & 0x30) == 0)) {
                            DAT_TileMapState::instance.CertainPathLayer[iVar8]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.WalkLayer[iVar8] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex] = psVar7[2] + sVar1;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex] = psVar7[4] + sVar2;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar8;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a0f < this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                        iVar8 = piVar9[1] + uVar4;
                        if ((DAT_TileMapState::instance.WalkLayer[iVar8] != this->searchGeneration)
                            && ((DAT_TileMapState::instance.LogicLayer[iVar8] & 0x30) == 0)) {
                            DAT_TileMapState::instance.CertainPathLayer[iVar8]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.WalkLayer[iVar8] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex] = psVar7[6] + sVar1;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex] = psVar7[8] + sVar2;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar8;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a0f < this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                        iVar8 = piVar9[2] + uVar4;
                        if ((DAT_TileMapState::instance.WalkLayer[iVar8] != this->searchGeneration)
                            && ((DAT_TileMapState::instance.LogicLayer[iVar8] & 0x30) == 0)) {
                            DAT_TileMapState::instance.CertainPathLayer[iVar8]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.WalkLayer[iVar8] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex] = psVar7[10] + sVar1;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex] = psVar7[0xc] + sVar2;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar8;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a0f < this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                        psVar7 = psVar7 + 0x10;
                        piVar9 = piVar9 + 4;
                    } while ((int)psVar7 < 0xb4908c);
                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                    if (0x13a0f < this->searchQueue.readIndex) {
                        this->searchQueue.readIndex = 0;
                    }
                    if (this->searchQueue.readIndex == this->searchQueue.writeIndex) {
                        return (undefined4)(0);
                    }
                }
            }
            return (undefined4)(0);
        }

    }
}
}
