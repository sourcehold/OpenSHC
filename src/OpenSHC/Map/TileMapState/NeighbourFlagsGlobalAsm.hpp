/**
  HAND WRITTEN - not generated.

  path: 'OpenSHC/Map/TileMapState/NeighbourFlagsGlobalAsm.hpp'

  The same handwritten-assembly macros as NeighbourFlagsAsm.hpp (see there for what they compute, the
  five shapes, the bitFlag bits and the ID/MASK rules), but reaching TileMapState's fields through the
  global instance's absolute address, as the original does at every place they occur:

      mov edi, dword ptr [0x1fe7c70]   ; DAT_TileMapState.ptr_MovementDirectionTranslationMatrix
      ...
      mov byte ptr [0x1fe7c48], dl     ; DAT_TileMapState.bitFlag

  NeighbourFlagsAsm.hpp goes through "this" instead, at the cost of a "mov eax, this" per field access.
  It is kept unchanged so the functions measured against it are not disturbed.

  MSVC inline asm accepts the resolver instance as a bracketed operand,
  "[DAT_TileMapState::instance]TileMapState.field", but only after the static member has been odr-used
  from C++ in the same function; otherwise it reports C2143/C2059. Every macro therefore starts with a
  "(void)&DAT_TileMapState::instance;" statement, which emits no code. Use the macros as statements.

  The neighbour macros clobber eax, ebx, ecx, edx, esi and edi and leave the result in
  DAT_TileMapState::instance.bitFlag; MACRO_MARK_CHANGED_NEIGHBOURS_GLOBAL clobbers eax, ecx, edx and esi.
*/

#pragma once

#include "OpenSHC/Map/TileMapState.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

// clang-format off

#define MACRO_NEIGHBOUR_FLAGS_GLOBAL_LOGIC_4(ID, MASK)                                                        \
    (void)&DAT_TileMapState::instance;                                                                        \
    __asm mov edi, dword ptr [DAT_TileMapState::instance]TileMapState.ptr_MovementDirectionTranslationMatrix  \
    __asm mov esi, dword ptr [DAT_TileMapState::instance]TileMapState.ptr_LogicLayer                          \
    __asm mov eax, dword ptr [DAT_TileMapState::instance]TileMapState.DAT_SomeTile                            \
    __asm shl eax, 0x2                                                                                        \
    __asm add esi, eax                                                                                        \
    __asm push esi                                                                                            \
    __asm mov eax, dword ptr [DAT_TileMapState::instance]TileMapState.DAT_SomeY                               \
    __asm shl eax, 0x5                                                                                        \
    __asm add edi, eax                                                                                        \
    __asm mov edx, 0x0                                                                                        \
    __asm mov eax, dword ptr [esi + 0x4]                                                                      \
    __asm mov ebx, dword ptr [esi - 0x4]                                                                      \
    __asm and eax, MASK                                                                                       \
    __asm jz east_done_##ID                                                                                   \
    __asm or edx, 0x20                                                                                        \
    __asm east_done_##ID:                                                                                     \
    __asm and ebx, MASK                                                                                       \
    __asm jz west_done_##ID                                                                                   \
    __asm or edx, 0x2                                                                                         \
    __asm west_done_##ID:                                                                                     \
    __asm mov ecx, dword ptr [edi]                                                                            \
    __asm add esi, ecx                                                                                        \
    __asm add esi, ecx                                                                                        \
    __asm add esi, ecx                                                                                        \
    __asm add esi, ecx                                                                                        \
    __asm mov eax, dword ptr [esi]                                                                            \
    __asm and eax, MASK                                                                                       \
    __asm jz north_done_##ID                                                                                  \
    __asm or edx, 0x80                                                                                        \
    __asm north_done_##ID:                                                                                    \
    __asm mov ecx, dword ptr [edi + 0x10]                                                                     \
    __asm pop esi                                                                                             \
    __asm add esi, ecx                                                                                        \
    __asm add esi, ecx                                                                                        \
    __asm add esi, ecx                                                                                        \
    __asm add esi, ecx                                                                                        \
    __asm mov eax, dword ptr [esi]                                                                            \
    __asm and eax, MASK                                                                                       \
    __asm jz south_done_##ID                                                                                  \
    __asm or edx, 0x8                                                                                         \
    __asm south_done_##ID:                                                                                    \
    __asm mov byte ptr [DAT_TileMapState::instance]TileMapState.bitFlag, dl

