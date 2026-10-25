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
            if (399 < x || 399 < y) {
                return FALSE;
            }
            if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == '\0') {
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
              From here to the return the original is handwritten assembly in the hand of
              LinkageNeighbourAsm.hpp, including the loop head: the queue indices live in the
              parameter slots (y is the write index, x2 the read index, continuePreviousSearch the
              depth, x the target tile), every layer base is reloaded from its slot before each use,
              the row position is zero-extended with "mov eax, 0 / mov ax" and the distance is kept
              in bx. Only the local set-up before the loop and the write-back after it are C.
             */
            uint _curGen = (ushort)this->searchGeneration;
            short* _walkLayer = DAT_TileMapState::instance.WalkLayer;
            short* _certainPath = DAT_TileMapState::instance.CertainPathLayer;
            int* _tilesQueue = this->searchQueue.tilesQueue;
            short* _yQueue = this->searchQueue.yQueue;
            int* _dirMatrix = &DAT_TileMapState::instance.directionTranslationMatrix[0][0];
            uchar* _linkage = DAT_TileMapState::instance.PathLinkageLayer;
            int _tile;
            int _cY;
            int _cCardinalDistance = 0;
            int _result = 0;
            this->searchQueue.yQueue[0] = (short)y;
            this->searchQueue.tilesQueue[0] = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
            DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]] = 1;
            DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)_curGen;
            y = this->searchQueue.writeIndex;
            continuePreviousSearch = this->searchQueue.depth;
            if (x2 == -1) {
                x = 0;
            } else {
                x = DAT_ViewportRenderState::instance.translationMatrix[y2].addXgetTile + x2;
            }
            x2 = this->searchQueue.readIndex;
            // clang-format off
            __asm {
            flr_loop:
                mov ecx, x2
                cmp ecx, y
                je flr_exit
                mov eax, continuePreviousSearch
                cmp eax, maxIterations
                jge flr_exit
                add dword ptr continuePreviousSearch, 1
                mov esi, _tilesQueue
                mov edx, dword ptr [esi + ecx*4]
                mov _tile, edx
                cmp edx, x
                je flr_found
                mov esi, _certainPath
                mov bx, word ptr [esi + edx*2]
                add bx, 1
                cmp bx, 0x320
                jge flr_exit
                mov word ptr _cCardinalDistance, bx
                mov esi, _yQueue
                mov eax, 0
                mov ax, word ptr [esi + ecx*2]
                mov _cY, eax
                mov edi, _walkLayer
                mov edx, _tile
                mov esi, _linkage
                mov bl, byte ptr [esi + edx]
            }
            MACRO_LINKAGE_PUSH(1, w, y, -2, 0x40, MACRO_ASM_SAME, MACRO_ASM_DEC, MACRO_ASM_SAME)
            MACRO_LINKAGE_PUSH(1, e, y, +2, 0x04, MACRO_ASM_SAME, MACRO_ASM_INC, MACRO_ASM_SAME)
            __asm mov eax, _cY
            __asm shl eax, 3
            __asm mov esi, _dirMatrix
            __asm add edx, dword ptr [esi + eax*4]
            MACRO_LINKAGE_PUSH(1, n, y, 0, 0x01, MACRO_ASM_SAME, MACRO_ASM_SAME, MACRO_ASM_DEC)
            MACRO_LINKAGE_PUSH(1, nw, y, -2, 0x80, MACRO_ASM_DIAGONAL, MACRO_ASM_DEC, MACRO_ASM_DEC)
            MACRO_LINKAGE_PUSH(1, ne, y, +2, 0x02, MACRO_ASM_DIAGONAL, MACRO_ASM_INC, MACRO_ASM_DEC)
            __asm mov edx, _tile
            __asm mov eax, _cY
            __asm shl eax, 3
            __asm add eax, 4
            __asm mov esi, _dirMatrix
            __asm add edx, dword ptr [esi + eax*4]
            MACRO_LINKAGE_PUSH(1, s, y, 0, 0x10, MACRO_ASM_SAME, MACRO_ASM_SAME, MACRO_ASM_INC)
            MACRO_LINKAGE_PUSH(1, sw, y, -2, 0x20, MACRO_ASM_DIAGONAL, MACRO_ASM_DEC, MACRO_ASM_INC)
            MACRO_LINKAGE_PUSH(1, se, y, +2, 0x08, MACRO_ASM_DIAGONAL, MACRO_ASM_INC, MACRO_ASM_INC)
            __asm {
                add dword ptr x2, 1
                jmp flr_loop
            flr_found:
                mov dword ptr _result, 1
            flr_exit:
            }
            // clang-format on
            this->searchQueue.writeIndex = y;
            this->searchQueue.readIndex = x2;
            this->searchQueue.depth = continuePreviousSearch;
            return (BOOLEnum)_result;
        }

    }
}
}
