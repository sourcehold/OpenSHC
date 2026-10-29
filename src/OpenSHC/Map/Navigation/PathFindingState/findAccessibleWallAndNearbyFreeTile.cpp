#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A3220
        BOOLEnum PathFindingState::findAccessibleWallAndNearbyFreeTile(
            uint unitID, int tileUnk, int* pFreeTile, int* pDefensesTile)
        {
            uint uVar2;
            int _candidateNorthOrSouth;
            uint _tile;
            uint _dirBase = (unitID & 1) * 4;
            this->searchGeneration = this->searchGeneration + 1;
            this->calculations = this->calculations + 1;
            if (32000 < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
            }
            int _y0 = (short)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tileUnk];
            int _x0 = tileUnk - DAT_ViewportRenderState::instance.translationMatrix[_y0].addXgetTile;
            this->searchQueue.yQueue[0] = (short)_y0;
            this->searchQueue.tilesQueue[0] = tileUnk;
            this->searchQueue.readIndex = 0;
            this->searchQueue.writeIndex = 1;
            this->searchQueue.xQueue[0] = (short)_x0;
            this->searchQueue.currentDistance = 1;
            DAT_TileMapState::instance.CertainPathLayer[tileUnk] = (short)this->searchQueue.currentDistance;
            DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
            while (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                _tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                if ((int)_tile < 0) {
                    return FALSE;
                }
                if (0x13a10 <= (int)_tile) {
                    return FALSE;
                }
                int sVar1 = (int)this->searchQueue.xQueue[this->searchQueue.readIndex];
                int _y = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[_tile];
                if (0x13a10 < (int)this->searchQueue.currentDistance) {
                    return FALSE;
                }
                if (0xc < (int)this->searchQueue.currentDistance) {
                    return FALSE;
                }
                if (3 < (int)this->searchQueue.currentDistance
                    && (DAT_TileMapState::instance.LogicLayer[_tile] & 0x100U) != 0) {
                    /*
                      wall or gatehouse (or tower?)
                     */
                    uVar2 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::findFreeTileNearby,
                        DAT_UnitsState::ptr)(unitID, _tile);
                    *pFreeTile = uVar2;
                    if (uVar2 != 0) {
                        *pDefensesTile = _tile;
                        return TRUE;
                    }
                }
                /*
                  every other unit searches in a different direction
                 */
                tileUnk = _dirBase + 1;
                int local_8 = 2;
                do {
                    uint uVar4 = tileUnk - 1 & 7;
                    _candidateNorthOrSouth
                        = DAT_TileMapState::instance.directionTranslationMatrix[_y][uVar4] + _tile;
                    if (DAT_TileMapState::instance.WalkLayer[_candidateNorthOrSouth] != this->searchGeneration
                        && (DAT_TileMapState::instance.LogicLayer[_candidateNorthOrSouth] & 0x30) == 0) {
                        DAT_TileMapState::instance.CertainPathLayer[_candidateNorthOrSouth]
                            = (short)this->searchQueue.currentDistance + 1;
                        DAT_TileMapState::instance.WalkLayer[_candidateNorthOrSouth]
                            = (short)this->searchGeneration;
                        this->searchQueue.xQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[uVar4]
                                  .short_.xOffset
                            + sVar1;
                        this->searchQueue.yQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[uVar4]
                                  .short_.yOffset
                            + _y;
                        this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _candidateNorthOrSouth;
                        this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                        if (0x13a10 <= (int)this->searchQueue.writeIndex) {
                            this->searchQueue.writeIndex = 0;
                        }
                    }
                    uVar4 = tileUnk & 7;
                    int iVar3 = DAT_TileMapState::instance.directionTranslationMatrix[_y][uVar4] + _tile;
                    if (DAT_TileMapState::instance.WalkLayer[iVar3] != this->searchGeneration
                        && (DAT_TileMapState::instance.LogicLayer[iVar3] & 0x30) == 0) {
                        DAT_TileMapState::instance.CertainPathLayer[iVar3]
                            = (short)this->searchQueue.currentDistance + 1;
                        DAT_TileMapState::instance.WalkLayer[iVar3] = (short)this->searchGeneration;
                        this->searchQueue.xQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[uVar4]
                                  .short_.xOffset
                            + sVar1;
                        this->searchQueue.yQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[uVar4]
                                  .short_.yOffset
                            + _y;
                        this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar3;
                        this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                        if (0x13a10 <= (int)this->searchQueue.writeIndex) {
                            this->searchQueue.writeIndex = 0;
                        }
                    }
                    uVar4 = tileUnk + 1 & 7;
                    iVar3 = DAT_TileMapState::instance.directionTranslationMatrix[_y][uVar4] + _tile;
                    if (DAT_TileMapState::instance.WalkLayer[iVar3] != this->searchGeneration
                        && (DAT_TileMapState::instance.LogicLayer[iVar3] & 0x30) == 0) {
                        DAT_TileMapState::instance.CertainPathLayer[iVar3]
                            = (short)this->searchQueue.currentDistance + 1;
                        DAT_TileMapState::instance.WalkLayer[iVar3] = (short)this->searchGeneration;
                        this->searchQueue.xQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[uVar4]
                                  .short_.xOffset
                            + sVar1;
                        this->searchQueue.yQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[uVar4]
                                  .short_.yOffset
                            + _y;
                        this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar3;
                        this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                        if (0x13a10 <= (int)this->searchQueue.writeIndex) {
                            this->searchQueue.writeIndex = 0;
                        }
                    }
                    uVar4 = tileUnk + 2 & 7;
                    iVar3 = DAT_TileMapState::instance.directionTranslationMatrix[_y][uVar4] + _tile;
                    if (DAT_TileMapState::instance.WalkLayer[iVar3] != this->searchGeneration
                        && (DAT_TileMapState::instance.LogicLayer[iVar3] & 0x30) == 0) {
                        DAT_TileMapState::instance.CertainPathLayer[iVar3]
                            = (short)this->searchQueue.currentDistance + 1;
                        DAT_TileMapState::instance.WalkLayer[iVar3] = (short)this->searchGeneration;
                        this->searchQueue.xQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[uVar4]
                                  .short_.xOffset
                            + sVar1;
                        this->searchQueue.yQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[uVar4]
                                  .short_.yOffset
                            + _y;
                        this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar3;
                        this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                        if (0x13a10 <= (int)this->searchQueue.writeIndex) {
                            this->searchQueue.writeIndex = 0;
                        }
                    }
                    tileUnk = tileUnk + 4;
                    local_8 = local_8 + -1;
                } while (local_8 != 0);
                this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                if (0x13a10 <= (int)this->searchQueue.readIndex) {
                    this->searchQueue.readIndex = 0;
                }
            }
            return FALSE;
        }

    }
}
}
