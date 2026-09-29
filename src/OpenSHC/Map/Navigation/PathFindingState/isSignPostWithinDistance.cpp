#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Location/Point8ShortXY.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::Game::GameMode;
        using OpenSHC::Map::Buildings::BuildingType;
        using OpenSHC::Map::Location::Point8ShortXY;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A2650
        BOOLEnum PathFindingState::isSignPostWithinDistance(uint x, uint y, int limit)
        {
            int iVar3;
            short* psVar4;
            int* piVar5;
            int iVar6;
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                return FALSE;
            }
            if (399 < x || 399 < y || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == '\0') {
                return FALSE;
            }
            this->calculations = this->calculations + 1;
            this->searchGeneration = this->searchGeneration + 1;
            if (32000 < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
            }
            this->searchQueue.readIndex = 0;
            this->searchQueue.writeIndex = 1;
            this->searchQueue.currentDistance = 1;
            this->searchQueue.yQueue[0] = (short)y;
            this->searchQueue.xQueue[0] = (short)x;
            this->searchQueue.tilesQueue[0] = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
            DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]] = 1;
            DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
            if (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                while ((iVar3 = this->searchQueue.tilesQueue[this->searchQueue.readIndex],
                    -1 < iVar3 && (iVar3 < 0x13a10))) {
                    int sVar1 = (int)this->searchQueue.xQueue[this->searchQueue.readIndex];
                    int sVar2 = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                    this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[iVar3];
                    if (0x13a10 < this->searchQueue.currentDistance) {
                        return FALSE;
                    }
                    if (this->searchQueue.currentDistance > limit) {
                        return FALSE;
                    }
                    if ((DAT_TileMapState::instance.BuildingLayer[iVar3] != 0)
                        && (DAT_BuildingsState::instance.buildings[DAT_TileMapState::instance.BuildingLayer[iVar3]]
                                .buildingType
                            == OpenSHC::Map::Buildings::BT_SIGNPOST)) {
                        return TRUE;
                    }
                    for (int _direction = 0; _direction < 8; _direction = _direction + 4) {
                        iVar6 = DAT_TileMapState::instance.directionTranslationMatrix[sVar2][_direction] + iVar3;
                        if (DAT_TileMapState::instance.WalkLayer[iVar6] != this->searchGeneration
                            && (DAT_TileMapState::instance.LogicLayer[iVar6] & 0x30) == 0) {
                            DAT_TileMapState::instance.CertainPathLayer[iVar6]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.WalkLayer[iVar6] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction]
                                      .short_.xOffset
                                + sVar1;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction]
                                      .short_.yOffset
                                + sVar2;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar6;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a0f < this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                        iVar6 = DAT_TileMapState::instance.directionTranslationMatrix[sVar2][_direction + 1] + iVar3;
                        if (DAT_TileMapState::instance.WalkLayer[iVar6] != this->searchGeneration
                            && (DAT_TileMapState::instance.LogicLayer[iVar6] & 0x30) == 0) {
                            DAT_TileMapState::instance.CertainPathLayer[iVar6]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.WalkLayer[iVar6] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction + 1]
                                      .short_.xOffset
                                + sVar1;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction + 1]
                                      .short_.yOffset
                                + sVar2;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar6;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a0f < this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                        iVar6 = DAT_TileMapState::instance.directionTranslationMatrix[sVar2][_direction + 2] + iVar3;
                        if (DAT_TileMapState::instance.WalkLayer[iVar6] != this->searchGeneration
                            && (DAT_TileMapState::instance.LogicLayer[iVar6] & 0x30) == 0) {
                            DAT_TileMapState::instance.CertainPathLayer[iVar6]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.WalkLayer[iVar6] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction + 2]
                                      .short_.xOffset
                                + sVar1;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction + 2]
                                      .short_.yOffset
                                + sVar2;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar6;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a0f < this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                        iVar6 = DAT_TileMapState::instance.directionTranslationMatrix[sVar2][_direction + 3] + iVar3;
                        if (DAT_TileMapState::instance.WalkLayer[iVar6] != this->searchGeneration
                            && (DAT_TileMapState::instance.LogicLayer[iVar6] & 0x30) == 0) {
                            DAT_TileMapState::instance.CertainPathLayer[iVar6]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.WalkLayer[iVar6] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction + 3]
                                      .short_.xOffset
                                + sVar1;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction + 3]
                                      .short_.yOffset
                                + sVar2;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar6;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a0f < this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                    }

                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                    if (0x13a0f < this->searchQueue.readIndex) {
                        this->searchQueue.readIndex = 0;
                    }
                    if (this->searchQueue.readIndex == this->searchQueue.writeIndex) {
                        return FALSE;
                    }
                }
            }
            return FALSE;
        }

    }
}
}