#define MACRO_NEIGHBOUR_FLAGS_GLOBAL_LOGIC_8(ID, MASK)                                                        \
    (void)&DAT_TileMapState::instance;                                                                        \
    __asm mov edi, dword ptr [DAT_TileMapState::instance]TileMapState.ptr_MovementDirectionTranslationMatrix  \
    __asm mov esi, dword ptr [DAT_TileMapState::instance]TileMapState.ptr_LogicLayer                          \
    __asm mov eax, dword ptr [DAT_TileMapState::instance]TileMapState.DAT_SomeTile                            \
    __asm shl eax, 0x2                                                                                        \
    __asm add esi, eax                                                                                        \
    __asm push esi                                                                                            \
    __asm mov eax, dword ptr [DAT_TileMapState::instance]TileMapState.DAT_SomeY                               \
    __asm shl eax, 0x5                                                                                        \
    __asm add edi, eax                                                                                        \
    __asm mov edx, 0x0                                                                                        \
    __asm mov eax, dword ptr [esi + 0x4]                                                                      \
    __asm mov ebx, dword ptr [esi - 0x4]                                                                      \
    __asm and eax, MASK                                                                                       \
    __asm jz east_done_##ID                                                                                   \
    __asm or edx, 0x20                                                                                        \
    __asm east_done_##ID:                                                                                     \
    __asm and ebx, MASK                                                                                       \
    __asm jz west_done_##ID                                                                                   \
    __asm or edx, 0x2                                                                                         \
    __asm west_done_##ID:                                                                                     \
    __asm mov ecx, dword ptr [edi]                                                                            \
    __asm add esi, ecx                                                                                        \
    __asm add esi, ecx                                                                                        \
    __asm add esi, ecx                                                                                        \
    __asm add esi, ecx                                                                                        \
    __asm mov eax, dword ptr [esi - 0x4]                                                                      \
    __asm mov ebx, dword ptr [esi + 0x4]                                                                      \
    __asm mov ecx, dword ptr [esi]                                                                            \
    __asm and eax, MASK                                                                                       \
    __asm jz north_west_done_##ID                                                                             \
    __asm or edx, 0x1                                                                                         \
    __asm north_west_done_##ID:                                                                               \
    __asm and ebx, MASK                                                                                       \
    __asm jz north_east_done_##ID                                                                             \
    __asm or edx, 0x40                                                                                        \
    __asm north_east_done_##ID:                                                                               \
    __asm and ecx, MASK                                                                                       \
    __asm jz north_done_##ID                                                                                  \
    __asm or edx, 0x80                                                                                        \
    __asm north_done_##ID:                                                                                    \
    __asm mov ecx, dword ptr [edi + 0x10]                                                                     \
    __asm pop esi                                                                                             \
    __asm add esi, ecx                                                                                        \
    __asm add esi, ecx                                                                                        \
    __asm add esi, ecx                                                                                        \
    __asm add esi, ecx                                                                                        \
    __asm mov eax, dword ptr [esi - 0x4]                                                                      \
    __asm mov ebx, dword ptr [esi + 0x4]                                                                      \
    __asm mov ecx, dword ptr [esi]                                                                            \
    __asm and eax, MASK                                                                                       \
    __asm jz south_west_done_##ID                                                                             \
    __asm or edx, 0x4                                                                                         \
    __asm south_west_done_##ID:                                                                               \
    __asm and ebx, MASK                                                                                       \
    __asm jz south_east_done_##ID                                                                             \
    __asm or edx, 0x10                                                                                        \
    __asm south_east_done_##ID:                                                                               \
    __asm and ecx, MASK                                                                                       \
    __asm jz south_done_##ID                                                                                  \
    __asm or edx, 0x8                                                                                         \
    __asm south_done_##ID:                                                                                    \
    __asm mov byte ptr [DAT_TileMapState::instance]TileMapState.bitFlag, dl

