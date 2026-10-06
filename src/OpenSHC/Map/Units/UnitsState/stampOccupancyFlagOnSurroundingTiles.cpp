#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00534490
        void UnitsState::stampOccupancyFlagOnSurroundingTiles(int unitID)
        {
            /* The 3x3 stamp is handwritten assembly in the original: the row centre is parked with
               push/pop and the locals are reloaded from their stack slots. It ORs a word
               into the byte layer, so the flag's (zero) high byte is applied to the next tile as well. */
            uchar* _layer = DAT_TileMapState::instance.OccupancyLayer;
            int _tile = this->units[unitID].tile;
            int _y = this->units[unitID].y;
            int _value = this->units[unitID].occupancyOrFlag;
            __asm {
                mov ebx, _value
                mov esi, _layer
                mov eax, _tile
                add esi, eax
                push esi
                mov edx, dword ptr [DAT_TileMapState::instance]TileMapState.ptr_MovementDirectionTranslationMatrix
                mov eax, _y
                shl eax, 5
                add edx, eax
                or word ptr [esi + 1], bx
                or word ptr [esi - 1], bx
                or word ptr [esi], bx
                mov ecx, dword ptr [edx]
                add esi, ecx
                or word ptr [esi - 1], bx
                or word ptr [esi + 1], bx
                or word ptr [esi], bx
                mov ecx, dword ptr [edx + 0x10]
                pop esi
                add esi, ecx
                or word ptr [esi - 1], bx
                or word ptr [esi + 1], bx
                or word ptr [esi], bx
            }
        }

    }
}
}
