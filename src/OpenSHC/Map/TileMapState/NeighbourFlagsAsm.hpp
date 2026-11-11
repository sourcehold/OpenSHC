/**
  HAND WRITTEN - not generated.

  path: 'OpenSHC/Map/TileMapState/NeighbourFlagsAsm.hpp'

  The original gathers the neighbours of DAT_SomeTile into bitFlag with handwritten assembly, and that
  assembly is a MACRO: the identical instruction stream appears verbatim inside
  setBitFlagBasedOnWallTowerGatehouseOrKeep (0x004FF870, once), updateGFXLayers (0x004FC9E0, eleven
  times), updateMacroLayerRelated (0x004FDB00, eleven times) and updateGfxLayer (0x00509180, nineteen
  times) - never as a call. It is recognisable by "mov edx, 0" (no compiler materialises zero that
  way), by advancing the row pointer with repeated "add esi, ecx" instead of one scaled lea, and, in
  the TERRAIN variants, by loading a dword at a one-byte offset and masking it down to the low byte.

  Five shapes occur, selected by which layer pointer is read and how many neighbours are gathered:

    LOGIC   - ptr_LogicLayer,         4-byte elements: "shl eax, 2", "add esi, ecx" x4, [esi +/- 4]
    MISC    - ptr_MiscDisplayLayer,   2-byte elements: "shl eax, 1", "add esi, ecx" x2, [esi +/- 2]
    TERRAIN - ptr_TerrainTypeTileMap, 1-byte elements: no shift,     "add esi, ecx" x1, [esi +/- 1]
    _4      - east, west, north and south only
    _8      - also north-west, north-east, south-west and south-east

  bitFlag bits: 0x02 west, 0x20 east, 0x80 north, 0x08 south,
                0x01 north-west, 0x40 north-east, 0x04 south-west, 0x10 south-east.

  Every expansion clobbers eax, ebx, ecx, edx, esi and edi and leaves the result in this->bitFlag.

  ID must be unique within the enclosing function; it exists only to keep the asm labels of two
  expansions apart. MASK must be a numeric literal or a preprocessor constant: MASM has no "|"
  operator, so an enum OR expression cannot be used as an asm operand.

  The original reaches the fields through the global instance's absolute address; we go through "this"
  because MSVC inline asm cannot name DAT_TileMapState::instance ("::" is not parseable in an asm
  operand). That costs the "mov eax, this" instructions and nothing else.
*/

#pragma once

#include "OpenSHC/Map/TileMapState.hpp"

// A "jz" over the "or edx, imm" that follows it (SKIP = 3 for an imm8, 6 for an imm32), in the 6-byte near
// encoding 0F 84 rel32 that the original's assembler produced. MSVC's inline assembler only emits the 2-byte short
// form for a jump to a nearby label, even when written "jz near ptr label", so the bytes are emitted directly.
#ifndef MACRO_ASM_JZ_NEAR
#define MACRO_ASM_JZ_NEAR(SKIP)                                                                                        \
    __asm _emit 0x0F __asm _emit 0x84 __asm _emit SKIP __asm _emit 0 __asm _emit 0 __asm _emit 0
#endif

// clang-format off

