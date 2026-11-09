#include "../UnusedEconomicGametypeSelect.func.hpp"

#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UIButtonDefinedData.hpp"
#include "OpenSHC/Globals/INT_00b95abc.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        // FUNCTION: STRONGHOLDCRUSADER 0x004259D0
        void UnusedEconomicGametypeSelect::MenuView_UnusedEconomicGametypeSelect_Prepare()
        {
            DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                DAT_TextureRenderCoreObject::ptr)(s_frontend_economics_tgx_005a2054);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                DAT_TextureRenderCoreObject::ptr)(s_frontend_economics2_tgx_005a203c);
            MACRO_CALL(OpenSHC::UI::Helpers_Func::LoadTGX_shc_back)();
            DWORD const now = timeGetTime();
            for (int i = 0; i < 3; ++i) {
                DAT_UIButtonDefinedData::instance.ButtonGmDataArray[360 + i].stateTransitionTimeBaseUnk_0x18
                    = now - (3 - i) * 1600;
            }
            INT_00b95abc::instance = -1;
            DAT_GameCore::instance.isTimeHalted2 = 0;
        }

    }
}
}
