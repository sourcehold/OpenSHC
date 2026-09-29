#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState/LinkageNeighbourAsm.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
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
         * Performs BFS pathfinding for AI units to determine if a path exists between two points.    * This is a fast
         * "can reach" check rather than a full path reconstruction.    *     * Key features:    * - Diagonal movement
         * costs 2, cardinal movement costs 1    * - Can optionally reuse previous search state (for incremental
         * searches)    * - Returns immediately upon finding target (doesn't compute full distance map)    * - Limited
         * by param_5 (max search depth)    *     * @param this - PathFindingState object pointer    * @param x -
         * Starting X coordinate (0-399)    * @param y - Starting Y coordinate (0-399)    * @param x2 - Target X
         * coordinate (0-399, or -1 for "search without target")    * @param y2 - Target Y coordinate (0-399)    *
         * @param param_5 - Maximum search depth/distance limit    * @param doNotIncrementSearchGeneration - If
         * non-zero, continue previous search (incremental   mode)    * @return 1 if target is reachable, 0 otherwise
         * decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00497740
        BOOLEnum PathFindingState::findLinkageBasedPathOrWalkRadius(
            uint x, uint y, int x2, int y2, int maxIterations, BOOLEnum continuePreviousSearch)
        {
            /*
              === VALIDATE STARTING POSITION ===   Check bounds (400x400) and walkability
             */
            if (399 < x || 399 < y || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == '\0') {
                return FALSE;
            }
            /*
              === VALIDATE TARGET POSITION ===   If the target is given but invalid, cap the search depth at 500
             */
            if (x2 != -1
                && (399 < (uint)x2 || 399 < (uint)y2
                    || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y2 * 400 + x2] == '\0')
                && 500 < maxIterations) {
                maxIterations = 500;
            }
            if (continuePreviousSearch == FALSE) {
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
              the layers and the queue through these locals; see LinkageNeighbourAsm.hpp. The queue
              indices and the target tile live in the parameter slots, as they do in the original.
             */
            short _curGen = (short)this->searchGeneration;
            short* _walkLayer = DAT_TileMapState::instance.WalkLayer;
            short* _certainPath = DAT_TileMapState::instance.CertainPathLayer;
            int* _tilesQueue = this->searchQueue.tilesQueue;
            short* _yQueue = this->searchQueue.yQueue;
            int* _dirMatrix = &DAT_TileMapState::instance.directionTranslationMatrix[0][0];
            uchar* _linkage = DAT_TileMapState::instance.PathLinkageLayer;

            this->searchQueue.yQueue[0] = (short)y;
            this->searchQueue.tilesQueue[0] = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
            DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]] = 1;
            DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = _curGen;

            y = this->searchQueue.writeIndex;
            int _readIndex = this->searchQueue.readIndex;
            continuePreviousSearch = this->searchQueue.depth;
            if (x2 == -1) {
                x = 0;
            } else {
                x = DAT_ViewportRenderState::instance.translationMatrix[y2].addXgetTile + x2;
            }
            int _result = 0;
            while (_readIndex != (int)y && (int)continuePreviousSearch < maxIterations) {
                continuePreviousSearch = continuePreviousSearch + 1;
                int _tile = this->searchQueue.tilesQueue[_readIndex];
                if (_tile == (int)x) {
                    _result = 1;
                    break;
                }
                short _cCardinalDistance = _certainPath[_tile] + 1;
                if (800 <= _cCardinalDistance) {
                    break;
                }
                int _cY = (ushort)this->searchQueue.yQueue[_readIndex];
                int _cLink = _linkage[_tile];

                MACRO_LINKAGE_EXPAND_NEIGHBOURS(1, y)

                _readIndex = _readIndex + 1;
            }
            this->searchQueue.writeIndex = y;
            this->searchQueue.readIndex = _readIndex;
            this->searchQueue.depth = continuePreviousSearch;
            return (BOOLEnum)_result;
        }

    }
}
}