#define MACRO_NEIGHBOUR_FLAGS_LOGIC_4(ID, MASK)                                       \
    __asm mov eax, this                                                               \
    __asm mov edi, dword ptr [eax]TileMapState.ptr_MovementDirectionTranslationMatrix \
    __asm mov esi, dword ptr [eax]TileMapState.ptr_LogicLayer                         \
    __asm mov eax, dword ptr [eax]TileMapState.DAT_SomeTile                           \
    __asm shl eax, 0x2                                                                \
    __asm add esi, eax                                                                \
    __asm push esi                                                                    \
    __asm mov eax, this                                                               \
    __asm mov eax, dword ptr [eax]TileMapState.DAT_SomeY                              \
    __asm shl eax, 0x5                                                                \
    __asm add edi, eax                                                                \
    __asm mov edx, 0x0                                                                \
    __asm mov eax, dword ptr [esi + 0x4]                                              \
    __asm mov ebx, dword ptr [esi - 0x4]                                              \
    __asm and eax, MASK                                                               \
    MACRO_ASM_JZ_NEAR(3)                                                              \
    __asm or edx, 0x20                                                                \
    __asm east_done_##ID:                                                             \
    __asm and ebx, MASK                                                               \
    MACRO_ASM_JZ_NEAR(3)                                                              \
    __asm or edx, 0x2                                                                 \
    __asm west_done_##ID:                                                             \
    __asm mov ecx, dword ptr [edi]                                                    \
    __asm add esi, ecx                                                                \
    __asm add esi, ecx                                                                \
    __asm add esi, ecx                                                                \
    __asm add esi, ecx                                                                \
    __asm mov eax, dword ptr [esi]                                                    \
    __asm and eax, MASK                                                               \
    MACRO_ASM_JZ_NEAR(6)                                                              \
    __asm or edx, 0x80                                                                \
    __asm north_done_##ID:                                                            \
    __asm mov ecx, dword ptr [edi + 0x10]                                             \
    __asm pop esi                                                                     \
    __asm add esi, ecx                                                                \
    __asm add esi, ecx                                                                \
    __asm add esi, ecx                                                                \
    __asm add esi, ecx                                                                \
    __asm mov eax, dword ptr [esi]                                                    \
    __asm and eax, MASK                                                               \
    MACRO_ASM_JZ_NEAR(3)                                                              \
    __asm or edx, 0x8                                                                 \
    __asm south_done_##ID:                                                            \
    __asm mov eax, this                                                               \
    __asm mov byte ptr [eax]TileMapState.bitFlag, dl

#define MACRO_NEIGHBOUR_FLAGS_LOGIC_8(ID, MASK)                                       \
    __asm mov eax, this                                                               \
    __asm mov edi, dword ptr [eax]TileMapState.ptr_MovementDirectionTranslationMatrix \
    __asm mov esi, dword ptr [eax]TileMapState.ptr_LogicLayer                         \
    __asm mov eax, dword ptr [eax]TileMapState.DAT_SomeTile                           \
    __asm shl eax, 0x2                                                                \
    __asm add esi, eax                                                                \
    __asm push esi                                                                    \
    __asm mov eax, this                                                               \
    __asm mov eax, dword ptr [eax]TileMapState.DAT_SomeY                              \
    __asm shl eax, 0x5                                                                \
    __asm add edi, eax                                                                \
    __asm mov edx, 0x0                                                                \
    __asm mov eax, dword ptr [esi + 0x4]                                              \
    __asm mov ebx, dword ptr [esi - 0x4]                                              \
    __asm and eax, MASK                                                               \
    MACRO_ASM_JZ_NEAR(3)                                                              \
    __asm or edx, 0x20                                                                \
    __asm east_done_##ID:                                                             \
    __asm and ebx, MASK                                                               \
    MACRO_ASM_JZ_NEAR(3)                                                              \
    __asm or edx, 0x2                                                                 \
    __asm west_done_##ID:                                                             \
    __asm mov ecx, dword ptr [edi]                                                    \
    __asm add esi, ecx                                                                \
    __asm add esi, ecx                                                                \
    __asm add esi, ecx                                                                \
    __asm add esi, ecx                                                                \
    __asm mov eax, dword ptr [esi - 0x4]                                              \
    __asm mov ebx, dword ptr [esi + 0x4]                                              \
    __asm mov ecx, dword ptr [esi]                                                    \
    __asm and eax, MASK                                                               \
    MACRO_ASM_JZ_NEAR(3)                                                              \
    __asm or edx, 0x1                                                                 \
    __asm north_west_done_##ID:                                                       \
    __asm and ebx, MASK                                                               \
    MACRO_ASM_JZ_NEAR(3)                                                              \
    __asm or edx, 0x40                                                                \
    __asm north_east_done_##ID:                                                       \
    __asm and ecx, MASK                                                               \
    MACRO_ASM_JZ_NEAR(6)                                                              \
    __asm or edx, 0x80                                                                \
    __asm north_done_##ID:                                                            \
    __asm mov ecx, dword ptr [edi + 0x10]                                             \
    __asm pop esi                                                                     \
    __asm add esi, ecx                                                                \
    __asm add esi, ecx                                                                \
    __asm add esi, ecx                                                                \
    __asm add esi, ecx                                                                \
    __asm mov eax, dword ptr [esi - 0x4]                                              \
    __asm mov ebx, dword ptr [esi + 0x4]                                              \
    __asm mov ecx, dword ptr [esi]                                                    \
    __asm and eax, MASK                                                               \
    MACRO_ASM_JZ_NEAR(3)                                                              \
    __asm or edx, 0x4                                                                 \
    __asm south_west_done_##ID:                                                       \
    __asm and ebx, MASK                                                               \
    MACRO_ASM_JZ_NEAR(3)                                                              \
    __asm or edx, 0x10                                                                \
    __asm south_east_done_##ID:                                                       \
    __asm and ecx, MASK                                                               \
    MACRO_ASM_JZ_NEAR(3)                                                              \
    __asm or edx, 0x8                                                                 \
    __asm south_done_##ID:                                                            \
    __asm mov eax, this                                                               \
    __asm mov byte ptr [eax]TileMapState.bitFlag, dl

