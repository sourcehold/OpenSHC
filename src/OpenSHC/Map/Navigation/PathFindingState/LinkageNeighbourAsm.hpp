/**
  HAND WRITTEN - not generated.

  path: 'OpenSHC/Map/Navigation/PathFindingState/LinkageNeighbourAsm.hpp'

  The inner loop of the PathLinkageLayer searches - pushing the eight neighbours of the tile just
  taken off the queue - is handwritten assembly in the original, and it is a MACRO: the identical
  instruction stream appears verbatim inside findLinkageBasedPathOrWalkRadius (0x00497740),
  findSuitableSpawnLocationUnk (0x00497B80) and updateSeparateAreaTileMap (0x004995E0), never as a
  call. It is recognisable by

    - "mov eax, 0" followed by "mov ax, word ptr [..]", a zero extension no compiler writes that way
      (MSVC emits movzx),
    - the search generation and the distance kept in 16-bit registers and compared with "cmp ax, cx"
      rather than widened to int,
    - every layer base reloaded from its own stack slot before each use instead of being held in a
      register across the block.

  Do NOT add "#pragma optimize("", off)" to the enclosing functions. orig_asm.py --stats reports a
  frame pointer for all three, but that is caused by the inline assembly itself - MSVC keeps ebp in
  any function containing an __asm block - not by a missing /O2. Their prologues are plainly
  optimised (the bounds check runs out of registers, "this" stays in esi), and forcing /Od costs
  about half of the match.

  PathLinkageLayer bits: 0x01 north, 0x02 north-east, 0x04 east, 0x08 south-east,
                         0x10 south, 0x20 south-west, 0x40 west, 0x80 north-west.

  Cardinal neighbours are entered at distance + 1 and diagonal ones at distance + 2; the north and
  south rows are reached by adding directionTranslationMatrix[y][0] and [y][4] to the tile.

  The macro expects these locals in the enclosing function, by these names:

    short* _walkLayer, _certainPath   the two adjacent short layers
    int*   _tilesQueue                this->searchQueue.tilesQueue
    short* _yQueue                    this->searchQueue.yQueue
    int*   _dirMatrix                 directionTranslationMatrix, as a flat int array
    int    _tile, _cY, _cLink
    short  _curGen, _cCardinalDistance

  and takes the queue end as the WRITEIDX macro argument, which it advances. It clobbers eax, ebx, ecx, edx, esi and edi.

  ID must be unique within the enclosing function; it exists only to keep the assembler labels of two
  expansions apart.

  The original reaches the layers through the global instance's absolute address; we load them from
  locals because MSVC inline assembly cannot name DAT_TileMapState::instance ("::" is not parseable
  in an asm operand). That costs the initial "mov esi, _<layer>" instructions and nothing else - the
  original reloads from a stack slot at exactly those points anyway.
*/

#pragma once

#include "OpenSHC/Map/TileMapState.hpp"

// clang-format off

// One neighbour: OFF is the byte offset on the short layers (-2, 0 or +2), BIT the linkage bit,
// DIST the distance instruction (none for a cardinal step, "add ax, 1" for a diagonal one),
// TILE the tile-delta instruction and YADJ the row-delta instruction.
#define MACRO_LINKAGE_PUSH(ID, N, WRITEIDX, OFF, BIT, DIST, TILE, YADJ)                         \
    __asm mov ax, word ptr [edi + edx*2 + OFF]                                        \
    __asm cmp ax, word ptr _curGen                                                    \
    __asm je push_done_##ID##_##N                                                     \
    __asm test bl, BIT                                                                \
    __asm je push_done_##ID##_##N                                                     \
    __asm mov esi, _certainPath                                                       \
    __asm mov ax, word ptr _cCardinalDistance                                         \
    DIST                                                                              \
    __asm mov cx, word ptr _curGen                                                    \
    __asm mov word ptr [esi + edx*2 + OFF], ax                                        \
    __asm mov word ptr [edi + edx*2 + OFF], cx                                        \
    __asm mov ecx, WRITEIDX                                                        \
    __asm mov esi, _tilesQueue                                                        \
    __asm mov eax, edx                                                                \
    TILE                                                                              \
    __asm mov dword ptr [esi + ecx*4], eax                                            \
    __asm mov eax, _cY                                                                \
    YADJ                                                                              \
    __asm mov esi, _yQueue                                                            \
    __asm mov word ptr [esi + ecx*2], ax                                              \
    __asm add WRITEIDX, 1                                                          \
    __asm push_done_##ID##_##N:

