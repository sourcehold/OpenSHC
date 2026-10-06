#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Location/Point8ShortXY.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

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
            uint uVar4;
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
            this->searchQueue.yQueue[0]
                = (short)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[param_1];
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
                    short sVar1 = this->searchQueue.xQueue[this->searchQueue.readIndex];
                    short sVar2 = this->searchQueue.yQueue[this->searchQueue.readIndex];
                    this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[uVar4];
                    if (0x13a10 < (int)this->searchQueue.currentDistance) {
                        return (undefined4)(0);
                    }
                    if (this->searchQueue.currentDistance > param_2) {
                        return (undefined4)(0);
                    }
                    int uVar3 = (short)DAT_TileMapState::instance.UnitLayer[uVar4];
                    while (iVar8 = (int)(short)uVar3, iVar8 != 0) {
                        if (DAT_UnitsState::instance.units[iVar8].owner == param_3) {
                            DAT_UnitsState::instance.units[iVar8].health
                                = DAT_UnitsState::instance.units[iVar8].health + param_4;
                            int iVar5 = DAT_UnitsState::instance.units[iVar8].maxHealth;
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
                    for (int _direction = 0; _direction < 8; _direction = _direction + 4) {
                        iVar8 = DAT_TileMapState::instance.directionTranslationMatrix[sVar2][_direction] + uVar4;
                        if (DAT_TileMapState::instance.WalkLayer[iVar8] != this->searchGeneration
                            && (DAT_TileMapState::instance.LogicLayer[iVar8] & 0x30) == 0) {
                            DAT_TileMapState::instance.CertainPathLayer[iVar8]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.WalkLayer[iVar8] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction]
                                      .short_.xOffset
                                + sVar1;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction]
                                      .short_.yOffset
                                + sVar2;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar8;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a10 <= (int)this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                        iVar8 = DAT_TileMapState::instance.directionTranslationMatrix[sVar2][_direction + 1] + uVar4;
                        if (DAT_TileMapState::instance.WalkLayer[iVar8] != this->searchGeneration
                            && (DAT_TileMapState::instance.LogicLayer[iVar8] & 0x30) == 0) {
                            DAT_TileMapState::instance.CertainPathLayer[iVar8]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.WalkLayer[iVar8] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction + 1]
                                      .short_.xOffset
                                + sVar1;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction + 1]
                                      .short_.yOffset
                                + sVar2;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar8;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a10 <= (int)this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                        iVar8 = DAT_TileMapState::instance.directionTranslationMatrix[sVar2][_direction + 2] + uVar4;
                        if (DAT_TileMapState::instance.WalkLayer[iVar8] != this->searchGeneration
                            && (DAT_TileMapState::instance.LogicLayer[iVar8] & 0x30) == 0) {
                            DAT_TileMapState::instance.CertainPathLayer[iVar8]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.WalkLayer[iVar8] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction + 2]
                                      .short_.xOffset
                                + sVar1;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction + 2]
                                      .short_.yOffset
                                + sVar2;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar8;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a10 <= (int)this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                        iVar8 = DAT_TileMapState::instance.directionTranslationMatrix[sVar2][_direction + 3] + uVar4;
                        if (DAT_TileMapState::instance.WalkLayer[iVar8] != this->searchGeneration
                            && (DAT_TileMapState::instance.LogicLayer[iVar8] & 0x30) == 0) {
                            DAT_TileMapState::instance.CertainPathLayer[iVar8]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.WalkLayer[iVar8] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction + 3]
                                      .short_.xOffset
                                + sVar1;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction + 3]
                                      .short_.yOffset
                                + sVar2;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar8;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a10 <= (int)this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                    }

                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                    if (0x13a10 <= (int)this->searchQueue.readIndex) {
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
