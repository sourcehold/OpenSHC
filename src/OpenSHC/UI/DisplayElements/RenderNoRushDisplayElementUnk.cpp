#include "../DisplayElements.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Rendering/ScreenResolutionEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/COL_DARK_LIME.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace DisplayElements {

        // FUNCTION: STRONGHOLDCRUSADER 0x004B20B0
        void RenderNoRushDisplayElementUnk(int posX, int posY, DWORD elementState)
        {
            if (DAT_GameState::instance.mapAndTime.skirmishNoRushTicks == 0) {
                // Plays pa paam pa pa pa paam
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                    s_battlehorn_wav_005a77d8);
                MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                    OpenSHC::UI::Enums::DEID_NO_RUSH, 0);
                return;
            }
            int const barWidth
                = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(
                      MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                          DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_MISC, 7),
                      18)
                + 50;
            int x = posX + 800;
            DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            // Separate ifs, not an else-if chain (an else-if chain: quick_diff 0.9797 -> 0.9054)
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x768) {
                x += 112;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x1024) {
                x -= 240;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1600x1200) {
                x -= 400;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x720) {
                x -= 240;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1440x900) {
                x -= 320;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1080) {
                x -= 560;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1200) {
                x -= 560;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1440) {
                x -= 880;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1600) {
                x -= 880;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1366x768) {
                x -= 283;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1680x1050) {
                x -= 440;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1600x900) {
                x -= 400;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x600) {
                x -= 112;
            }
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1360x768) {
                x -= 280;
            }
            x -= 18 + barWidth / 2;
            int const left = x - (barWidth / 2);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                DAT_PencilRenderCore::ptr)(left - 7, posY - 5, (barWidth / 2) + 5 + x, posY + 30, 16);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_MISC, 7),
                x, posY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 0, 18, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
                left - 1, posY + 18, (barWidth / 2) + 1 + x, posY + 24, COL_BLACK::instance.shortValue);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                left, posY + 19,
                (DAT_GameState::instance.mapAndTime.skirmishNoRushTicks * barWidth)
                        / DAT_GameState::instance.mapAndTime.skirmishNoRushTicksLeft
                    - (barWidth / 2) + x,
                posY + 23, COL_DARK_LIME::instance.shortValue);
            DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        }

    }
}
}
