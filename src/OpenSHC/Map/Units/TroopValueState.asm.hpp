#pragma once

/**
  Hand-written assembly macros for OpenSHC::Map::Units::TroopValueState.

  Only sequences that MSVC provably will not emit from C++ belong here. Every
  macro reproduces one byte-identical run from the original binary; the C++
  equivalent is kept as a comment above it so the behaviour stays readable.

  A resolver global cannot be named inside an __asm operand (`::` is not
  parseable there), so the operands are absolute addresses derived from the
  one instance base below. That base is the same address the resolver uses,
  `Address::SHC_3BB0A8C1_0x01A93208` in `DAT_TileMapState.hpp`, so with the
  struct resolvers enabled these operands are the original's own addresses.
 */

// StructResolver::Instance<OpenSHC::Map::TileMapState,27865608>::instance
#define ASM_TileMapState 0x01A93208

#define ASM_TileMapState_DAT_SomeY (ASM_TileMapState + 0x554A38)
#define ASM_TileMapState_DAT_SomeTile (ASM_TileMapState + 0x554A3C)
#define ASM_TileMapState_ptr_MovementDirectionTranslationMatrix (ASM_TileMapState + 0x554A68)
#define ASM_TileMapState_ptr_PathConnectionLayer (ASM_TileMapState + 0x554A74)
#define ASM_TileMapState_ptr_SpecialAreasArray (ASM_TileMapState + 0x554A7C)

/**
  Fill the four even slots of `specialAreasArray` with the path connection
  values of the four cardinal neighbours of `DAT_SomeTile`, using row
  `DAT_SomeY` of the movement direction translation matrix.

  Both inputs are read back out of the globals, which is what makes this
  unreachable from C++: MSVC forwards the value it just stored and folds the
  repeated address arithmetic, so it emits neither the reloads nor the
  doubling-by-two-adds that the original uses.

  C++ equivalent:

      short* pSpecialAreas = (short*)DAT_TileMapState::instance.ptr_SpecialAreasArray;
      ushort* pConnection = (ushort*)DAT_TileMapState::instance.ptr_PathConnectionLayer
          + DAT_TileMapState::instance.DAT_SomeTile;
      int* pDirection = (int*)((char*)DAT_TileMapState::instance.ptr_MovementDirectionTranslationMatrix
          + DAT_TileMapState::instance.DAT_SomeY * 0x20);
      pSpecialAreas[2] = pConnection[1];
      pSpecialAreas[6] = pConnection[-1];
      pSpecialAreas[0] = pConnection[pDirection[0]];
      pSpecialAreas[4] = pConnection[pDirection[4]];

  Clobbers eax, ebx, ecx, edx, esi, edi.
 */
#define MACRO_ASM_FILL_CARDINAL_PATH_CONNECTIONS()                                                                     \
    __asm                                                                                                              \
    {                                                                                                                  \
        __asm mov edi, dword ptr ds:[ASM_TileMapState_ptr_MovementDirectionTranslationMatrix]                             \
        __asm mov esi, dword ptr ds:[ASM_TileMapState_ptr_PathConnectionLayer]                                            \
        __asm mov edx, dword ptr ds:[ASM_TileMapState_ptr_SpecialAreasArray]                                              \
        __asm mov eax, dword ptr ds:[ASM_TileMapState_DAT_SomeTile]                                                       \
        __asm shl eax, 1                                                                                               \
        __asm add esi, eax                                                                                             \
        __asm push esi                                                                                                 \
        __asm mov eax, dword ptr ds:[ASM_TileMapState_DAT_SomeY]                                                          \
        __asm shl eax, 5                                                                                               \
        __asm add edi, eax                                                                                             \
        __asm mov bx, word ptr [esi + 2]                                                                               \
        __asm mov ax, word ptr [esi - 2]                                                                               \
        __asm mov word ptr [edx + 4], bx                                                                               \
        __asm mov word ptr [edx + 0xC], ax                                                                             \
        __asm mov ecx, dword ptr [edi]                                                                                 \
        __asm add esi, ecx                                                                                             \
        __asm add esi, ecx                                                                                             \
        __asm mov bx, word ptr [esi]                                                                                   \
        __asm mov ecx, dword ptr [edi + 0x10]                                                                          \
        __asm pop esi                                                                                                  \
        __asm add esi, ecx                                                                                             \
        __asm add esi, ecx                                                                                             \
        __asm mov ax, word ptr [esi]                                                                                   \
        __asm mov word ptr [edx], bx                                                                                   \
        __asm mov word ptr [edx + 8], ax                                                                               \
    }
