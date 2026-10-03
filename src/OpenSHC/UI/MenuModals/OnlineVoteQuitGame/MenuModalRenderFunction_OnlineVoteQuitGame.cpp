#include "../OnlineVoteQuitGame.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004937E0
        void OnlineVoteQuitGame::MenuModalRenderFunction_OnlineVoteQuitGame(int x, int y, int width, int height)
        {
            DWORD DVar1;
            int number;
            /*
              added by script: "End this game?"
             */
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                DAT_PencilRenderCore::ptr)(0x4c, 0x3b, x, y, width, height);
            DVar1 = timeGetTime();
            number = 10 - (DVar1 - DAT_GameSynchronyState::instance.quitGameVoteRequestTime) / 1000;
            if (number < 0) {
                number = 0;
            }
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                number, x + 0x14, y + 0x7d, OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0x12, FALSE, 0);
        }

    }
}
}
