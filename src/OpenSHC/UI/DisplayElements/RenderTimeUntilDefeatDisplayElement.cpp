#include "../DisplayElements.func.hpp"

#include "OpenSHC/Map/MapPropertiesState.func.hpp"
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
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace DisplayElements {

        // FUNCTION: STRONGHOLDCRUSADER 0x004B2280
        void RenderTimeUntilDefeatDisplayElement(int posX, int posY, DWORD elementState)
        {
            if (DAT_GameCore::instance.section1095 == 2) {
                MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                    OpenSHC::UI::Enums::DEID_TIME_UNTIL_DEFEAT, 0);
                return;
            }
            // "Time Until Defeat"
            int const barWidth
                = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_OBJECTIVES, 17),
                    18);
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
            // posX becomes the bar's centre (a centre local: reccmp 100.0% -> 98.5%)
            posX += 10 + halfWidth;
            // Drawn right of the victory timer's bar when both are shown
            if (MACRO_CALL(OpenSHC::UI::DisplayElements_Func::GetIfDisplayElementStateNotZero)(
                    OpenSHC::UI::Enums::DEID_TIME_UNTIL_VICTORY)) {
                posX += DAT_00df4290::instance;
            }
            DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            // The bar's left edge is written out at each use (a left local: reccmp 100.0% -> 91.1%)
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                DAT_PencilRenderCore::ptr)(posX - halfWidth - 7, posY - 5, halfWidth + 5 + posX, posY + 30, 16);
            // "Time Until Defeat"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_OBJECTIVES, 17),
                posX, posY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 0, 18, FALSE, 0);
            int const eventID
                = MACRO_CALL_MEMBER(OpenSHC::Map::MapPropertiesState_Func::getEventIDForTimeUntilDefeatEventType,
                    DAT_MapPropertiesState::ptr)();
            int const startMonths = DAT_MapPropertiesState::instance.SEC_StartingMonth
                + DAT_MapPropertiesState::instance.SEC_StartingYear * 12;
            // A month is 800 ticks (4 weeks of 200)
            int const deadlineTicks
                = (DAT_MapPropertiesState::instance.scenarioEvents[eventID].header.month
                      + DAT_MapPropertiesState::instance.scenarioEvents[eventID].header.year * 12 - startMonths)
                * 800;
            int const elapsedMonthTicks = (DAT_GameState::instance.mapAndTime.year * 12 - startMonths
                                              + DAT_GameState::instance.mapAndTime.month)
                * 800;
            // While time is halted, or the keep placement hint is up, only whole months count
            int ticksLeft;
            if (!DAT_GameCore::instance.isTimeHalted
                && !MACRO_CALL(OpenSHC::UI::DisplayElements_Func::GetIfDisplayElementStateNotZero)(
                    OpenSHC::UI::Enums::DEID_KEEP_AND_GRANERY_PLACEMENT_INFO)) {
                ticksLeft = deadlineTicks - DAT_GameState::instance.mapAndTime.week * 200
                    - DAT_GameState::instance.gameTicksLoadBalancer - elapsedMonthTicks;
            } else {
                ticksLeft = deadlineTicks - elapsedMonthTicks;
            }
            if (ticksLeft < 0) {
                ticksLeft = 0;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
                posX - halfWidth - 1, posY + 18, halfWidth + 1 + posX, posY + 24, COL_BLACK::instance.shortValue);
            if (ticksLeft != deadlineTicks) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                    DAT_PencilRenderCore::ptr)(posX - halfWidth, posY + 19,
                    ((deadlineTicks - ticksLeft) * barWidth) / deadlineTicks - halfWidth + posX, posY + 23,
                    COL_DARK_LIME::instance.shortValue);
            }
            DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        }

    }
}
}
