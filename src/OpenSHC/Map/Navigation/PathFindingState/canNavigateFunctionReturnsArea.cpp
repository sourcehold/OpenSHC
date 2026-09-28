#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          returns area (a value >= 1) if the unit can get there, if not, 0   decompilerscript: committed: 2025-01-30
          21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A6DF0
        int PathFindingState::canNavigateFunctionReturnsArea(int playerID, dword targetArea, uint unitX, uint unitY)
        {
            int (*paiVar5)[8];
            int iVar6;
            ushort _area;
            this->ALG_ResultTile = 0;
            this->ALG_ResultY = 0;
            this->ALG_ResultX = 0;
            if (399 < unitX || 399 < unitY || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[unitY * 400 + unitX] == '\0') {
                return 0;
            }
            this->searchGeneration = this->searchGeneration + 1;
            if (32000 < this->searchGeneration) {
                this->searchGeneration = 1;
                /*
                  clear up the tilemap short[160800]
                 */
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    160800, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
            }
            this->searchQueue.readIndex = 0;
            this->searchQueue.writeIndex = 1;
            this->searchQueue.currentDistance = 1;
            this->searchQueue.yQueue[0] = (short)unitY;
            this->searchQueue.xQueue[0] = (short)unitX;
            this->searchQueue.tilesQueue[0]
                = DAT_ViewportRenderState::instance.translationMatrix[unitY].addXgetTile + unitX;
            DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]] = 1;
            DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
            if (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                do {
                    int iVar3 = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                    if (iVar3 < 0) {
                        return 0;
                    }
                    if (80400 < iVar3) {
                        return 0;
                    }
                    int sVar1 = (int)this->searchQueue.xQueue[this->searchQueue.readIndex];
                    int sVar2 = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                    this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[iVar3];
                    if (0x13a10 < this->searchQueue.currentDistance) {
                        return 0;
                    }
                    iVar6 = 0;
                    paiVar5 = DAT_TileMapState::instance.directionTranslationMatrix + sVar2;
                    do {
                        int _tile = (*paiVar5)[0] + iVar3;
                        uint uVar4 = DAT_TileMapState::instance.LogicLayer[_tile];
                        if (DAT_TileMapState::instance.WalkLayer[_tile] != this->searchGeneration) {
                            if ((uVar4 & 0x40000000) != 0) {
                                DAT_TileMapState::instance.CertainPathLayer[_tile]
                                    = (short)this->searchQueue.currentDistance + 1;
                                DAT_TileMapState::instance.WalkLayer[_tile] = (short)this->searchGeneration;
                                this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[iVar6]
                                          .short_.xOffset
                                    + sVar1;
                                this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                    = *(short*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix
                                          + iVar6 * 8 + 4)
                                    + sVar2;
                                this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _tile;
                                this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                if (0x13a0f < this->searchQueue.writeIndex) {
                                    this->searchQueue.writeIndex = 0;
                                }
                            }
                            if ((uVar4 & 0x4a5014b1) == 0) {
                                _area = (short)DAT_TileMapState::instance.PathConnectionLayer[_tile];
                                _tile = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                              calculateCanPlayerUnitsNavigateToAreaFromArea,
                                    this)(playerID, (dword)((int)((short)_area)), (dword)((int)(targetArea)), 0);
                                if (_tile != 0) {
                                    this->climbX
                                        = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[iVar6]
                                              .int_.xOffset
                                        + (int)sVar1;
                                    this->climbY = *(int*)((int)DAT_TerrainDefinedData::instance
                                                               .clockwiseCardinalTranslationMatrix
                                                       + iVar6 * 8 + 4)
                                        + (int)sVar2;
                                    return (int)(short)_area;
                                }
                            }
                        }
                        iVar6 = iVar6 + 1;
                        paiVar5 = (int (*)[8])(*paiVar5 + 1);
                    } while (iVar6 < 8);
                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                    if (0x13a0f < this->searchQueue.readIndex) {
                        this->searchQueue.readIndex = 0;
                    }
                } while (this->searchQueue.readIndex != this->searchQueue.writeIndex);
            }
            return 0;
        }

    }
}
}
