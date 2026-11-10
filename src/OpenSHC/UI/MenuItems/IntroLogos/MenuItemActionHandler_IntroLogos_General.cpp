#include "../IntroLogos.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/BOOLEnum_00b98404.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_IntroBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_IntroStep.hpp"
#include "OpenSHC/Globals/DAT_IntroTimestamp.hpp"
#include "OpenSHC/Globals/DAT_IntroTransitionStep.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x00424990
        void IntroLogos::MenuItemActionHandler_IntroLogos_General(int unused, ...)
        {
            if (DAT_MouseState::instance.leftClickStart) {
                BOOLEnum_00b98404::instance = TRUE;
                return;
            }
            // a click (press, then release) skips to the next logo, and after the second one to the video
            if (!DAT_MouseState::instance.draggingStopped || !BOOLEnum_00b98404::instance) {
                return;
            }
            BOOLEnum_00b98404::instance = FALSE;
            if (DAT_IntroStep::instance == 0) {
                DAT_IntroTransitionStep::instance = 0;
                DAT_IntroBlendStrength::instance = 0;
                DAT_IntroStep::instance = 1;
                DAT_IntroTimestamp::instance = timeGetTime();
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_INTRO_LOGOS, 0);
                return;
            }
            if (DAT_IntroStep::instance == 1) {
                DAT_IntroTransitionStep::instance = 0;
                DAT_IntroBlendStrength::instance = 0;
                DAT_IntroStep::instance = 2;
                DAT_IntroTimestamp::instance = timeGetTime();
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_INTRO_LOGOS, 0);
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                OpenSHC::UI::Enums::MVT_INTRO_VIDEO, 0);
        }

    }
}
}
