#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00534520
        void UnitsState::writeSixToTileMap1104InAllDirections(int unitID, undefined4 six)
        {
            /* The 3x3 stamp is handwritten assembly in the original: the row centre is parked with
               push/pop and the locals are reloaded from their stack slots. */
            uchar* _layer = DAT_TileMapState::instance.SEC_TileMap1104;
            int _tile = this->units[unitID].tile;
            int _y = this->units[unitID].y;
            __asm {
                mov ebx, six
                mov esi, _layer
                mov eax, _tile
                add esi, eax
                push esi
                mov edx, dword ptr [DAT_TileMapState::instance]TileMapState.ptr_MovementDirectionTranslationMatrix
                mov eax, _y
                shl eax, 5
                add edx, eax
                mov byte ptr [esi + 1], bl
                mov byte ptr [esi - 1], bl
                mov byte ptr [esi], bl
                mov ecx, dword ptr [edx]
                add esi, ecx
                mov byte ptr [esi - 1], bl
                mov byte ptr [esi + 1], bl
                mov byte ptr [esi], bl
                mov ecx, dword ptr [edx + 0x10]
                pop esi
                add esi, ecx
                mov byte ptr [esi - 1], bl
                mov byte ptr [esi + 1], bl
                mov byte ptr [esi], bl
            }
        }

    }
}
}
