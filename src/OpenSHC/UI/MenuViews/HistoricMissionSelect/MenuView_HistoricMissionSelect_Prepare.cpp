#include "../HistoricMissionSelect.func.hpp"

#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00b95b2c.hpp"
#include "OpenSHC/Globals/DAT_00b96100.hpp"
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
        // FUNCTION: STRONGHOLDCRUSADER 0x00426830
        void HistoricMissionSelect::MenuView_HistoricMissionSelect_Prepare()
        {
            DAT_GameCore::instance.currentlyInGameUnk_0xa4 = FALSE;
            DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                DAT_TextureRenderCoreObject::ptr)("frontend_combat2.tgx");
            MACRO_CALL(OpenSHC::UI::Helpers_Func::LoadTGX_shc_back)();
            DAT_GameCore::instance.section1066 = 0;
            DAT_MenuTextInputState::instance.field39_0x90 = 0;
            DAT_MenuTextInputState::instance.field38_0x8c = 0xffffffff;
            if (DAT_GameCore::instance.missionNumber1to20 < 6) {
                DAT_00b95b2c::instance = 0;
                DAT_00b96100::instance = 1;
            }
            if (DAT_GameCore::instance.missionNumber1to20 < 0xb) {
                DAT_00b95b2c::instance = 1;
                DAT_00b96100::instance = 6;
            }
            DAT_00b95b2c::instance = (0xf < DAT_GameCore::instance.missionNumber1to20) + 2;
            DAT_00b96100::instance = DAT_00b95b2c::instance * 5 + 1;
        }

    }
}
}