#define MACRO_ASM_SAME
#define MACRO_ASM_INC __asm add eax, 1
#define MACRO_ASM_DEC __asm sub eax, 1
#define MACRO_ASM_DIAGONAL __asm add ax, 1

// The whole eight-neighbour expansion, in the original's order: west, east, then the north row
// (north, north-west, north-east) and the south row (south, south-west, south-east).
#define MACRO_LINKAGE_EXPAND_NEIGHBOURS(ID, WRITEIDX)                                           \
    __asm mov edx, _tile                                                              \
    __asm mov edi, _walkLayer                                                         \
    __asm mov ebx, _cLink                                                             \
    MACRO_LINKAGE_PUSH(ID, w, WRITEIDX, -2, 0x40, MACRO_ASM_SAME, MACRO_ASM_DEC, MACRO_ASM_SAME) \
    MACRO_LINKAGE_PUSH(ID, e, WRITEIDX, +2, 0x04, MACRO_ASM_SAME, MACRO_ASM_INC, MACRO_ASM_SAME) \
    __asm mov eax, _cY                                                                \
    __asm shl eax, 3                                                                  \
    __asm mov esi, _dirMatrix                                                         \
    __asm add edx, dword ptr [esi + eax*4]                                            \
    MACRO_LINKAGE_PUSH(ID, n, WRITEIDX, 0, 0x01, MACRO_ASM_SAME, MACRO_ASM_SAME, MACRO_ASM_DEC) \
    MACRO_LINKAGE_PUSH(ID, nw, WRITEIDX, -2, 0x80, MACRO_ASM_DIAGONAL, MACRO_ASM_DEC, MACRO_ASM_DEC) \
    MACRO_LINKAGE_PUSH(ID, ne, WRITEIDX, +2, 0x02, MACRO_ASM_DIAGONAL, MACRO_ASM_INC, MACRO_ASM_DEC) \
    __asm mov edx, _tile                                                              \
    __asm mov eax, _cY                                                                \
    __asm shl eax, 3                                                                  \
    __asm add eax, 4                                                                  \
    __asm mov esi, _dirMatrix                                                         \
    __asm add edx, dword ptr [esi + eax*4]                                            \
    MACRO_LINKAGE_PUSH(ID, s, WRITEIDX, 0, 0x10, MACRO_ASM_SAME, MACRO_ASM_SAME, MACRO_ASM_INC) \
    MACRO_LINKAGE_PUSH(ID, sw, WRITEIDX, -2, 0x20, MACRO_ASM_DIAGONAL, MACRO_ASM_DEC, MACRO_ASM_INC) \
    MACRO_LINKAGE_PUSH(ID, se, WRITEIDX, +2, 0x08, MACRO_ASM_DIAGONAL, MACRO_ASM_INC, MACRO_ASM_INC)

