#include "../IntroLogos.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_IntroBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_IntroStep.hpp"
#include "OpenSHC/Globals/DAT_IntroTimestamp.hpp"
#include "OpenSHC/Globals/DAT_IntroTransitionStep.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        // FUNCTION: STRONGHOLDCRUSADER 0x004247A0
        void IntroLogos::MenuView_IntroLogos_DoEveryFrame()
        {
            // the two logos, then the online-play notice on black
            if (DAT_IntroStep::instance < 2) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawGfxOnFlaggedSurface,
                    DAT_TextureRenderCoreObject::ptr)(0,
                    (DAT_WindowAndDirectDraw::instance.resolutionX
                        - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].width)
                        / 2,
                    (DAT_WindowAndDirectDraw::instance.resolutionY
                        - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height)
                        / 2);
            } else {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                    DAT_PencilRenderCore::ptr)(0, 0, DAT_WindowAndDirectDraw::instance.resolutionX,
                    DAT_WindowAndDirectDraw::instance.resolutionY, COL_BLACK::instance.shortValue);
                int const y = DAT_WindowAndDirectDraw::instance.resolutionY / 2 - 30;
                int const x = DAT_WindowAndDirectDraw::instance.resolutionX / 2;
                // "Gameplay may change during online play"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAMEPLAY_ONLINE, 0),
                    x, y, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_FFFFFF, 16, FALSE, 0);
            }
            DWORD const currentTime = timeGetTime();
            if (DAT_IntroTransitionStep::instance == 0) {
                // fade in
                DAT_IntroBlendStrength::instance = (int)(currentTime - DAT_IntroTimestamp::instance) / 20;
                if (DAT_IntroBlendStrength::instance >= 32) {
                    DAT_IntroBlendStrength::instance = 32;
                    DAT_IntroTransitionStep::instance = 1;
                    DAT_IntroTimestamp::instance = timeGetTime();
                }
            } else if (DAT_IntroTransitionStep::instance == 1) {
                // hold: 2.5 seconds, the second logo 6
                int duration = 2500;
                if (DAT_IntroStep::instance == 1) {
                    duration = 6000;
                }
                if ((int)(currentTime - DAT_IntroTimestamp::instance) > duration) {
                    DAT_IntroTransitionStep::instance = 2;
                    DAT_IntroTimestamp::instance = timeGetTime();
                }
            } else if (DAT_IntroTransitionStep::instance == 2) {
                // fade out, then the next logo or the intro video
                DAT_IntroBlendStrength::instance = 32 - (int)(currentTime - DAT_IntroTimestamp::instance) / 20;
                if (DAT_IntroBlendStrength::instance <= 0) {
                    if (DAT_IntroStep::instance == 0) {
                        DAT_IntroTransitionStep::instance = 0;
                        DAT_IntroBlendStrength::instance = 0;
                        DAT_IntroStep::instance = 1;
                        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            OpenSHC::UI::Enums::MVT_INTRO_LOGOS, 0);
                    } else if (DAT_IntroStep::instance == 1) {
                        DAT_IntroTransitionStep::instance = 0;
                        DAT_IntroBlendStrength::instance = 0;
                        DAT_IntroStep::instance = 2;
                        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            OpenSHC::UI::Enums::MVT_INTRO_LOGOS, 0);
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            OpenSHC::UI::Enums::MVT_INTRO_VIDEO, 0);
                    }
                }
            }
            if (DAT_IntroBlendStrength::instance >= 32) {
                return;
            }
            // the original calls timeGetTime() here and drops the result
            timeGetTime();
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                DAT_PencilRenderCore::ptr)(0, 0, DAT_WindowAndDirectDraw::instance.resolutionX,
                DAT_WindowAndDirectDraw::instance.resolutionY, DAT_IntroBlendStrength::instance);
        }

    }
}
}
