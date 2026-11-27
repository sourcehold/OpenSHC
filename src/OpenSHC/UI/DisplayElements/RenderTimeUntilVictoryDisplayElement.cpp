#include "../DisplayElements.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Rendering/ScreenResolutionEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/COL_DARK_LIME.hpp"
#include "OpenSHC/Globals/DAT_00df4290.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace DisplayElements {

        // FUNCTION: STRONGHOLDCRUSADER 0x004B1EB0
        void RenderTimeUntilVictoryDisplayElement(int posX, int posY, DWORD elementState)
        {
            if (DAT_GameCore::instance.section1095 == 2) {
                MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                    OpenSHC::UI::Enums::DEID_TIME_UNTIL_VICTORY, 0);
                return;
            }
            // "Time Until Victory"
            int const barWidth
                = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_OBJECTIVES, 25),
                    18);
            DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            // Centred for an 800-pixel-wide layout: shifted left by (width - 800) / 2
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x768) {
                posX -= 112;
            } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x1024) {
                posX -= 240;
            } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1600x1200) {
                posX -= 400;
            } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x720) {
                posX -= 240;
            } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1440x900) {
                posX -= 320;
            } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1080) {
                posX -= 560;
            } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1200) {
                posX -= 560;
            } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1440) {
                posX -= 880;
            } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1600) {
                posX -= 880;
            } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1366x768) {
                posX -= 283;
            } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1680x1050) {
                posX -= 440;
            } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1600x900) {
                posX -= 400;
            } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x600) {
                posX -= 112;
            } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1360x768) {
                posX -= 280;
            }
            int const halfWidth = barWidth / 2;
            // Read by RenderTimeUntilDefeatDisplayElement, which draws its bar to the right of this one
            DAT_00df4290::instance = barWidth + 16;
            // posX becomes the bar's centre (a centre local: quick_diff 0.9810 -> 0.9620)
            posX += 10 + halfWidth;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                DAT_PencilRenderCore::ptr)(posX - halfWidth - 7, posY - 5, halfWidth + 5 + posX, posY + 30, 16);
            // "Time Until Victory"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_OBJECTIVES, 25),
                posX, posY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 0, 18, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
                posX - halfWidth - 1, posY + 18, halfWidth + 1 + posX, posY + 24, COL_BLACK::instance.shortValue);
            if (DAT_MapPropertiesState::instance.SEC_Section1080 != DAT_MapPropertiesState::instance.SEC_Section1090) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                    DAT_PencilRenderCore::ptr)(posX - halfWidth, posY + 19,
                    ((DAT_MapPropertiesState::instance.SEC_Section1090
                         - DAT_MapPropertiesState::instance.SEC_Section1080)
                        * barWidth)
                            / DAT_MapPropertiesState::instance.SEC_Section1090
                        - halfWidth + posX,
                    posY + 23, COL_DARK_LIME::instance.shortValue);
            }
            DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        }

    }
}
}
