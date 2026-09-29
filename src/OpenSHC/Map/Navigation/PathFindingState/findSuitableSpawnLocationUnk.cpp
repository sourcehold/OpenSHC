#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState/LinkageNeighbourAsm.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
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
        // FUNCTION: STRONGHOLDCRUSADER 0x00497B80
        undefined4 PathFindingState::findSuitableSpawnLocationUnk(
            int x, int y, int x2, int y2, int param_5, int param_6)
        {
            if (399 < (uint)x || 399 < (uint)y
                || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == '\0') {
                return (undefined4)(0);
            }
            if (x2 != -1
                && (399 < (uint)x2 || 399 < (uint)y2
                    || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y2 * 400 + x2] == '\0')
                && 500 < param_5) {
                param_5 = 500;
            }
            if (param_6 == 0) {
                this->searchGeneration = this->searchGeneration + 1;
                if (32000 < this->searchGeneration) {
                    this->searchGeneration = 1;
                    MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                        0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
                }
                this->searchQueue.writeIndex = 1;
                this->searchQueue.readIndex = 0;
                this->searchQueue.depth = 0;
            }
            /*
              The eight-neighbour expansion below is handwritten assembly in the original and reaches
              the layers and the queue through these locals; see LinkageNeighbourAsm.hpp. This is the
              variant that only enters a neighbour whose OccupancyLayer byte is zero.
             */
            short _curGen = (short)this->searchGeneration;
            short* _walkLayer = DAT_TileMapState::instance.WalkLayer;
            short* _certainPath = DAT_TileMapState::instance.CertainPathLayer;
            uchar* _linkage = DAT_TileMapState::instance.PathLinkageLayer;
            uchar* _occupancy = DAT_TileMapState::instance.OccupancyLayer;
            int* _tilesQueue = this->searchQueue.tilesQueue;
            short* _yQueue = this->searchQueue.yQueue;
            int* _dirMatrix = &DAT_TileMapState::instance.directionTranslationMatrix[0][0];

            this->searchQueue.yQueue[0] = (short)y;
            this->searchQueue.tilesQueue[0] = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
            DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]] = 1;
            DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = _curGen;

            y = this->searchQueue.writeIndex;
            int _readIndex = this->searchQueue.readIndex;
            param_6 = this->searchQueue.depth;
            if (x2 == -1) {
                x = 0;
            } else {
                x = DAT_ViewportRenderState::instance.translationMatrix[y2].addXgetTile + x2;
            }
            int _result = 0;
            while (_readIndex != y && param_6 < param_5) {
                param_6 = param_6 + 1;
                int _tile = this->searchQueue.tilesQueue[_readIndex];
                if (_tile == x) {
                    _result = 1;
                    break;
                }
                short _cCardinalDistance = _certainPath[_tile] + 1;
                int _cY = (ushort)this->searchQueue.yQueue[_readIndex];
                int _cLink = _linkage[_tile];

                MACRO_LINKAGE_EXPAND_FREE_NEIGHBOURS(1, y)

                _readIndex = _readIndex + 1;
            }
            this->searchQueue.writeIndex = y;
            this->searchQueue.readIndex = _readIndex;
            this->searchQueue.depth = param_6;
            return (undefined4)(_result);
        }

    }
}
}
