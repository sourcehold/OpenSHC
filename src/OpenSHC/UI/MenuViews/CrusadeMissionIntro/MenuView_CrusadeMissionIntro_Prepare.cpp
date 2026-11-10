#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuViews/CrusadeMissionIntro.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_MissionDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/INT_00eb9ae8.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace CrusadeMissionIntro {

            // FUNCTION: STRONGHOLDCRUSADER 0x004D8AB0
            void MenuView_CrusadeMissionIntro_Prepare()
            {
                DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                // "skirmish_background.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_skirmish_background_tgx_005aaf8c);
                MACRO_CALL(OpenSHC::UI::Helpers_Func::LoadTGX_shc_back)();
                INT_00eb9ae8::instance = 0;
                DAT_MissionDefinedData::instance.field_0xaf8 = true;
            }

        }
    }
}
}