#define MACRO_NEIGHBOUR_FLAGS_MISC_8(ID, MASK)                                       \
    __asm mov eax, this                                                               \
    __asm mov edi, dword ptr [eax]TileMapState.ptr_MovementDirectionTranslationMatrix \
    __asm mov esi, dword ptr [eax]TileMapState.ptr_MiscDisplayLayer                         \
    __asm mov eax, dword ptr [eax]TileMapState.DAT_SomeTile                           \
    __asm shl eax, 0x1                                                                \
    __asm add esi, eax                                                                \
    __asm push esi                                                                    \
    __asm mov eax, this                                                               \
    __asm mov eax, dword ptr [eax]TileMapState.DAT_SomeY                              \
    __asm shl eax, 0x5                                                                \
    __asm add edi, eax                                                                \
    __asm mov edx, 0x0                                                                \
    __asm mov eax, dword ptr [esi + 0x2]                                              \
    __asm mov ebx, dword ptr [esi - 0x2]                                              \
    __asm and eax, MASK                                                               \
    MACRO_ASM_JZ_NEAR(3)                                                              \
    __asm or edx, 0x20                                                                \
    __asm east_done_##ID:                                                             \
    __asm and ebx, MASK                                                               \
    MACRO_ASM_JZ_NEAR(3)                                                              \
    __asm or edx, 0x2                                                                 \
    __asm west_done_##ID:                                                             \
    __asm mov ecx, dword ptr [edi]                                                    \
    __asm add esi, ecx                                                                \
    __asm add esi, ecx                                                                \
    __asm mov eax, dword ptr [esi - 0x2]                                              \
    __asm mov ebx, dword ptr [esi + 0x2]                                              \
    __asm mov ecx, dword ptr [esi]                                                    \
    __asm and eax, MASK                                                               \
    MACRO_ASM_JZ_NEAR(3)                                                              \
    __asm or edx, 0x1                                                                 \
    __asm north_west_done_##ID:                                                       \
    __asm and ebx, MASK                                                               \
    MACRO_ASM_JZ_NEAR(3)                                                              \
    __asm or edx, 0x40                                                                \
    __asm north_east_done_##ID:                                                       \
    __asm and ecx, MASK                                                               \
    MACRO_ASM_JZ_NEAR(6)                                                              \
    __asm or edx, 0x80                                                                \
    __asm north_done_##ID:                                                            \
    __asm mov ecx, dword ptr [edi + 0x10]                                             \
    __asm pop esi                                                                     \
    __asm add esi, ecx                                                                \
    __asm add esi, ecx                                                                \
    __asm mov eax, dword ptr [esi - 0x2]                                              \
    __asm mov ebx, dword ptr [esi + 0x2]                                              \
    __asm mov ecx, dword ptr [esi]                                                    \
    __asm and eax, MASK                                                               \
    MACRO_ASM_JZ_NEAR(3)                                                              \
    __asm or edx, 0x4                                                                 \
    __asm south_west_done_##ID:                                                       \
    __asm and ebx, MASK                                                               \
    MACRO_ASM_JZ_NEAR(3)                                                              \
    __asm or edx, 0x10                                                                \
    __asm south_east_done_##ID:                                                       \
    __asm and ecx, MASK                                                               \
    MACRO_ASM_JZ_NEAR(3)                                                              \
    __asm or edx, 0x8                                                                 \
    __asm south_done_##ID:                                                            \
    __asm mov eax, this                                                               \
    __asm mov byte ptr [eax]TileMapState.bitFlag, dl

