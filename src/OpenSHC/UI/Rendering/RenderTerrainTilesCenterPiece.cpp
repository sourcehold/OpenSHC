#include "../Rendering.func.hpp"

#include "OpenSHC/Globals/DAT_00ed3154.hpp"
#include "OpenSHC/Globals/DAT_GMImageOffsets.hpp"
#include "OpenSHC/Globals/DAT_GmImageAddressToBeRendered.hpp"
#include "OpenSHC/Globals/DAT_RenderMap_DrawSomeX.hpp"
#include "OpenSHC/Globals/DAT_RenderMap_DrawSomeY.hpp"
#include "OpenSHC/Globals/DAT_RenderMap_YOffset.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {

    using UI::Rendering::WindowAndDirectDraw;

    // Copies the 32x16 centre piece of a terrain tile (stored as 0x200 bytes of RGB words, row by row) onto the map
    // surface, or every other pixel of it when zoomed out. The copies are handwritten assembly in the original,
    // transcribed here from the binary.

    // Inline assembly cannot name a resolver global, so the copies reach the globals they use through these.
    static WindowAndDirectDraw* const s_windowAndDirectDraw = &DAT_WindowAndDirectDraw::instance;
    static uint* const s_drawSomeX = &DAT_RenderMap_DrawSomeX::instance;

    // FUNCTION: STRONGHOLDCRUSADER 0x00452900
    void Rendering::RenderTerrainTilesCenterPiece()
    {
        int const drawY
            = DAT_RenderMap_DrawSomeY::instance + (DAT_00ed3154::instance - DAT_RenderMap_YOffset::instance);
        if (drawY >= DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.end
            || drawY < DAT_TextureRenderCoreObject::instance.mapGameSurfaceHeightRange.start) {
            return;
        }
        char* const source = DAT_GMImageOffsets::instance[DAT_GmImageAddressToBeRendered::instance]
            + (char*)DAT_TextureRenderCoreObject::instance.gmProcessedImageData;
        if (!DAT_TextureRenderCoreObject::instance.isZoom2) {
            // clang-format off
            __asm {
        mov esi, source
        mov ecx, s_windowAndDirectDraw
        mov edi, dword ptr [ecx]WindowAndDirectDraw.surfacePointer_mapGame
        mov eax, s_drawSomeX
        mov eax, dword ptr [eax]
        add eax, eax
        add edi, eax
        mov eax, drawY
        mov edx, 0x1fb0
        mul edx
        add edi, eax
        mov dword ptr [ecx]WindowAndDirectDraw.unknownSpecificPointer, edi
        mov eax, dword ptr [esi]
        mov ebx, dword ptr [esi + 4]
        mov ecx, dword ptr [esi + 8]
        mov edx, dword ptr [esi + 0xc]
        mov dword ptr [edi + 0x1c], eax
        mov dword ptr [edi + 0x1fc8], ebx
        mov dword ptr [edi + 0x1fcc], ecx
        mov dword ptr [edi + 0x1fd0], edx
        mov eax, dword ptr [esi + 0x10]
        mov ebx, dword ptr [esi + 0x14]
        mov ecx, dword ptr [esi + 0x18]
        mov edx, dword ptr [esi + 0x1c]
        mov dword ptr [edi + 0x3f74], eax
        mov dword ptr [edi + 0x3f78], ebx
        mov dword ptr [edi + 0x3f7c], ecx
        mov dword ptr [edi + 0x3f80], edx
        mov eax, dword ptr [esi + 0x20]
        mov ebx, dword ptr [esi + 0x24]
        mov ecx, dword ptr [esi + 0x28]
        mov edx, dword ptr [esi + 0x2c]
        mov dword ptr [edi + 0x3f84], eax
        mov dword ptr [edi + 0x5f20], ebx
        mov dword ptr [edi + 0x5f24], ecx
        mov dword ptr [edi + 0x5f28], edx
        mov eax, dword ptr [esi + 0x30]
        mov ebx, dword ptr [esi + 0x34]
        mov ecx, dword ptr [esi + 0x38]
        mov edx, dword ptr [esi + 0x3c]
        mov dword ptr [edi + 0x5f2c], eax
        mov dword ptr [edi + 0x5f30], ebx
        mov dword ptr [edi + 0x5f34], ecx
        mov dword ptr [edi + 0x5f38], edx
        mov eax, dword ptr [esi + 0x40]
        mov ebx, dword ptr [esi + 0x44]
        mov ecx, dword ptr [esi + 0x48]
        mov edx, dword ptr [esi + 0x4c]
        mov dword ptr [edi + 0x7ecc], eax
        mov dword ptr [edi + 0x7ed0], ebx
        mov dword ptr [edi + 0x7ed4], ecx
        mov dword ptr [edi + 0x7ed8], edx
        mov eax, dword ptr [esi + 0x50]
        mov ebx, dword ptr [esi + 0x54]
        mov ecx, dword ptr [esi + 0x58]
        mov edx, dword ptr [esi + 0x5c]
        mov dword ptr [edi + 0x7edc], eax
        mov dword ptr [edi + 0x7ee0], ebx
        mov dword ptr [edi + 0x7ee4], ecx
        mov dword ptr [edi + 0x7ee8], edx
        mov eax, dword ptr [esi + 0x60]
        mov ebx, dword ptr [esi + 0x64]
        mov ecx, dword ptr [esi + 0x68]
        mov edx, dword ptr [esi + 0x6c]
        mov dword ptr [edi + 0x7eec], eax
        mov dword ptr [edi + 0x9e78], ebx
        mov dword ptr [edi + 0x9e7c], ecx
        mov dword ptr [edi + 0x9e80], edx
        mov eax, dword ptr [esi + 0x70]
        mov ebx, dword ptr [esi + 0x74]
        mov ecx, dword ptr [esi + 0x78]
        mov edx, dword ptr [esi + 0x7c]
        mov dword ptr [edi + 0x9e84], eax
        mov dword ptr [edi + 0x9e88], ebx
        mov dword ptr [edi + 0x9e8c], ecx
        mov dword ptr [edi + 0x9e90], edx
        mov eax, dword ptr [esi + 0x80]
        mov ebx, dword ptr [esi + 0x84]
        mov ecx, dword ptr [esi + 0x88]
        mov edx, dword ptr [esi + 0x8c]
        mov dword ptr [edi + 0x9e94], eax
        mov dword ptr [edi + 0x9e98], ebx
        mov dword ptr [edi + 0x9e9c], ecx
        mov dword ptr [edi + 0x9ea0], edx
        mov eax, dword ptr [esi + 0x90]
        mov ebx, dword ptr [esi + 0x94]
        mov ecx, dword ptr [esi + 0x98]
        mov edx, dword ptr [esi + 0x9c]
        mov dword ptr [edi + 0xbe24], eax
        mov dword ptr [edi + 0xbe28], ebx
        mov dword ptr [edi + 0xbe2c], ecx
        mov dword ptr [edi + 0xbe30], edx
        mov eax, dword ptr [esi + 0xa0]
        mov ebx, dword ptr [esi + 0xa4]
        mov ecx, dword ptr [esi + 0xa8]
        mov edx, dword ptr [esi + 0xac]
        mov dword ptr [edi + 0xbe34], eax
        mov dword ptr [edi + 0xbe38], ebx
        mov dword ptr [edi + 0xbe3c], ecx
        mov dword ptr [edi + 0xbe40], edx
        mov eax, dword ptr [esi + 0xb0]
        mov ebx, dword ptr [esi + 0xb4]
        mov ecx, dword ptr [esi + 0xb8]
        mov edx, dword ptr [esi + 0xbc]
        mov dword ptr [edi + 0xbe44], eax
        mov dword ptr [edi + 0xbe48], ebx
        mov dword ptr [edi + 0xbe4c], ecx
        mov dword ptr [edi + 0xbe50], edx
        mov eax, dword ptr [esi + 0xc0]
        mov ebx, dword ptr [esi + 0xc4]
        mov ecx, dword ptr [esi + 0xc8]
        mov edx, dword ptr [esi + 0xcc]
        mov dword ptr [edi + 0xbe54], eax
        mov dword ptr [edi + 0xddd0], ebx
        mov dword ptr [edi + 0xddd4], ecx
        mov dword ptr [edi + 0xddd8], edx
        mov eax, dword ptr [esi + 0xd0]
        mov ebx, dword ptr [esi + 0xd4]
        mov ecx, dword ptr [esi + 0xd8]
        mov edx, dword ptr [esi + 0xdc]
        mov dword ptr [edi + 0xdddc], eax
        mov dword ptr [edi + 0xdde0], ebx
        mov dword ptr [edi + 0xdde4], ecx
        mov dword ptr [edi + 0xdde8], edx
        mov eax, dword ptr [esi + 0xe0]
        mov ebx, dword ptr [esi + 0xe4]
        mov ecx, dword ptr [esi + 0xe8]
        mov edx, dword ptr [esi + 0xec]
        mov dword ptr [edi + 0xddec], eax
        mov dword ptr [edi + 0xddf0], ebx
        mov dword ptr [edi + 0xddf4], ecx
        mov dword ptr [edi + 0xddf8], edx
        mov eax, dword ptr [esi + 0xf0]
        mov ebx, dword ptr [esi + 0xf4]
        mov ecx, dword ptr [esi + 0xf8]
        mov edx, dword ptr [esi + 0xfc]
        mov dword ptr [edi + 0xddfc], eax
        mov dword ptr [edi + 0xde00], ebx
        mov dword ptr [edi + 0xde04], ecx
        mov dword ptr [edi + 0xde08], edx
        mov eax, dword ptr [esi + 0x100]
        mov ebx, dword ptr [esi + 0x104]
        mov ecx, dword ptr [esi + 0x108]
        mov edx, dword ptr [esi + 0x10c]
        mov dword ptr [edi + 0xfd80], eax
        mov dword ptr [edi + 0xfd84], ebx
        mov dword ptr [edi + 0xfd88], ecx
        mov dword ptr [edi + 0xfd8c], edx
        mov eax, dword ptr [esi + 0x110]
        mov ebx, dword ptr [esi + 0x114]
        mov ecx, dword ptr [esi + 0x118]
        mov edx, dword ptr [esi + 0x11c]
        mov dword ptr [edi + 0xfd90], eax
        mov dword ptr [edi + 0xfd94], ebx
        mov dword ptr [edi + 0xfd98], ecx
        mov dword ptr [edi + 0xfd9c], edx
        mov eax, dword ptr [esi + 0x120]
        mov ebx, dword ptr [esi + 0x124]
        mov ecx, dword ptr [esi + 0x128]
        mov edx, dword ptr [esi + 0x12c]
        mov dword ptr [edi + 0xfda0], eax
        mov dword ptr [edi + 0xfda4], ebx
        mov dword ptr [edi + 0xfda8], ecx
        mov dword ptr [edi + 0xfdac], edx
        mov eax, dword ptr [esi + 0x130]
        mov ebx, dword ptr [esi + 0x134]
        mov ecx, dword ptr [esi + 0x138]
        mov edx, dword ptr [esi + 0x13c]
        mov dword ptr [edi + 0xfdb0], eax
        mov dword ptr [edi + 0xfdb4], ebx
        mov dword ptr [edi + 0xfdb8], ecx
        mov dword ptr [edi + 0x11d34], edx
        mov eax, dword ptr [esi + 0x140]
        mov ebx, dword ptr [esi + 0x144]
        mov ecx, dword ptr [esi + 0x148]
        mov edx, dword ptr [esi + 0x14c]
        mov dword ptr [edi + 0x11d38], eax
        mov dword ptr [edi + 0x11d3c], ebx
        mov dword ptr [edi + 0x11d40], ecx
        mov dword ptr [edi + 0x11d44], edx
        mov eax, dword ptr [esi + 0x150]
        mov ebx, dword ptr [esi + 0x154]
        mov ecx, dword ptr [esi + 0x158]
        mov edx, dword ptr [esi + 0x15c]
        mov dword ptr [edi + 0x11d48], eax
        mov dword ptr [edi + 0x11d4c], ebx
        mov dword ptr [edi + 0x11d50], ecx
        mov dword ptr [edi + 0x11d54], edx
        mov eax, dword ptr [esi + 0x160]
        mov ebx, dword ptr [esi + 0x164]
        mov ecx, dword ptr [esi + 0x168]
        mov edx, dword ptr [esi + 0x16c]
        mov dword ptr [edi + 0x11d58], eax
        mov dword ptr [edi + 0x11d5c], ebx
        mov dword ptr [edi + 0x11d60], ecx
        mov dword ptr [edi + 0x11d64], edx
        mov eax, dword ptr [esi + 0x170]
        mov ebx, dword ptr [esi + 0x174]
        mov ecx, dword ptr [esi + 0x178]
        mov edx, dword ptr [esi + 0x17c]
        mov dword ptr [edi + 0x13ce8], eax
        mov dword ptr [edi + 0x13cec], ebx
        mov dword ptr [edi + 0x13cf0], ecx
        mov dword ptr [edi + 0x13cf4], edx
        mov eax, dword ptr [esi + 0x180]
        mov ebx, dword ptr [esi + 0x184]
        mov ecx, dword ptr [esi + 0x188]
        mov edx, dword ptr [esi + 0x18c]
        mov dword ptr [edi + 0x13cf8], eax
        mov dword ptr [edi + 0x13cfc], ebx
        mov dword ptr [edi + 0x13d00], ecx
        mov dword ptr [edi + 0x13d04], edx
        mov eax, dword ptr [esi + 0x190]
        mov ebx, dword ptr [esi + 0x194]
        mov ecx, dword ptr [esi + 0x198]
        mov edx, dword ptr [esi + 0x19c]
        mov dword ptr [edi + 0x13d08], eax
        mov dword ptr [edi + 0x13d0c], ebx
        mov dword ptr [edi + 0x13d10], ecx
        mov dword ptr [edi + 0x15c9c], edx
        mov eax, dword ptr [esi + 0x1a0]
        mov ebx, dword ptr [esi + 0x1a4]
        mov ecx, dword ptr [esi + 0x1a8]
        mov edx, dword ptr [esi + 0x1ac]
        mov dword ptr [edi + 0x15ca0], eax
        mov dword ptr [edi + 0x15ca4], ebx
        mov dword ptr [edi + 0x15ca8], ecx
        mov dword ptr [edi + 0x15cac], edx
        mov eax, dword ptr [esi + 0x1b0]
        mov ebx, dword ptr [esi + 0x1b4]
        mov ecx, dword ptr [esi + 0x1b8]
        mov edx, dword ptr [esi + 0x1bc]
        mov dword ptr [edi + 0x15cb0], eax
        mov dword ptr [edi + 0x15cb4], ebx
        mov dword ptr [edi + 0x15cb8], ecx
        mov dword ptr [edi + 0x15cbc], edx
        mov eax, dword ptr [esi + 0x1c0]
        mov ebx, dword ptr [esi + 0x1c4]
        mov ecx, dword ptr [esi + 0x1c8]
        mov edx, dword ptr [esi + 0x1cc]
        mov dword ptr [edi + 0x17c50], eax
        mov dword ptr [edi + 0x17c54], ebx
        mov dword ptr [edi + 0x17c58], ecx
        mov dword ptr [edi + 0x17c5c], edx
        mov eax, dword ptr [esi + 0x1d0]
        mov ebx, dword ptr [esi + 0x1d4]
        mov ecx, dword ptr [esi + 0x1d8]
        mov edx, dword ptr [esi + 0x1dc]
        mov dword ptr [edi + 0x17c60], eax
        mov dword ptr [edi + 0x17c64], ebx
        mov dword ptr [edi + 0x17c68], ecx
        mov dword ptr [edi + 0x19c04], edx
        mov eax, dword ptr [esi + 0x1e0]
        mov ebx, dword ptr [esi + 0x1e4]
        mov ecx, dword ptr [esi + 0x1e8]
        mov edx, dword ptr [esi + 0x1ec]
        mov dword ptr [edi + 0x19c08], eax
        mov dword ptr [edi + 0x19c0c], ebx
        mov dword ptr [edi + 0x19c10], ecx
        mov dword ptr [edi + 0x19c14], edx
        mov eax, dword ptr [esi + 0x1f0]
        mov ebx, dword ptr [esi + 0x1f4]
        mov ecx, dword ptr [esi + 0x1f8]
        mov edx, dword ptr [esi + 0x1fc]
        mov dword ptr [edi + 0x1bbb8], eax
        mov dword ptr [edi + 0x1bbbc], ebx
        mov dword ptr [edi + 0x1bbc0], ecx
        mov dword ptr [edi + 0x1db6c], edx
            }
            // clang-format on
            return;
        }
        // clang-format off
        __asm {
        mov esi, source
        mov ecx, s_windowAndDirectDraw
        mov edi, dword ptr [ecx]WindowAndDirectDraw.surfacePointer_mapGame
        mov eax, s_drawSomeX
        mov eax, dword ptr [eax]
        and eax, 0xfffffffe
        add edi, eax
        mov eax, drawY
        mov ebx, eax
        shr eax, 1
        mov edx, 0x1fb0
        mul edx
        add edi, eax
        mov dword ptr [ecx]WindowAndDirectDraw.unknownSpecificPointer, edi
        and ebx, 1
        cmp ebx, 0
        jne zm_4532a7
        mov ax, word ptr [esi]
        mov word ptr [edi + 0xe], ax
        mov ax, word ptr [esi + 0x10]
        mov bx, word ptr [esi + 0x14]
        mov cx, word ptr [esi + 0x18]
        mov dx, word ptr [esi + 0x1c]
        mov word ptr [edi + 0x1fba], ax
        mov word ptr [edi + 0x1fbc], bx
        mov word ptr [edi + 0x1fbe], cx
        mov word ptr [edi + 0x1fc0], dx
        mov ax, word ptr [esi + 0x20]
        mov word ptr [edi + 0x1fc2], ax
        mov ax, word ptr [esi + 0x40]
        mov bx, word ptr [esi + 0x44]
        mov cx, word ptr [esi + 0x48]
        mov dx, word ptr [esi + 0x4c]
        mov word ptr [edi + 0x3f66], ax
        mov word ptr [edi + 0x3f68], bx
        mov word ptr [edi + 0x3f6a], cx
        mov word ptr [edi + 0x3f6c], dx
        mov ax, word ptr [esi + 0x50]
        mov bx, word ptr [esi + 0x54]
        mov cx, word ptr [esi + 0x58]
        mov dx, word ptr [esi + 0x5c]
        mov word ptr [edi + 0x3f6e], ax
        mov word ptr [edi + 0x3f70], bx
        mov word ptr [edi + 0x3f72], cx
        mov word ptr [edi + 0x3f74], dx
        mov ax, word ptr [esi + 0x60]
        mov word ptr [edi + 0x3f76], ax
        mov ax, word ptr [esi + 0x90]
        mov bx, word ptr [esi + 0x94]
        mov cx, word ptr [esi + 0x98]
        mov dx, word ptr [esi + 0x9c]
        mov word ptr [edi + 0x5f12], ax
        mov word ptr [edi + 0x5f14], bx
        mov word ptr [edi + 0x5f16], cx
        mov word ptr [edi + 0x5f18], dx
        mov ax, word ptr [esi + 0xa0]
        mov bx, word ptr [esi + 0xa4]
        mov cx, word ptr [esi + 0xa8]
        mov dx, word ptr [esi + 0xac]
        mov word ptr [edi + 0x5f1a], ax
        mov word ptr [edi + 0x5f1c], bx
        mov word ptr [edi + 0x5f1e], cx
        mov word ptr [edi + 0x5f20], dx
        mov ax, word ptr [esi + 0xb0]
        mov bx, word ptr [esi + 0xb4]
        mov cx, word ptr [esi + 0xb8]
        mov dx, word ptr [esi + 0xbc]
        mov word ptr [edi + 0x5f22], ax
        mov word ptr [edi + 0x5f24], bx
        mov word ptr [edi + 0x5f26], cx
        mov word ptr [edi + 0x5f28], dx
        mov ax, word ptr [esi + 0xc0]
        mov word ptr [edi + 0x5f2a], ax
        mov ax, word ptr [esi + 0x100]
        mov bx, word ptr [esi + 0x104]
        mov cx, word ptr [esi + 0x108]
        mov dx, word ptr [esi + 0x10c]
        mov word ptr [edi + 0x7ec0], ax
        mov word ptr [edi + 0x7ec2], bx
        mov word ptr [edi + 0x7ec4], cx
        mov word ptr [edi + 0x7ec6], dx
        mov ax, word ptr [esi + 0x110]
        mov bx, word ptr [esi + 0x114]
        mov cx, word ptr [esi + 0x118]
        mov dx, word ptr [esi + 0x11c]
        mov word ptr [edi + 0x7ec8], ax
        mov word ptr [edi + 0x7eca], bx
        mov word ptr [edi + 0x7ecc], cx
        mov word ptr [edi + 0x7ece], dx
        mov ax, word ptr [esi + 0x120]
        mov bx, word ptr [esi + 0x124]
        mov cx, word ptr [esi + 0x128]
        mov dx, word ptr [esi + 0x12c]
        mov word ptr [edi + 0x7ed0], ax
        mov word ptr [edi + 0x7ed2], bx
        mov word ptr [edi + 0x7ed4], cx
        mov word ptr [edi + 0x7ed6], dx
        mov ax, word ptr [esi + 0x130]
        mov bx, word ptr [esi + 0x134]
        mov cx, word ptr [esi + 0x138]
        mov word ptr [edi + 0x7ed8], ax
        mov word ptr [edi + 0x7eda], bx
        mov word ptr [edi + 0x7edc], cx
        mov ax, word ptr [esi + 0x170]
        mov bx, word ptr [esi + 0x174]
        mov cx, word ptr [esi + 0x178]
        mov dx, word ptr [esi + 0x17c]
        mov word ptr [edi + 0x9e74], ax
        mov word ptr [edi + 0x9e76], bx
        mov word ptr [edi + 0x9e78], cx
        mov word ptr [edi + 0x9e7a], dx
        mov ax, word ptr [esi + 0x180]
        mov bx, word ptr [esi + 0x184]
        mov cx, word ptr [esi + 0x188]
        mov dx, word ptr [esi + 0x18c]
        mov word ptr [edi + 0x9e7c], ax
        mov word ptr [edi + 0x9e7e], bx
        mov word ptr [edi + 0x9e80], cx
        mov word ptr [edi + 0x9e82], dx
        mov ax, word ptr [esi + 0x190]
        mov bx, word ptr [esi + 0x194]
        mov cx, word ptr [esi + 0x198]
        mov word ptr [edi + 0x9e84], ax
        mov word ptr [edi + 0x9e86], bx
        mov word ptr [edi + 0x9e88], cx
        mov ax, word ptr [esi + 0x1c0]
        mov bx, word ptr [esi + 0x1c4]
        mov cx, word ptr [esi + 0x1c8]
        mov dx, word ptr [esi + 0x1cc]
        mov word ptr [edi + 0xbe28], ax
        mov word ptr [edi + 0xbe2a], bx
        mov word ptr [edi + 0xbe2c], cx
        mov word ptr [edi + 0xbe2e], dx
        mov ax, word ptr [esi + 0x1d0]
        mov bx, word ptr [esi + 0x1d4]
        mov cx, word ptr [esi + 0x1d8]
        mov word ptr [edi + 0xbe30], ax
        mov word ptr [edi + 0xbe32], bx
        mov word ptr [edi + 0xbe34], cx
        mov ax, word ptr [esi + 0x1f0]
        mov bx, word ptr [esi + 0x1f4]
        mov cx, word ptr [esi + 0x1f8]
        mov word ptr [edi + 0xdddc], ax
        mov word ptr [edi + 0xddde], bx
        mov word ptr [edi + 0xdde0], cx
        jmp zm_4535f4
zm_4532a7:
        mov bx, word ptr [esi + 4]
        mov cx, word ptr [esi + 8]
        mov dx, word ptr [esi + 0xc]
        mov word ptr [edi + 0x1fbc], bx
        mov word ptr [edi + 0x1fbe], cx
        mov word ptr [edi + 0x1fc0], dx
        mov bx, word ptr [esi + 0x24]
        mov cx, word ptr [esi + 0x28]
        mov dx, word ptr [esi + 0x2c]
        mov word ptr [edi + 0x3f68], bx
        mov word ptr [edi + 0x3f6a], cx
        mov word ptr [edi + 0x3f6c], dx
        mov ax, word ptr [esi + 0x30]
        mov bx, word ptr [esi + 0x34]
        mov cx, word ptr [esi + 0x38]
        mov dx, word ptr [esi + 0x3c]
        mov word ptr [edi + 0x3f6e], ax
        mov word ptr [edi + 0x3f70], bx
        mov word ptr [edi + 0x3f72], cx
        mov word ptr [edi + 0x3f74], dx
        mov bx, word ptr [esi + 0x64]
        mov cx, word ptr [esi + 0x68]
        mov dx, word ptr [esi + 0x6c]
        mov word ptr [edi + 0x5f14], bx
        mov word ptr [edi + 0x5f16], cx
        mov word ptr [edi + 0x5f18], dx
        mov ax, word ptr [esi + 0x70]
        mov bx, word ptr [esi + 0x74]
        mov cx, word ptr [esi + 0x78]
        mov dx, word ptr [esi + 0x7c]
        mov word ptr [edi + 0x5f1a], ax
        mov word ptr [edi + 0x5f1c], bx
        mov word ptr [edi + 0x5f1e], cx
        mov word ptr [edi + 0x5f20], dx
        mov ax, word ptr [esi + 0x80]
        mov bx, word ptr [esi + 0x84]
        mov cx, word ptr [esi + 0x88]
        mov dx, word ptr [esi + 0x8c]
        mov word ptr [edi + 0x5f22], ax
        mov word ptr [edi + 0x5f24], bx
        mov word ptr [edi + 0x5f26], cx
        mov word ptr [edi + 0x5f28], dx
        mov bx, word ptr [esi + 0xc4]
        mov cx, word ptr [esi + 0xc8]
        mov dx, word ptr [esi + 0xcc]
        mov word ptr [edi + 0x7ec0], bx
        mov word ptr [edi + 0x7ec2], cx
        mov word ptr [edi + 0x7ec4], dx
        mov ax, word ptr [esi + 0xd0]
        mov bx, word ptr [esi + 0xd4]
        mov cx, word ptr [esi + 0xd8]
        mov dx, word ptr [esi + 0xdc]
        mov word ptr [edi + 0x7ec6], ax
        mov word ptr [edi + 0x7ec8], bx
        mov word ptr [edi + 0x7eca], cx
        mov word ptr [edi + 0x7ecc], dx
        mov ax, word ptr [esi + 0xe0]
        mov bx, word ptr [esi + 0xe4]
        mov cx, word ptr [esi + 0xe8]
        mov dx, word ptr [esi + 0xec]
        mov word ptr [edi + 0x7ece], ax
        mov word ptr [edi + 0x7ed0], bx
        mov word ptr [edi + 0x7ed2], cx
        mov word ptr [edi + 0x7ed4], dx
        mov ax, word ptr [esi + 0xf0]
        mov bx, word ptr [esi + 0xf4]
        mov cx, word ptr [esi + 0xf8]
        mov dx, word ptr [esi + 0xfc]
        mov word ptr [edi + 0x7ed6], ax
        mov word ptr [edi + 0x7ed8], bx
        mov word ptr [edi + 0x7eda], cx
        mov word ptr [edi + 0x7edc], dx
        mov dx, word ptr [esi + 0x13c]
        mov word ptr [edi + 0x9e72], dx
        mov ax, word ptr [esi + 0x140]
        mov bx, word ptr [esi + 0x144]
        mov cx, word ptr [esi + 0x148]
        mov dx, word ptr [esi + 0x14c]
        mov word ptr [edi + 0x9e74], ax
        mov word ptr [edi + 0x9e76], bx
        mov word ptr [edi + 0x9e78], cx
        mov word ptr [edi + 0x9e7a], dx
        mov ax, word ptr [esi + 0x150]
        mov bx, word ptr [esi + 0x154]
        mov cx, word ptr [esi + 0x158]
        mov dx, word ptr [esi + 0x15c]
        mov word ptr [edi + 0x9e7c], ax
        mov word ptr [edi + 0x9e7e], bx
        mov word ptr [edi + 0x9e80], cx
        mov word ptr [edi + 0x9e82], dx
        mov ax, word ptr [esi + 0x160]
        mov bx, word ptr [esi + 0x164]
        mov cx, word ptr [esi + 0x168]
        mov dx, word ptr [esi + 0x16c]
        mov word ptr [edi + 0x9e84], ax
        mov word ptr [edi + 0x9e86], bx
        mov word ptr [edi + 0x9e88], cx
        mov word ptr [edi + 0x9e8a], dx
        mov dx, word ptr [esi + 0x19c]
        mov word ptr [edi + 0xbe26], dx
        mov ax, word ptr [esi + 0x1a0]
        mov bx, word ptr [esi + 0x1a4]
        mov cx, word ptr [esi + 0x1a8]
        mov dx, word ptr [esi + 0x1ac]
        mov word ptr [edi + 0xbe28], ax
        mov word ptr [edi + 0xbe2a], bx
        mov word ptr [edi + 0xbe2c], cx
        mov word ptr [edi + 0xbe2e], dx
        mov ax, word ptr [esi + 0x1b0]
        mov bx, word ptr [esi + 0x1b4]
        mov cx, word ptr [esi + 0x1b8]
        mov dx, word ptr [esi + 0x1bc]
        mov word ptr [edi + 0xbe30], ax
        mov word ptr [edi + 0xbe32], bx
        mov word ptr [edi + 0xbe34], cx
        mov word ptr [edi + 0xbe36], dx
        mov dx, word ptr [esi + 0x1dc]
        mov word ptr [edi + 0xddda], dx
        mov ax, word ptr [esi + 0x1e0]
        mov bx, word ptr [esi + 0x1e4]
        mov cx, word ptr [esi + 0x1e8]
        mov dx, word ptr [esi + 0x1ec]
        mov word ptr [edi + 0xdddc], ax
        mov word ptr [edi + 0xddde], bx
        mov word ptr [edi + 0xdde0], cx
        mov word ptr [edi + 0xdde2], dx
        mov dx, word ptr [esi + 0x1fc]
        mov word ptr [edi + 0xfd8e], dx
zm_4535f4:
        }
        // clang-format on
    }

}
}
