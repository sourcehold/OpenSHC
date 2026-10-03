#include "../MinimapViewState.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Rendering/ColorMode.hpp"

#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Rendering::ColorMode;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004B61F0
    int MinimapViewState::generateMinimapImage()
    {
        void* _Src;
        int iVar1;
        uint uVar2;
        int iVar3;
        int iVar4;
        short (*pasVar5)[200];
        ushort* puVar6;
        MinimapViewState* local_20c;
        uint local_208;
        ushort local_204[256];
        uint local_4;
        local_4 = MSVC_SecurityCookie::instance ^ (uint)&local_20c;
        local_20c = this;
        iVar4 = 0;
        _Src = MACRO_CALL(OpenSHC::OS_Func::_malloc)(40000);
        local_208
            = (-(uint)(DAT_WindowAndDirectDraw::instance.colorBitMode != OpenSHC::Rendering::RGB_565) & 0x440) + 0xf79e
            & 0xffff;
        iVar3 = 0;
        pasVar5 = this->loadedMiniMap;
        do {
            uVar2 = (ushort)(*pasVar5)[0] & local_208;
            iVar1 = 0;
            if (0 < iVar4) {
                do {
                    if (uVar2 == local_204[iVar1]) {
                        *(char*)(iVar3 + (int)_Src) = (char)iVar1;
                        goto LAB_004b6281;
                    }
                    iVar1 = iVar1 + 1;
                } while (iVar1 < iVar4);
            }
            if (iVar4 < 0x100) {
                local_204[iVar4] = (ushort)uVar2;
                *(char*)(iVar3 + (int)_Src) = (char)iVar4;
                iVar4 = iVar4 + 1;
            } else {
                *(undefined1*)(iVar3 + (int)_Src) = 0;
            }
        LAB_004b6281:
            iVar3 = iVar3 + 1;
            pasVar5 = (short (*)[200])(*pasVar5 + 1);
            if (39999 < iVar3) {
                if ((DAT_WindowAndDirectDraw::instance.colorBitMode == OpenSHC::Rendering::RGB_565)
                    && (iVar3 = 0, 0 < iVar4)) {
                    do {
                        local_204[iVar3]
                            = (ushort)((int)(uint)local_204[iVar3] >> 1) & 0x7fe0 | local_204[iVar3] & 0x1f;
                        iVar3 = iVar3 + 1;
                    } while (iVar3 < iVar4);
                }
                puVar6 = local_204;
                pasVar5 = local_20c->loadedMiniMap;
                for (iVar3 = 0x80; iVar3 != 0; iVar3 = iVar3 + -1) {
                    *(undefined4*)*pasVar5 = *(undefined4*)puVar6;
                    puVar6 = puVar6 + 2;
                    pasVar5 = (short (*)[200])(*pasVar5 + 2);
                }
                MACRO_CALL(OpenSHC::OS_Func::_memcpy)(local_20c->loadedMiniMap[1] + 0x38, _Src, 40000);
                MACRO_CALL(OpenSHC::OS_Func::_free_base)(_Src);
                iVar3 = 40512;
                ;
                return iVar3;
            }
        } while (true);
    }

}
}
