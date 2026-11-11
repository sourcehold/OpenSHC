#include "../Unknown26.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Rendering.func.hpp"
#include "OpenSHC/UI/Credits.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_UnknownBinkCount.hpp"
#include "OpenSHC/Globals/DAT_UnknownBinkIndex.hpp"
#include "OpenSHC/Globals/INT_00b95954.hpp"
#include "OpenSHC/Globals/INT_00ed3114.hpp"
#include "OpenSHC/Globals/INT_00ed3144.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace Unknown26 {

            // FUNCTION: STRONGHOLDCRUSADER 0x004E1E70
            void MenuView_Unknown26_CampaignRelatedUnk_DoEveryFrame()
            {
                if (!MACRO_CALL(OpenSHC::UI::Helpers_Func::TicksSinceCounterStart)()) {
                    return;
                }
                if (DAT_MouseState::instance.rightClickStop) {
                    MACRO_CALL(OpenSHC::UI::Credits_Func::StopCreditsPlaybackAndSounds)();
                }
                if (DAT_MouseState::instance.leftClickStart) {
                    MACRO_CALL(OpenSHC::UI::Credits_Func::EndCreditsSegmentAndAdvanceToNext)();
                }
                MACRO_CALL(OpenSHC::Rendering_Func::ProcessCreditsScriptCommands)();
                if (DAT_UnknownBinkIndex::instance < DAT_UnknownBinkCount::instance) {
                    MACRO_CALL(OpenSHC::Rendering_Func::RenderActiveCreditsElements)();
                }
                ++INT_00ed3144::instance;
                if (DAT_UnknownBinkIndex::instance < DAT_UnknownBinkCount::instance) {
                    return;
                }

                // the sequence is over: on to the next view
                // mission 1000: the intro sequence
                if (DAT_GameCore::instance.missionNumber1to20 == 1000) {
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_INTRO_VIDEO, 0);
                    return;
                }
                if (DAT_GameCore::instance.section1066 == 2) {
                    // past mission 21 first (<= 21 first: quick_diff 0.9057 -> 0.8113)
                    if (DAT_GameCore::instance.missionNumber1to20 > 21) {
                        if (INT_00ed3114::instance != 0) {
                            MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                OpenSHC::UI::Enums::MVT_UNKNOWN_27_CAMPAIGNUnk, 0);
                            return;
                        }
                        // the end credits (switchToMenuView then plays music 38 instead of 15)
                        INT_00b95954::instance = 1;
                        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            OpenSHC::UI::Enums::MVT_CREDITS, 0);
                        return;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_UNKNOWN_27_CAMPAIGNUnk, 0);
                    DAT_GameCore::instance.section1066 = 0;
                    return;
                }
                if (DAT_GameCore::instance.missionNumber1to20 == 1) {
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_UNKNOWN_27_CAMPAIGNUnk, 0);
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_SCENARIO_DESCRIPTION, 0);
            }

        }
    }
}
}
