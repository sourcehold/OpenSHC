#include "../DisplayElements.func.hpp"

#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Rendering/ScreenResolutionEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

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

    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Rendering::ScreenResolutionEnum;
    using OpenSHC::Rendering::Enums::RenderTarget;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::UI::Enums::DisplayElementID;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004B2280
    void DisplayElements::RenderTimeUntilDefeatDisplayElement(int posX, int posY, DWORD elementState)
    {
        char* _textAddr;
        BOOLEnum _stateNotZero;
        int iVar1;
        int iVar2;
        int iVar3;
        int left;
        int iVar4;
        TextAlignment alignment;
        uint foregroundColor;
        uint backgroundColor;
        int iVar5;
        int blendStrength;
        int iVar6;
        int local_c;
        if (DAT_GameCore::instance.section1095 == 2) {
            MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                OpenSHC::UI::Enums::DEID_TIME_UNTIL_DEFEAT, 0);
            return;
        }
        iVar6 = 0x12;
        /*
          "Time Until Defeat"   added by script: "Time Until Defeat"
         */
        iVar6 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_OBJECTIVES, 0x11),
            iVar6);
        if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x768) {
            posX = posX + -0x70;
        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x1024) {
            posX = posX + -0xf0;
        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1600x1200) {
            posX = posX + -400;
        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x720) {
            posX = posX + -0xf0;
        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1440x900) {
            posX = posX + -0x140;
        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1080) {
            posX = posX + -0x230;
        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1200) {
            posX = posX + -0x230;
        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1440) {
            posX = posX + -0x370;
        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1600) {
            posX = posX + -0x370;
        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1366x768) {
            posX = posX + -0x11b;
        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1680x1050) {
            posX = posX + -0x1b8;
        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1600x900) {
            posX = posX + -400;
        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x600) {
            posX = posX + -0x70;
        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1360x768) {
            posX = posX + -0x118;
        }
        iVar2 = iVar6 / 2;
        iVar3 = posX + 10 + iVar2;
        _stateNotZero = MACRO_CALL(OpenSHC::UI::DisplayElements_Func::GetIfDisplayElementStateNotZero)(
            OpenSHC::UI::Enums::DEID_TIME_UNTIL_VICTORY);
        if (_stateNotZero != FALSE) {
            iVar3 = iVar3 + DAT_00df4290::instance;
        }
        left = iVar3 - iVar2;
        DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
            DAT_PencilRenderCore::ptr)(left + -7, posY + -5, iVar2 + 5 + iVar3, posY + 0x1e, 0x10);
        blendStrength = 0;
        _stateNotZero = FALSE;
        iVar5 = 0x12;
        backgroundColor = 0;
        foregroundColor = 0xc2f0eb;
        alignment = OpenSHC::Text::TTA_CENTER;
        iVar4 = iVar3;
        iVar1 = posY;
        /*
          "Time Until Defeat"   added by script: "Time Until Defeat"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_OBJECTIVES, 0x11),
            iVar4, iVar1, alignment, foregroundColor, backgroundColor, iVar5, _stateNotZero, blendStrength);
        iVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::MapPropertiesState_Func::getEventIDForTimeUntilDefeatEventType,
            DAT_MapPropertiesState::ptr)();
        iVar4 = DAT_MapPropertiesState::instance.SEC_StartingMonth
            + DAT_MapPropertiesState::instance.SEC_StartingYear * 0xc;
        iVar5 = (DAT_GameState::instance.mapAndTime.year * 0xc - iVar4) + DAT_GameState::instance.mapAndTime.month;
        iVar4 = ((DAT_MapPropertiesState::instance.scenarioEvents[iVar1].header.month
                     + DAT_MapPropertiesState::instance.scenarioEvents[iVar1].header.year * 0xc)
                    - iVar4)
            * 800;
        if (DAT_GameCore::instance.isTimeHalted == FALSE) {
            _stateNotZero = MACRO_CALL(OpenSHC::UI::DisplayElements_Func::GetIfDisplayElementStateNotZero)(
                OpenSHC::UI::Enums::DEID_KEEP_AND_GRANERY_PLACEMENT_INFO);
            if (_stateNotZero == FALSE) {
                local_c = ((iVar4 + DAT_GameState::instance.mapAndTime.week * -200)
                              - DAT_GameState::instance.gameTicksLoadBalancer)
                    + iVar5 * -800;
                goto LAB_004b24b1;
            }
        }
        local_c = iVar4 + iVar5 * -800;
    LAB_004b24b1:
        if (local_c < 0) {
            local_c = 0;
        }
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
            left + -1, posY + 0x12, iVar2 + 1 + iVar3, posY + 0x18, (ushort)((int)(COL_BLACK::instance.shortValue)));
        if (local_c != iVar4) {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                left, posY + 0x13, (((iVar4 - local_c) * iVar6) / iVar4 - iVar2) + iVar3, posY + 0x17,
                (ushort)((int)(COL_DARK_LIME::instance.shortValue)));
        }
        DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
    }

}
}
