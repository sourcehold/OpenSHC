#include "../HistoricMissionSelect.func.hpp"

#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_00b95b2c.hpp"
#include "OpenSHC/Globals/DAT_00b96100.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        // FUNCTION: STRONGHOLDCRUSADER 0x00426830
        void HistoricMissionSelect::MenuView_HistoricMissionSelect_Prepare()
        {
            DAT_GameCore::instance.currentlyInGameUnk_0xa4 = FALSE;
            DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                s_frontend_combat2_tgx_005a2010);
            MACRO_CALL(UI::Helpers_Func::LoadTGX_shc_back)();
            DAT_GameCore::instance.section1066 = 0;
            DAT_MenuTextInputState::instance.lastListClickTime = 0;
            DAT_MenuTextInputState::instance.lastClickedListIndex = 0xffffffff;
            int iVar1;
            if (DAT_GameCore::instance.missionNumber1to20 < 6) {
                iVar1 = 0;
            } else if (DAT_GameCore::instance.missionNumber1to20 < 11) {
                iVar1 = 1;
            } else if (DAT_GameCore::instance.missionNumber1to20 < 16) {
                iVar1 = 2;
            } else {
                iVar1 = 3;
            }
            DAT_00b95b2c::instance = iVar1;
            DAT_00b96100::instance = iVar1 * 5 + 1;
        }

    }
}
}
