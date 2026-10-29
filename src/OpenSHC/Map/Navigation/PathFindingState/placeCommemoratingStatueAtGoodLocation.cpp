#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Map/Location/Point8ShortXY.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::Commands::MappersEnum;
        using OpenSHC::Map::Location::Point8ShortXY;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          WARNING: Enum "MappersEnumInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A21B0
        void PathFindingState::placeCommemoratingStatueAtGoodLocation(int playerID)
        {
            int iVar3;
            short* psVar4;
            int* piVar5;
            int iVar6;
            MappersEnum commandBuildingType;
            int sVar1 = (int)DAT_GameState::instance.playerDataArray[playerID].someKeepRelatedX2;
            int sVar2 = (int)DAT_GameState::instance.playerDataArray[playerID].someKeepRelatedY2;
            if ((uint)sVar1 > 399 || (uint)sVar2 > 399
                || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[sVar2 * 400 + sVar1] == '\0') {
                return;
            }
            this->calculations = this->calculations + 1;
            this->searchGeneration = this->searchGeneration + 1;
            if (32000 < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
            }
            this->searchQueue.currentDistance = 1;
            this->searchQueue.readIndex = 0;
            this->searchQueue.writeIndex = 1;
            this->searchQueue.yQueue[0] = (short)sVar2;
            this->searchQueue.xQueue[0] = (short)sVar1;
            this->searchQueue.tilesQueue[0] = DAT_ViewportRenderState::instance.translationMatrix[sVar2].addXgetTile + sVar1;
            DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]]
                = (short)this->searchQueue.currentDistance;
            DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
            commandBuildingType = (OpenSHC::Commands::MappersEnum)((int)SEC_RNG::instance.currentNumber2 % 5
                + OpenSHC::Commands::M_MAPPER_STATUE1);
            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            while (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                iVar3 = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                if (iVar3 < 0) {
                    return;
                }
                if (iVar3 >= 0x13a10) {
                    return;
                }
                sVar1 = (int)this->searchQueue.xQueue[this->searchQueue.readIndex];
                sVar2 = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[iVar3];
                if (0x13a10 < (int)this->searchQueue.currentDistance) {
                    return;
                }
                if (0x14 < (int)this->searchQueue.currentDistance) {
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::checkBuildingCanBePlacedHere,
                    DAT_TileMapState::ptr)(playerID, (uint)(sVar1), (uint)(sVar2), commandBuildingType, -2);
                if (DAT_TileMapState::instance.buildingPlacementFail == FALSE) {
                    DAT_TileMapState::instance.field122_0x554930 = 1;
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placeBuilding, DAT_TileMapState::ptr)(
                        playerID, sVar1, sVar2, commandBuildingType, 2, 0xf);
                    iVar3 = DAT_TileMapState::instance.placedBuildingID;
                    DAT_BuildingsState::instance.buildings[iVar3].owner = 0;
                    DAT_BuildingsState::instance.buildings[iVar3].statueCommemoratingPlayerID = (short)playerID;
                    return;
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
                            + (short)sVar1;
                        this->searchQueue.yQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction]
                                  .short_.yOffset
                            + (short)sVar2;
                        this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar6;
                        this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                        if (0x13a10 <= (int)this->searchQueue.writeIndex) {
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
                            + (short)sVar1;
                        this->searchQueue.yQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction + 1]
                                  .short_.yOffset
                            + (short)sVar2;
                        this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar6;
                        this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                        if (0x13a10 <= (int)this->searchQueue.writeIndex) {
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
                            + (short)sVar1;
                        this->searchQueue.yQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction + 2]
                                  .short_.yOffset
                            + (short)sVar2;
                        this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar6;
                        this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                        if (0x13a10 <= (int)this->searchQueue.writeIndex) {
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
                            + (short)sVar1;
                        this->searchQueue.yQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction + 3]
                                  .short_.yOffset
                            + (short)sVar2;
                        this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar6;
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
            }
            return;
        }

    }
}
}
