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
          WARNING: Type propagation algorithm not settling
         */
        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0049F040
        int PathFindingState::findArcherRelatedAttackInfoIndex(int max, uint x, uint y, int tribeID)
        {
            int iVar4;
            int _candidate;
            int _tile;
            if (399 < x || 399 < y || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == '\0') {
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
                while ((_tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex],
                    -1 < _tile && (_tile < 0x13a10))) {
                    int sVar1 = (int)this->searchQueue.xQueue[this->searchQueue.readIndex];
                    int sVar2 = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                    this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[_tile];
                    if (0x13a10 < (int)this->searchQueue.currentDistance) {
                        return 0;
                    }
                    if (this->searchQueue.currentDistance > max) {
                        return 0;
                    }
                    for (int iVar5 = 0; iVar5 < 8; iVar5 = iVar5 + 1) {
                        if ((DAT_TileMapState::instance.PathLinkageLayer[_tile]
                                & DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[iVar5])
                                != 0
                            && (_candidate
                                = DAT_TileMapState::instance.directionTranslationMatrix[sVar2][iVar5] + _tile,
                                DAT_TileMapState::instance.WalkLayer[_candidate] != this->searchGeneration)) {
                            if (4 < this->searchQueue.currentDistance
                                && (DAT_TileMapState::instance.AIInfoLayer[_candidate] & 0x10) != 0
                                && (iVar4 = MACRO_CALL_MEMBER(
                                        OpenSHC::Map::Units::TroopValueState_Func::findOrReserveArcherPointSlot,
                                        DAT_TroopValueState::ptr)(_candidate),
                                    iVar4 != 0)
                                && iVar4 != DAT_TribesState::instance.tribes[tribeID].archerRelated
                                && iVar4 != DAT_TribesState::instance.tribes[tribeID].archerRelated2
                                && DAT_TroopValueState::instance.attackInfo.arch2ValuesArray[iVar4 * 2 + 0x3eb].tile
                                    == 0
                                && DAT_TroopValueState::instance.attackInfo.arch2ValuesArray[iVar4 * 2 + 0x3ea]
                                        .buildingID
                                    == 0) {
                                return iVar4;
                            }
                            DAT_TileMapState::instance.CertainPathLayer[_candidate]
                                = (short)this->searchQueue.currentDistance + 1;
                            short sVar3 = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[iVar5]
                                              .short_.xOffset;
                            DAT_TileMapState::instance.WalkLayer[_candidate] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex] = sVar3 + sVar1;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[iVar5]
                                      .short_.yOffset
                                + sVar2;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _candidate;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a10 <= this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                    }
                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                    if (0x13a10 <= this->searchQueue.readIndex) {
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
