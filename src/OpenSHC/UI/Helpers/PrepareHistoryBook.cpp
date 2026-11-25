#include "../Helpers.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00eb0b28.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004DB210
    void Helpers::PrepareHistoryBook()
    {
        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
        // "sand.tgx"
        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
            s_sand_tgx_005ab080);
        // "pc0.tgx"
        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
            s_pc0_tgx_005ab078);
        // "pc1.tgx"
        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
            s_pc1_tgx_005ab070);
        // "pc2.tgx"
        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
            s_pc2_tgx_005ab068);
        // "pc3.tgx"
        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
            s_pc3_tgx_005ab060);
        // "pc4.tgx"
        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
            s_pc4_tgx_005ab058);
        // "pc5.tgx"
        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
            s_pc5_tgx_005ab050);
        // "pc6.tgx"
        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
            s_pc6_tgx_005ab048);
        // "pc7.tgx"
        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
            s_pc7_tgx_005ab040);
        for (int particle = 0; particle < 48; ++particle) {
            INT_ARRAY_00eb0b28::instance[particle][0] = (MACRO_CALL(OS_Func::_rand)() % 900) << 8;
            INT_ARRAY_00eb0b28::instance[particle][1] = (MACRO_CALL(OS_Func::_rand)() % 600) << 8;
            INT_ARRAY_00eb0b28::instance[particle][2] = MACRO_CALL(OS_Func::_rand)() % 8;
            INT_ARRAY_00eb0b28::instance[particle][3] = MACRO_CALL(OS_Func::_rand)() % 10 + 10;
        }
    }

}
}
