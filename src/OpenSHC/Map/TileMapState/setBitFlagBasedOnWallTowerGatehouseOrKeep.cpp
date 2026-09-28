#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"

#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004FF870
    byte TileMapState::setBitFlagBasedOnWallTowerGatehouseOrKeep(int x, int y)
    {
        /*
          The original is handwritten assembly: it materialises zero with "mov edx, 0" instead of
          "xor edx, edx", advances the tile pointer with four "add esi, ecx" instead of a scaled lea,
          spills the row base with a bare push/pop across the middle of the body, and reaches the
          fields through the global instance's absolute address rather than through this (which is why
          the loads below differ: MSVC inline asm cannot name DAT_TileMapState::instance, as "::" is
          not parseable there). Written as C++ it would be:

          this->bitFlag = 0;
          if ((this->ptr_LogicLayer[this->DAT_SomeTile + 1] & (L_WALL_OR_GATEHOUSE | L_KEEP_NON_MANOR_HOUSE)) != 0) {
              this->bitFlag = 0x20;
          }
          ... and so on for the eight neighbours, where the north row is offset by
          ptr_MovementDirectionTranslationMatrix[DAT_SomeY * 8 + 0] and the south row by [+ 4].
        */
        this->DAT_SomeY = y;
        this->DAT_SomeTile = MACRO_CALL_MEMBER(
            OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile, DAT_ViewportRenderState::ptr)(x, y);

        __asm {
            mov eax, this
            mov edi, dword ptr [eax]TileMapState.ptr_MovementDirectionTranslationMatrix
            mov esi, dword ptr [eax]TileMapState.ptr_LogicLayer
            mov eax, dword ptr [eax]TileMapState.DAT_SomeTile
            shl eax, 0x2
            add esi, eax
            push esi
            mov eax, this
            mov eax, dword ptr [eax]TileMapState.DAT_SomeY
            shl eax, 0x5
            add edi, eax
            mov edx, 0x0
            mov eax, dword ptr [esi + 0x4]
            mov ebx, dword ptr [esi - 0x4]
            and eax, 0x10000100
            jz east_done
            or edx, 0x20
        east_done:
            and ebx, 0x10000100
            jz west_done
            or edx, 0x2
        west_done:
            mov ecx, dword ptr [edi]
            add esi, ecx
            add esi, ecx
            add esi, ecx
            add esi, ecx
            mov eax, dword ptr [esi - 0x4]
            mov ebx, dword ptr [esi + 0x4]
            mov ecx, dword ptr [esi]
            and eax, 0x10000100
            jz north_west_done
            or edx, 0x1
        north_west_done:
            and ebx, 0x10000100
            jz north_east_done
            or edx, 0x40
        north_east_done:
            and ecx, 0x10000100
            jz north_done
            or edx, 0x80
        north_done:
            mov ecx, dword ptr [edi + 0x10]
            pop esi
            add esi, ecx
            add esi, ecx
            add esi, ecx
            add esi, ecx
            mov eax, dword ptr [esi - 0x4]
            mov ebx, dword ptr [esi + 0x4]
            mov ecx, dword ptr [esi]
            and eax, 0x10000100
            jz south_west_done
            or edx, 0x4
        south_west_done:
            and ebx, 0x10000100
            jz south_east_done
            or edx, 0x10
        south_east_done:
            and ecx, 0x10000100
            jz south_done
            or edx, 0x8
        south_done:
            mov eax, this
            mov byte ptr [eax]TileMapState.bitFlag, dl
        }

        return this->bitFlag;
    }

}
}
