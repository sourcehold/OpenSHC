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
    // FUNCTION: STRONGHOLDCRUSADER 0x004B6320
    void MinimapViewState::convertLoadedMinimapColors()
    {
        short* psVar1;
        int iVar2;
        byte* pbVar3;
        short (*pasVar4)[200];
        ushort* puVar5;
        void* local_214;
        ushort local_210[258];
        uint local_c;
        local_c = MSVC_SecurityCookie::instance ^ (uint)&local_214;
        local_214 = MACRO_CALL(OpenSHC::OS_Func::_malloc)(40000);
        pasVar4 = this->loadedMiniMap;
        puVar5 = local_210;
        for (iVar2 = 0x80; iVar2 != 0; iVar2 = iVar2 + -1) {
            *(undefined4*)puVar5 = *(undefined4*)*pasVar4;
            pasVar4 = (short (*)[200])(*pasVar4 + 2);
            puVar5 = puVar5 + 2;
        }
        MACRO_CALL(OpenSHC::OS_Func::_memcpy)(local_214, (void*)((int)(this->loadedMiniMap[1] + 0x38)), 40000);
        if (DAT_WindowAndDirectDraw::instance.colorBitMode == OpenSHC::Rendering::RGB_565) {
            iVar2 = 0;
            do {
                local_210[iVar2] = (local_210[iVar2] & 0xffe0) * 2 | local_210[iVar2] & 0x1f;
                iVar2 = iVar2 + 1;
            } while (iVar2 < 0x100);
        }
        pbVar3 = (byte*)((int)local_214 + 1);
        psVar1 = this->loadedMiniMap[0] + 1;
        iVar2 = 8000;
        do {
            (*(short (*)[200])(psVar1 + -1))[0] = local_210[pbVar3[-1]];
            *psVar1 = local_210[*pbVar3];
            psVar1[1] = local_210[pbVar3[1]];
            psVar1[2] = local_210[pbVar3[2]];
            psVar1[3] = local_210[pbVar3[3]];
            psVar1 = psVar1 + 5;
            pbVar3 = pbVar3 + 5;
            iVar2 = iVar2 + -1;
        } while (iVar2 != 0);
        MACRO_CALL(OpenSHC::OS_Func::_free_base)(local_214);
        ;
    }

}
}