#define MACRO_NEIGHBOUR_FLAGS_TERRAIN_4(ID, MASK)                                     \
    __asm mov eax, this                                                               \
    __asm mov edi, dword ptr [eax]TileMapState.ptr_MovementDirectionTranslationMatrix \
    __asm mov esi, dword ptr [eax]TileMapState.ptr_TerrainTypeTileMap                 \
    __asm mov eax, dword ptr [eax]TileMapState.DAT_SomeTile                           \
    __asm add esi, eax                                                                \
    __asm push esi                                                                    \
    __asm mov eax, this                                                               \
    __asm mov eax, dword ptr [eax]TileMapState.DAT_SomeY                              \
    __asm shl eax, 0x5                                                                \
    __asm add edi, eax                                                                \
    __asm mov edx, 0x0                                                                \
    __asm mov eax, dword ptr [esi + 0x1]                                              \
    __asm mov ebx, dword ptr [esi - 0x1]                                              \
    __asm and eax, MASK                                                               \
    MACRO_ASM_JZ_NEAR(3)                                                              \
    __asm or edx, 0x20                                                                \
    __asm east_done_##ID:                                                             \
    __asm and ebx, MASK                                                               \
    MACRO_ASM_JZ_NEAR(3)                                                              \
    __asm or edx, 0x2                                                                 \
    __asm west_done_##ID:                                                             \
    __asm mov ecx, dword ptr [edi]                                                    \
    __asm add esi, ecx                                                                \
    __asm mov eax, dword ptr [esi]                                                    \
    __asm and eax, MASK                                                               \
    MACRO_ASM_JZ_NEAR(6)                                                              \
    __asm or edx, 0x80                                                                \
    __asm north_done_##ID:                                                            \
    __asm mov ecx, dword ptr [edi + 0x10]                                             \
    __asm pop esi                                                                     \
    __asm add esi, ecx                                                                \
    __asm mov eax, dword ptr [esi]                                                    \
    __asm and eax, MASK                                                               \
    MACRO_ASM_JZ_NEAR(3)                                                              \
    __asm or edx, 0x8                                                                 \
    __asm south_done_##ID:                                                            \
    __asm mov eax, this                                                               \
    __asm mov byte ptr [eax]TileMapState.bitFlag, dl

