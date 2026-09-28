#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0049F2D0
        int PathFindingState::findSupportPointIndex(int max, uint x, uint y, int tribeID)
        {
            short sVar1;
            short sVar2;
            short sVar3;
            int iVar4;
            int iVar5;
            int iVar6;
            int tile;
            if (((399 < x) || (399 < y)) || (*(char*)(y * 400 + 0x21aec98 + x) == '\0')) {
                return 0;
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
                while ((iVar4 = this->searchQueue.tilesQueue[this->searchQueue.readIndex],
                    -1 < iVar4 && (iVar4 < 0x13a10))) {
                    sVar1 = this->searchQueue.xQueue[this->searchQueue.readIndex];
                    sVar2 = this->searchQueue.yQueue[this->searchQueue.readIndex];
                    this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[iVar4];
                    if (0x13a10 < this->searchQueue.currentDistance) {
                        return 0;
                    }
                    if (max < this->searchQueue.currentDistance) {
                        return 0;
                    }
                    iVar6 = 0;
                    do {
                        if (((DAT_TileMapState::instance.PathLinkageLayer[iVar4]
                                 & DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[iVar6])
                                != 0)
                            && (tile = DAT_TileMapState::instance.directionTranslationMatrix[sVar2][iVar6] + iVar4,
                                DAT_TileMapState::instance.WalkLayer[tile] != this->searchGeneration)) {
                            if (((4 < this->searchQueue.currentDistance)
                                    && ((((DAT_TileMapState::instance.AIInfoLayer[tile] & 0x40) != 0
                                             && (iVar5 = MACRO_CALL_MEMBER(
                                                     OpenSHC::Map::Units::TroopValueState_Func::getSupportPointIndex,
                                                     DAT_TroopValueState::ptr)(tile),
                                                 iVar5 != 0))
                                        && (iVar5 != DAT_TribesState::instance.tribes[tribeID].supportPointIndex))))
                                && (DAT_TroopValueState::instance.attackInfo.supportPointsArray[iVar5].tribeID == 0)) {
                                return iVar5;
                            }
                            DAT_TileMapState::instance.CertainPathLayer[tile]
                                = (short)this->searchQueue.currentDistance + 1;
                            sVar3 = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[iVar6]
                                        .short_.xOffset;
                            DAT_TileMapState::instance.WalkLayer[tile] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex] = sVar3 + sVar1;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                = *(short*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix
                                      + iVar6 * 8 + 4)
                                + sVar2;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = tile;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a0f < this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                        iVar6 = iVar6 + 1;
                    } while (iVar6 < 8);
                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                    if (0x13a0f < this->searchQueue.readIndex) {
                        this->searchQueue.readIndex = 0;
                    }
                    if (this->searchQueue.readIndex == this->searchQueue.writeIndex) {
                        return 0;
                    }
                }
            }
            return 0;
        }

    }
}
}
