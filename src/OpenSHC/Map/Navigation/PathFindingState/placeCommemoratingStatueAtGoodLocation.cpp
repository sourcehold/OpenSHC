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
            uint uVar7;
            uint uVar8;
            short sVar1 = DAT_GameState::instance.playerDataArray[playerID].someKeepRelatedX2;
            uVar7 = (uint)sVar1;
            short sVar2 = DAT_GameState::instance.playerDataArray[playerID].someKeepRelatedY2;
            uVar8 = (uint)sVar2;
            if (uVar7 <= 399 && uVar8 <= 399 && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[uVar8 * 400 + uVar7] != '\0') {
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
                this->searchQueue.tilesQueue[0]
                    = DAT_ViewportRenderState::instance.translationMatrix[uVar8].addXgetTile + uVar7;
                this->searchQueue.yQueue[0] = sVar2;
                this->searchQueue.xQueue[0] = sVar1;
                DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]] = 1;
                DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
                commandBuildingType = (OpenSHC::Commands::MappersEnum)((int)SEC_RNG::instance.currentNumber2 % 5
                    + OpenSHC::Commands::M_MAPPER_STATUE1);
                MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
                if (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                    while (true) {
                        iVar3 = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                        if (iVar3 < 0) {
                            return;
                        }
                        if (0x13a0f < iVar3) {
                            return;
                        }
                        sVar1 = this->searchQueue.xQueue[this->searchQueue.readIndex];
                        sVar2 = this->searchQueue.yQueue[this->searchQueue.readIndex];
                        uVar7 = (uint)sVar2;
                        this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[iVar3];
                        if (0x13a10 < this->searchQueue.currentDistance) {
                            return;
                        }
                        if (0x14 < this->searchQueue.currentDistance) {
                            return;
                        }
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::checkBuildingCanBePlacedHere,
                            DAT_TileMapState::ptr)(playerID, (uint)(sVar1), uVar7, commandBuildingType, -2);
                        if (DAT_TileMapState::instance.buildingPlacementFail == FALSE)
                            break;
                        piVar5 = DAT_TileMapState::instance.directionTranslationMatrix[uVar7] + 1;
                        psVar4 = &DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[0].short_.yOffset;
                        do {
                            iVar6 = (*(int (*)[8])(piVar5 + -1))[0] + iVar3;
                            if (DAT_TileMapState::instance.WalkLayer[iVar6] != this->searchGeneration
                                && (DAT_TileMapState::instance.LogicLayer[iVar6] & 0x30) == 0) {
                                DAT_TileMapState::instance.CertainPathLayer[iVar6]
                                    = (short)this->searchQueue.currentDistance + 1;
                                DAT_TileMapState::instance.WalkLayer[iVar6] = (short)this->searchGeneration;
                                this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                    = ((Point8ShortXY*)(psVar4 + -2))->xOffset + sVar1;
                                this->searchQueue.yQueue[this->searchQueue.writeIndex] = *psVar4 + sVar2;
                                this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar6;
                                this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                if (0x13a0f < this->searchQueue.writeIndex) {
                                    this->searchQueue.writeIndex = 0;
                                }
                            }
                            iVar6 = *piVar5 + iVar3;
                            if (DAT_TileMapState::instance.WalkLayer[iVar6] != this->searchGeneration
                                && (DAT_TileMapState::instance.LogicLayer[iVar6] & 0x30) == 0) {
                                DAT_TileMapState::instance.CertainPathLayer[iVar6]
                                    = (short)this->searchQueue.currentDistance + 1;
                                DAT_TileMapState::instance.WalkLayer[iVar6] = (short)this->searchGeneration;
                                this->searchQueue.xQueue[this->searchQueue.writeIndex] = psVar4[2] + sVar1;
                                this->searchQueue.yQueue[this->searchQueue.writeIndex] = psVar4[4] + sVar2;
                                this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar6;
                                this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                if (0x13a0f < this->searchQueue.writeIndex) {
                                    this->searchQueue.writeIndex = 0;
                                }
                            }
                            iVar6 = piVar5[1] + iVar3;
                            if (DAT_TileMapState::instance.WalkLayer[iVar6] != this->searchGeneration
                                && (DAT_TileMapState::instance.LogicLayer[iVar6] & 0x30) == 0) {
                                DAT_TileMapState::instance.CertainPathLayer[iVar6]
                                    = (short)this->searchQueue.currentDistance + 1;
                                DAT_TileMapState::instance.WalkLayer[iVar6] = (short)this->searchGeneration;
                                this->searchQueue.xQueue[this->searchQueue.writeIndex] = psVar4[6] + sVar1;
                                this->searchQueue.yQueue[this->searchQueue.writeIndex] = psVar4[8] + sVar2;
                                this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar6;
                                this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                if (0x13a0f < this->searchQueue.writeIndex) {
                                    this->searchQueue.writeIndex = 0;
                                }
                            }
                            iVar6 = piVar5[2] + iVar3;
                            if (DAT_TileMapState::instance.WalkLayer[iVar6] != this->searchGeneration
                                && (DAT_TileMapState::instance.LogicLayer[iVar6] & 0x30) == 0) {
                                DAT_TileMapState::instance.CertainPathLayer[iVar6]
                                    = (short)this->searchQueue.currentDistance + 1;
                                DAT_TileMapState::instance.WalkLayer[iVar6] = (short)this->searchGeneration;
                                this->searchQueue.xQueue[this->searchQueue.writeIndex] = psVar4[10] + sVar1;
                                this->searchQueue.yQueue[this->searchQueue.writeIndex] = psVar4[0xc] + sVar2;
                                this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar6;
                                this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                if (0x13a0f < this->searchQueue.writeIndex) {
                                    this->searchQueue.writeIndex = 0;
                                }
                            }
                            piVar5 = piVar5 + 4;
                            psVar4 = psVar4 + 0x10;
                        } while ((int)psVar4 < 0xb4908c);
                        this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                        if (0x13a0f < this->searchQueue.readIndex) {
                            this->searchQueue.readIndex = 0;
                        }
                        if (this->searchQueue.readIndex == this->searchQueue.writeIndex) {
                            return;
                        }
                    }
                    DAT_TileMapState::instance.field122_0x554930 = 1;
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placeBuilding, DAT_TileMapState::ptr)(
                        playerID, (int)(sVar1), (int)(uVar7), commandBuildingType, 2, 0xf);
                    iVar3 = DAT_TileMapState::instance.placedBuildingID;
                    DAT_BuildingsState::instance.buildings[DAT_TileMapState::instance.placedBuildingID].owner = 0;
                    DAT_BuildingsState::instance.buildings[iVar3].statueCommemoratingPlayerID = (short)playerID;
                }
            }
            return;
        }

    }
}
}
