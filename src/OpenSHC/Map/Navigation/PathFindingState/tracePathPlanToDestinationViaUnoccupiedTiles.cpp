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
        BOOLEnum PathFindingState::tracePathPlanToDestinationViaUnoccupiedTiles(uint x, uint y, uint destX, uint destY)
        {
            byte* _pPathPlan;
            int _budget;
            int _direction;
            int _result;
            uint _ppIndex;
            Point8* _cardinal;
            int* _dirMatrix;
            uchar* _linkage;
            uchar* _occupancy;
            int _fireCount;
            int _destTile;
            uint _gen;
            int _tile;
            short* _walkLayer;
            if (399 < x || 399 < y) {
                return FALSE;
            }
            if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == '\0') {
                return FALSE;
            }
            if (399 < destX || 399 < destY) {
                return FALSE;
            }
            if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[destY * 400 + destX] == '\0') {
                return FALSE;
            }
            this->searchGeneration = this->searchGeneration + 1;
            if (32000 < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
            }
            _budget = 0;
            _result = 0;
            _direction = 0;
            _gen = (ushort)this->searchGeneration;
            _fireCount = DAT_EntityState::instance.fireCount;
            _tile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
            _destTile = DAT_ViewportRenderState::instance.translationMatrix[destY].addXgetTile + destX;
            _occupancy = DAT_TileMapState::instance.OccupancyLayer;
            _walkLayer = DAT_TileMapState::instance.WalkLayer;
            _linkage = DAT_TileMapState::instance.PathLinkageLayer;
            _dirMatrix = &DAT_TileMapState::instance.directionTranslationMatrix[0][0];
            _cardinal = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix;
            _pPathPlan = this->searchQueue.ptrPathPlan;
            _ppIndex = this->searchQueue.pathPlanIndex;
            // The walk itself is handwritten assembly in the original (0x0049A481..0x0049A5BB), in
            // the same hand as LinkageNeighbourAsm.hpp: x, y, the tile and the walk layer stay in
            // ebx, ecx, edx and edi across iterations, everything else is reloaded from its slot
            // before each use, the direction is stored as a constant and read back, and the
            // three-way compare on y then x picks the direction and its linkage bit.
            // clang-format off
            __asm {
                mov edi, _walkLayer
                mov ebx, x
                mov ecx, y
                mov edx, _tile
            trace_loop:
                add dword ptr _budget, 1
                cmp dword ptr _budget, 400
                jge trace_exit
                mov ax, word ptr _gen
                mov word ptr [edi + edx*2], ax
                mov eax, _destTile
                cmp edx, eax
                je trace_found
                mov eax, _fireCount
                cmp eax, 0
                je trace_links
                mov esi, _occupancy
                mov al, byte ptr [esi + edx]
                cmp al, 0
                jne trace_exit
            trace_links:
                mov esi, _linkage
                mov al, byte ptr [esi + edx]
                cmp ecx, destY
                jg trace_y_greater
                jl trace_y_less
                cmp ebx, destX
                jg trace_dir6
                jl trace_dir2
                jmp trace_exit
            trace_dir6:
                mov dword ptr _direction, 6
                test al, 0x40
                je trace_exit
                jmp trace_step
            trace_dir2:
                mov dword ptr _direction, 2
                test al, 4
                je trace_exit
                jmp trace_step
            trace_y_greater:
                cmp ebx, destX
                jg trace_dir7
                jl trace_dir1
                mov dword ptr _direction, 0
                test al, 1
                je trace_exit
                jmp trace_step
            trace_dir7:
                mov dword ptr _direction, 7
                test al, 0x80
                je trace_exit
                jmp trace_step
            trace_dir1:
                mov dword ptr _direction, 1
                test al, 2
                je trace_exit
                jmp trace_step
            trace_y_less:
                cmp ebx, destX
                jg trace_dir5
                jl trace_dir3
                mov dword ptr _direction, 4
                test al, 0x10
                je trace_exit
                jmp trace_step
            trace_dir5:
                mov dword ptr _direction, 5
                test al, 0x20
                je trace_exit
                jmp trace_step
            trace_dir3:
                mov dword ptr _direction, 3
                test al, 8
                je trace_exit
                jmp trace_step
            trace_step:
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
                add dword ptr _ppIndex, 1
                test eax, 1
                je trace_even_slot
                shr eax, 1
                add esi, eax
                mov eax, _direction
                shl eax, 4
                and byte ptr [esi], 0xf
                or byte ptr [esi], al
                jmp trace_loop
            trace_even_slot:
                shr eax, 1
                add esi, eax
                mov eax, _direction
                mov byte ptr [esi], al
                jmp trace_loop
            trace_found:
                mov dword ptr _result, 1
            trace_exit:
            }
            // clang-format on
            this->searchQueue.pathPlanIndex = _ppIndex;
            return (BOOLEnum)_result;
        }
    }
}
}
