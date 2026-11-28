#pragma once

#include <cstddef>

#include "OpenSHC/Map/TileMapState.hpp"

/**
  Hand-written assembly macros for OpenSHC::Map::Units::TroopValueState.

  Only sequences that MSVC provably will not emit from C++ belong here. Every
  macro reproduces one byte-identical run from the original binary; the C++
  equivalent is kept as a comment above it so the behaviour stays readable.

  A resolver global cannot be named inside an __asm operand (`::` is not
  parseable there), and a base passed in as a pointer would assemble as
  register-indirect addressing where the original uses absolute. So the
  namespace below re-declares the resolver's own address as unqualified
  enumerators, which the inline assembler accepts as compile-time constants.
  The address comes from the project's address table and the field offsets from
  the generated struct, so no literal is repeated here.

  The `ds:` override is load bearing: a bracketed constant expression on its
  own assembles as an immediate, which would load the field's address instead
  of its value.
 */

namespace OpenSHC {
namespace Map {
    namespace Units {

        // The same address DAT_TileMapState.hpp hands to MACRO_STRUCT_RESOLVER,
        // so with the struct resolvers enabled these are the original's own
        // addresses. Unqualified on purpose: __asm cannot parse `::`.
        enum {
            ASM_TileMapState = Address::SHC_3BB0A8C1_0x01A93208,

            ASM_TileMapState_DAT_SomeY = ASM_TileMapState + offsetof(TileMapState, DAT_SomeY),
            ASM_TileMapState_DAT_SomeTile = ASM_TileMapState + offsetof(TileMapState, DAT_SomeTile),
            ASM_TileMapState_ptr_MovementDirectionTranslationMatrix
            = ASM_TileMapState + offsetof(TileMapState, ptr_MovementDirectionTranslationMatrix),
            ASM_TileMapState_ptr_PathConnectionLayer
            = ASM_TileMapState + offsetof(TileMapState, ptr_PathConnectionLayer),
            ASM_TileMapState_ptr_SpecialAreasArray
            = ASM_TileMapState + offsetof(TileMapState, ptr_SpecialAreasArray),
        };

    }
}
}

/**
  Shared prologue of both neighbour fills. Leaves

      edx = specialAreasArray
      esi = &pathConnectionLayer[DAT_SomeTile]   (a copy is pushed for the body)
      edi = row DAT_SomeY of the movement direction translation matrix

  Both inputs are read back out of the globals, which is what makes these
  sequences unreachable from C++: MSVC forwards the value it just stored and
  folds the repeated address arithmetic, so it emits neither the reloads nor
  the doubling-by-two-adds that the original uses.
 */
#define MACRO_ASM_LOAD_CARDINAL_BASES()                                                                                \
    __asm mov edi, dword ptr ds:[ASM_TileMapState_ptr_MovementDirectionTranslationMatrix]                              \
    __asm mov esi, dword ptr ds:[ASM_TileMapState_ptr_PathConnectionLayer]                                             \
    __asm mov edx, dword ptr ds:[ASM_TileMapState_ptr_SpecialAreasArray]                                               \
    __asm mov eax, dword ptr ds:[ASM_TileMapState_DAT_SomeTile]                                                        \
    __asm shl eax, 1                                                                                                   \
    __asm add esi, eax                                                                                                 \
    __asm push esi                                                                                                     \
    __asm mov eax, dword ptr ds:[ASM_TileMapState_DAT_SomeY]                                                           \
    __asm shl eax, 5                                                                                                   \
    __asm add edi, eax

/**
  Fill the four even slots of `specialAreasArray` with the path connection
  values of the four cardinal neighbours of `DAT_SomeTile`.

  C++ equivalent, with the bases as named by MACRO_ASM_LOAD_CARDINAL_BASES:

      pSpecialAreas[2] = pConnection[1];
      pSpecialAreas[6] = pConnection[-1];
      pSpecialAreas[0] = pConnection[pDirection[0]];
      pSpecialAreas[4] = pConnection[pDirection[4]];

  Clobbers eax, ebx, ecx, edx, esi, edi.
 */
#define MACRO_ASM_FILL_CARDINAL_PATH_CONNECTIONS()                                                                     \
    MACRO_ASM_LOAD_CARDINAL_BASES()                                                                                    \
    __asm mov bx, word ptr [esi + 2]                                                                                   \
    __asm mov ax, word ptr [esi - 2]                                                                                   \
    __asm mov word ptr [edx + 4], bx                                                                                   \
    __asm mov word ptr [edx + 0xC], ax                                                                                 \
    __asm mov ecx, dword ptr [edi]                                                                                     \
    __asm add esi, ecx                                                                                                 \
    __asm add esi, ecx                                                                                                 \
    __asm mov bx, word ptr [esi]                                                                                       \
    __asm mov ecx, dword ptr [edi + 0x10]                                                                              \
    __asm pop esi                                                                                                      \
    __asm add esi, ecx                                                                                                 \
    __asm add esi, ecx                                                                                                 \
    __asm mov ax, word ptr [esi]                                                                                       \
    __asm mov word ptr [edx], bx                                                                                       \
    __asm mov word ptr [edx + 8], ax

/**
  Fill the four odd slots of `specialAreasArray` with the path connection
  values either side of the two diagonal neighbours of `DAT_SomeTile`.

  Same prologue and the same unreachable-from-C++ reasoning; only the tile each
  pair is taken around, and the slots written, differ.

  C++ equivalent:

      pSpecialAreas[1] = pConnection[pDirection[0] + 1];
      pSpecialAreas[7] = pConnection[pDirection[0] - 1];
      pSpecialAreas[3] = pConnection[pDirection[4] + 1];
      pSpecialAreas[5] = pConnection[pDirection[4] - 1];

  Clobbers eax, ebx, ecx, edx, esi, edi.
 */
#define MACRO_ASM_FILL_DIAGONAL_PATH_CONNECTIONS()                                                                     \
    MACRO_ASM_LOAD_CARDINAL_BASES()                                                                                    \
    __asm mov ecx, dword ptr [edi]                                                                                     \
    __asm add esi, ecx                                                                                                 \
    __asm add esi, ecx                                                                                                 \
    __asm mov bx, word ptr [esi + 2]                                                                                   \
    __asm mov ax, word ptr [esi - 2]                                                                                   \
    __asm mov word ptr [edx + 2], bx                                                                                   \
    __asm mov word ptr [edx + 0xE], ax                                                                                 \
    __asm mov ecx, dword ptr [edi + 0x10]                                                                              \
    __asm pop esi                                                                                                      \
    __asm add esi, ecx                                                                                                 \
    __asm add esi, ecx                                                                                                 \
    __asm mov bx, word ptr [esi + 2]                                                                                   \
    __asm mov ax, word ptr [esi - 2]                                                                                   \
    __asm mov word ptr [edx + 6], bx                                                                                   \
    __asm mov word ptr [edx + 0xA], ax