// The same neighbour, but only entered when OccupancyLayer says the tile is free. TOFF is the
// neighbour's offset in tiles (the occupancy layer holds one byte per tile, so it is not scaled
// like OFF is on the short layers). Needs one more local, "uchar* _occupancy".
#define MACRO_LINKAGE_PUSH_FREE(ID, N, WRITEIDX, OFF, TOFF, BIT, DIST, TILE, YADJ)    \
    __asm mov ax, word ptr [edi + edx*2 + OFF]                                        \
    __asm cmp ax, word ptr _curGen                                                    \
    __asm je push_done_##ID##_##N                                                     \
    __asm test bl, BIT                                                                \
    __asm je push_done_##ID##_##N                                                     \
    __asm mov esi, _occupancy                                                         \
    __asm mov cl, byte ptr [esi + edx + TOFF]                                         \
    __asm cmp cl, 0                                                                   \
    __asm jne push_done_##ID##_##N                                                    \
    __asm mov esi, _certainPath                                                       \
    __asm mov ax, word ptr _cCardinalDistance                                         \
    DIST                                                                              \
    __asm mov cx, word ptr _curGen                                                    \
    __asm mov word ptr [esi + edx*2 + OFF], ax                                        \
    __asm mov word ptr [edi + edx*2 + OFF], cx                                        \
    __asm mov ecx, WRITEIDX                                                           \
    __asm mov esi, _tilesQueue                                                        \
    __asm mov eax, edx                                                                \
    TILE                                                                              \
    __asm mov dword ptr [esi + ecx*4], eax                                            \
    __asm mov eax, _cY                                                                \
    YADJ                                                                              \
    __asm mov esi, _yQueue                                                            \
    __asm mov word ptr [esi + ecx*2], ax                                              \
    __asm add WRITEIDX, 1                                                             \
    __asm push_done_##ID##_##N:

#define MACRO_LINKAGE_EXPAND_FREE_NEIGHBOURS(ID, WRITEIDX)                            \
    __asm mov edx, _tile                                                              \
    __asm mov edi, _walkLayer                                                         \
    __asm mov ebx, _cLink                                                             \
    MACRO_LINKAGE_PUSH_FREE(ID, w, WRITEIDX, -2, -1, 0x40, MACRO_ASM_SAME, MACRO_ASM_DEC, MACRO_ASM_SAME) \
    MACRO_LINKAGE_PUSH_FREE(ID, e, WRITEIDX, +2, +1, 0x04, MACRO_ASM_SAME, MACRO_ASM_INC, MACRO_ASM_SAME) \
    __asm mov eax, _cY                                                                \
    __asm shl eax, 3                                                                  \
    __asm mov esi, _dirMatrix                                                         \
    __asm add edx, dword ptr [esi + eax*4]                                            \
    MACRO_LINKAGE_PUSH_FREE(ID, n, WRITEIDX, 0, 0, 0x01, MACRO_ASM_SAME, MACRO_ASM_SAME, MACRO_ASM_DEC) \
    MACRO_LINKAGE_PUSH_FREE(ID, nw, WRITEIDX, -2, -1, 0x80, MACRO_ASM_DIAGONAL, MACRO_ASM_DEC, MACRO_ASM_DEC) \
    MACRO_LINKAGE_PUSH_FREE(ID, ne, WRITEIDX, +2, +1, 0x02, MACRO_ASM_DIAGONAL, MACRO_ASM_INC, MACRO_ASM_DEC) \
    __asm mov edx, _tile                                                              \
    __asm mov eax, _cY                                                                \
    __asm shl eax, 3                                                                  \
    __asm add eax, 4                                                                  \
    __asm mov esi, _dirMatrix                                                         \
    __asm add edx, dword ptr [esi + eax*4]                                            \
    MACRO_LINKAGE_PUSH_FREE(ID, s, WRITEIDX, 0, 0, 0x10, MACRO_ASM_SAME, MACRO_ASM_SAME, MACRO_ASM_INC) \
    MACRO_LINKAGE_PUSH_FREE(ID, sw, WRITEIDX, -2, -1, 0x20, MACRO_ASM_DIAGONAL, MACRO_ASM_DEC, MACRO_ASM_INC) \
    MACRO_LINKAGE_PUSH_FREE(ID, se, WRITEIDX, +2, +1, 0x08, MACRO_ASM_DIAGONAL, MACRO_ASM_INC, MACRO_ASM_INC)

// clang-format on
