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
            if (399 < (uint)x || 399 < (uint)y) {
                return (undefined4)(0);
            }
            if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == '\0') {
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
            /*
              From here to the return the original is handwritten assembly in the hand of
              LinkageNeighbourAsm.hpp, loop head included: the queue indices live in the parameter
              slots (y is the write index, x2 the read index, param_6 the depth, x the target tile),
              every layer base is reloaded from its slot before each use and the row position is
              zero-extended with "mov eax, 0 / mov ax". Unlike findLinkageBasedPathOrWalkRadius there
              is no cap on the distance. Only the set-up and the write-back are C.
             */
            uint _curGen = (ushort)this->searchGeneration;
            int* _tilesQueue = this->searchQueue.tilesQueue;
            short* _certainPath = DAT_TileMapState::instance.CertainPathLayer;
            short* _yQueue = this->searchQueue.yQueue;
            short* _walkLayer = DAT_TileMapState::instance.WalkLayer;
            uchar* _linkage = DAT_TileMapState::instance.PathLinkageLayer;
            uchar* _occupancy = DAT_TileMapState::instance.OccupancyLayer;
            int* _dirMatrix = &DAT_TileMapState::instance.directionTranslationMatrix[0][0];
            int _cY;
            int _tile;
            int _cCardinalDistance = 0;
            int _result = 0;
            this->searchQueue.yQueue[0] = (short)y;
            this->searchQueue.tilesQueue[0] = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
            DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]] = 1;
            DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)_curGen;
            y = this->searchQueue.writeIndex;
            param_6 = this->searchQueue.depth;
            if (x2 == -1) {
                x = 0;
            } else {
                x = DAT_ViewportRenderState::instance.translationMatrix[y2].addXgetTile + x2;
            }
            x2 = this->searchQueue.readIndex;
            // clang-format off
            __asm {
            fssl_loop:
                mov ecx, x2
                cmp ecx, y
                je fssl_exit
                mov eax, param_6
                cmp eax, param_5
                jge fssl_exit
                add dword ptr param_6, 1
                mov esi, _tilesQueue
                mov edx, dword ptr [esi + ecx*4]
                mov _tile, edx
                cmp edx, x
                je fssl_found
                mov esi, _certainPath
                mov bx, word ptr [esi + edx*2]
                add bx, 1
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
            MACRO_LINKAGE_PUSH_FREE(1, w, y, -2, -1, 0x40, MACRO_ASM_SAME, MACRO_ASM_DEC, MACRO_ASM_SAME)
            MACRO_LINKAGE_PUSH_FREE(1, e, y, +2, +1, 0x04, MACRO_ASM_SAME, MACRO_ASM_INC, MACRO_ASM_SAME)
            __asm mov eax, _cY
            __asm shl eax, 3
            __asm mov esi, _dirMatrix
            __asm add edx, dword ptr [esi + eax*4]
            MACRO_LINKAGE_PUSH_FREE(1, n, y, 0, 0, 0x01, MACRO_ASM_SAME, MACRO_ASM_SAME, MACRO_ASM_DEC)
            MACRO_LINKAGE_PUSH_FREE(1, nw, y, -2, -1, 0x80, MACRO_ASM_DIAGONAL, MACRO_ASM_DEC, MACRO_ASM_DEC)
            MACRO_LINKAGE_PUSH_FREE(1, ne, y, +2, +1, 0x02, MACRO_ASM_DIAGONAL, MACRO_ASM_INC, MACRO_ASM_DEC)
            __asm mov edx, _tile
            __asm mov eax, _cY
            __asm shl eax, 3
            __asm add eax, 4
            __asm mov esi, _dirMatrix
            __asm add edx, dword ptr [esi + eax*4]
            MACRO_LINKAGE_PUSH_FREE(1, s, y, 0, 0, 0x10, MACRO_ASM_SAME, MACRO_ASM_SAME, MACRO_ASM_INC)
            MACRO_LINKAGE_PUSH_FREE(1, sw, y, -2, -1, 0x20, MACRO_ASM_DIAGONAL, MACRO_ASM_DEC, MACRO_ASM_INC)
            MACRO_LINKAGE_PUSH_FREE(1, se, y, +2, +1, 0x08, MACRO_ASM_DIAGONAL, MACRO_ASM_INC, MACRO_ASM_INC)
            __asm {
                add dword ptr x2, 1
                jmp fssl_loop
            fssl_found:
                mov dword ptr _result, 1
            fssl_exit:
            }
            // clang-format on
            this->searchQueue.writeIndex = y;
            this->searchQueue.readIndex = x2;
            this->searchQueue.depth = param_6;
            return (undefined4)(_result);
        }

    }
}
}