#define MACRO_NEIGHBOUR_FLAGS_GLOBAL_MISC_8(ID, MASK)                                                         \
    (void)&DAT_TileMapState::instance;                                                                        \
    __asm mov edi, dword ptr [DAT_TileMapState::instance]TileMapState.ptr_MovementDirectionTranslationMatrix  \
    __asm mov esi, dword ptr [DAT_TileMapState::instance]TileMapState.ptr_MiscDisplayLayer                    \
    __asm mov eax, dword ptr [DAT_TileMapState::instance]TileMapState.DAT_SomeTile                            \
    __asm shl eax, 0x1                                                                                        \
    __asm add esi, eax                                                                                        \
    __asm push esi                                                                                            \
    __asm mov eax, dword ptr [DAT_TileMapState::instance]TileMapState.DAT_SomeY                               \
    __asm shl eax, 0x5                                                                                        \
    __asm add edi, eax                                                                                        \
    __asm mov edx, 0x0                                                                                        \
    __asm mov eax, dword ptr [esi + 0x2]                                                                      \
    __asm mov ebx, dword ptr [esi - 0x2]                                                                      \
    __asm and eax, MASK                                                                                       \
    __asm jz east_done_##ID                                                                                   \
    __asm or edx, 0x20                                                                                        \
    __asm east_done_##ID:                                                                                     \
    __asm and ebx, MASK                                                                                       \
    __asm jz west_done_##ID                                                                                   \
    __asm or edx, 0x2                                                                                         \
    __asm west_done_##ID:                                                                                     \
    __asm mov ecx, dword ptr [edi]                                                                            \
    __asm add esi, ecx                                                                                        \
    __asm add esi, ecx                                                                                        \
    __asm mov eax, dword ptr [esi - 0x2]                                                                      \
    __asm mov ebx, dword ptr [esi + 0x2]                                                                      \
    __asm mov ecx, dword ptr [esi]                                                                            \
    __asm and eax, MASK                                                                                       \
    __asm jz north_west_done_##ID                                                                             \
    __asm or edx, 0x1                                                                                         \
    __asm north_west_done_##ID:                                                                               \
    __asm and ebx, MASK                                                                                       \
    __asm jz north_east_done_##ID                                                                             \
    __asm or edx, 0x40                                                                                        \
    __asm north_east_done_##ID:                                                                               \
    __asm and ecx, MASK                                                                                       \
    __asm jz north_done_##ID                                                                                  \
    __asm or edx, 0x80                                                                                        \
    __asm north_done_##ID:                                                                                    \
    __asm mov ecx, dword ptr [edi + 0x10]                                                                     \
    __asm pop esi                                                                                             \
    __asm add esi, ecx                                                                                        \
    __asm add esi, ecx                                                                                        \
    __asm mov eax, dword ptr [esi - 0x2]                                                                      \
    __asm mov ebx, dword ptr [esi + 0x2]                                                                      \
    __asm mov ecx, dword ptr [esi]                                                                            \
    __asm and eax, MASK                                                                                       \
    __asm jz south_west_done_##ID                                                                             \
    __asm or edx, 0x4                                                                                         \
    __asm south_west_done_##ID:                                                                               \
    __asm and ebx, MASK                                                                                       \
    __asm jz south_east_done_##ID                                                                             \
    __asm or edx, 0x10                                                                                        \
    __asm south_east_done_##ID:                                                                               \
    __asm and ecx, MASK                                                                                       \
    __asm jz south_done_##ID                                                                                  \
    __asm or edx, 0x8                                                                                         \
    __asm south_done_##ID:                                                                                    \
    __asm mov byte ptr [DAT_TileMapState::instance]TileMapState.bitFlag, dl

