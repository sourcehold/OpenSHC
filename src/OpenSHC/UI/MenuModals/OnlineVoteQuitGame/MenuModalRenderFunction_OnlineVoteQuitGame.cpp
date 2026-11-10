#include "../OnlineVoteQuitGame.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        // FUNCTION: STRONGHOLDCRUSADER 0x004937E0
        void OnlineVoteQuitGame::MenuModalRenderFunction_OnlineVoteQuitGame(int x, int y, int width, int height)
        {
            // "End this game?"
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                DAT_PencilRenderCore::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 59, x, y, width, height);
            int secondsLeft = 10 - (timeGetTime() - DAT_GameSynchronyState::instance.quitGameVoteRequestTime) / 1000;
            if (secondsLeft < 0) {
                secondsLeft = 0;
            }
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                secondsLeft, x + 20, y + 125, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 18,
                FALSE, 0);
        }

    }
}
}