#define MACRO_NEIGHBOUR_FLAGS_TERRAIN_8(ID, MASK)                                     \
    __asm mov eax, this                                                               \
    __asm mov edi, dword ptr [eax]TileMapState.ptr_MovementDirectionTranslationMatrix \
    __asm mov esi, dword ptr [eax]TileMapState.ptr_TerrainTypeTileMap                 \
    __asm mov eax, dword ptr [eax]TileMapState.DAT_SomeTile                           \
    __asm add esi, eax                                                                \
    __asm push esi                                                                    \
    __asm mov eax, this                                                               \
    __asm mov eax, dword ptr [eax]TileMapState.DAT_SomeY                              \
    __asm shl eax, 0x5                                                                \
    __asm add edi, eax                                                                \
    __asm mov edx, 0x0                                                                \
    __asm mov eax, dword ptr [esi + 0x1]                                              \
    __asm mov ebx, dword ptr [esi - 0x1]                                              \
    __asm and eax, MASK                                                               \
    MACRO_ASM_JZ_NEAR(3)                                                              \
    __asm or edx, 0x20                                                                \
    __asm east_done_##ID:                                                             \
    __asm and ebx, MASK                                                               \
    MACRO_ASM_JZ_NEAR(3)                                                              \
    __asm or edx, 0x2                                                                 \
    __asm west_done_##ID:                                                             \
    __asm mov ecx, dword ptr [edi]                                                    \
    __asm add esi, ecx                                                                \
    __asm mov eax, dword ptr [esi - 0x1]                                              \
    __asm mov ebx, dword ptr [esi + 0x1]                                              \
    __asm mov ecx, dword ptr [esi]                                                    \
    __asm and eax, MASK                                                               \
    MACRO_ASM_JZ_NEAR(3)                                                              \
    __asm or edx, 0x1                                                                 \
    __asm north_west_done_##ID:                                                       \
    __asm and ebx, MASK                                                               \
    MACRO_ASM_JZ_NEAR(3)                                                              \
    __asm or edx, 0x40                                                                \
    __asm north_east_done_##ID:                                                       \
    __asm and ecx, MASK                                                               \
    MACRO_ASM_JZ_NEAR(6)                                                              \
    __asm or edx, 0x80                                                                \
    __asm north_done_##ID:                                                            \
    __asm mov ecx, dword ptr [edi + 0x10]                                             \
    __asm pop esi                                                                     \
    __asm add esi, ecx                                                                \
    __asm mov eax, dword ptr [esi - 0x1]                                              \
    __asm mov ebx, dword ptr [esi + 0x1]                                              \
    __asm mov ecx, dword ptr [esi]                                                    \
    __asm and eax, MASK                                                               \
    MACRO_ASM_JZ_NEAR(3)                                                              \
    __asm or edx, 0x4                                                                 \
    __asm south_west_done_##ID:                                                       \
    __asm and ebx, MASK                                                               \
    MACRO_ASM_JZ_NEAR(3)                                                              \
    __asm or edx, 0x10                                                                \
    __asm south_east_done_##ID:                                                       \
    __asm and ecx, MASK                                                               \
    MACRO_ASM_JZ_NEAR(3)                                                              \
    __asm or edx, 0x8                                                                 \
    __asm south_done_##ID:                                                            \
    __asm mov eax, this                                                               \
    __asm mov byte ptr [eax]TileMapState.bitFlag, dl

/*
  A second handwritten macro: mark DAT_SomeTile and its eight neighbours as changed (2) in the
  changed layer. It appears verbatim in createPlateau (0x00501F50), useLevelBrush (0x00502110) and
  useTerrainHeightBrush (0x00502680), each time right after DAT_SomeTile and DAT_SomeY are stored.
  Same tells as above: a bare push/pop of esi around the north row, and the fields read through the
  global instance's absolute address.

  Clobbers eax, ecx, edx and esi. "this" is loaded once into ecx (which the original does not need)
  so that no named operand is resolved while the pushed esi is on the stack.
*/
#define MACRO_MARK_CHANGED_NEIGHBOURS()                                               \
    __asm mov ecx, this                                                               \
    __asm mov esi, dword ptr [ecx]TileMapState.ptr_ChangedLayer                       \
    __asm mov eax, dword ptr [ecx]TileMapState.DAT_SomeTile                           \
    __asm add esi, eax                                                                \
    __asm push esi                                                                    \
    __asm mov edx, dword ptr [ecx]TileMapState.ptr_MovementDirectionTranslationMatrix \
    __asm mov eax, dword ptr [ecx]TileMapState.DAT_SomeY                              \
    __asm shl eax, 0x5                                                                \
    __asm add edx, eax                                                                \
    __asm mov byte ptr [esi + 0x1], 0x2                                               \
    __asm mov byte ptr [esi - 0x1], 0x2                                               \
    __asm mov byte ptr [esi], 0x2                                                     \
    __asm mov ecx, dword ptr [edx]                                                    \
    __asm add esi, ecx                                                                \
    __asm mov byte ptr [esi - 0x1], 0x2                                               \
    __asm mov byte ptr [esi + 0x1], 0x2                                               \
    __asm mov byte ptr [esi], 0x2                                                     \
    __asm mov ecx, dword ptr [edx + 0x10]                                             \
    __asm pop esi                                                                     \
    __asm add esi, ecx                                                                \
    __asm mov byte ptr [esi - 0x1], 0x2                                               \
    __asm mov byte ptr [esi + 0x1], 0x2                                               \
    __asm mov byte ptr [esi], 0x2

// clang-format on