#define MACRO_NEIGHBOUR_FLAGS_GLOBAL_TERRAIN_4(ID, MASK)                                                      \
    (void)&DAT_TileMapState::instance;                                                                        \
    __asm mov edi, dword ptr [DAT_TileMapState::instance]TileMapState.ptr_MovementDirectionTranslationMatrix  \
    __asm mov esi, dword ptr [DAT_TileMapState::instance]TileMapState.ptr_TerrainTypeTileMap                  \
    __asm mov eax, dword ptr [DAT_TileMapState::instance]TileMapState.DAT_SomeTile                            \
    __asm add esi, eax                                                                                        \
    __asm push esi                                                                                            \
    __asm mov eax, dword ptr [DAT_TileMapState::instance]TileMapState.DAT_SomeY                               \
    __asm shl eax, 0x5                                                                                        \
    __asm add edi, eax                                                                                        \
    __asm mov edx, 0x0                                                                                        \
    __asm mov eax, dword ptr [esi + 0x1]                                                                      \
    __asm mov ebx, dword ptr [esi - 0x1]                                                                      \
    __asm and eax, MASK                                                                                       \
    __asm jz east_done_##ID                                                                                   \
    __asm or edx, 0x20                                                                                        \
    __asm east_done_##ID:                                                                                     \
    __asm and ebx, MASK                                                                                       \
    __asm jz west_done_##ID                                                                                   \
    __asm or edx, 0x2                                                                                         \
    __asm west_done_##ID:                                                                                     \
    __asm mov ecx, dword ptr [edi]                                                                            \
    __asm add esi, ecx                                                                                        \
    __asm mov eax, dword ptr [esi]                                                                            \
    __asm and eax, MASK                                                                                       \
    __asm jz north_done_##ID                                                                                  \
    __asm or edx, 0x80                                                                                        \
    __asm north_done_##ID:                                                                                    \
    __asm mov ecx, dword ptr [edi + 0x10]                                                                     \
    __asm pop esi                                                                                             \
    __asm add esi, ecx                                                                                        \
    __asm mov eax, dword ptr [esi]                                                                            \
    __asm and eax, MASK                                                                                       \
    __asm jz south_done_##ID                                                                                  \
    __asm or edx, 0x8                                                                                         \
    __asm south_done_##ID:                                                                                    \
    __asm mov byte ptr [DAT_TileMapState::instance]TileMapState.bitFlag, dl

