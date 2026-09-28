#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
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
        // FUNCTION: STRONGHOLDCRUSADER 0x0049EDF0
        BOOLEnum PathFindingState::findAIZoneWithFlags(int maxDistance, uint x, uint y, undefined4 aiInfoFlags)
        {
            int _candidate;
            int _tile;
            this->calculations = this->calculations + 1;
            if (x <= 399 && y <= 399 && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] != '\0') {
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
                this->searchQueue.tilesQueue[0]
                    = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
                DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]] = 1;
                DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
                if (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                    while ((_tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex],
                        -1 < _tile && (_tile < 0x13a10))) {
                        int sVar1 = (int)this->searchQueue.xQueue[this->searchQueue.readIndex];
                        int sVar2 = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                        this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[_tile];
                        if (0x13a10 < this->searchQueue.currentDistance) {
                            return FALSE;
                        }
                        if (this->searchQueue.currentDistance > maxDistance) {
                            return FALSE;
                        }
                        int _direction = 0;
                        do {
                            if ((DAT_TileMapState::instance.PathLinkageLayer[_tile]
                                    & DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[_direction])
                                    != 0
                                && (_candidate
                                    = DAT_TileMapState::instance.directionTranslationMatrix[sVar2][_direction] + _tile,
                                    DAT_TileMapState::instance.WalkLayer[_candidate] != this->searchGeneration)) {
                                if ((DAT_TileMapState::instance.AIInfoLayer[_candidate] & (byte)aiInfoFlags) != 0) {
                                    this->ALG_ResultY = (int)sVar2;
                                    this->ALG_ResultX = (int)sVar1;
                                    return TRUE;
                                }
                                DAT_TileMapState::instance.CertainPathLayer[_candidate]
                                    = (short)this->searchQueue.currentDistance + 1;
                                DAT_TileMapState::instance.WalkLayer[_candidate] = (short)this->searchGeneration;
                                this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                    = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction]
                                          .short_.xOffset
                                    + sVar1;
                                this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                    = *(short*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix
                                          + _direction * 8 + 4)
                                    + sVar2;
                                this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _candidate;
                                this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                if (0x13a0f < this->searchQueue.writeIndex) {
                                    this->searchQueue.writeIndex = 0;
                                }
                            }
                            _direction = _direction + 1;
                        } while (_direction < 8);
                        this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                        if (0x13a0f < this->searchQueue.readIndex) {
                            this->searchQueue.readIndex = 0;
                        }
                        if (this->searchQueue.readIndex == this->searchQueue.writeIndex) {
                            return FALSE;
                        }
                    }
                }
            }
            return FALSE;
        }

    }
}
}
