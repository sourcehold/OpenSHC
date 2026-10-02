#include "../UnusedEconomicMissionSelect.func.hpp"

#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00426C50
        void UnusedEconomicMissionSelect::MenuView_UnusedEconomicMissionSelect_Prepare()
        {
            DAT_GameCore::instance.currentlyInGameUnk_0xa4 = FALSE;
            DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                DAT_TextureRenderCoreObject::ptr)("frontend_economics2.tgx");
            MACRO_CALL(OpenSHC::UI::Helpers_Func::LoadTGX_shc_back)();
            DAT_GameCore::instance.section1066 = 0;
            DAT_MenuTextInputState::instance.field39_0x90 = 0;
            DAT_GameCore::instance.missionNumber1to20 = 0x21;
            DAT_MenuTextInputState::instance.field38_0x8c = 0xffffffff;
        }

    }
}
}
