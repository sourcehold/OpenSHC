/**
  HAND WRITTEN - not generated.

  path: 'OpenSHC/Map/TileMapState/GfxNeighbourMaskAsm.hpp'

  The eight-neighbour mask gather inside updateGfxLayer (0x00509180) is handwritten assembly in the
  original, and it is a MACRO: the identical instruction stream appears 19 times verbatim inside the
  one function, never as a call. Each expansion walks the eight neighbours of the current tile on one
  layer, tests one mask bit on each, and ORs a direction bit into an accumulator kept in dl.

  It is recognisable by

    - "mov edx, 0" to clear the accumulator, which no compiler writes that way (MSVC emits
      "xor edx, edx"),
    - the mask test done as "and eax, MASK" / "je" / "or edx, BIT" - a branch over a three-byte or,
      where a compiler would use setcc or cmov and would not destroy the loaded value,
    - the row stride added one instruction at a time ("add esi, ecx" four times for a four-byte
      layer) instead of "lea esi, [esi + ecx*4]",
    - a dword load at every neighbour regardless of the layer's element size, so a two-byte layer is
      read with "mov eax, dword ptr [esi + 2]",
    - the row centre parked on the stack with push/pop across the north row rather than in a
      register.

  updateGfxLayer DOES keep "#pragma optimize("", off)". That is unlike the PathFindingState asm
  macros (see Map/Navigation/PathFindingState/LinkageNeighbourAsm.hpp), where forcing /Od costs about
  half the match: here removing it measured 16.1% -> 2.1%, so the enclosing function really is built
  without optimisation and the frame pointer orig_asm.py reports is not just the __asm block.

  Direction bits are the same in all 19 expansions; only the layer, its element size and the tested
  mask change:

      middle row   [esi - OFF] 0x02   [esi + OFF] 0x20
      north row    [esi - OFF] 0x01   [esi + OFF] 0x40   [esi] 0x80
      south row    [esi - OFF] 0x04   [esi + OFF] 0x10   [esi] 0x08

  The north row is reached by adding directionTranslationMatrix[y][0] to the tile and the south row
  by adding [y][4], which is why the row delta is read from [edi] and [edi + 0x10] after edi has been
  advanced by y * 0x20 (eight ints per row).

  The macro expects these locals in the enclosing function, by these names:

    char* _gfxLayer      the layer being tested, as a flat char array
    char* _gfxDirMatrix  directionTranslationMatrix, as a flat char array
    int   _gfxTile       the current tile
    int   _gfxY          the current row

  and takes the accumulator as the DEST macro argument.
    uchar _gfxMask       the accumulator the expansion writes

  It clobbers eax, ebx, ecx, edx, esi and edi.

  ID must be unique within the enclosing function; it exists only to keep the assembler labels of two
  expansions apart.

  We reach the layers through locals because MSVC inline assembly cannot name
  StructResolver::Instance<...>::instance ("::" is not parseable in an asm operand); the original
  loads them from the global instance's absolute address at exactly these points, so this costs the
  initial "mov esi, _gfxLayer" instructions and nothing else.
*/

#pragma once

#include "OpenSHC/Map/TileMapState.hpp"

// clang-format off

// The tile-to-byte scaling of one layer: the original shifts the tile index by the element size
// rather than multiplying, and emits nothing at all for a one-byte layer.
#define MACRO_GFX_SHIFT_1
#define MACRO_GFX_SHIFT_2 __asm shl eax, 1
#define MACRO_GFX_SHIFT_4 __asm shl eax, 2

// One row step, added one instruction at a time, once per byte of the element.
#define MACRO_GFX_ROWSTEP_1 __asm add esi, ecx
#define MACRO_GFX_ROWSTEP_2 __asm add esi, ecx __asm add esi, ecx
#define MACRO_GFX_ROWSTEP_4 __asm add esi, ecx __asm add esi, ecx __asm add esi, ecx __asm add esi, ecx

// One neighbour: REG holds the loaded dword, BIT the direction bit to OR in on a hit.
#define MACRO_GFX_TEST(ID, N, REG, MASK, BIT)                                                   \
    __asm and REG, MASK                                                                         \
    __asm je gfx_done_##ID##_##N                                                                \
    __asm or edx, BIT                                                                           \
    __asm gfx_done_##ID##_##N:

// The whole eight-neighbour gather, in the original's order: the middle row (east then west), the
// north row (north-west, north-east, north) and the south row (south-west, south-east, south).
// OFF is the element size in bytes, SHIFT and ROWSTEP its MACRO_GFX_SHIFT_n / MACRO_GFX_ROWSTEP_n,
// and DEST the accumulator the expansion stores dl into - an asm-nameable local, so that the store
// is the original's single instruction and not a store plus a copy.
#define MACRO_GFX_NEIGHBOUR_MASK(ID, OFF, SHIFT, ROWSTEP, MASK, DEST)                                 \
    __asm mov edi, _gfxDirMatrix                                                                \
    __asm mov esi, _gfxLayer                                                                    \
    __asm mov eax, _gfxTile                                                                     \
    SHIFT                                                                                       \
    __asm add esi, eax                                                                          \
    __asm push esi                                                                              \
    __asm mov eax, _gfxY                                                                        \
    __asm shl eax, 5                                                                            \
    __asm add edi, eax                                                                          \
    __asm mov edx, 0                                                                            \
    __asm mov eax, dword ptr [esi + OFF]                                                        \
    __asm mov ebx, dword ptr [esi - OFF]                                                        \
    MACRO_GFX_TEST(ID, e, eax, MASK, 0x20)                                                      \
    MACRO_GFX_TEST(ID, w, ebx, MASK, 2)                                                         \
    __asm mov ecx, dword ptr [edi]                                                              \
    ROWSTEP                                                                                     \
    __asm mov eax, dword ptr [esi - OFF]                                                        \
    __asm mov ebx, dword ptr [esi + OFF]                                                        \
    __asm mov ecx, dword ptr [esi]                                                              \
    MACRO_GFX_TEST(ID, nw, eax, MASK, 1)                                                        \
    MACRO_GFX_TEST(ID, ne, ebx, MASK, 0x40)                                                     \
    MACRO_GFX_TEST(ID, n, ecx, MASK, 0x80)                                                      \
    __asm mov ecx, dword ptr [edi + 0x10]                                                       \
    __asm pop esi                                                                               \
    ROWSTEP                                                                                     \
    __asm mov eax, dword ptr [esi - OFF]                                                        \
    __asm mov ebx, dword ptr [esi + OFF]                                                        \
    __asm mov ecx, dword ptr [esi]                                                              \
    MACRO_GFX_TEST(ID, sw, eax, MASK, 4)                                                        \
    MACRO_GFX_TEST(ID, se, ebx, MASK, 0x10)                                                     \
    MACRO_GFX_TEST(ID, s, ecx, MASK, 8)                                                         \
    __asm mov byte ptr DEST, dl

// clang-format on
