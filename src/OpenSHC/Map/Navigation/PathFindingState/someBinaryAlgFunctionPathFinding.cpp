#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Location/Point8ShortXY.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {
        using OpenSHC::Map::Location::Point8ShortXY;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0049D640
        undefined4 PathFindingState::someBinaryAlgFunctionPathFinding(int param_1)
        {
            short* psVar6;
            int (*paiVar7)[8];
            this->searchGeneration = this->searchGeneration + 1;
            if (32000 < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
            }
            this->searchQueue.readIndex = 0;
            this->searchQueue.writeIndex = 1;
            this->searchQueue.currentDistance = 1;
            ushort uVar1 = DAT_TileMapState::instance.PathConnectionLayer[DAT_UnitsState::instance.units[param_1].tile];
            this->searchQueue.yQueue[0] = DAT_UnitsState::instance.units[param_1].y;
            this->searchQueue.xQueue[0] = DAT_UnitsState::instance.units[param_1].x;
            this->searchQueue.tilesQueue[0] = DAT_UnitsState::instance.units[param_1].tile;
            DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]] = 1;
            DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
            if (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                do {
                    int iVar4 = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                    if (iVar4 < 0) {
                        return (undefined4)(1);
                    }
                    if (0x13a0f < iVar4) {
                        return (undefined4)(1);
                    }
                    int sVar2 = (int)this->searchQueue.xQueue[this->searchQueue.readIndex];
                    int sVar3 = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                    this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[iVar4];
                    if (0x13a10 < this->searchQueue.currentDistance) {
                        return (undefined4)(1);
                    }
                    for (int _direction = 0; _direction < 8; _direction = _direction + 1) {
                        int iVar5 = DAT_TileMapState::instance.directionTranslationMatrix[sVar3][_direction] + iVar4;
                        if ((DAT_TileMapState::instance.WalkLayer[iVar5] != this->searchGeneration)
                            && (DAT_TileMapState::instance.PathConnectionLayer[iVar5] == uVar1)) {
                            if ((DAT_TileMapState::instance.LogicLayer[iVar5] & 0x10000100U) == 0
                                || (DAT_TileMapState::instance.LogicLayer[iVar5] & 0x400000U) != 0) {
                                return (undefined4)(0);
                            }
                            DAT_TileMapState::instance.CertainPathLayer[iVar5]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.WalkLayer[iVar5] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].short_.xOffset + sVar2;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex] = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].short_.yOffset + sVar3;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar5;
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
                } while (this->searchQueue.readIndex != this->searchQueue.writeIndex);
            }
            return (undefined4)(1);
        }

    }
}
}
