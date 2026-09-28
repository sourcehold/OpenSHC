#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
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
            uint uVar1;
            int iVar2;
            int _candidateNorth;
            int _candidateSouth;
            short _cCardinalDistance;
            short _curGen;
            uint _candidate;
            short _cD;
            byte _cLink;
            ushort _cY;
            int _gen;
            iVar2 = x2;
            uVar1 = y;
            /*
              === VALIDATE STARTING POSITION ===   Check bounds (400x400) and walkability
             */
            if (((399 < x) || (399 < y)) || (*(char*)(y * 400 + 0x21aec98 + x) == '\0')) {
                return FALSE;
            }
            /*
              === VALIDATE TARGET POSITION ===   If target is specified (x2 != -1) and invalid, cap search depth to 500
             */
            if ((x2 != -1)
                && ((((399 < (uint)x2 || (399 < (uint)y2)) || (*(char*)(y2 * 400 + 0x21aec98 + x2) == '\0'))
                    && (500 < maxIterations)))) {
                /*
                  Limit search when target is unreachable
                 */
                maxIterations = 500;
            }
            /*
              === INITIALIZE OR CONTINUE SEARCH ===
             */
            if (continuePreviousSearch == FALSE) {
                /*
                  Start NEW search - initialize search state
                 */
                this->searchGeneration = this->searchGeneration + 1;
                if (32000 < this->searchGeneration) {
                    /*
                      Reset generation and clear WalkLayer
                     */
                    this->searchGeneration = 1;
                    MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                        0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
                }
                /*
                  Initialize BFS queue   Next free slot
                 */
                this->searchQueue.writeIndex = 1;
                /*
                  Current tile to process
                 */
                this->searchQueue.readIndex = 0;
                /*
                  Search depth counter
                 */
                this->searchQueue.depth = 0;
            }
            /*
              === SETUP SEARCH STATE ===
             */
            _gen = this->searchGeneration;
            y = this->searchQueue.writeIndex;
            /*
              Add starting position to queue
             */
            this->searchQueue.yQueue[0] = (short)uVar1;
            x2 = this->searchQueue.readIndex;
            this->searchQueue.tilesQueue[0]
                = DAT_ViewportRenderState::instance.translationMatrix[uVar1].addXgetTile + x;
            /*
              Mark starting tile with distance 1
             */
            DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]] = 1;
            continuePreviousSearch = this->searchQueue.depth;
            /*
              === COMPUTE TARGET TILE INDEX ===
             */
            /*
              Mark as visited with current search generation
             */
            DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
            if (iVar2 == -1) {
                /*
                  No target specified (exploratory search)
                 */
                x = 0;
            } else {
                x = DAT_ViewportRenderState::instance.translationMatrix[y2].addXgetTile + iVar2;
            }
            while (true) {
                /*
                   === MAIN BFS LOOP ===    === CHECK TERMINATION CONDITIONS ===
                 */
                /*
                  Queue empty - no path found
                 */
                if (x2 == y) {
                    this->searchQueue.readIndex = x2;
                    this->searchQueue.writeIndex = y;
                    this->searchQueue.depth = continuePreviousSearch;
                    return FALSE;
                }
                /*
                  Exceeded search depth limit - no path found within range
                 */
                if (maxIterations <= (int)continuePreviousSearch) {
                    this->searchQueue.readIndex = x2;
                    this->searchQueue.writeIndex = y;
                    this->searchQueue.depth = continuePreviousSearch;
                    return FALSE;
                }
                /*
                  Increment search depth counter
                 */
                continuePreviousSearch = continuePreviousSearch + TRUE;
                /*
                  === PROCESS CURRENT TILE ===
                 */
                _candidate = this->searchQueue.tilesQueue[x2];
                if (_candidate == x) {
                    /*
                      Found target! Return success
                     */
                    this->searchQueue.writeIndex = y;
                    this->searchQueue.readIndex = x2;
                    this->searchQueue.depth = continuePreviousSearch;
                    /*
                      SUCCESS - path exists
                     */
                    return TRUE;
                }
                /*
                  Get current tile's distance
                 */
                _cD = DAT_TileMapState::instance.CertainPathLayer[_candidate];
                /*
                   Distance for cardinal neighbors
                 */
                _cCardinalDistance = _cD + 1;
                /*
                  Safety check: distance overflow
                 */
                if (799 < _cCardinalDistance)
                    break;
                /*
                  Get Y coordinate and path linkage flags for current tile
                 */
                _cY = this->searchQueue.yQueue[x2];
                /*
                  8-bit flags for 8 directions
                 */
                _cLink = DAT_TileMapState::instance.PathLinkageLayer[_candidate];
                /*
                  Current search generation
                 */
                _curGen = (short)_gen;
                /*
                  === EXPAND TO 8 ADJACENT TILES ===   PathLinkageLayer bit flags:   0x01 = North, 0x02 = NorthEast,
                  0x04 = East, 0x08 = SouthEast   0x10 = South, 0x20 = SouthWest, 0x40 = West, 0x80 = NorthWest      ===
                  WEST (Cardinal: distance +1) ===
                 */
                if ((DAT_TileMapState::instance.CertainPathLayer[_candidate + 0x13a0f] != _curGen)
                    && ((_cLink & 0x40) != 0)) {
                    DAT_TileMapState::instance.CertainPathLayer[_candidate - 1] = _cCardinalDistance;
                    DAT_TileMapState::instance.CertainPathLayer[_candidate + 0x13a0f] = _curGen;
                    this->searchQueue.tilesQueue[y] = _candidate - 1;
                    this->searchQueue.yQueue[y] = _cY;
                    y = y + 1;
                }
                /*
                  === EAST (Cardinal: distance +1) ===
                 */
                if ((DAT_TileMapState::instance.WalkLayer[_candidate + 1] != _curGen) && ((_cLink & 4) != 0)) {
                    DAT_TileMapState::instance.CertainPathLayer[_candidate + 1] = _cCardinalDistance;
                    DAT_TileMapState::instance.WalkLayer[_candidate + 1] = _curGen;
                    this->searchQueue.tilesQueue[y] = _candidate + 1;
                    this->searchQueue.yQueue[y] = _cY;
                    y = y + 1;
                }
                /*
                  === NORTH (Cardinal: distance +1) ===
                 */
                _candidateNorth = _candidate + DAT_TileMapState::instance.directionTranslationMatrix[_cY][0];
                if ((DAT_TileMapState::instance.WalkLayer[_candidateNorth] != _curGen) && ((_cLink & 1) != 0)) {
                    DAT_TileMapState::instance.CertainPathLayer[_candidateNorth] = _cCardinalDistance;
                    DAT_TileMapState::instance.WalkLayer[_candidateNorth] = _curGen;
                    this->searchQueue.tilesQueue[y] = _candidateNorth;
                    this->searchQueue.yQueue[y] = _cY - 1;
                    y = y + 1;
                }
                /*
                  === NORTHWEST (Diagonal: distance +2) ===
                 */
                if ((DAT_TileMapState::instance.CertainPathLayer[_candidateNorth + 0x13a0f] != _curGen)
                    && ((_cLink & 0x80) != 0)) {
                    DAT_TileMapState::instance.CertainPathLayer[_candidateNorth + -1] = _cD + 2;
                    DAT_TileMapState::instance.CertainPathLayer[_candidateNorth + 0x13a0f] = _curGen;
                    this->searchQueue.tilesQueue[y] = _candidateNorth + -1;
                    this->searchQueue.yQueue[y] = _cY - 1;
                    y = y + 1;
                }
                /*
                  === NORTHEAST (Diagonal: distance +2) ===
                 */
                if ((DAT_TileMapState::instance.WalkLayer[_candidateNorth + 1] != _curGen) && ((_cLink & 2) != 0)) {
                    DAT_TileMapState::instance.CertainPathLayer[_candidateNorth + 1] = _cD + 2;
                    DAT_TileMapState::instance.WalkLayer[_candidateNorth + 1] = _curGen;
                    this->searchQueue.tilesQueue[y] = _candidateNorth + 1;
                    this->searchQueue.yQueue[y] = _cY - 1;
                    y = y + 1;
                }
                /*
                  === SOUTH (Cardinal: distance +1) ===
                 */
                _candidateSouth = _candidate + DAT_TileMapState::instance.directionTranslationMatrix[_cY][4];
                if ((DAT_TileMapState::instance.WalkLayer[_candidateSouth] != _curGen) && ((_cLink & 0x10) != 0)) {
                    DAT_TileMapState::instance.CertainPathLayer[_candidateSouth] = _cCardinalDistance;
                    DAT_TileMapState::instance.WalkLayer[_candidateSouth] = _curGen;
                    this->searchQueue.tilesQueue[y] = _candidateSouth;
                    this->searchQueue.yQueue[y] = _cY + 1;
                    y = y + 1;
                }
                /*
                  === SOUTHWEST (Diagonal: distance +2) ===
                 */
                if ((DAT_TileMapState::instance.CertainPathLayer[_candidateSouth + 0x13a0f] != _curGen)
                    && ((_cLink & 0x20) != 0)) {
                    DAT_TileMapState::instance.CertainPathLayer[_candidateSouth + -1] = _cD + 2;
                    DAT_TileMapState::instance.CertainPathLayer[_candidateSouth + 0x13a0f] = _curGen;
                    this->searchQueue.tilesQueue[y] = _candidateSouth + -1;
                    this->searchQueue.yQueue[y] = _cY + 1;
                    y = y + 1;
                }
                /*
                  === SOUTHEAST (Diagonal: distance +2) ===
                 */
                if ((DAT_TileMapState::instance.WalkLayer[_candidateSouth + 1] != _curGen) && ((_cLink & 8) != 0)) {
                    DAT_TileMapState::instance.CertainPathLayer[_candidateSouth + 1] = _cD + 2;
                    DAT_TileMapState::instance.WalkLayer[_candidateSouth + 1] = _curGen;
                    this->searchQueue.tilesQueue[y] = _candidateSouth + 1;
                    this->searchQueue.yQueue[y] = _cY + 1;
                    y = y + 1;
                }
                /*
                  Move to next tile in queue
                 */
                x2 = x2 + 1;
            }
            this->searchQueue.readIndex = x2;
            this->searchQueue.writeIndex = y;
            this->searchQueue.depth = continuePreviousSearch;
            return FALSE;
        }

    }
}
}
