#include "../Helpers.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00eb0b28.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004DB210
    int Helpers::PrepareHistoryBook()
    {
        int iVar1;
        uint uVar2;
        int* piVar3;
        int* piVar4;
        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
            "sand.tgx");
        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
            "pc0.tgx");
        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
            "pc1.tgx");
        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
            "pc2.tgx");
        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
            "pc3.tgx");
        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
            "pc4.tgx");
        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
            "pc5.tgx");
        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
            "pc6.tgx");
        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
            "pc7.tgx");
        piVar3 = INT_ARRAY_00eb0b28::instance[0] + 1;
        do {
            iVar1 = MACRO_CALL(OS_Func::_rand)();
            (*(int (*)[4])(piVar3 + -1))[0] = iVar1 % 900 << 8;
            iVar1 = MACRO_CALL(OS_Func::_rand)();
            *piVar3 = iVar1 % 600 << 8;
            uVar2 = MACRO_CALL(OS_Func::_rand)();
            uVar2 = (int)uVar2 % 8;
            piVar3[1] = uVar2;
            iVar1 = MACRO_CALL(OS_Func::_rand)();
            piVar4 = piVar3 + 4;
            piVar3[2] = iVar1 % 10 + 10;
            piVar3 = piVar4;
        } while ((int)piVar4 < 0xeb0e2c);
        return iVar1 / 10;
    }

}
}
