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

        using Text::TextAlignment;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004937E0
        void OnlineVoteQuitGame::MenuModalRenderFunction_OnlineVoteQuitGame(int x, int y, int width, int height)
        {
            /*
              added by script: "End this game?"
             */
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner, DAT_PencilRenderCore::ptr)(
                0x4c, 0x3b, x, y, width, height);
            DWORD DVar1 = timeGetTime();
            int number = 10 - (DVar1 - DAT_GameSynchronyState::instance.quitGameVoteRequestTime) / 1000;
            if (number < 0) {
                number = 0;
            }
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                number, x + 0x14, y + 0x7d, Text::TTA_LEFT, 0xc2f0eb, 0x12, FALSE, 0);
        }

    }
}
}
