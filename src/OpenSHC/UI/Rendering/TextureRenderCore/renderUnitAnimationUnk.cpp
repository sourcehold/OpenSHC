#include "OpenSHC/IO/Graphics/TgxTokenByte.hpp"
#include "OpenSHC/Rendering/BlendingDefinedData.hpp"
#include "OpenSHC/Rendering/Enums/RenderTargetInt.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.hpp"

#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_CurrentlyRenderedSpriteID.hpp"
#include "OpenSHC/Globals/DAT_RenderedUnitOwner.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/PTR_ARRAY_00c9a490.hpp"
#include "OpenSHC/Globals/PTR_ARRAY_Unknown_UnitGMHeights.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // These must exist even if not used, otherwise the instances don't even exist...
        void* const* const _PTR_ARRAY_00c9a490 = &PTR_ARRAY_00c9a490::instance[0];
        void* const* const _PTR_ARRAY_Unknown_UnitGMHeights = &PTR_ARRAY_Unknown_UnitGMHeights::instance[0];

        undefined4* const RenderedUnitOwner = &DAT_RenderedUnitOwner::instance;
        undefined4* const CurrentlyRenderedSpriteID = &DAT_CurrentlyRenderedSpriteID::instance;
        int* const PlayerSlotUnitColor = &DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[0];
        ushort* const surfacePointer_mapGame = &DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame[0];
        ushort* const surfacePointer_screenMenu = &DAT_WindowAndDirectDraw::instance.surfacePointer_screenMenu[0];
        int* const isZoom2 = &DAT_TextureRenderCoreObject::instance.isZoom2;
        ushort* const currentRenderSurface = &DAT_TextureRenderCoreObject::instance.currentRenderSurface[0];
        int* const byteSizeOfOneHorizontalLine = &DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine;

        // FUNCTION: STRONGHOLDCRUSADER 0x0044fbf0
        __declspec(naked) void TextureRenderCore::renderUnitAnimationUnk(
            int xPosition, int yPosition, int width, int height, byte* imageAddress)
        {

            __asm {
    push ebp
    mov ebp,esp
    sub esp,0x28
    push ebx
    push esi
    push edi
    mov dword ptr [ebp-0x28],ecx
    mov dword ptr [ebp-0xc],offset PTR_ARRAY_00c9a490::instance
    mov dword ptr [ebp-0x18],offset PTR_ARRAY_Unknown_UnitGMHeights::instance
    cmp dword ptr [ebp+0x14],0
    jg L44fc15
    jmp Lexit
  L44fc15:
    cmp dword ptr [DAT_RenderedUnitOwner::instance],1
    jnz L44fc2a
    mov dword ptr [DAT_RenderedUnitOwner::instance],4
    jmp L44fc3d
  L44fc2a:
    cmp dword ptr [DAT_RenderedUnitOwner::instance],4
    jnz L44fc3d
    mov dword ptr [DAT_RenderedUnitOwner::instance],1
  L44fc3d:
    mov eax,dword ptr [ebp-0x28]
    cmp dword ptr [eax+0x10],0
    jz L44fc6e
    mov ecx,dword ptr [DAT_CurrentlyRenderedSpriteID::instance]
    imul ecx,ecx,0x1458
    mov edx,dword ptr [ebp-0x28]
    lea eax,[edx+ecx+0x51c]
    mov ecx,dword ptr [DAT_RenderedUnitOwner::instance]
    shl ecx,8
    lea edx,[eax+ecx*2+0x58]
    mov dword ptr [ebp-4],edx
    jmp L44fc99
  L44fc6e:
    mov eax,dword ptr [DAT_CurrentlyRenderedSpriteID::instance]
    imul eax,eax,0x1458
    mov ecx,dword ptr [ebp-0x28]
    lea edx,[ecx+eax+0x51c]
    mov eax,dword ptr [DAT_RenderedUnitOwner::instance]
    mov ecx,dword ptr [eax*4+DAT_BlendingDefinedData::instance.PlayerSlotUnitColor]
    shl ecx,8
    lea edx,[edx+ecx*2+0x58]
    mov dword ptr [ebp-4],edx
  L44fc99:
    mov eax,dword ptr [ebp-0x28]
    cmp dword ptr [eax+0x70],0
    jz L44fcab
    mov ecx,dword ptr [ebp-0x28]
    mov edx,dword ptr [ecx+0x70]
    mov dword ptr [ebp-4],edx
  L44fcab:
    cmp dword ptr [DAT_TextureRenderCoreObject::instance.isZoom2],0
    jnz Lzoom2
    mov eax,dword ptr [ebp-0x28]
    cmp dword ptr [eax+4],0
    jz L44fcef
    mov ecx,dword ptr [DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame]
    mov dword ptr [DAT_TextureRenderCoreObject::instance.currentRenderSurface],ecx
    mov dword ptr [ebp-0x1c],0x1fb0
    mov dword ptr [ebp-0x10],0x1fb0
    mov edx,dword ptr [ebp-0x28]
    mov eax,dword ptr [edx+0x58]
    mov dword ptr [ebp-0x14],eax
    mov ecx,dword ptr [ebp-0x28]
    mov edx,dword ptr [ecx+0x5c]
    mov dword ptr [ebp-8],edx
    jmp L44fd1d
  L44fcef:
    mov eax,dword ptr [DAT_WindowAndDirectDraw::instance.surfacePointer_screenMenu]
    mov dword ptr [DAT_TextureRenderCoreObject::instance.currentRenderSurface],eax
    mov ecx,dword ptr [DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine]
    mov dword ptr [ebp-0x1c],ecx
    mov edx,dword ptr [DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine]
    mov dword ptr [ebp-0x10],edx
    mov eax,dword ptr [ebp-0x28]
    mov ecx,dword ptr [eax+0x60]
    mov dword ptr [ebp-0x14],ecx
    mov edx,dword ptr [ebp-0x28]
    mov eax,dword ptr [edx+0x64]
    mov dword ptr [ebp-8],eax
  L44fd1d:
    mov ecx,dword ptr [ebp+0xc]
    add ecx,dword ptr [ebp+0x14]
    cmp ecx,dword ptr [ebp-8]
    jle L44fd44
    mov edx,dword ptr [ebp+0xc]
    add edx,dword ptr [ebp+0x14]
    sub edx,dword ptr [ebp-8]
    mov eax,dword ptr [ebp+0x14]
    sub eax,edx
    mov dword ptr [ebp+0x14],eax
    cmp dword ptr [ebp+0x14],0
    jg L44fd44
    jmp Lexit
  L44fd44:
    mov edi,dword ptr [ebp-0xc]
    mov eax,0
    cmp dword ptr [edi],eax
    jz Linit
  L44fd54:
    mov esi,dword ptr [ebp+0x18]
    mov edi,dword ptr [DAT_TextureRenderCoreObject::instance.currentRenderSurface]
    mov eax,dword ptr [ebp+8]
    cmp eax,0
    jl Lc2e
    add eax,eax
    add edi,eax
    mov eax,dword ptr [ebp+0xc]
    mov ebx,dword ptr [ebp-0x14]
    cmp eax,ebx
    jge L44fdc1
    sub ebx,eax
    mov eax,ebx
    cmp dword ptr [ebp+0x14],eax
    jle Lc2e
    sub dword ptr [ebp+0x14],eax
  L44fd87:
    mov ecx,0
    mov bl,byte ptr [esi]
    mov cl,byte ptr [esi]
    and bl,0xe0
    and cl,0x1f
    add esi,1
    cmp bl,0x20
    jz L44fd87
    cmp bl,0
    jz L44fdaa
    cmp bl,0x40
    jz L44fdb1
    jmp L44fdb6
  L44fdaa:
    add ecx,1
    add esi,ecx
    jmp L44fd87
  L44fdb1:
    add esi,1
    jmp L44fd87
  L44fdb6:
    sub eax,1
    cmp eax,0
    jg L44fd87
    mov eax,dword ptr [ebp-0x14]
  L44fdc1:
    mov edx,dword ptr [ebp-0x10]
    mul edx
    add edi,eax
    mov edx,dword ptr [ebp-4]
  Lmainpush:
    push edi
  Lmain:
    mov ecx,0
    mov al,byte ptr [esi]
    mov cl,byte ptr [esi]
    and al,0xe0
    and cl,0x1f
    add esi,1
    cmp al,0x20
    jz L44fdfc
    cmp al,0
    jz L44fe27
    cmp al,0x40
    jz L44fe05
    pop edi
    add edi,dword ptr [ebp-0x1c]
    sub dword ptr [ebp+0x14],1
    cmp dword ptr [ebp+0x14],0
    jg Lmainpush
    jmp Lc2e
  L44fdfc:
    add ecx,1
    add ecx,ecx
    add edi,ecx
    jmp Lmain
  L44fe05:
    mov ebx,0
    mov eax,0
    mov bl,byte ptr [esi]
    mov ax,word ptr [edx+ebx*2]
    mov bx,ax
    shl ebx,0x10
    add eax,ebx
    add esi,1
    jmp dword ptr [ecx*4+PTR_ARRAY_00c9a490::instance]
  L44fe27:
    mov ebx,0
    mov eax,0
    jmp dword ptr [ecx*4+PTR_ARRAY_Unknown_UnitGMHeights::instance]
  lit1:
    mov al,byte ptr [esi]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi],cx
    add esi,1
    add edi,2
    jmp Lmain
  lit2:
    mov al,byte ptr [esi]
    mov bl,byte ptr [esi+1]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi],cx
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+2],cx
    add esi,2
    add edi,4
    jmp Lmain
  lit3:
    mov al,byte ptr [esi]
    mov bl,byte ptr [esi+1]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi],cx
    mov al,byte ptr [esi+2]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+2],cx
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+4],cx
    add esi,3
    add edi,6
    jmp Lmain
  lit4:
    mov al,byte ptr [esi]
    mov bl,byte ptr [esi+1]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi],cx
    mov al,byte ptr [esi+2]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+2],cx
    mov bl,byte ptr [esi+3]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+4],cx
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+6],cx
    add esi,4
    add edi,8
    jmp Lmain
  lit5:
    mov al,byte ptr [esi]
    mov bl,byte ptr [esi+1]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi],cx
    mov al,byte ptr [esi+2]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+2],cx
    mov bl,byte ptr [esi+3]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+4],cx
    mov al,byte ptr [esi+4]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+6],cx
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+8],cx
    add esi,5
    add edi,0xa
    jmp Lmain
  lit6:
    mov al,byte ptr [esi]
    mov bl,byte ptr [esi+1]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi],cx
    mov al,byte ptr [esi+2]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+2],cx
    mov bl,byte ptr [esi+3]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+4],cx
    mov al,byte ptr [esi+4]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+6],cx
    mov bl,byte ptr [esi+5]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+8],cx
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xa],cx
    add esi,6
    add edi,0xc
    jmp Lmain
  lit7:
    mov al,byte ptr [esi]
    mov bl,byte ptr [esi+1]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi],cx
    mov al,byte ptr [esi+2]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+2],cx
    mov bl,byte ptr [esi+3]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+4],cx
    mov al,byte ptr [esi+4]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+6],cx
    mov bl,byte ptr [esi+5]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+8],cx
    mov al,byte ptr [esi+6]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xa],cx
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0xc],cx
    add esi,7
    add edi,0xe
    jmp Lmain
  lit8:
    mov al,byte ptr [esi]
    mov bl,byte ptr [esi+1]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi],cx
    mov al,byte ptr [esi+2]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+2],cx
    mov bl,byte ptr [esi+3]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+4],cx
    mov al,byte ptr [esi+4]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+6],cx
    mov bl,byte ptr [esi+5]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+8],cx
    mov al,byte ptr [esi+6]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xa],cx
    mov bl,byte ptr [esi+7]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0xc],cx
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xe],cx
    add esi,8
    add edi,0x10
    jmp Lmain
  lit9:
    mov al,byte ptr [esi]
    mov bl,byte ptr [esi+1]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi],cx
    mov al,byte ptr [esi+2]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+2],cx
    mov bl,byte ptr [esi+3]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+4],cx
    mov al,byte ptr [esi+4]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+6],cx
    mov bl,byte ptr [esi+5]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+8],cx
    mov al,byte ptr [esi+6]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xa],cx
    mov bl,byte ptr [esi+7]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0xc],cx
    mov al,byte ptr [esi+8]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xe],cx
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x10],cx
    add esi,9
    add edi,0x12
    jmp Lmain
  lit10:
    mov al,byte ptr [esi]
    mov bl,byte ptr [esi+1]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi],cx
    mov al,byte ptr [esi+2]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+2],cx
    mov bl,byte ptr [esi+3]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+4],cx
    mov al,byte ptr [esi+4]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+6],cx
    mov bl,byte ptr [esi+5]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+8],cx
    mov al,byte ptr [esi+6]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xa],cx
    mov bl,byte ptr [esi+7]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0xc],cx
    mov al,byte ptr [esi+8]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xe],cx
    mov bl,byte ptr [esi+9]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x10],cx
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x12],cx
    add esi,0xa
    add edi,0x14
    jmp Lmain
  lit11:
    mov al,byte ptr [esi]
    mov bl,byte ptr [esi+1]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi],cx
    mov al,byte ptr [esi+2]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+2],cx
    mov bl,byte ptr [esi+3]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+4],cx
    mov al,byte ptr [esi+4]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+6],cx
    mov bl,byte ptr [esi+5]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+8],cx
    mov al,byte ptr [esi+6]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xa],cx
    mov bl,byte ptr [esi+7]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0xc],cx
    mov al,byte ptr [esi+8]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xe],cx
    mov bl,byte ptr [esi+9]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x10],cx
    mov al,byte ptr [esi+0xa]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x12],cx
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x14],cx
    add esi,0xb
    add edi,0x16
    jmp Lmain
  lit12:
    mov al,byte ptr [esi]
    mov bl,byte ptr [esi+1]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi],cx
    mov al,byte ptr [esi+2]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+2],cx
    mov bl,byte ptr [esi+3]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+4],cx
    mov al,byte ptr [esi+4]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+6],cx
    mov bl,byte ptr [esi+5]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+8],cx
    mov al,byte ptr [esi+6]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xa],cx
    mov bl,byte ptr [esi+7]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0xc],cx
    mov al,byte ptr [esi+8]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xe],cx
    mov bl,byte ptr [esi+9]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x10],cx
    mov al,byte ptr [esi+0xa]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x12],cx
    mov bl,byte ptr [esi+0xb]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x14],cx
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x16],cx
    add esi,0xc
    add edi,0x18
    jmp Lmain
  lit13:
    mov al,byte ptr [esi]
    mov bl,byte ptr [esi+1]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi],cx
    mov al,byte ptr [esi+2]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+2],cx
    mov bl,byte ptr [esi+3]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+4],cx
    mov al,byte ptr [esi+4]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+6],cx
    mov bl,byte ptr [esi+5]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+8],cx
    mov al,byte ptr [esi+6]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xa],cx
    mov bl,byte ptr [esi+7]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0xc],cx
    mov al,byte ptr [esi+8]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xe],cx
    mov bl,byte ptr [esi+9]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x10],cx
    mov al,byte ptr [esi+0xa]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x12],cx
    mov bl,byte ptr [esi+0xb]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x14],cx
    mov al,byte ptr [esi+0xc]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x16],cx
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x18],cx
    add esi,0xd
    add edi,0x1a
    jmp Lmain
  lit14:
    mov al,byte ptr [esi]
    mov bl,byte ptr [esi+1]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi],cx
    mov al,byte ptr [esi+2]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+2],cx
    mov bl,byte ptr [esi+3]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+4],cx
    mov al,byte ptr [esi+4]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+6],cx
    mov bl,byte ptr [esi+5]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+8],cx
    mov al,byte ptr [esi+6]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xa],cx
    mov bl,byte ptr [esi+7]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0xc],cx
    mov al,byte ptr [esi+8]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xe],cx
    mov bl,byte ptr [esi+9]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x10],cx
    mov al,byte ptr [esi+0xa]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x12],cx
    mov bl,byte ptr [esi+0xb]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x14],cx
    mov al,byte ptr [esi+0xc]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x16],cx
    mov bl,byte ptr [esi+0xd]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x18],cx
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x1a],cx
    add esi,0xe
    add edi,0x1c
    jmp Lmain
  lit15:
    mov al,byte ptr [esi]
    mov bl,byte ptr [esi+1]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi],cx
    mov al,byte ptr [esi+2]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+2],cx
    mov bl,byte ptr [esi+3]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+4],cx
    mov al,byte ptr [esi+4]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+6],cx
    mov bl,byte ptr [esi+5]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+8],cx
    mov al,byte ptr [esi+6]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xa],cx
    mov bl,byte ptr [esi+7]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0xc],cx
    mov al,byte ptr [esi+8]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xe],cx
    mov bl,byte ptr [esi+9]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x10],cx
    mov al,byte ptr [esi+0xa]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x12],cx
    mov bl,byte ptr [esi+0xb]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x14],cx
    mov al,byte ptr [esi+0xc]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x16],cx
    mov bl,byte ptr [esi+0xd]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x18],cx
    mov al,byte ptr [esi+0xe]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x1a],cx
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x1c],cx
    add esi,0xf
    add edi,0x1e
    jmp Lmain
  lit16:
    mov al,byte ptr [esi]
    mov bl,byte ptr [esi+1]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi],cx
    mov al,byte ptr [esi+2]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+2],cx
    mov bl,byte ptr [esi+3]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+4],cx
    mov al,byte ptr [esi+4]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+6],cx
    mov bl,byte ptr [esi+5]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+8],cx
    mov al,byte ptr [esi+6]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xa],cx
    mov bl,byte ptr [esi+7]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0xc],cx
    mov al,byte ptr [esi+8]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xe],cx
    mov bl,byte ptr [esi+9]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x10],cx
    mov al,byte ptr [esi+0xa]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x12],cx
    mov bl,byte ptr [esi+0xb]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x14],cx
    mov al,byte ptr [esi+0xc]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x16],cx
    mov bl,byte ptr [esi+0xd]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x18],cx
    mov al,byte ptr [esi+0xe]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x1a],cx
    mov bl,byte ptr [esi+0xf]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x1c],cx
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x1e],cx
    add esi,0x10
    add edi,0x20
    jmp Lmain
  lit17:
    mov al,byte ptr [esi]
    mov bl,byte ptr [esi+1]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi],cx
    mov al,byte ptr [esi+2]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+2],cx
    mov bl,byte ptr [esi+3]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+4],cx
    mov al,byte ptr [esi+4]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+6],cx
    mov bl,byte ptr [esi+5]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+8],cx
    mov al,byte ptr [esi+6]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xa],cx
    mov bl,byte ptr [esi+7]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0xc],cx
    mov al,byte ptr [esi+8]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xe],cx
    mov bl,byte ptr [esi+9]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x10],cx
    mov al,byte ptr [esi+0xa]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x12],cx
    mov bl,byte ptr [esi+0xb]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x14],cx
    mov al,byte ptr [esi+0xc]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x16],cx
    mov bl,byte ptr [esi+0xd]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x18],cx
    mov al,byte ptr [esi+0xe]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x1a],cx
    mov bl,byte ptr [esi+0xf]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x1c],cx
    mov al,byte ptr [esi+0x10]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x1e],cx
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x20],cx
    add esi,0x11
    add edi,0x22
    jmp Lmain
  lit18:
    mov al,byte ptr [esi]
    mov bl,byte ptr [esi+1]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi],cx
    mov al,byte ptr [esi+2]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+2],cx
    mov bl,byte ptr [esi+3]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+4],cx
    mov al,byte ptr [esi+4]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+6],cx
    mov bl,byte ptr [esi+5]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+8],cx
    mov al,byte ptr [esi+6]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xa],cx
    mov bl,byte ptr [esi+7]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0xc],cx
    mov al,byte ptr [esi+8]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xe],cx
    mov bl,byte ptr [esi+9]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x10],cx
    mov al,byte ptr [esi+0xa]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x12],cx
    mov bl,byte ptr [esi+0xb]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x14],cx
    mov al,byte ptr [esi+0xc]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x16],cx
    mov bl,byte ptr [esi+0xd]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x18],cx
    mov al,byte ptr [esi+0xe]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x1a],cx
    mov bl,byte ptr [esi+0xf]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x1c],cx
    mov al,byte ptr [esi+0x10]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x1e],cx
    mov bl,byte ptr [esi+0x11]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x20],cx
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x22],cx
    add esi,0x12
    add edi,0x24
    jmp Lmain
  lit19:
    mov al,byte ptr [esi]
    mov bl,byte ptr [esi+1]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi],cx
    mov al,byte ptr [esi+2]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+2],cx
    mov bl,byte ptr [esi+3]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+4],cx
    mov al,byte ptr [esi+4]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+6],cx
    mov bl,byte ptr [esi+5]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+8],cx
    mov al,byte ptr [esi+6]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xa],cx
    mov bl,byte ptr [esi+7]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0xc],cx
    mov al,byte ptr [esi+8]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xe],cx
    mov bl,byte ptr [esi+9]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x10],cx
    mov al,byte ptr [esi+0xa]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x12],cx
    mov bl,byte ptr [esi+0xb]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x14],cx
    mov al,byte ptr [esi+0xc]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x16],cx
    mov bl,byte ptr [esi+0xd]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x18],cx
    mov al,byte ptr [esi+0xe]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x1a],cx
    mov bl,byte ptr [esi+0xf]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x1c],cx
    mov al,byte ptr [esi+0x10]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x1e],cx
    mov bl,byte ptr [esi+0x11]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x20],cx
    mov al,byte ptr [esi+0x12]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x22],cx
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x24],cx
    add esi,0x13
    add edi,0x26
    jmp Lmain
  lit20:
    mov al,byte ptr [esi]
    mov bl,byte ptr [esi+1]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi],cx
    mov al,byte ptr [esi+2]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+2],cx
    mov bl,byte ptr [esi+3]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+4],cx
    mov al,byte ptr [esi+4]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+6],cx
    mov bl,byte ptr [esi+5]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+8],cx
    mov al,byte ptr [esi+6]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xa],cx
    mov bl,byte ptr [esi+7]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0xc],cx
    mov al,byte ptr [esi+8]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xe],cx
    mov bl,byte ptr [esi+9]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x10],cx
    mov al,byte ptr [esi+0xa]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x12],cx
    mov bl,byte ptr [esi+0xb]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x14],cx
    mov al,byte ptr [esi+0xc]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x16],cx
    mov bl,byte ptr [esi+0xd]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x18],cx
    mov al,byte ptr [esi+0xe]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x1a],cx
    mov bl,byte ptr [esi+0xf]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x1c],cx
    mov al,byte ptr [esi+0x10]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x1e],cx
    mov bl,byte ptr [esi+0x11]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x20],cx
    mov al,byte ptr [esi+0x12]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x22],cx
    mov bl,byte ptr [esi+0x13]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x24],cx
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x26],cx
    add esi,0x14
    add edi,0x28
    jmp Lmain
  lit21:
    mov al,byte ptr [esi]
    mov bl,byte ptr [esi+1]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi],cx
    mov al,byte ptr [esi+2]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+2],cx
    mov bl,byte ptr [esi+3]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+4],cx
    mov al,byte ptr [esi+4]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+6],cx
    mov bl,byte ptr [esi+5]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+8],cx
    mov al,byte ptr [esi+6]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xa],cx
    mov bl,byte ptr [esi+7]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0xc],cx
    mov al,byte ptr [esi+8]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xe],cx
    mov bl,byte ptr [esi+9]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x10],cx
    mov al,byte ptr [esi+0xa]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x12],cx
    mov bl,byte ptr [esi+0xb]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x14],cx
    mov al,byte ptr [esi+0xc]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x16],cx
    mov bl,byte ptr [esi+0xd]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x18],cx
    mov al,byte ptr [esi+0xe]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x1a],cx
    mov bl,byte ptr [esi+0xf]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x1c],cx
    mov al,byte ptr [esi+0x10]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x1e],cx
    mov bl,byte ptr [esi+0x11]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x20],cx
    mov al,byte ptr [esi+0x12]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x22],cx
    mov bl,byte ptr [esi+0x13]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x24],cx
    mov al,byte ptr [esi+0x14]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x26],cx
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x28],cx
    add esi,0x15
    add edi,0x2a
    jmp Lmain
  lit22:
    mov al,byte ptr [esi]
    mov bl,byte ptr [esi+1]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi],cx
    mov al,byte ptr [esi+2]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+2],cx
    mov bl,byte ptr [esi+3]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+4],cx
    mov al,byte ptr [esi+4]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+6],cx
    mov bl,byte ptr [esi+5]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+8],cx
    mov al,byte ptr [esi+6]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xa],cx
    mov bl,byte ptr [esi+7]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0xc],cx
    mov al,byte ptr [esi+8]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xe],cx
    mov bl,byte ptr [esi+9]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x10],cx
    mov al,byte ptr [esi+0xa]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x12],cx
    mov bl,byte ptr [esi+0xb]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x14],cx
    mov al,byte ptr [esi+0xc]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x16],cx
    mov bl,byte ptr [esi+0xd]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x18],cx
    mov al,byte ptr [esi+0xe]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x1a],cx
    mov bl,byte ptr [esi+0xf]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x1c],cx
    mov al,byte ptr [esi+0x10]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x1e],cx
    mov bl,byte ptr [esi+0x11]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x20],cx
    mov al,byte ptr [esi+0x12]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x22],cx
    mov bl,byte ptr [esi+0x13]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x24],cx
    mov al,byte ptr [esi+0x14]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x26],cx
    mov bl,byte ptr [esi+0x15]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x28],cx
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x2a],cx
    add esi,0x16
    add edi,0x2c
    jmp Lmain
  lit23:
    mov al,byte ptr [esi]
    mov bl,byte ptr [esi+1]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi],cx
    mov al,byte ptr [esi+2]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+2],cx
    mov bl,byte ptr [esi+3]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+4],cx
    mov al,byte ptr [esi+4]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+6],cx
    mov bl,byte ptr [esi+5]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+8],cx
    mov al,byte ptr [esi+6]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xa],cx
    mov bl,byte ptr [esi+7]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0xc],cx
    mov al,byte ptr [esi+8]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xe],cx
    mov bl,byte ptr [esi+9]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x10],cx
    mov al,byte ptr [esi+0xa]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x12],cx
    mov bl,byte ptr [esi+0xb]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x14],cx
    mov al,byte ptr [esi+0xc]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x16],cx
    mov bl,byte ptr [esi+0xd]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x18],cx
    mov al,byte ptr [esi+0xe]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x1a],cx
    mov bl,byte ptr [esi+0xf]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x1c],cx
    mov al,byte ptr [esi+0x10]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x1e],cx
    mov bl,byte ptr [esi+0x11]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x20],cx
    mov al,byte ptr [esi+0x12]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x22],cx
    mov bl,byte ptr [esi+0x13]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x24],cx
    mov al,byte ptr [esi+0x14]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x26],cx
    mov bl,byte ptr [esi+0x15]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x28],cx
    mov al,byte ptr [esi+0x16]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x2a],cx
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x2c],cx
    add esi,0x17
    add edi,0x2e
    jmp Lmain
  lit24:
    mov al,byte ptr [esi]
    mov bl,byte ptr [esi+1]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi],cx
    mov al,byte ptr [esi+2]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+2],cx
    mov bl,byte ptr [esi+3]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+4],cx
    mov al,byte ptr [esi+4]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+6],cx
    mov bl,byte ptr [esi+5]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+8],cx
    mov al,byte ptr [esi+6]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xa],cx
    mov bl,byte ptr [esi+7]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0xc],cx
    mov al,byte ptr [esi+8]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xe],cx
    mov bl,byte ptr [esi+9]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x10],cx
    mov al,byte ptr [esi+0xa]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x12],cx
    mov bl,byte ptr [esi+0xb]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x14],cx
    mov al,byte ptr [esi+0xc]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x16],cx
    mov bl,byte ptr [esi+0xd]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x18],cx
    mov al,byte ptr [esi+0xe]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x1a],cx
    mov bl,byte ptr [esi+0xf]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x1c],cx
    mov al,byte ptr [esi+0x10]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x1e],cx
    mov bl,byte ptr [esi+0x11]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x20],cx
    mov al,byte ptr [esi+0x12]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x22],cx
    mov bl,byte ptr [esi+0x13]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x24],cx
    mov al,byte ptr [esi+0x14]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x26],cx
    mov bl,byte ptr [esi+0x15]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x28],cx
    mov al,byte ptr [esi+0x16]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x2a],cx
    mov bl,byte ptr [esi+0x17]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x2c],cx
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x2e],cx
    add esi,0x18
    add edi,0x30
    jmp Lmain
  lit25:
    mov al,byte ptr [esi]
    mov bl,byte ptr [esi+1]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi],cx
    mov al,byte ptr [esi+2]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+2],cx
    mov bl,byte ptr [esi+3]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+4],cx
    mov al,byte ptr [esi+4]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+6],cx
    mov bl,byte ptr [esi+5]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+8],cx
    mov al,byte ptr [esi+6]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xa],cx
    mov bl,byte ptr [esi+7]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0xc],cx
    mov al,byte ptr [esi+8]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xe],cx
    mov bl,byte ptr [esi+9]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x10],cx
    mov al,byte ptr [esi+0xa]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x12],cx
    mov bl,byte ptr [esi+0xb]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x14],cx
    mov al,byte ptr [esi+0xc]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x16],cx
    mov bl,byte ptr [esi+0xd]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x18],cx
    mov al,byte ptr [esi+0xe]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x1a],cx
    mov bl,byte ptr [esi+0xf]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x1c],cx
    mov al,byte ptr [esi+0x10]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x1e],cx
    mov bl,byte ptr [esi+0x11]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x20],cx
    mov al,byte ptr [esi+0x12]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x22],cx
    mov bl,byte ptr [esi+0x13]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x24],cx
    mov al,byte ptr [esi+0x14]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x26],cx
    mov bl,byte ptr [esi+0x15]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x28],cx
    mov al,byte ptr [esi+0x16]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x2a],cx
    mov bl,byte ptr [esi+0x17]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x2c],cx
    mov al,byte ptr [esi+0x18]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x2e],cx
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x30],cx
    add esi,0x19
    add edi,0x32
    jmp Lmain
  lit26:
    mov al,byte ptr [esi]
    mov bl,byte ptr [esi+1]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi],cx
    mov al,byte ptr [esi+2]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+2],cx
    mov bl,byte ptr [esi+3]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+4],cx
    mov al,byte ptr [esi+4]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+6],cx
    mov bl,byte ptr [esi+5]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+8],cx
    mov al,byte ptr [esi+6]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xa],cx
    mov bl,byte ptr [esi+7]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0xc],cx
    mov al,byte ptr [esi+8]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xe],cx
    mov bl,byte ptr [esi+9]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x10],cx
    mov al,byte ptr [esi+0xa]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x12],cx
    mov bl,byte ptr [esi+0xb]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x14],cx
    mov al,byte ptr [esi+0xc]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x16],cx
    mov bl,byte ptr [esi+0xd]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x18],cx
    mov al,byte ptr [esi+0xe]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x1a],cx
    mov bl,byte ptr [esi+0xf]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x1c],cx
    mov al,byte ptr [esi+0x10]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x1e],cx
    mov bl,byte ptr [esi+0x11]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x20],cx
    mov al,byte ptr [esi+0x12]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x22],cx
    mov bl,byte ptr [esi+0x13]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x24],cx
    mov al,byte ptr [esi+0x14]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x26],cx
    mov bl,byte ptr [esi+0x15]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x28],cx
    mov al,byte ptr [esi+0x16]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x2a],cx
    mov bl,byte ptr [esi+0x17]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x2c],cx
    mov al,byte ptr [esi+0x18]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x2e],cx
    mov bl,byte ptr [esi+0x19]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x30],cx
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x32],cx
    add esi,0x1a
    add edi,0x34
    jmp Lmain
  lit27:
    mov al,byte ptr [esi]
    mov bl,byte ptr [esi+1]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi],cx
    mov al,byte ptr [esi+2]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+2],cx
    mov bl,byte ptr [esi+3]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+4],cx
    mov al,byte ptr [esi+4]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+6],cx
    mov bl,byte ptr [esi+5]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+8],cx
    mov al,byte ptr [esi+6]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xa],cx
    mov bl,byte ptr [esi+7]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0xc],cx
    mov al,byte ptr [esi+8]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xe],cx
    mov bl,byte ptr [esi+9]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x10],cx
    mov al,byte ptr [esi+0xa]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x12],cx
    mov bl,byte ptr [esi+0xb]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x14],cx
    mov al,byte ptr [esi+0xc]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x16],cx
    mov bl,byte ptr [esi+0xd]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x18],cx
    mov al,byte ptr [esi+0xe]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x1a],cx
    mov bl,byte ptr [esi+0xf]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x1c],cx
    mov al,byte ptr [esi+0x10]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x1e],cx
    mov bl,byte ptr [esi+0x11]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x20],cx
    mov al,byte ptr [esi+0x12]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x22],cx
    mov bl,byte ptr [esi+0x13]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x24],cx
    mov al,byte ptr [esi+0x14]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x26],cx
    mov bl,byte ptr [esi+0x15]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x28],cx
    mov al,byte ptr [esi+0x16]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x2a],cx
    mov bl,byte ptr [esi+0x17]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x2c],cx
    mov al,byte ptr [esi+0x18]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x2e],cx
    mov bl,byte ptr [esi+0x19]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x30],cx
    mov al,byte ptr [esi+0x1a]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x32],cx
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x34],cx
    add esi,0x1b
    add edi,0x36
    jmp Lmain
  lit28:
    mov al,byte ptr [esi]
    mov bl,byte ptr [esi+1]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi],cx
    mov al,byte ptr [esi+2]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+2],cx
    mov bl,byte ptr [esi+3]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+4],cx
    mov al,byte ptr [esi+4]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+6],cx
    mov bl,byte ptr [esi+5]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+8],cx
    mov al,byte ptr [esi+6]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xa],cx
    mov bl,byte ptr [esi+7]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0xc],cx
    mov al,byte ptr [esi+8]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xe],cx
    mov bl,byte ptr [esi+9]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x10],cx
    mov al,byte ptr [esi+0xa]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x12],cx
    mov bl,byte ptr [esi+0xb]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x14],cx
    mov al,byte ptr [esi+0xc]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x16],cx
    mov bl,byte ptr [esi+0xd]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x18],cx
    mov al,byte ptr [esi+0xe]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x1a],cx
    mov bl,byte ptr [esi+0xf]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x1c],cx
    mov al,byte ptr [esi+0x10]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x1e],cx
    mov bl,byte ptr [esi+0x11]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x20],cx
    mov al,byte ptr [esi+0x12]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x22],cx
    mov bl,byte ptr [esi+0x13]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x24],cx
    mov al,byte ptr [esi+0x14]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x26],cx
    mov bl,byte ptr [esi+0x15]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x28],cx
    mov al,byte ptr [esi+0x16]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x2a],cx
    mov bl,byte ptr [esi+0x17]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x2c],cx
    mov al,byte ptr [esi+0x18]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x2e],cx
    mov bl,byte ptr [esi+0x19]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x30],cx
    mov al,byte ptr [esi+0x1a]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x32],cx
    mov bl,byte ptr [esi+0x1b]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x34],cx
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x36],cx
    add esi,0x1c
    add edi,0x38
    jmp Lmain
  lit29:
    mov al,byte ptr [esi]
    mov bl,byte ptr [esi+1]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi],cx
    mov al,byte ptr [esi+2]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+2],cx
    mov bl,byte ptr [esi+3]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+4],cx
    mov al,byte ptr [esi+4]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+6],cx
    mov bl,byte ptr [esi+5]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+8],cx
    mov al,byte ptr [esi+6]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xa],cx
    mov bl,byte ptr [esi+7]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0xc],cx
    mov al,byte ptr [esi+8]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xe],cx
    mov bl,byte ptr [esi+9]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x10],cx
    mov al,byte ptr [esi+0xa]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x12],cx
    mov bl,byte ptr [esi+0xb]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x14],cx
    mov al,byte ptr [esi+0xc]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x16],cx
    mov bl,byte ptr [esi+0xd]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x18],cx
    mov al,byte ptr [esi+0xe]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x1a],cx
    mov bl,byte ptr [esi+0xf]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x1c],cx
    mov al,byte ptr [esi+0x10]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x1e],cx
    mov bl,byte ptr [esi+0x11]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x20],cx
    mov al,byte ptr [esi+0x12]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x22],cx
    mov bl,byte ptr [esi+0x13]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x24],cx
    mov al,byte ptr [esi+0x14]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x26],cx
    mov bl,byte ptr [esi+0x15]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x28],cx
    mov al,byte ptr [esi+0x16]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x2a],cx
    mov bl,byte ptr [esi+0x17]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x2c],cx
    mov al,byte ptr [esi+0x18]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x2e],cx
    mov bl,byte ptr [esi+0x19]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x30],cx
    mov al,byte ptr [esi+0x1a]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x32],cx
    mov bl,byte ptr [esi+0x1b]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x34],cx
    mov al,byte ptr [esi+0x1c]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x36],cx
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x38],cx
    add esi,0x1d
    add edi,0x3a
    jmp Lmain
  lit30:
    mov al,byte ptr [esi]
    mov bl,byte ptr [esi+1]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi],cx
    mov al,byte ptr [esi+2]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+2],cx
    mov bl,byte ptr [esi+3]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+4],cx
    mov al,byte ptr [esi+4]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+6],cx
    mov bl,byte ptr [esi+5]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+8],cx
    mov al,byte ptr [esi+6]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xa],cx
    mov bl,byte ptr [esi+7]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0xc],cx
    mov al,byte ptr [esi+8]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xe],cx
    mov bl,byte ptr [esi+9]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x10],cx
    mov al,byte ptr [esi+0xa]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x12],cx
    mov bl,byte ptr [esi+0xb]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x14],cx
    mov al,byte ptr [esi+0xc]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x16],cx
    mov bl,byte ptr [esi+0xd]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x18],cx
    mov al,byte ptr [esi+0xe]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x1a],cx
    mov bl,byte ptr [esi+0xf]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x1c],cx
    mov al,byte ptr [esi+0x10]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x1e],cx
    mov bl,byte ptr [esi+0x11]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x20],cx
    mov al,byte ptr [esi+0x12]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x22],cx
    mov bl,byte ptr [esi+0x13]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x24],cx
    mov al,byte ptr [esi+0x14]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x26],cx
    mov bl,byte ptr [esi+0x15]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x28],cx
    mov al,byte ptr [esi+0x16]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x2a],cx
    mov bl,byte ptr [esi+0x17]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x2c],cx
    mov al,byte ptr [esi+0x18]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x2e],cx
    mov bl,byte ptr [esi+0x19]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x30],cx
    mov al,byte ptr [esi+0x1a]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x32],cx
    mov bl,byte ptr [esi+0x1b]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x34],cx
    mov al,byte ptr [esi+0x1c]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x36],cx
    mov bl,byte ptr [esi+0x1d]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x38],cx
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x3a],cx
    add esi,0x1e
    add edi,0x3c
    jmp Lmain
  lit31:
    mov al,byte ptr [esi]
    mov bl,byte ptr [esi+1]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi],cx
    mov al,byte ptr [esi+2]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+2],cx
    mov bl,byte ptr [esi+3]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+4],cx
    mov al,byte ptr [esi+4]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+6],cx
    mov bl,byte ptr [esi+5]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+8],cx
    mov al,byte ptr [esi+6]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xa],cx
    mov bl,byte ptr [esi+7]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0xc],cx
    mov al,byte ptr [esi+8]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xe],cx
    mov bl,byte ptr [esi+9]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x10],cx
    mov al,byte ptr [esi+0xa]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x12],cx
    mov bl,byte ptr [esi+0xb]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x14],cx
    mov al,byte ptr [esi+0xc]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x16],cx
    mov bl,byte ptr [esi+0xd]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x18],cx
    mov al,byte ptr [esi+0xe]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x1a],cx
    mov bl,byte ptr [esi+0xf]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x1c],cx
    mov al,byte ptr [esi+0x10]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x1e],cx
    mov bl,byte ptr [esi+0x11]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x20],cx
    mov al,byte ptr [esi+0x12]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x22],cx
    mov bl,byte ptr [esi+0x13]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x24],cx
    mov al,byte ptr [esi+0x14]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x26],cx
    mov bl,byte ptr [esi+0x15]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x28],cx
    mov al,byte ptr [esi+0x16]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x2a],cx
    mov bl,byte ptr [esi+0x17]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x2c],cx
    mov al,byte ptr [esi+0x18]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x2e],cx
    mov bl,byte ptr [esi+0x19]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x30],cx
    mov al,byte ptr [esi+0x1a]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x32],cx
    mov bl,byte ptr [esi+0x1b]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x34],cx
    mov al,byte ptr [esi+0x1c]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x36],cx
    mov bl,byte ptr [esi+0x1d]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x38],cx
    mov al,byte ptr [esi+0x1e]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x3a],cx
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x3c],cx
    add esi,0x1f
    add edi,0x3e
    jmp Lmain
  lit32:
    mov al,byte ptr [esi]
    mov bl,byte ptr [esi+1]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi],cx
    mov al,byte ptr [esi+2]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+2],cx
    mov bl,byte ptr [esi+3]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+4],cx
    mov al,byte ptr [esi+4]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+6],cx
    mov bl,byte ptr [esi+5]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+8],cx
    mov al,byte ptr [esi+6]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xa],cx
    mov bl,byte ptr [esi+7]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0xc],cx
    mov al,byte ptr [esi+8]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0xe],cx
    mov bl,byte ptr [esi+9]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x10],cx
    mov al,byte ptr [esi+0xa]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x12],cx
    mov bl,byte ptr [esi+0xb]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x14],cx
    mov al,byte ptr [esi+0xc]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x16],cx
    mov bl,byte ptr [esi+0xd]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x18],cx
    mov al,byte ptr [esi+0xe]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x1a],cx
    mov bl,byte ptr [esi+0xf]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x1c],cx
    mov al,byte ptr [esi+0x10]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x1e],cx
    mov bl,byte ptr [esi+0x11]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x20],cx
    mov al,byte ptr [esi+0x12]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x22],cx
    mov bl,byte ptr [esi+0x13]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x24],cx
    mov al,byte ptr [esi+0x14]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x26],cx
    mov bl,byte ptr [esi+0x15]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x28],cx
    mov al,byte ptr [esi+0x16]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x2a],cx
    mov bl,byte ptr [esi+0x17]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x2c],cx
    mov al,byte ptr [esi+0x18]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x2e],cx
    mov bl,byte ptr [esi+0x19]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x30],cx
    mov al,byte ptr [esi+0x1a]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x32],cx
    mov bl,byte ptr [esi+0x1b]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x34],cx
    mov al,byte ptr [esi+0x1c]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x36],cx
    mov bl,byte ptr [esi+0x1d]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x38],cx
    mov al,byte ptr [esi+0x1e]
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x3a],cx
    mov bl,byte ptr [esi+0x1f]
    mov cx,word ptr [edx+eax*2]
    mov word ptr [edi+0x3c],cx
    mov cx,word ptr [edx+ebx*2]
    mov word ptr [edi+0x3e],cx
    add esi,0x20
    add edi,0x40
    jmp Lmain
  fill1:
    mov word ptr [edi],ax
    add edi,2
    jmp Lmain
  fill2:
    mov dword ptr [edi],eax
    add edi,4
    jmp Lmain
  fill3:
    mov dword ptr [edi],eax
    mov word ptr [edi+4],ax
    add edi,6
    jmp Lmain
  fill4:
    mov dword ptr [edi],eax
    mov dword ptr [edi+4],eax
    add edi,8
    jmp Lmain
  fill5:
    mov dword ptr [edi],eax
    mov dword ptr [edi+4],eax
    mov word ptr [edi+8],ax
    add edi,0xa
    jmp Lmain
  fill6:
    mov dword ptr [edi],eax
    mov dword ptr [edi+4],eax
    mov dword ptr [edi+8],eax
    add edi,0xc
    jmp Lmain
  fill7:
    mov dword ptr [edi],eax
    mov dword ptr [edi+4],eax
    mov dword ptr [edi+8],eax
    mov word ptr [edi+0xc],ax
    add edi,0xe
    jmp Lmain
  fill8:
    mov dword ptr [edi],eax
    mov dword ptr [edi+4],eax
    mov dword ptr [edi+8],eax
    mov dword ptr [edi+0xc],eax
    add edi,0x10
    jmp Lmain
  fill9:
    mov dword ptr [edi],eax
    mov dword ptr [edi+4],eax
    mov dword ptr [edi+8],eax
    mov dword ptr [edi+0xc],eax
    mov word ptr [edi+0x10],ax
    add edi,0x12
    jmp Lmain
  fill10:
    mov dword ptr [edi],eax
    mov dword ptr [edi+4],eax
    mov dword ptr [edi+8],eax
    mov dword ptr [edi+0xc],eax
    mov dword ptr [edi+0x10],eax
    add edi,0x14
    jmp Lmain
  fill11:
    mov dword ptr [edi],eax
    mov dword ptr [edi+4],eax
    mov dword ptr [edi+8],eax
    mov dword ptr [edi+0xc],eax
    mov dword ptr [edi+0x10],eax
    mov word ptr [edi+0x14],ax
    add edi,0x16
    jmp Lmain
  fill12:
    mov dword ptr [edi],eax
    mov dword ptr [edi+4],eax
    mov dword ptr [edi+8],eax
    mov dword ptr [edi+0xc],eax
    mov dword ptr [edi+0x10],eax
    mov dword ptr [edi+0x14],eax
    add edi,0x18
    jmp Lmain
  fill13:
    mov dword ptr [edi],eax
    mov dword ptr [edi+4],eax
    mov dword ptr [edi+8],eax
    mov dword ptr [edi+0xc],eax
    mov dword ptr [edi+0x10],eax
    mov dword ptr [edi+0x14],eax
    mov word ptr [edi+0x18],ax
    add edi,0x1a
    jmp Lmain
  fill14:
    mov dword ptr [edi],eax
    mov dword ptr [edi+4],eax
    mov dword ptr [edi+8],eax
    mov dword ptr [edi+0xc],eax
    mov dword ptr [edi+0x10],eax
    mov dword ptr [edi+0x14],eax
    mov dword ptr [edi+0x18],eax
    add edi,0x1c
    jmp Lmain
  fill15:
    mov dword ptr [edi],eax
    mov dword ptr [edi+4],eax
    mov dword ptr [edi+8],eax
    mov dword ptr [edi+0xc],eax
    mov dword ptr [edi+0x10],eax
    mov dword ptr [edi+0x14],eax
    mov dword ptr [edi+0x18],eax
    mov word ptr [edi+0x1c],ax
    add edi,0x1e
    jmp Lmain
  fill16:
    mov dword ptr [edi],eax
    mov dword ptr [edi+4],eax
    mov dword ptr [edi+8],eax
    mov dword ptr [edi+0xc],eax
    mov dword ptr [edi+0x10],eax
    mov dword ptr [edi+0x14],eax
    mov dword ptr [edi+0x18],eax
    mov dword ptr [edi+0x1c],eax
    add edi,0x20
    jmp Lmain
  fill17:
    mov dword ptr [edi],eax
    mov dword ptr [edi+4],eax
    mov dword ptr [edi+8],eax
    mov dword ptr [edi+0xc],eax
    mov dword ptr [edi+0x10],eax
    mov dword ptr [edi+0x14],eax
    mov dword ptr [edi+0x18],eax
    mov dword ptr [edi+0x1c],eax
    mov word ptr [edi+0x20],ax
    add edi,0x22
    jmp Lmain
  fill18:
    mov dword ptr [edi],eax
    mov dword ptr [edi+4],eax
    mov dword ptr [edi+8],eax
    mov dword ptr [edi+0xc],eax
    mov dword ptr [edi+0x10],eax
    mov dword ptr [edi+0x14],eax
    mov dword ptr [edi+0x18],eax
    mov dword ptr [edi+0x1c],eax
    mov dword ptr [edi+0x20],eax
    add edi,0x24
    jmp Lmain
  fill19:
    mov dword ptr [edi],eax
    mov dword ptr [edi+4],eax
    mov dword ptr [edi+8],eax
    mov dword ptr [edi+0xc],eax
    mov dword ptr [edi+0x10],eax
    mov dword ptr [edi+0x14],eax
    mov dword ptr [edi+0x18],eax
    mov dword ptr [edi+0x1c],eax
    mov dword ptr [edi+0x20],eax
    mov word ptr [edi+0x24],ax
    add edi,0x26
    jmp Lmain
  fill20:
    mov dword ptr [edi],eax
    mov dword ptr [edi+4],eax
    mov dword ptr [edi+8],eax
    mov dword ptr [edi+0xc],eax
    mov dword ptr [edi+0x10],eax
    mov dword ptr [edi+0x14],eax
    mov dword ptr [edi+0x18],eax
    mov dword ptr [edi+0x1c],eax
    mov dword ptr [edi+0x20],eax
    mov dword ptr [edi+0x24],eax
    add edi,0x28
    jmp Lmain
  fill21:
    mov dword ptr [edi],eax
    mov dword ptr [edi+4],eax
    mov dword ptr [edi+8],eax
    mov dword ptr [edi+0xc],eax
    mov dword ptr [edi+0x10],eax
    mov dword ptr [edi+0x14],eax
    mov dword ptr [edi+0x18],eax
    mov dword ptr [edi+0x1c],eax
    mov dword ptr [edi+0x20],eax
    mov dword ptr [edi+0x24],eax
    mov word ptr [edi+0x28],ax
    add edi,0x2a
    jmp Lmain
  fill22:
    mov dword ptr [edi],eax
    mov dword ptr [edi+4],eax
    mov dword ptr [edi+8],eax
    mov dword ptr [edi+0xc],eax
    mov dword ptr [edi+0x10],eax
    mov dword ptr [edi+0x14],eax
    mov dword ptr [edi+0x18],eax
    mov dword ptr [edi+0x1c],eax
    mov dword ptr [edi+0x20],eax
    mov dword ptr [edi+0x24],eax
    mov dword ptr [edi+0x28],eax
    add edi,0x2c
    jmp Lmain
  fill23:
    mov dword ptr [edi],eax
    mov dword ptr [edi+4],eax
    mov dword ptr [edi+8],eax
    mov dword ptr [edi+0xc],eax
    mov dword ptr [edi+0x10],eax
    mov dword ptr [edi+0x14],eax
    mov dword ptr [edi+0x18],eax
    mov dword ptr [edi+0x1c],eax
    mov dword ptr [edi+0x20],eax
    mov dword ptr [edi+0x24],eax
    mov dword ptr [edi+0x28],eax
    mov word ptr [edi+0x2c],ax
    add edi,0x2e
    jmp Lmain
  fill24:
    mov dword ptr [edi],eax
    mov dword ptr [edi+4],eax
    mov dword ptr [edi+8],eax
    mov dword ptr [edi+0xc],eax
    mov dword ptr [edi+0x10],eax
    mov dword ptr [edi+0x14],eax
    mov dword ptr [edi+0x18],eax
    mov dword ptr [edi+0x1c],eax
    mov dword ptr [edi+0x20],eax
    mov dword ptr [edi+0x24],eax
    mov dword ptr [edi+0x28],eax
    mov dword ptr [edi+0x2c],eax
    add edi,0x30
    jmp Lmain
  fill25:
    mov dword ptr [edi],eax
    mov dword ptr [edi+4],eax
    mov dword ptr [edi+8],eax
    mov dword ptr [edi+0xc],eax
    mov dword ptr [edi+0x10],eax
    mov dword ptr [edi+0x14],eax
    mov dword ptr [edi+0x18],eax
    mov dword ptr [edi+0x1c],eax
    mov dword ptr [edi+0x20],eax
    mov dword ptr [edi+0x24],eax
    mov dword ptr [edi+0x28],eax
    mov dword ptr [edi+0x2c],eax
    mov word ptr [edi+0x30],ax
    add edi,0x32
    jmp Lmain
  fill26:
    mov dword ptr [edi],eax
    mov dword ptr [edi+4],eax
    mov dword ptr [edi+8],eax
    mov dword ptr [edi+0xc],eax
    mov dword ptr [edi+0x10],eax
    mov dword ptr [edi+0x14],eax
    mov dword ptr [edi+0x18],eax
    mov dword ptr [edi+0x1c],eax
    mov dword ptr [edi+0x20],eax
    mov dword ptr [edi+0x24],eax
    mov dword ptr [edi+0x28],eax
    mov dword ptr [edi+0x2c],eax
    mov dword ptr [edi+0x30],eax
    add edi,0x34
    jmp Lmain
  fill27:
    mov dword ptr [edi],eax
    mov dword ptr [edi+4],eax
    mov dword ptr [edi+8],eax
    mov dword ptr [edi+0xc],eax
    mov dword ptr [edi+0x10],eax
    mov dword ptr [edi+0x14],eax
    mov dword ptr [edi+0x18],eax
    mov dword ptr [edi+0x1c],eax
    mov dword ptr [edi+0x20],eax
    mov dword ptr [edi+0x24],eax
    mov dword ptr [edi+0x28],eax
    mov dword ptr [edi+0x2c],eax
    mov dword ptr [edi+0x30],eax
    mov word ptr [edi+0x34],ax
    add edi,0x36
    jmp Lmain
  fill28:
    mov dword ptr [edi],eax
    mov dword ptr [edi+4],eax
    mov dword ptr [edi+8],eax
    mov dword ptr [edi+0xc],eax
    mov dword ptr [edi+0x10],eax
    mov dword ptr [edi+0x14],eax
    mov dword ptr [edi+0x18],eax
    mov dword ptr [edi+0x1c],eax
    mov dword ptr [edi+0x20],eax
    mov dword ptr [edi+0x24],eax
    mov dword ptr [edi+0x28],eax
    mov dword ptr [edi+0x2c],eax
    mov dword ptr [edi+0x30],eax
    mov dword ptr [edi+0x34],eax
    add edi,0x38
    jmp Lmain
  fill29:
    mov dword ptr [edi],eax
    mov dword ptr [edi+4],eax
    mov dword ptr [edi+8],eax
    mov dword ptr [edi+0xc],eax
    mov dword ptr [edi+0x10],eax
    mov dword ptr [edi+0x14],eax
    mov dword ptr [edi+0x18],eax
    mov dword ptr [edi+0x1c],eax
    mov dword ptr [edi+0x20],eax
    mov dword ptr [edi+0x24],eax
    mov dword ptr [edi+0x28],eax
    mov dword ptr [edi+0x2c],eax
    mov dword ptr [edi+0x30],eax
    mov dword ptr [edi+0x34],eax
    mov word ptr [edi+0x38],ax
    add edi,0x3a
    jmp Lmain
  fill30:
    mov dword ptr [edi],eax
    mov dword ptr [edi+4],eax
    mov dword ptr [edi+8],eax
    mov dword ptr [edi+0xc],eax
    mov dword ptr [edi+0x10],eax
    mov dword ptr [edi+0x14],eax
    mov dword ptr [edi+0x18],eax
    mov dword ptr [edi+0x1c],eax
    mov dword ptr [edi+0x20],eax
    mov dword ptr [edi+0x24],eax
    mov dword ptr [edi+0x28],eax
    mov dword ptr [edi+0x2c],eax
    mov dword ptr [edi+0x30],eax
    mov dword ptr [edi+0x34],eax
    mov dword ptr [edi+0x38],eax
    add edi,0x3c
    jmp Lmain
  fill31:
    mov dword ptr [edi],eax
    mov dword ptr [edi+4],eax
    mov dword ptr [edi+8],eax
    mov dword ptr [edi+0xc],eax
    mov dword ptr [edi+0x10],eax
    mov dword ptr [edi+0x14],eax
    mov dword ptr [edi+0x18],eax
    mov dword ptr [edi+0x1c],eax
    mov dword ptr [edi+0x20],eax
    mov dword ptr [edi+0x24],eax
    mov dword ptr [edi+0x28],eax
    mov dword ptr [edi+0x2c],eax
    mov dword ptr [edi+0x30],eax
    mov dword ptr [edi+0x34],eax
    mov dword ptr [edi+0x38],eax
    mov word ptr [edi+0x3c],ax
    add edi,0x3e
    jmp Lmain
  fill32:
    mov dword ptr [edi],eax
    mov dword ptr [edi+4],eax
    mov dword ptr [edi+8],eax
    mov dword ptr [edi+0xc],eax
    mov dword ptr [edi+0x10],eax
    mov dword ptr [edi+0x14],eax
    mov dword ptr [edi+0x18],eax
    mov dword ptr [edi+0x1c],eax
    mov dword ptr [edi+0x20],eax
    mov dword ptr [edi+0x24],eax
    mov dword ptr [edi+0x28],eax
    mov dword ptr [edi+0x2c],eax
    mov dword ptr [edi+0x30],eax
    mov dword ptr [edi+0x34],eax
    mov dword ptr [edi+0x38],eax
    mov dword ptr [edi+0x3c],eax
    add edi,0x40
    jmp Lmain
  Linit:
    mov edi,dword ptr [ebp-0xc]
    mov eax,offset fill1
    mov dword ptr [edi],eax
    mov eax,offset fill2
    mov dword ptr [edi+4],eax
    mov eax,offset fill3
    mov dword ptr [edi+8],eax
    mov eax,offset fill4
    mov dword ptr [edi+0xc],eax
    mov eax,offset fill5
    mov dword ptr [edi+0x10],eax
    mov eax,offset fill6
    mov dword ptr [edi+0x14],eax
    mov eax,offset fill7
    mov dword ptr [edi+0x18],eax
    mov eax,offset fill8
    mov dword ptr [edi+0x1c],eax
    mov eax,offset fill9
    mov dword ptr [edi+0x20],eax
    mov eax,offset fill10
    mov dword ptr [edi+0x24],eax
    mov eax,offset fill11
    mov dword ptr [edi+0x28],eax
    mov eax,offset fill12
    mov dword ptr [edi+0x2c],eax
    mov eax,offset fill13
    mov dword ptr [edi+0x30],eax
    mov eax,offset fill14
    mov dword ptr [edi+0x34],eax
    mov eax,offset fill15
    mov dword ptr [edi+0x38],eax
    mov eax,offset fill16
    mov dword ptr [edi+0x3c],eax
    mov eax,offset fill17
    mov dword ptr [edi+0x40],eax
    mov eax,offset fill18
    mov dword ptr [edi+0x44],eax
    mov eax,offset fill19
    mov dword ptr [edi+0x48],eax
    mov eax,offset fill20
    mov dword ptr [edi+0x4c],eax
    mov eax,offset fill21
    mov dword ptr [edi+0x50],eax
    mov eax,offset fill22
    mov dword ptr [edi+0x54],eax
    mov eax,offset fill23
    mov dword ptr [edi+0x58],eax
    mov eax,offset fill24
    mov dword ptr [edi+0x5c],eax
    mov eax,offset fill25
    mov dword ptr [edi+0x60],eax
    mov eax,offset fill26
    mov dword ptr [edi+0x64],eax
    mov eax,offset fill27
    mov dword ptr [edi+0x68],eax
    mov eax,offset fill28
    mov dword ptr [edi+0x6c],eax
    mov eax,offset fill29
    mov dword ptr [edi+0x70],eax
    mov eax,offset fill30
    mov dword ptr [edi+0x74],eax
    mov eax,offset fill31
    mov dword ptr [edi+0x78],eax
    mov eax,offset fill32
    mov dword ptr [edi+0x7c],eax
    mov edi,dword ptr [ebp-0x18]
    mov eax,offset lit1
    mov dword ptr [edi],eax
    mov eax,offset lit2
    mov dword ptr [edi+4],eax
    mov eax,offset lit3
    mov dword ptr [edi+8],eax
    mov eax,offset lit4
    mov dword ptr [edi+0xc],eax
    mov eax,offset lit5
    mov dword ptr [edi+0x10],eax
    mov eax,offset lit6
    mov dword ptr [edi+0x14],eax
    mov eax,offset lit7
    mov dword ptr [edi+0x18],eax
    mov eax,offset lit8
    mov dword ptr [edi+0x1c],eax
    mov eax,offset lit9
    mov dword ptr [edi+0x20],eax
    mov eax,offset lit10
    mov dword ptr [edi+0x24],eax
    mov eax,offset lit11
    mov dword ptr [edi+0x28],eax
    mov eax,offset lit12
    mov dword ptr [edi+0x2c],eax
    mov eax,offset lit13
    mov dword ptr [edi+0x30],eax
    mov eax,offset lit14
    mov dword ptr [edi+0x34],eax
    mov eax,offset lit15
    mov dword ptr [edi+0x38],eax
    mov eax,offset lit16
    mov dword ptr [edi+0x3c],eax
    mov eax,offset lit17
    mov dword ptr [edi+0x40],eax
    mov eax,offset lit18
    mov dword ptr [edi+0x44],eax
    mov eax,offset lit19
    mov dword ptr [edi+0x48],eax
    mov eax,offset lit20
    mov dword ptr [edi+0x4c],eax
    mov eax,offset lit21
    mov dword ptr [edi+0x50],eax
    mov eax,offset lit22
    mov dword ptr [edi+0x54],eax
    mov eax,offset lit23
    mov dword ptr [edi+0x58],eax
    mov eax,offset lit24
    mov dword ptr [edi+0x5c],eax
    mov eax,offset lit25
    mov dword ptr [edi+0x60],eax
    mov eax,offset lit26
    mov dword ptr [edi+0x64],eax
    mov eax,offset lit27
    mov dword ptr [edi+0x68],eax
    mov eax,offset lit28
    mov dword ptr [edi+0x6c],eax
    mov eax,offset lit29
    mov dword ptr [edi+0x70],eax
    mov eax,offset lit30
    mov dword ptr [edi+0x74],eax
    mov eax,offset lit31
    mov dword ptr [edi+0x78],eax
    mov eax,offset lit32
    mov dword ptr [edi+0x7c],eax
    jmp L44fd54
  Lc2e:
    jmp Lexit
  Lzoom2:
    mov ecx,dword ptr [ebp+8]
    and ecx,1
    mov dword ptr [ebp-0x24],ecx
    mov edx,dword ptr [DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame]
    mov dword ptr [DAT_TextureRenderCoreObject::instance.currentRenderSurface],edx
    mov dword ptr [ebp-0x1c],0x1fb0
    mov dword ptr [ebp-0x10],0x1fb0
    mov eax,dword ptr [ebp-0x28]
    mov ecx,dword ptr [eax+0x58]
    mov dword ptr [ebp-0x14],ecx
    mov edx,dword ptr [ebp+0xc]
    add edx,dword ptr [ebp+0x14]
    mov eax,dword ptr [ebp-0x28]
    cmp edx,dword ptr [eax+0x5c]
    jle L451c8c
    mov ecx,dword ptr [ebp+0xc]
    add ecx,dword ptr [ebp+0x14]
    mov edx,dword ptr [ebp-0x28]
    sub ecx,dword ptr [edx+0x5c]
    mov eax,dword ptr [ebp+0x14]
    sub eax,ecx
    mov dword ptr [ebp+0x14],eax
    cmp dword ptr [ebp+0x14],0
    jg L451c8c
    jmp Lexit
  L451c8c:
    mov esi,dword ptr [ebp+0x18]
    mov edi,dword ptr [DAT_TextureRenderCoreObject::instance.currentRenderSurface]
    mov eax,dword ptr [ebp+8]
    cmp eax,0
    jl Lexit
    and eax,0xfffffffe
    add edi,eax
    mov eax,dword ptr [ebp+0xc]
    mov ebx,dword ptr [ebp-0x14]
    cmp eax,ebx
    jge L451cfa
    sub ebx,eax
    mov eax,ebx
    cmp dword ptr [ebp+0x14],eax
    jle Lexit
    sub dword ptr [ebp+0x14],eax
  L451cc0:
    mov ecx,0
    mov bl,byte ptr [esi]
    mov cl,byte ptr [esi]
    and bl,0xe0
    and cl,0x1f
    add esi,1
    cmp bl,0x20
    jz L451cc0
    cmp bl,0
    jz L451ce3
    cmp bl,0x40
    jz L451cea
    jmp L451cef
  L451ce3:
    add ecx,1
    add esi,ecx
    jmp L451cc0
  L451cea:
    add esi,1
    jmp L451cc0
  L451cef:
    sub eax,1
    cmp eax,0
    jg L451cc0
    mov eax,dword ptr [ebp-0x14]
  L451cfa:
    mov edx,dword ptr [ebp-0x10]
    mov ecx,eax
    shr eax,1
    mul edx
    add edi,eax
    mov edx,dword ptr [ebp-4]
  L451d08:
    mov ebx,dword ptr [ebp-0x24]
    mov dword ptr [ebp-0x20],ebx
    push edi
  L451d0f:
    mov ecx,0
    mov al,byte ptr [esi]
    mov cl,byte ptr [esi]
    and al,0xe0
    and cl,0x1f
    add esi,1
    cmp al,0x20
    jz L451d7d
    cmp al,0
    jz L451dba
    cmp al,0x40
    jz L451d85
    pop edi
    add edi,dword ptr [ebp-0x1c]
    sub dword ptr [ebp+0x14],1
    cmp dword ptr [ebp+0x14],0
    jle Lexit
  L451d42:
    mov ecx,0
    mov bl,byte ptr [esi]
    mov cl,byte ptr [esi]
    and bl,0xe0
    and cl,0x1f
    add esi,1
    cmp bl,0x20
    jz L451d42
    cmp bl,0
    jz L451d65
    cmp bl,0x40
    jz L451d6c
    jmp L451d71
  L451d65:
    add ecx,1
    add esi,ecx
    jmp L451d42
  L451d6c:
    add esi,1
    jmp L451d42
  L451d71:
    sub dword ptr [ebp+0x14],1
    cmp dword ptr [ebp+0x14],0
    jg L451d08
    jmp Lexit
  L451d7d:
    add ecx,1
    add dword ptr [ebp-0x20],ecx
    jmp L451d0f
  L451d85:
    mov ebx,0
    mov eax,0
    mov bl,byte ptr [esi]
    mov ax,word ptr [edx+ebx*2]
    add esi,1
    add ecx,1
    mov ebx,dword ptr [ebp-0x20]
    add dword ptr [ebp-0x20],ecx
  L451da1:
    test ebx,1
    jnz L451dad
    mov word ptr [edi+ebx],ax
  L451dad:
    add ebx,1
    sub ecx,1
    jnz L451da1
    jmp L451d0f
  L451dba:
    mov eax,0
    add ecx,1
    mov ebx,dword ptr [ebp-0x20]
    add dword ptr [ebp-0x20],ecx
  L451dc8:
    test ebx,1
    jnz L451dde
    mov ax,0
    mov al,byte ptr [esi]
    mov ax,word ptr [edx+eax*2]
    mov word ptr [edi+ebx],ax
  L451dde:
    add esi,1
    add ebx,1
    sub ecx,1
    jnz L451dc8
    jmp L451d0f
  Lexit:
    pop edi
    pop esi
    pop ebx
    mov esp,ebp
    pop ebp
    ret 0x14
            }
        }

    }
}
}
