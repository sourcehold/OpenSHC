#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_EntityState.hpp"
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
             @return bool whether destination was reached   decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0049A370
        BOOLEnum PathFindingState::tracePathPlanToDestinationViaUnoccupiedTiles(uint ySpace, uint y, uint destX, uint destY)
        {
            if (399 < ySpace || 399 < y || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + ySpace] == '\0') {
                return FALSE;
            }
            if (399 < destX || 399 < destY
                || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[destY * 400 + destX] == '\0') {
                return FALSE;
            }
            this->searchGeneration = this->searchGeneration + 1;
            if (32000 < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
            }
            /*
              The walk itself is handwritten assembly in the original (0x0049A481-0x0049A5C2): every layer
              base and both end points live in their own stack slot and are reloaded at each use,
              "cmp eax, 0" instead of "test", and a "jmp" to the very next instruction. The setup and the
              epilogue around it are compiler-generated.
             */
            int _budget = 0;
            int _result = 0;
            int _direction = 0;
            uint _gen = (ushort)this->searchGeneration;
            int _fireCount = DAT_EntityState::instance.fireCount;
            int _tile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + ySpace;
            int _destTile = DAT_ViewportRenderState::instance.translationMatrix[destY].addXgetTile + destX;
            uchar* _occupancy = DAT_TileMapState::instance.OccupancyLayer;
            short* _walkLayer = DAT_TileMapState::instance.WalkLayer;
            uchar* _linkage = DAT_TileMapState::instance.PathLinkageLayer;
            int* _dirMatrix = &DAT_TileMapState::instance.directionTranslationMatrix[0][0];
            Point8* _cardinal = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix;
            byte* _pPathPlan = this->searchQueue.ptrPathPlan;
            uint _ppIndex = this->searchQueue.pathPlanIndex;
            // clang-format off
            __asm {
                mov edi, _walkLayer
                mov ebx, ySpace
                mov ecx, y
                mov edx, _tile
            L_loop:
                add _budget, 1
                cmp _budget, 0x190
                jge L_exit
                mov ax, word ptr _gen
                mov word ptr [edi + edx*2], ax
                mov eax, _destTile
                cmp edx, eax
                je L_found
                mov eax, _fireCount
                cmp eax, 0
                je L_noFire
                mov esi, _occupancy
                mov al, byte ptr [esi + edx]
                cmp al, 0
                jne L_exit
            L_noFire:
                mov esi, _linkage
                mov al, byte ptr [esi + edx]
                cmp ecx, destY
                jg L_north
                jl L_south
                cmp ebx, destX
                jg L_west
                jl L_east
                jmp L_exit
            L_west:
                mov _direction, 6
                test al, 0x40
                je L_exit
                jmp L_step
            L_east:
                mov _direction, 2
                test al, 4
                je L_exit
                jmp L_step
            L_north:
                cmp ebx, destX
                jg L_northWest
                jl L_northEast
                mov _direction, 0
                test al, 1
                je L_exit
                jmp L_step
            L_northWest:
                mov _direction, 7
                test al, 0x80
                je L_exit
                jmp L_step
            L_northEast:
                mov _direction, 1
                test al, 2
                je L_exit
                jmp L_step
            L_south:
                cmp ebx, destX
                jg L_southWest
                jl L_southEast
                mov _direction, 4
                test al, 0x10
                je L_exit
                jmp L_step
            L_southWest:
                mov _direction, 5
                test al, 0x20
                je L_exit
                jmp L_step
            L_southEast:
                mov _direction, 3
                test al, 8
                je L_exit
                jmp L_step
            L_step:
                mov eax, ecx
                shl eax, 3
                add eax, _direction
                shl eax, 2
                mov esi, _dirMatrix
                add edx, dword ptr [esi + eax]
                mov esi, _cardinal
                mov eax, _direction
                add ebx, dword ptr [esi + eax*8]
                add ecx, dword ptr [esi + eax*8 + 4]
                mov eax, _ppIndex
                mov esi, _pPathPlan
                add _ppIndex, 1
                test eax, 1
                je L_even
                shr eax, 1
                add esi, eax
                mov eax, _direction
                shl eax, 4
                and byte ptr [esi], 0xf
                or byte ptr [esi], al
                jmp L_loop
            L_even:
                shr eax, 1
                add esi, eax
                mov eax, _direction
                mov byte ptr [esi], al
                jmp L_loop
            L_found:
                mov _result, 1
            L_exit:
            }
            // clang-format on
            this->searchQueue.pathPlanIndex = _ppIndex;
            return (BOOLEnum)_result;
        }
    }
}
}
