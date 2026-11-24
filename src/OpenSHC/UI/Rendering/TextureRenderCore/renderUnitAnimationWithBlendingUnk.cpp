#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/IO/Graphics/TgxToken.hpp"
#include "OpenSHC/Rendering/ColorMode.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

#include "OpenSHC/Globals/DAT_BlendFilterArrays.hpp"
#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_CurrentlyRenderedSpriteID.hpp"
#include "OpenSHC/Globals/DAT_RenderedUnitOwner.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::IO::Graphics::TT_REPEATING_PIXELS;
        using OpenSHC::IO::Graphics::TT_STREAM_OF_PIXELS;
        using OpenSHC::IO::Graphics::TT_TGX_PIXEL_HEADER;
        using OpenSHC::IO::Graphics::TT_TGX_PIXEL_LENGTH;
        using OpenSHC::IO::Graphics::TT_TRANSPARENT_PIXELS;

        // The four drawing loops are handwritten assembly in the original, transcribed here from the binary.

        // FUNCTION: STRONGHOLDCRUSADER 0x00451E00
        void TextureRenderCore::renderUnitAnimationWithBlendingUnk(
            int xPosition, int yPosition, int width, int height, byte* imageAddress, int blendStrengthUnk)
        {
            // Both paths and both surface arms assign these; the asm reads the first two
            int lineBytes;
            int heightStart;
            int heightEnd;
            if (DAT_RenderedUnitOwner::instance == 1) {
                DAT_RenderedUnitOwner::instance = 4;
            } else if (DAT_RenderedUnitOwner::instance == 4) {
                DAT_RenderedUnitOwner::instance = 1;
            }
            short* colorPalette = this->gmFileHeaderColorpaletteArray[DAT_CurrentlyRenderedSpriteID::instance]
                                      .colorPalette[DAT_BlendingDefinedData::instance
                                              .PlayerSlotUnitColor[DAT_RenderedUnitOwner::instance]];
            if (height <= 0) {
                return;
            }
            if (this->colorPaletteOverride != 0) {
                colorPalette = (short*)this->colorPaletteOverride;
            }
            if (blendStrengthUnk >= 32) {
                return;
            }
            // The last filter entry is still zero until the filter arrays are built
            if (DAT_BlendFilterArrays::instance[32][31][0] == 0) {
                MACRO_CALL(OpenSHC::UI::Rendering_Func::InitBlendFilterArraysUnk)();
            }
            // The asm weighs the destination with one row and the drawn colour with the other
            short* const dstFilter = DAT_BlendFilterArrays::instance[blendStrengthUnk][0];
            short* const srcFilter = DAT_BlendFilterArrays::instance[32 - blendStrengthUnk][0];
            // From here blendStrengthUnk holds the line step the asm adds per row, in its own slot as in the original
            if (!DAT_TextureRenderCoreObject::instance.isZoom2) {
                if (this->drawBufferChoiceValue != OpenSHC::Rendering::Enums::RT_SCREEN_MENU) {
                    DAT_TextureRenderCoreObject::instance.currentRenderSurface
                        = DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame;
                    // The map surface is 4056 pixels wide; the heights after the steps (before them loses the match)
                    blendStrengthUnk = 4056 * 2;
                    lineBytes = 4056 * 2;
                    heightStart = this->mapGameSurfaceHeightRange.start;
                    heightEnd = this->mapGameSurfaceHeightRange.end;
                } else {
                    DAT_TextureRenderCoreObject::instance.currentRenderSurface
                        = DAT_WindowAndDirectDraw::instance.surfacePointer_screenMenu;
                    blendStrengthUnk = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine;
                    lineBytes = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine;
                    heightStart = this->screenMenuSurfaceHeightRange.start;
                    heightEnd = this->screenMenuSurfaceHeightRange.end;
                }
                if (height + yPosition > heightEnd) {
                    height = heightEnd - yPosition;
                    if (height <= 0) {
                        return;
                    }
                }
                if (DAT_WindowAndDirectDraw::instance.colorBitMode == OpenSHC::Rendering::RGB_555) {
                    // clang-format off
                    __asm {
                        mov esi, imageAddress
                        mov edi, DAT_TextureRenderCoreObject::instance.currentRenderSurface
                        mov eax, xPosition
                        cmp eax, 0
                        jl done_555
                        add eax, eax
                        add edi, eax
                        mov eax, yPosition
                        mov ebx, heightStart
                        cmp eax, ebx
                        jge add_y_offset_555
                        sub ebx, eax
                        mov eax, ebx
                        cmp height, eax
                        jle done_555
                        sub height, eax
                    skip_token_555:
                        mov ecx, 0
                        mov bl, byte ptr [esi]
                        mov cl, byte ptr [esi]
                        and bl, TT_TGX_PIXEL_HEADER
                        and cl, TT_TGX_PIXEL_LENGTH
                        add esi, 1
                        cmp bl, TT_TRANSPARENT_PIXELS
                        je skip_token_555
                        cmp bl, TT_STREAM_OF_PIXELS
                        je skip_stream_555
                        cmp bl, TT_REPEATING_PIXELS
                        je skip_repeating_555
                        jmp skip_newline_555
                    skip_stream_555:
                        add ecx, 1
                        add esi, ecx
                        jmp skip_token_555
                    skip_repeating_555:
                        add esi, 1
                        jmp skip_token_555
                    skip_newline_555:
                        sub eax, 1
                        cmp eax, 0
                        jg skip_token_555
                        mov eax, heightStart
                    add_y_offset_555:
                        mov edx, lineBytes
                        mul edx
                        add edi, eax
                        mov edx, colorPalette
                    draw_row_555:
                        push edi
                    draw_token_555:
                        mov ecx, 0
                        mov al, byte ptr [esi]
                        mov cl, byte ptr [esi]
                        and al, TT_TGX_PIXEL_HEADER
                        and cl, TT_TGX_PIXEL_LENGTH
                        add esi, 1
                        cmp al, TT_TRANSPARENT_PIXELS
                        je draw_transparent_555
                        cmp al, TT_STREAM_OF_PIXELS
                        je draw_stream_555
                        cmp al, TT_REPEATING_PIXELS
                        je draw_repeating_555
                        pop edi
                        add edi, blendStrengthUnk
                        sub height, 1
                        cmp height, 0
                        jg draw_row_555
                        jmp done_555
                    draw_transparent_555:
                        add ecx, 1
                        add ecx, ecx
                        add edi, ecx
                        jmp draw_token_555
                    draw_repeating_555:
                        mov ebx, 0
                        mov eax, 0
                        mov bl, byte ptr [esi]
                        mov ax, word ptr [edx + ebx*2]
                        add esi, 1
                        add ecx, 1
                        push edx
                        mov edx, srcFilter
                        mov ebx, 0
                        mov bx, ax
                        and bx, 0x1f
                        mov bx, word ptr [edx + ebx*8]
                        and ax, 0xffe0
                        or ax, bx
                        mov bx, ax
                        shr bx, 5
                        and bx, 0x1f
                        mov bx, word ptr [edx + ebx*8 + 2]
                        and ax, 0xfc1f
                        or ax, bx
                        mov bx, ax
                        shr bx, 10
                        and bx, 0x1f
                        mov bx, word ptr [edx + ebx*8 + 4]
                        and ax, 0x3ff
                        or ax, bx
                    repeating_pixel_555:
                        mov dx, word ptr [edi]
                        push ax
                        mov eax, dstFilter
                        mov ebx, 0
                        mov bx, dx
                        and bx, 0x1f
                        mov bx, word ptr [eax + ebx*8]
                        and dx, 0xffe0
                        or dx, bx
                        mov bx, dx
                        shr bx, 5
                        and bx, 0x1f
                        mov bx, word ptr [eax + ebx*8 + 2]
                        and dx, 0xfc1f
                        or dx, bx
                        mov bx, dx
                        shr bx, 10
                        and bx, 0x1f
                        mov bx, word ptr [eax + ebx*8 + 4]
                        and dx, 0x83ff
                        or dx, bx
                        pop ax
                        add dx, ax
                        mov word ptr [edi], dx
                        add edi, 2
                        sub ecx, 1
                        jne repeating_pixel_555
                        pop edx
                        jmp draw_token_555
                    draw_stream_555:
                        mov ebx, 0
                        add ecx, 1
                    stream_pixel_555:
                        mov eax, 0
                        mov al, byte ptr [esi]
                        mov ax, word ptr [edx + eax*2]
                        push edx
                        mov edx, srcFilter
                        mov bx, ax
                        and bx, 0x1f
                        mov bx, word ptr [edx + ebx*8]
                        and ax, 0xffe0
                        or ax, bx
                        mov bx, ax
                        shr bx, 5
                        and bx, 0x1f
                        mov bx, word ptr [edx + ebx*8 + 2]
                        and ax, 0xfc1f
                        or ax, bx
                        mov bx, ax
                        shr bx, 10
                        and bx, 0x1f
                        mov bx, word ptr [edx + ebx*8 + 4]
                        and ax, 0x3ff
                        or ax, bx
                        mov dx, word ptr [edi]
                        mov word ptr [edi], ax
                        mov eax, dstFilter
                        mov ebx, 0
                        mov bx, dx
                        and bx, 0x1f
                        mov bx, word ptr [eax + ebx*8]
                        and dx, 0xffe0
                        or dx, bx
                        mov bx, dx
                        shr bx, 5
                        and bx, 0x1f
                        mov bx, word ptr [eax + ebx*8 + 2]
                        and dx, 0xfc1f
                        or dx, bx
                        mov bx, dx
                        shr bx, 10
                        and bx, 0x1f
                        mov bx, word ptr [eax + ebx*8 + 4]
                        and dx, 0x83ff
                        or dx, bx
                        add word ptr [edi], dx
                        pop edx
                        add esi, 1
                        add edi, 2
                        sub ecx, 1
                        jne stream_pixel_555
                        jmp draw_token_555
                    done_555:
                    }
                    // clang-format on
                    return;
                }
                // clang-format off
                __asm {
                    mov esi, imageAddress
                    mov edi, DAT_TextureRenderCoreObject::instance.currentRenderSurface
                    mov eax, xPosition
                    cmp eax, 0
                    jl done_565
                    add eax, eax
                    add edi, eax
                    mov eax, yPosition
                    mov ebx, heightStart
                    cmp eax, ebx
                    jge add_y_offset_565
                    sub ebx, eax
                    mov eax, ebx
                    cmp height, eax
                    jle done_565
                    sub height, eax
                skip_token_565:
                    mov ecx, 0
                    mov bl, byte ptr [esi]
                    mov cl, byte ptr [esi]
                    and bl, TT_TGX_PIXEL_HEADER
                    and cl, TT_TGX_PIXEL_LENGTH
                    add esi, 1
                    cmp bl, TT_TRANSPARENT_PIXELS
                    je skip_token_565
                    cmp bl, TT_STREAM_OF_PIXELS
                    je skip_stream_565
                    cmp bl, TT_REPEATING_PIXELS
                    je skip_repeating_565
                    jmp skip_newline_565
                skip_stream_565:
                    add ecx, 1
                    add esi, ecx
                    jmp skip_token_565
                skip_repeating_565:
                    add esi, 1
                    jmp skip_token_565
                skip_newline_565:
                    sub eax, 1
                    cmp eax, 0
                    jg skip_token_565
                    mov eax, heightStart
                add_y_offset_565:
                    mov edx, lineBytes
                    mul edx
                    add edi, eax
                    mov edx, colorPalette
                draw_row_565:
                    push edi
                draw_token_565:
                    mov ecx, 0
                    mov al, byte ptr [esi]
                    mov cl, byte ptr [esi]
                    and al, TT_TGX_PIXEL_HEADER
                    and cl, TT_TGX_PIXEL_LENGTH
                    add esi, 1
                    cmp al, TT_TRANSPARENT_PIXELS
                    je draw_transparent_565
                    cmp al, TT_STREAM_OF_PIXELS
                    je draw_stream_565
                    cmp al, TT_REPEATING_PIXELS
                    je draw_repeating_565
                    pop edi
                    add edi, blendStrengthUnk
                    sub height, 1
                    cmp height, 0
                    jg draw_row_565
                    jmp done_565
                draw_transparent_565:
                    add ecx, 1
                    add ecx, ecx
                    add edi, ecx
                    jmp draw_token_565
                draw_repeating_565:
                    mov ebx, 0
                    mov eax, 0
                    mov bl, byte ptr [esi]
                    mov ax, word ptr [edx + ebx*2]
                    add esi, 1
                    push esi
                    add ecx, 1
                    push edx
                    mov esi, srcFilter
                    mov ebx, 0
                    mov bx, ax
                    and bx, 0x1f
                    mov dx, word ptr [esi + ebx*8]
                    mov bx, ax
                    shr bx, 5
                    and bx, 0x3f
                    or dx, word ptr [esi + ebx*8 + 2]
                    mov bx, ax
                    shr bx, 11
                    and bx, 0x1f
                    or dx, word ptr [esi + ebx*8 + 4]
                    mov ax, dx
                    mov esi, dstFilter
                repeating_pixel_565:
                    mov dx, word ptr [edi]
                    push ax
                    mov ebx, 0
                    mov bx, dx
                    and bx, 0x1f
                    mov ax, word ptr [esi + ebx*8]
                    mov bx, dx
                    shr bx, 5
                    and bx, 0x3f
                    or ax, word ptr [esi + ebx*8 + 2]
                    mov bx, dx
                    shr bx, 11
                    and bx, 0x1f
                    or ax, word ptr [esi + ebx*8 + 4]
                    mov dx, ax
                    pop ax
                    add dx, ax
                    mov word ptr [edi], dx
                    add edi, 2
                    sub ecx, 1
                    jne repeating_pixel_565
                    pop edx
                    pop esi
                    jmp draw_token_565
                draw_stream_565:
                    add ecx, 1
                stream_pixel_565:
                    mov eax, 0
                    mov al, byte ptr [esi]
                    mov ax, word ptr [edx + eax*2]
                    push ecx
                    push edx
                    mov edx, srcFilter
                    mov ebx, 0
                    mov bx, ax
                    and bx, 0x1f
                    mov cx, word ptr [edx + ebx*8]
                    mov bx, ax
                    shr bx, 5
                    and bx, 0x3f
                    or cx, word ptr [edx + ebx*8 + 2]
                    mov bx, ax
                    shr bx, 11
                    and bx, 0x1f
                    or cx, word ptr [edx + ebx*8 + 4]
                    mov dx, word ptr [edi]
                    mov eax, dstFilter
                    mov ebx, 0
                    mov bx, dx
                    and bx, 0x1f
                    add cx, word ptr [eax + ebx*8]
                    mov bx, dx
                    shr bx, 5
                    and bx, 0x3f
                    add cx, word ptr [eax + ebx*8 + 2]
                    mov bx, dx
                    shr bx, 11
                    and bx, 0x1f
                    add cx, word ptr [eax + ebx*8 + 4]
                    mov word ptr [edi], cx
                    pop edx
                    pop ecx
                    add esi, 1
                    add edi, 2
                    sub ecx, 1
                    jne stream_pixel_565
                    jmp draw_token_565
                done_565:
                }
                // clang-format on
            } else {
                // Only the zoomed asm uses it (declared at the top it takes the line width's slot and loses the match)
                int columnOffset;
                // The zoomed-out loops skip odd columns: the parity first (after the heights loses the match)
                int const startColumnParity = xPosition & 1;
                DAT_TextureRenderCoreObject::instance.currentRenderSurface
                    = DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame;
                blendStrengthUnk = 4056 * 2;
                lineBytes = 4056 * 2;
                heightStart = this->mapGameSurfaceHeightRange.start;
                heightEnd = this->mapGameSurfaceHeightRange.end;
                if (height + yPosition > heightEnd) {
                    height = heightEnd - yPosition;
                    if (height <= 0) {
                        return;
                    }
                }
                if (DAT_WindowAndDirectDraw::instance.colorBitMode == OpenSHC::Rendering::RGB_555) {
                    // clang-format off
                    __asm {
                        mov esi, imageAddress
                        mov edi, DAT_TextureRenderCoreObject::instance.currentRenderSurface
                        mov eax, xPosition
                        cmp eax, 0
                        jl done_zoomed_555
                        and eax, 0xfffffffe
                        add edi, eax
                        mov eax, yPosition
                        mov ebx, heightStart
                        cmp eax, ebx
                        jge add_y_offset_zoomed_555
                        sub ebx, eax
                        mov eax, ebx
                        cmp height, eax
                        jle done_zoomed_555
                        sub height, eax
                    skip_token_zoomed_555:
                        mov ecx, 0
                        mov bl, byte ptr [esi]
                        mov cl, byte ptr [esi]
                        and bl, TT_TGX_PIXEL_HEADER
                        and cl, TT_TGX_PIXEL_LENGTH
                        add esi, 1
                        cmp bl, TT_TRANSPARENT_PIXELS
                        je skip_token_zoomed_555
                        cmp bl, TT_STREAM_OF_PIXELS
                        je skip_stream_zoomed_555
                        cmp bl, TT_REPEATING_PIXELS
                        je skip_repeating_zoomed_555
                        jmp skip_newline_zoomed_555
                    skip_stream_zoomed_555:
                        add ecx, 1
                        add esi, ecx
                        jmp skip_token_zoomed_555
                    skip_repeating_zoomed_555:
                        add esi, 1
                        jmp skip_token_zoomed_555
                    skip_newline_zoomed_555:
                        sub eax, 1
                        cmp eax, 0
                        jg skip_token_zoomed_555
                        mov eax, heightStart
                    add_y_offset_zoomed_555:
                        mov edx, lineBytes
                        mov ecx, eax
                        shr eax, 1
                        mul edx
                        add edi, eax
                        mov edx, colorPalette
                    draw_row_zoomed_555:
                        mov ebx, startColumnParity
                        mov columnOffset, ebx
                        push edi
                    draw_token_zoomed_555:
                        mov ecx, 0
                        mov al, byte ptr [esi]
                        mov cl, byte ptr [esi]
                        and al, TT_TGX_PIXEL_HEADER
                        and cl, TT_TGX_PIXEL_LENGTH
                        add esi, 1
                        cmp al, TT_TRANSPARENT_PIXELS
                        je draw_transparent_zoomed_555
                        cmp al, TT_STREAM_OF_PIXELS
                        je draw_stream_zoomed_555
                        cmp al, TT_REPEATING_PIXELS
                        je draw_repeating_zoomed_555
                        pop edi
                        add edi, blendStrengthUnk
                        sub height, 1
                        cmp height, 0
                        jle done_zoomed_555
                    skip_row_token_zoomed_555:
                        mov ecx, 0
                        mov bl, byte ptr [esi]
                        mov cl, byte ptr [esi]
                        and bl, TT_TGX_PIXEL_HEADER
                        and cl, TT_TGX_PIXEL_LENGTH
                        add esi, 1
                        cmp bl, TT_TRANSPARENT_PIXELS
                        je skip_row_token_zoomed_555
                        cmp bl, TT_STREAM_OF_PIXELS
                        je skip_row_stream_zoomed_555
                        cmp bl, TT_REPEATING_PIXELS
                        je skip_row_repeating_zoomed_555
                        jmp skip_row_done_zoomed_555
                    skip_row_stream_zoomed_555:
                        add ecx, 1
                        add esi, ecx
                        jmp skip_row_token_zoomed_555
                    skip_row_repeating_zoomed_555:
                        add esi, 1
                        jmp skip_row_token_zoomed_555
                    skip_row_done_zoomed_555:
                        sub height, 1
                        cmp height, 0
                        jg draw_row_zoomed_555
                        jmp done_zoomed_555
                    draw_transparent_zoomed_555:
                        add ecx, 1
                        add columnOffset, ecx
                        jmp draw_token_zoomed_555
                    draw_repeating_zoomed_555:
                        mov ebx, 0
                        mov eax, 0
                        mov bl, byte ptr [esi]
                        mov ax, word ptr [edx + ebx*2]
                        add esi, 1
                        push edx
                        mov edx, srcFilter
                        mov ebx, 0
                        mov bx, ax
                        and bx, 0x1f
                        mov bx, word ptr [edx + ebx*8]
                        and ax, 0xffe0
                        or ax, bx
                        mov bx, ax
                        shr bx, 5
                        and bx, 0x1f
                        mov bx, word ptr [edx + ebx*8 + 2]
                        and ax, 0xfc1f
                        or ax, bx
                        mov bx, ax
                        shr bx, 10
                        and bx, 0x1f
                        mov bx, word ptr [edx + ebx*8 + 4]
                        and ax, 0x3ff
                        or ax, bx
                        add ecx, 1
                        mov ebx, columnOffset
                        add columnOffset, ecx
                    repeating_pixel_zoomed_555:
                        test ebx, 1
                        jne repeating_next_zoomed_555
                        mov dx, word ptr [edi + ebx]
                        push ax
                        push ebx
                        mov eax, dstFilter
                        mov ebx, 0
                        mov bx, dx
                        and bx, 0x1f
                        mov bx, word ptr [eax + ebx*8]
                        and dx, 0xffe0
                        or dx, bx
                        mov bx, dx
                        shr bx, 5
                        and bx, 0x1f
                        mov bx, word ptr [eax + ebx*8 + 2]
                        and dx, 0xfc1f
                        or dx, bx
                        mov bx, dx
                        shr bx, 10
                        and bx, 0x1f
                        mov bx, word ptr [eax + ebx*8 + 4]
                        and dx, 0x83ff
                        or dx, bx
                        pop ebx
                        pop ax
                        add dx, ax
                        mov word ptr [edi + ebx], dx
                    repeating_next_zoomed_555:
                        add ebx, 1
                        sub ecx, 1
                        jne repeating_pixel_zoomed_555
                        pop edx
                        jmp draw_token_zoomed_555
                    draw_stream_zoomed_555:
                        mov eax, 0
                        add ecx, 1
                        mov ebx, columnOffset
                        add columnOffset, ecx
                    stream_pixel_zoomed_555:
                        test ebx, 1
                        jne stream_next_zoomed_555
                        push edx
                        push ebx
                        mov eax, 0
                        mov al, byte ptr [esi]
                        mov ax, word ptr [edx + eax*2]
                        mov edx, srcFilter
                        mov bx, ax
                        and bx, 0x1f
                        mov bx, word ptr [edx + ebx*8]
                        and ax, 0xffe0
                        or ax, bx
                        mov bx, ax
                        shr bx, 5
                        and bx, 0x1f
                        mov bx, word ptr [edx + ebx*8 + 2]
                        and ax, 0xfc1f
                        or ax, bx
                        mov bx, ax
                        shr bx, 10
                        and bx, 0x1f
                        mov bx, word ptr [edx + ebx*8 + 4]
                        and ax, 0x3ff
                        or ax, bx
                        pop ebx
                        mov dx, word ptr [edi + ebx]
                        mov word ptr [edi + ebx], ax
                        mov eax, dstFilter
                        push ebx
                        mov ebx, 0
                        mov bx, dx
                        and bx, 0x1f
                        mov bx, word ptr [eax + ebx*8]
                        and dx, 0xffe0
                        or dx, bx
                        mov bx, dx
                        shr bx, 5
                        and bx, 0x1f
                        mov bx, word ptr [eax + ebx*8 + 2]
                        and dx, 0xfc1f
                        or dx, bx
                        mov bx, dx
                        shr bx, 10
                        and bx, 0x1f
                        mov bx, word ptr [eax + ebx*8 + 4]
                        and dx, 0x83ff
                        or dx, bx
                        pop ebx
                        add word ptr [edi + ebx], dx
                        pop edx
                    stream_next_zoomed_555:
                        add esi, 1
                        add ebx, 1
                        sub ecx, 1
                        jne stream_pixel_zoomed_555
                        jmp draw_token_zoomed_555
                    done_zoomed_555:
                    }
                    // clang-format on
                    return;
                }
                // clang-format off
                __asm {
                    mov esi, imageAddress
                    mov edi, DAT_TextureRenderCoreObject::instance.currentRenderSurface
                    mov eax, xPosition
                    cmp eax, 0
                    jl done_zoomed_565
                    and eax, 0xfffffffe
                    add edi, eax
                    mov eax, yPosition
                    mov ebx, heightStart
                    cmp eax, ebx
                    jge add_y_offset_zoomed_565
                    sub ebx, eax
                    mov eax, ebx
                    cmp height, eax
                    jle done_zoomed_565
                    sub height, eax
                skip_token_zoomed_565:
                    mov ecx, 0
                    mov bl, byte ptr [esi]
                    mov cl, byte ptr [esi]
                    and bl, TT_TGX_PIXEL_HEADER
                    and cl, TT_TGX_PIXEL_LENGTH
                    add esi, 1
                    cmp bl, TT_TRANSPARENT_PIXELS
                    je skip_token_zoomed_565
                    cmp bl, TT_STREAM_OF_PIXELS
                    je skip_stream_zoomed_565
                    cmp bl, TT_REPEATING_PIXELS
                    je skip_repeating_zoomed_565
                    jmp skip_newline_zoomed_565
                skip_stream_zoomed_565:
                    add ecx, 1
                    add esi, ecx
                    jmp skip_token_zoomed_565
                skip_repeating_zoomed_565:
                    add esi, 1
                    jmp skip_token_zoomed_565
                skip_newline_zoomed_565:
                    sub eax, 1
                    cmp eax, 0
                    jg skip_token_zoomed_565
                    mov eax, heightStart
                add_y_offset_zoomed_565:
                    mov edx, lineBytes
                    mov ecx, eax
                    shr eax, 1
                    mul edx
                    add edi, eax
                    mov edx, colorPalette
                draw_row_zoomed_565:
                    mov ebx, startColumnParity
                    mov columnOffset, ebx
                    push edi
                draw_token_zoomed_565:
                    mov ecx, 0
                    mov al, byte ptr [esi]
                    mov cl, byte ptr [esi]
                    and al, TT_TGX_PIXEL_HEADER
                    and cl, TT_TGX_PIXEL_LENGTH
                    add esi, 1
                    cmp al, TT_TRANSPARENT_PIXELS
                    je draw_transparent_zoomed_565
                    cmp al, TT_STREAM_OF_PIXELS
                    je draw_stream_zoomed_565
                    cmp al, TT_REPEATING_PIXELS
                    je draw_repeating_zoomed_565
                    pop edi
                    add edi, blendStrengthUnk
                    sub height, 1
                    cmp height, 0
                    jle done_zoomed_565
                skip_row_token_zoomed_565:
                    mov ecx, 0
                    mov bl, byte ptr [esi]
                    mov cl, byte ptr [esi]
                    and bl, TT_TGX_PIXEL_HEADER
                    and cl, TT_TGX_PIXEL_LENGTH
                    add esi, 1
                    cmp bl, TT_TRANSPARENT_PIXELS
                    je skip_row_token_zoomed_565
                    cmp bl, TT_STREAM_OF_PIXELS
                    je skip_row_stream_zoomed_565
                    cmp bl, TT_REPEATING_PIXELS
                    je skip_row_repeating_zoomed_565
                    jmp skip_row_done_zoomed_565
                skip_row_stream_zoomed_565:
                    add ecx, 1
                    add esi, ecx
                    jmp skip_row_token_zoomed_565
                skip_row_repeating_zoomed_565:
                    add esi, 1
                    jmp skip_row_token_zoomed_565
                skip_row_done_zoomed_565:
                    sub height, 1
                    cmp height, 0
                    jg draw_row_zoomed_565
                    jmp done_zoomed_565
                draw_transparent_zoomed_565:
                    add ecx, 1
                    add columnOffset, ecx
                    jmp draw_token_zoomed_565
                draw_repeating_zoomed_565:
                    mov ebx, 0
                    mov eax, 0
                    mov bl, byte ptr [esi]
                    mov ax, word ptr [edx + ebx*2]
                    add esi, 1
                    push edx
                    mov edx, srcFilter
                    mov ebx, 0
                    mov bx, ax
                    and bx, 0x1f
                    mov bx, word ptr [edx + ebx*8]
                    and ax, 0xffe0
                    or ax, bx
                    mov bx, ax
                    shr bx, 5
                    and bx, 0x3f
                    mov bx, word ptr [edx + ebx*8 + 2]
                    and ax, 0xf81f
                    or ax, bx
                    mov bx, ax
                    shr bx, 11
                    and bx, 0x1f
                    mov bx, word ptr [edx + ebx*8 + 4]
                    and ax, 0x7ff
                    or ax, bx
                    add ecx, 1
                    mov ebx, columnOffset
                    add columnOffset, ecx
                repeating_pixel_zoomed_565:
                    test ebx, 1
                    jne repeating_next_zoomed_565
                    mov dx, word ptr [edi + ebx]
                    push ax
                    push ebx
                    mov eax, dstFilter
                    mov ebx, 0
                    mov bx, dx
                    and bx, 0x1f
                    mov bx, word ptr [eax + ebx*8]
                    and dx, 0xffe0
                    or dx, bx
                    mov bx, dx
                    shr bx, 5
                    and bx, 0x3f
                    mov bx, word ptr [eax + ebx*8 + 2]
                    and dx, 0xf81f
                    or dx, bx
                    mov bx, dx
                    shr bx, 11
                    and bx, 0x1f
                    mov bx, word ptr [eax + ebx*8 + 4]
                    and dx, 0x7ff
                    or dx, bx
                    pop ebx
                    pop ax
                    add dx, ax
                    mov word ptr [edi + ebx], dx
                repeating_next_zoomed_565:
                    add ebx, 1
                    sub ecx, 1
                    jne repeating_pixel_zoomed_565
                    pop edx
                    jmp draw_token_zoomed_565
                draw_stream_zoomed_565:
                    mov eax, 0
                    add ecx, 1
                    mov ebx, columnOffset
                    add columnOffset, ecx
                stream_pixel_zoomed_565:
                    test ebx, 1
                    jne stream_next_zoomed_565
                    push edx
                    push ebx
                    mov eax, 0
                    mov al, byte ptr [esi]
                    mov ax, word ptr [edx + eax*2]
                    mov edx, srcFilter
                    mov bx, ax
                    and bx, 0x1f
                    mov bx, word ptr [edx + ebx*8]
                    and ax, 0xffe0
                    or ax, bx
                    mov bx, ax
                    shr bx, 5
                    and bx, 0x3f
                    mov bx, word ptr [edx + ebx*8 + 2]
                    and ax, 0xf81f
                    or ax, bx
                    mov bx, ax
                    shr bx, 11
                    and bx, 0x1f
                    mov bx, word ptr [edx + ebx*8 + 4]
                    and ax, 0x7ff
                    or ax, bx
                    pop ebx
                    mov dx, word ptr [edi + ebx]
                    mov word ptr [edi + ebx], ax
                    mov eax, dstFilter
                    push ebx
                    mov ebx, 0
                    mov bx, dx
                    and bx, 0x1f
                    mov bx, word ptr [eax + ebx*8]
                    and dx, 0xffe0
                    or dx, bx
                    mov bx, dx
                    shr bx, 5
                    and bx, 0x3f
                    mov bx, word ptr [eax + ebx*8 + 2]
                    and dx, 0xf81f
                    or dx, bx
                    mov bx, dx
                    shr bx, 11
                    and bx, 0x1f
                    mov bx, word ptr [eax + ebx*8 + 4]
                    and dx, 0x7ff
                    or dx, bx
                    pop ebx
                    add word ptr [edi + ebx], dx
                    pop edx
                stream_next_zoomed_565:
                    add esi, 1
                    add ebx, 1
                    sub ecx, 1
                    jne stream_pixel_zoomed_565
                    jmp draw_token_zoomed_565
                done_zoomed_565:
                }
                // clang-format on
            }
        }

    }
}
}
