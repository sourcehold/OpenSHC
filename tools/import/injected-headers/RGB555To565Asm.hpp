/**
  HAND WRITTEN - not generated.

  path: 'OpenSHC/UI/Rendering/TextureRenderCore/RGB555To565Asm.hpp'

  Converting RGB555 pixels to RGB565 in place is handwritten assembly in the original, and it is a
  MACRO: the identical instruction stream appears, never as a call, as the whole loop in
  transformRawWithMarkerUnkToRGB555To565 (0x0044C940), transformTileObjectToRGB565 (0x0044CAE0) and
  transformRawToRGB555To565 (0x0044CB60), and as the pixel body twice in transformTgxFromRGB555ToRGB565
  (0x0044C9C0: at 0x0044CA08 with the marker test, at 0x0044CA6D without). It is recognisable by

    - "cmp edx, 0" where MSVC would emit "test edx, edx",
    - the pixel read with "mov ax, word ptr [esi]" and every channel computed in 16-bit registers,
      where MSVC would emit movzx and work in 32 bits,
    - the loop closed with an unconditional "jmp" back to its test.

  Red goes into a dead parameter's stack slot, as in the original.

  The macros expect these names in the enclosing function:

    ushort  _blue       declared after the pixel pointer
    ushort  _green      declared after _blue
    RED                 the dead parameter that holds red: imageOffset in the loops, tgxDataPtr in
                        0x0044C9C0

  and the loops also

    ushort* _colorPtr   the first pixel, gmProcessedImageData + imageOffset, declared first
    int     imageOffset the parameter

  MACRO_RGB555_TO_565_PIXEL converts the pixel at [esi], then steps edx back by 2 and esi on by 2. With
  MACRO_ASM_SKIP_MARKER_TEST and MACRO_ASM_SKIP_MARKER_LABEL it leaves pixels equal to 0xf81f untouched;
  that is magenta already encoded as RGB565, the transparency marker. COUNT is the buffer size in bytes.
  All of them clobber eax and ebx, the loops also edx and esi. They define assembler labels, so a loop
  can be expanded once per function, and the pixel macro more than once, but with the skip label once.
*/

#pragma once

// clang-format off

#define MACRO_ASM_NONE
#define MACRO_ASM_SKIP_MARKER_TEST                                                    \
    __asm cmp ax, 0xf81f                                                              \
    __asm je skip_color
#define MACRO_ASM_SKIP_MARKER_LABEL                                                   \
    __asm skip_color:

#define MACRO_RGB555_TO_565_PIXEL(RED, SKIP_TEST, SKIP_LABEL)                         \
    __asm mov ax, word ptr [esi]                                                      \
    SKIP_TEST                                                                         \
    __asm mov bx, ax                                                                  \
    __asm and bx, 0x1f                                                                \
    __asm mov _blue, bx                                                               \
    __asm mov bx, ax                                                                  \
    __asm and bx, 0x3e0                                                               \
    __asm shr bx, 5                                                                   \
    __asm mov _green, bx                                                              \
    __asm mov bx, ax                                                                  \
    __asm and bx, 0x7c00                                                              \
    __asm shr bx, 10                                                                  \
    __asm mov word ptr RED, bx                                                        \
    __asm mov ax, _blue                                                               \
    __asm mov bx, _green                                                              \
    __asm shl bx, 6                                                                   \
    __asm add ax, bx                                                                  \
    __asm mov bx, word ptr RED                                                        \
    __asm shl bx, 11                                                                  \
    __asm add ax, bx                                                                  \
    __asm mov word ptr [esi], ax                                                      \
    SKIP_LABEL                                                                        \
    __asm sub edx, 2                                                                  \
    __asm add esi, 2

#define MACRO_RGB555_TO_565_LOOP_IMPL(COUNT, SKIP_TEST, SKIP_LABEL)                   \
    __asm mov esi, _colorPtr                                                          \
    __asm mov edx, COUNT                                                              \
    __asm next_color:                                                                 \
    __asm cmp edx, 0                                                                  \
    __asm jle done                                                                    \
    MACRO_RGB555_TO_565_PIXEL(imageOffset, SKIP_TEST, SKIP_LABEL)                     \
    __asm jmp next_color                                                              \
    __asm done:

#define MACRO_RGB555_TO_565_LOOP(COUNT)                                               \
    MACRO_RGB555_TO_565_LOOP_IMPL(COUNT, MACRO_ASM_NONE, MACRO_ASM_NONE)

#define MACRO_RGB555_TO_565_LOOP_SKIPPING_MARKER(COUNT)                               \
    MACRO_RGB555_TO_565_LOOP_IMPL(COUNT, MACRO_ASM_SKIP_MARKER_TEST, MACRO_ASM_SKIP_MARKER_LABEL)

// clang-format on