#define MACRO_NEIGHBOUR_FLAGS_GLOBAL_TERRAIN_8(ID, MASK)                                                      \
    (void)&DAT_TileMapState::instance;                                                                        \
    __asm mov edi, dword ptr [DAT_TileMapState::instance]TileMapState.ptr_MovementDirectionTranslationMatrix  \
    __asm mov esi, dword ptr [DAT_TileMapState::instance]TileMapState.ptr_TerrainTypeTileMap                  \
    __asm mov eax, dword ptr [DAT_TileMapState::instance]TileMapState.DAT_SomeTile                            \
    __asm add esi, eax                                                                                        \
    __asm push esi                                                                                            \
    __asm mov eax, dword ptr [DAT_TileMapState::instance]TileMapState.DAT_SomeY                               \
    __asm shl eax, 0x5                                                                                        \
    __asm add edi, eax                                                                                        \
    __asm mov edx, 0x0                                                                                        \
    __asm mov eax, dword ptr [esi + 0x1]                                                                      \
    __asm mov ebx, dword ptr [esi - 0x1]                                                                      \
    __asm and eax, MASK                                                                                       \
    __asm jz east_done_##ID                                                                                   \
    __asm or edx, 0x20                                                                                        \
    __asm east_done_##ID:                                                                                     \
    __asm and ebx, MASK                                                                                       \
    __asm jz west_done_##ID                                                                                   \
    __asm or edx, 0x2                                                                                         \
    __asm west_done_##ID:                                                                                     \
    __asm mov ecx, dword ptr [edi]                                                                            \
    __asm add esi, ecx                                                                                        \
    __asm mov eax, dword ptr [esi - 0x1]                                                                      \
    __asm mov ebx, dword ptr [esi + 0x1]                                                                      \
    __asm mov ecx, dword ptr [esi]                                                                            \
    __asm and eax, MASK                                                                                       \
    __asm jz north_west_done_##ID                                                                             \
    __asm or edx, 0x1                                                                                         \
    __asm north_west_done_##ID:                                                                               \
    __asm and ebx, MASK                                                                                       \
    __asm jz north_east_done_##ID                                                                             \
    __asm or edx, 0x40                                                                                        \
    __asm north_east_done_##ID:                                                                               \
    __asm and ecx, MASK                                                                                       \
    __asm jz north_done_##ID                                                                                  \
    __asm or edx, 0x80                                                                                        \
    __asm north_done_##ID:                                                                                    \
    __asm mov ecx, dword ptr [edi + 0x10]                                                                     \
    __asm pop esi                                                                                             \
    __asm add esi, ecx                                                                                        \
    __asm mov eax, dword ptr [esi - 0x1]                                                                      \
    __asm mov ebx, dword ptr [esi + 0x1]                                                                      \
    __asm mov ecx, dword ptr [esi]                                                                            \
    __asm and eax, MASK                                                                                       \
    __asm jz south_west_done_##ID                                                                             \
    __asm or edx, 0x4                                                                                         \
    __asm south_west_done_##ID:                                                                               \
    __asm and ebx, MASK                                                                                       \
    __asm jz south_east_done_##ID                                                                             \
    __asm or edx, 0x10                                                                                        \
    __asm south_east_done_##ID:                                                                               \
    __asm and ecx, MASK                                                                                       \
    __asm jz south_done_##ID                                                                                  \
    __asm or edx, 0x8                                                                                         \
    __asm south_done_##ID:                                                                                    \
    __asm mov byte ptr [DAT_TileMapState::instance]TileMapState.bitFlag, dl

#define MACRO_MARK_CHANGED_NEIGHBOURS_GLOBAL()                                                                \
    (void)&DAT_TileMapState::instance;                                                                        \
    __asm mov esi, dword ptr [DAT_TileMapState::instance]TileMapState.ptr_ChangedLayer                        \
    __asm mov eax, dword ptr [DAT_TileMapState::instance]TileMapState.DAT_SomeTile                            \
    __asm add esi, eax                                                                                        \
    __asm push esi                                                                                            \
    __asm mov edx, dword ptr [DAT_TileMapState::instance]TileMapState.ptr_MovementDirectionTranslationMatrix  \
    __asm mov eax, dword ptr [DAT_TileMapState::instance]TileMapState.DAT_SomeY                               \
    __asm shl eax, 0x5                                                                                        \
    __asm add edx, eax                                                                                        \
    __asm mov byte ptr [esi + 0x1], 0x2                                                                       \
    __asm mov byte ptr [esi - 0x1], 0x2                                                                       \
    __asm mov byte ptr [esi], 0x2                                                                             \
    __asm mov ecx, dword ptr [edx]                                                                            \
    __asm add esi, ecx                                                                                        \
    __asm mov byte ptr [esi - 0x1], 0x2                                                                       \
    __asm mov byte ptr [esi + 0x1], 0x2                                                                       \
    __asm mov byte ptr [esi], 0x2                                                                             \
    __asm mov ecx, dword ptr [edx + 0x10]                                                                     \
    __asm pop esi                                                                                             \
    __asm add esi, ecx                                                                                        \
    __asm mov byte ptr [esi - 0x1], 0x2                                                                       \
    __asm mov byte ptr [esi + 0x1], 0x2                                                                       \
    __asm mov byte ptr [esi], 0x2

// clang-format on
